use std::collections::VecDeque;

fn parse_input(input: &str) -> Cavern {
    Cavern::new(
        input
            .lines()
            .map(|l| {
                l.chars()
                    .map(|c| Octopus {
                        value: c.to_digit(10).unwrap(),
                        flashed: false,
                    })
                    .collect()
            })
            .collect(),
    )
}

#[derive(Debug)]
struct Octopus {
    value: u32,
    flashed: bool,
}

#[derive(Debug)]
struct Cavern {
    octopuses: Vec<Vec<Octopus>>,
    total_flashes: u32,
}

impl Cavern {
    fn new(octopuses: Vec<Vec<Octopus>>) -> Self {
        Self {
            octopuses,
            total_flashes: 0,
        }
    }

    fn width(&self) -> usize {
        self.octopuses[0].len()
    }

    fn height(&self) -> usize {
        self.octopuses.len()
    }

    fn step(&mut self) {
        let mut queue: VecDeque<(usize, usize)> = VecDeque::new();

        for y in 0..self.height() {
            for x in 0..self.width() {
                self.octopuses[y][x].flashed = false;
                self.octopuses[y][x].value += 1;

                if self.octopuses[y][x].value > 9 {
                    self.total_flashes += 1;
                    self.octopuses[y][x].value = 0;
                    self.octopuses[y][x].flashed = true;
                    queue.push_back((x, y));
                }
            }
        }

        while let Some((x, y)) = queue.pop_front() {
            for (dx, dy) in [
                (-1, 0),
                (1, 0),
                (0, -1),
                (0, 1),
                (1, 1),
                (-1, 1),
                (1, -1),
                (-1, -1),
            ] {
                let (nx, ny) = ((x as isize + dx) as usize, (y as isize + dy) as usize);

                if nx < self.width() && ny < self.height() && !self.octopuses[ny][nx].flashed {
                    let neighbor = &mut self.octopuses[ny][nx];

                    neighbor.value += 1;
                    if neighbor.value > 9 {
                        self.total_flashes += 1;
                        neighbor.value = 0;
                        neighbor.flashed = true;
                        queue.push_back((nx as usize, ny as usize));
                    }
                }
            }
        }
    }
}

fn part1(input: &str) -> u32 {
    let mut cave = parse_input(input);

    for _step in 1..=100 {
        cave.step();
    }

    cave.total_flashes
}

fn part2(input: &str) -> u32 {
    let mut cave = parse_input(input);

    for step in 1.. {
        cave.step();

        if cave
            .octopuses
            .iter()
            .flatten()
            .filter(|o| o.flashed)
            .count()
            == cave.width() * cave.height()
        {
            return step;
        }
    }

    unreachable!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d11() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 1562);
        assert_eq!(part2(input), 268);
    }

    #[test]
    fn example() {
        let input = "5483143223
2745854711
5264556173
6141336146
6357385478
4167524645
2176841721
6882881134
4846848554
5283751526";

        assert_eq!(part1(input), 1656);
        assert_eq!(part2(input), 195);
    }
}
