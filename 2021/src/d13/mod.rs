use std::collections::{HashSet, VecDeque};

fn parse_input(input: &str) -> Paper {
    let (points, folds): (Vec<_>, Vec<_>) =
        input.lines().into_iter().partition(|s| s.contains(','));
    let points: Vec<_> = points
        .into_iter()
        .map(|s| {
            let (x, y) = s.split_once(',').unwrap();
            Point::new(x.parse().unwrap(), y.parse().unwrap())
        })
        .collect();
    let folds: Vec<_> = folds
        .into_iter()
        .skip(1)
        .map(|s| {
            let mut iter = s.split_whitespace().skip(2);
            let fold = iter.next().unwrap();
            match fold.split_once('=').unwrap() {
                ("x", at) => Fold::XAxis(at.parse().unwrap()),
                ("y", at) => Fold::YAxis(at.parse().unwrap()),
                _ => unreachable!(),
            }
        })
        .collect();

    Paper::new(points, folds)
}

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
struct Point {
    x: isize,
    y: isize,
}

impl Point {
    fn new(x: isize, y: isize) -> Self {
        Self { x, y }
    }

    fn mirror(&self, fold: &Fold) -> Self {
        let (dx, dy) = match fold {
            Fold::XAxis(x) => (x - self.x, 0),
            Fold::YAxis(y) => (0, y - self.y),
        };
        Self::new(self.x + (2 * dx), self.y + (2 * dy))
    }
}

#[derive(Debug)]
enum Fold {
    XAxis(isize),
    YAxis(isize),
}

#[derive(Debug)]
struct Paper {
    pub points: HashSet<Point>,
    folds: VecDeque<Fold>,
}

impl ToString for Paper {
    fn to_string(&self) -> String {
        let width = self.points.iter().map(|p| p.x).max().unwrap();
        let height = self.points.iter().map(|p| p.y).max().unwrap();

        (0..height + 1)
            .map(|y| {
                (0..width + 1)
                    .map(|x| {
                        if self.points.contains(&Point::new(x, y)) {
                            '#'
                        } else {
                            '.'
                        }
                    })
                    .collect::<String>()
            })
            .collect::<Vec<_>>()
            .join("\n")
    }
}

impl Paper {
    fn new(points: Vec<Point>, folds: Vec<Fold>) -> Self {
        Self {
            points: HashSet::from_iter(points),
            folds: VecDeque::from_iter(folds),
        }
    }

    fn fold(&mut self) {
        let fold = self.folds.pop_front().unwrap();
        let (points_to_mirror, mut points): (Vec<_>, Vec<_>) =
            self.points.iter().copied().partition(|point| match fold {
                Fold::XAxis(at) => point.x > at,
                Fold::YAxis(at) => point.y > at,
            });
        let mut points_to_mirror: Vec<_> = points_to_mirror
            .into_iter()
            .map(|point| point.mirror(&fold))
            .collect();
        points.append(&mut points_to_mirror);

        self.points = HashSet::from_iter(points)
    }

    fn fold_all(&mut self) {
        while !self.folds.is_empty() {
            self.fold();
        }
    }
}

fn part1(input: &str) -> usize {
    let mut paper = parse_input(input);
    paper.fold();

    paper.points.len()
}

fn part2(input: &str) -> String {
    let mut paper = parse_input(input);
    paper.fold_all();

    paper.to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d13() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 693);
        assert_eq!(
            part2(input),
            "#..#..##..#....####.###...##..####.#..#
#..#.#..#.#.......#.#..#.#..#....#.#..#
#..#.#....#......#..#..#.#..#...#..#..#
#..#.#....#.....#...###..####..#...#..#
#..#.#..#.#....#....#.#..#..#.#....#..#
.##...##..####.####.#..#.#..#.####..##."
        );
    }

    #[test]
    fn example() {
        let input = "6,10
0,14
9,10
0,3
10,4
4,11
6,0
6,12
4,1
0,13
10,12
3,4
3,0
8,4
1,10
2,14
8,10
9,0

fold along y=7
fold along x=5";

        assert_eq!(part1(input), 17);
        assert_eq!(
            part2(input),
            "#####
#...#
#...#
#...#
#####"
        );
    }
}
