fn parse_input(input: &str) -> (Vec<u32>, Vec<Board>) {
    let (draw, input) = input.split_once("\n\n").unwrap();

    let draw: Vec<u32> = draw
        .split(',')
        .map(str::parse)
        .map(Result::unwrap)
        .collect();
    let boards: Vec<Board> = input
        .split("\n\n")
        .map(Board::try_from)
        .map(Result::unwrap)
        .collect();

    (draw, boards)
}

trait Markable {
    fn mark(&mut self, number: u32);
}

#[derive(Debug, Clone)]
struct Board(Vec<Vec<(u32, bool)>>);

impl Board {
    fn won(&self) -> bool {
        let row = self
            .0
            .iter()
            .map(|r| r.iter().map(|c| c.1 as u32).sum())
            .any(|r: u32| r == 5);

        let col = (0..5)
            .map(|j| (0..5).map(|i| self.0[i][j].1 as u32).collect())
            .map(|c: Vec<u32>| c.iter().sum())
            .any(|c: u32| c == 5);

        row || col
    }
}

impl TryFrom<&str> for Board {
    type Error = ();

    fn try_from(value: &str) -> Result<Self, Self::Error> {
        let grid = value
            .lines()
            .map(|s| {
                s.split_whitespace()
                    .map(str::parse)
                    .map(Result::unwrap)
                    .map(|v| (v, false))
                    .collect()
            })
            .collect();

        Ok(Self(grid))
    }
}

impl From<Board> for u32 {
    fn from(board: Board) -> Self {
        board.0.into_iter().fold(0, |mut acc, r| {
            acc += r
                .into_iter()
                .map(|(v, m)| if !m { v } else { 0 })
                .sum::<u32>();
            acc
        })
    }
}

impl Markable for Board {
    fn mark(&mut self, number: u32) {
        for row in &mut self.0 {
            for col in row {
                if col.0 == number {
                    col.1 = true;
                }
            }
        }
    }
}

impl Markable for Vec<Board> {
    fn mark(&mut self, number: u32) {
        for board in self {
            board.mark(number);
        }
    }
}

fn solve(input: &str) -> (u32, u32) {
    let (draw, mut boards) = parse_input(input);
    let mut winners: Vec<(Board, u32)> = Vec::new();

    for number in draw.into_iter() {
        boards.mark(number);

        let partition: (Vec<_>, Vec<_>) = boards.into_iter().partition(|b| b.won());
        boards = partition.1;

        winners.extend(partition.0.into_iter().map(|b| (b, number)));
    }

    let first = winners.first().unwrap().clone();
    let last = winners.last().unwrap().clone();

    ((u32::from(first.0) * first.1), (u32::from(last.0) * last.1))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d04() {
        let input = include_str!("./input/data.txt");
        let (part1, part2) = solve(input);

        assert_eq!(part1, 72770);
        assert_eq!(part2, 13912);
    }
}
