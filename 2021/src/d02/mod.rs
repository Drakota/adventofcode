fn parse_input(input: &str) -> Vec<String> {
    input.lines().map(|s| s.to_owned()).collect()
}

enum Direction {
    Forward,
    Up,
    Down,
}

impl TryFrom<&str> for Direction {
    type Error = ();

    fn try_from(value: &str) -> Result<Self, Self::Error> {
        match value {
            "forward" => Ok(Direction::Forward),
            "up" => Ok(Direction::Up),
            "down" => Ok(Direction::Down),
            _ => unreachable!(),
        }
    }
}

#[derive(Debug, Default)]
struct Point {
    pub x: isize,
    pub y: isize,
}

fn split_instructions(input: Vec<String>, mut handle: impl FnMut(Direction, isize)) {
    for line in input {
        let (direction, depth) = line
            .split_once(" ")
            .map(|(a, b)| (a.try_into().unwrap(), b.parse::<isize>().unwrap()))
            .unwrap();

        handle(direction, depth);
    }
}

fn part1(input: &str) -> isize {
    let input = parse_input(input);
    let mut position = Point::default();

    split_instructions(input, |direction, depth| match direction {
        Direction::Forward => position.x += depth,
        Direction::Up => position.y -= depth,
        Direction::Down => position.y += depth,
    });

    position.x * position.y
}

fn part2(input: &str) -> isize {
    let input = parse_input(input);
    let mut position = Point::default();
    let mut aim = 0;

    split_instructions(input, |direction, depth| match direction {
        Direction::Forward => {
            position.x += depth;
            position.y += aim * depth;
        }
        Direction::Up => aim -= depth,
        Direction::Down => aim += depth,
    });

    position.x * position.y
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d02() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 2322630);
        assert_eq!(part2(input), 2105273490);
    }
}
