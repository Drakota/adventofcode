use cached::proc_macro::cached;
use itertools::Itertools;
use std::cmp::max;

fn parse_input(input: &str) -> Vec<Player> {
    input
        .lines()
        .map(|l| l.split_once(": ").unwrap().1)
        .map(|p| Player::new(p.parse().unwrap()))
        .collect_vec()
}

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
struct Player {
    position: u32,
    score: u32,
}

impl Player {
    fn new(starting_position: u32) -> Self {
        Self {
            position: starting_position,
            score: 0,
        }
    }

    fn walk(&mut self, step: u32) {
        self.position = (self.position + step - 1) % 10 + 1;
        self.score += self.position;
    }
}

struct Dice {
    iter: Box<dyn Iterator<Item = u32>>,
    rolls: u32,
}

impl Dice {
    fn new(sides: u32) -> Self {
        Self {
            iter: Box::new((1..=sides).into_iter().cycle()),
            rolls: 0,
        }
    }

    fn roll(&mut self, times: u32) -> u32 {
        self.rolls += times;
        self.iter.as_mut().take(times as usize).sum()
    }
}

#[cached]
fn quantum_game(p1_position: u32, p1_score: u32, p2_position: u32, p2_score: u32) -> (u64, u64) {
    [(3, 1), (4, 3), (5, 6), (6, 7), (7, 6), (8, 3), (9, 1)]
        .into_iter()
        .fold((0, 0), |(p1_wins, p2_wins), (step, times)| {
            let p1_position = (p1_position + step - 1) % 10 + 1;
            let p1_score = p1_score + p1_position;

            if p1_score >= 21 {
                (p1_wins + times, p2_wins)
            } else {
                let (nested_p2_wins, nested_p1_wins) =
                    quantum_game(p2_position, p2_score, p1_position, p1_score);
                (
                    p1_wins + nested_p1_wins * times,
                    p2_wins + nested_p2_wins * times,
                )
            }
        })
}

fn part1(input: &str) -> u32 {
    let mut players = parse_input(input);
    let mut dice = Dice::new(100);

    'outer: loop {
        for player in players.iter_mut() {
            let step = dice.roll(3);
            player.walk(step);
            if player.score >= 1000 {
                break 'outer;
            }
        }
    }

    players.into_iter().map(|p| p.score).min().unwrap() * dice.rolls
}

fn part2(input: &str) -> u64 {
    let players = parse_input(input);

    let (player1_wins, player2_wins) = quantum_game(players[0].position, 0, players[1].position, 0);

    max(player1_wins, player2_wins)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d21() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 551901);
        assert_eq!(part2(input), 272847859601291);
    }

    #[test]
    fn example() {
        let input = "Player 1 starting position: 4
Player 2 starting position: 8";

        assert_eq!(part1(input), 739785);
        assert_eq!(part2(input), 444356092776315);
    }
}
