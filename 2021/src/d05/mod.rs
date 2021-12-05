use std::{
    collections::HashMap,
    hash::Hash,
    ops::{Add, AddAssign},
};

fn parse_input(input: &str) -> Vec<Line> {
    input
        .lines()
        .map(|s| {
            let (begin, end) = s.split_once(" -> ").unwrap();
            Line(
                Point::try_from(begin).unwrap(),
                Point::try_from(end).unwrap(),
            )
        })
        .collect()
}

#[derive(Debug)]
struct Line(Point, Point);

#[derive(Debug, Eq, PartialEq, Hash, Clone, Copy)]
struct Point {
    x: i32,
    y: i32,
}

impl Add<(i32, i32)> for Point {
    type Output = Point;

    fn add(self, rhs: (i32, i32)) -> Self::Output {
        Point {
            x: self.x + rhs.0,
            y: self.y + rhs.1,
        }
    }
}

impl AddAssign<(i32, i32)> for Point {
    fn add_assign(&mut self, rhs: (i32, i32)) {
        self.x += rhs.0;
        self.y += rhs.1;
    }
}

impl TryFrom<&str> for Point {
    type Error = ();

    fn try_from(value: &str) -> Result<Self, Self::Error> {
        let (x, y) = value.split_once(",").unwrap();
        Ok(Point {
            x: str::parse(x).unwrap(),
            y: str::parse(y).unwrap(),
        })
    }
}

fn solve(lines: Vec<Line>) -> usize {
    let mut grid = HashMap::new();

    for line in lines {
        let Line(mut start, end) = line;
        let direction = ((end.x - start.x).signum(), (end.y - start.y).signum());

        while start != end + direction {
            *grid.entry(start).or_insert(0) += 1;
            start += direction;
        }
    }

    grid.iter().filter(|(_, v)| **v >= 2).count()
}

fn part1(input: &str) -> usize {
    let lines = parse_input(input)
        .into_iter()
        .filter(|&Line(start, end)| start.x == end.x || start.y == end.y)
        .collect();

    solve(lines)
}

fn part2(input: &str) -> usize {
    solve(parse_input(input))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d05() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 6007);
        assert_eq!(part2(input), 19349);
    }

    #[test]
    fn example() {
        let input = "0,9 -> 5,9
8,0 -> 0,8
9,4 -> 3,4
2,2 -> 2,1
7,0 -> 7,4
6,4 -> 2,0
0,9 -> 2,9
3,4 -> 1,4
0,0 -> 8,8
5,5 -> 8,2";

        assert_eq!(part1(input), 5);
        assert_eq!(part2(input), 12);
    }
}
