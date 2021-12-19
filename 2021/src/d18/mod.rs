use std::{iter::Sum, ops::Add};

use pest::{iterators::Pair, Parser};
use pest_derive::Parser;

#[derive(Parser)]
#[grammar = "../src/d18/grammar.pest"]
struct SnailfishParser;

fn parse_input(input: &str) -> Vec<SnailfishNumber> {
    input
        .lines()
        .map(|l| SnailfishParser::parse(Rule::array, l).unwrap())
        .map(|mut p| SnailfishNumber::new(p.next().unwrap()))
        .collect::<Vec<_>>()
}

#[derive(Debug, PartialEq, Clone)]
struct SnailfishPair(SnailfishNumber, SnailfishNumber);

impl Add for SnailfishPair {
    type Output = SnailfishPair;

    fn add(self, rhs: Self) -> Self::Output {
        let mut s = SnailfishPair(
            SnailfishNumber::Pair(Box::new(self)),
            SnailfishNumber::Pair(Box::new(rhs)),
        );

        loop {
            if !(s.explode() || s.split()) {
                break;
            }
        }

        s
    }
}

impl Sum for SnailfishPair {
    fn sum<I: Iterator<Item = Self>>(iter: I) -> Self {
        iter.reduce(|lhs, rhs| lhs + rhs).unwrap()
    }
}

impl SnailfishPair {
    fn do_explode(&mut self, d: u8) -> Option<(bool, usize, usize)> {
        if d >= 4 {
            if let (SnailfishNumber::Number(l), SnailfishNumber::Number(r)) = (&self.0, &self.1) {
                return Some((true, *l, *r));
            }
        }

        let left_res = match &mut self.0 {
            SnailfishNumber::Number(_) => None,
            SnailfishNumber::Pair(p) => p.do_explode(d + 1),
        };

        if let Some((first, lhs, rhs)) = left_res {
            if first {
                self.0 = SnailfishNumber::Number(0);
            }
            let mut adjacent_right = &mut self.1;
            let x;
            loop {
                match adjacent_right {
                    SnailfishNumber::Pair(p) => adjacent_right = &mut p.0,
                    SnailfishNumber::Number(y) => {
                        x = *y;
                        break;
                    }
                }
            }
            *adjacent_right = SnailfishNumber::Number(x + rhs);
            Some((false, lhs, 0))
        } else {
            let right_res = match &mut self.1 {
                SnailfishNumber::Number(_) => None,
                SnailfishNumber::Pair(p) => p.do_explode(d + 1),
            };
            if let Some((first, lhs, rhs)) = right_res {
                if first {
                    self.1 = SnailfishNumber::Number(0);
                }
                let mut adjacent_left = &mut self.0;
                let x;
                loop {
                    match adjacent_left {
                        SnailfishNumber::Pair(p) => adjacent_left = &mut p.1,
                        SnailfishNumber::Number(y) => {
                            x = *y;
                            break;
                        }
                    }
                }
                *adjacent_left = SnailfishNumber::Number(x + lhs);
                Some((false, 0, rhs))
            } else {
                None
            }
        }
    }

    fn explode(&mut self) -> bool {
        !matches!(self.do_explode(0), None)
    }

    fn split(&mut self) -> bool {
        (match &mut self.0 {
            SnailfishNumber::Number(n) => {
                if *n >= 10 {
                    self.0 = SnailfishNumber::Pair(Box::new(Self(
                        SnailfishNumber::Number(*n / 2),
                        SnailfishNumber::Number(*n / 2 + *n % 2),
                    )));
                    true
                } else {
                    false
                }
            }
            SnailfishNumber::Pair(p) => p.split(),
        } || match &mut self.1 {
            SnailfishNumber::Number(n) => {
                if *n >= 10 {
                    self.1 = SnailfishNumber::Pair(Box::new(Self(
                        SnailfishNumber::Number(*n / 2),
                        SnailfishNumber::Number(*n / 2 + *n % 2),
                    )));
                    true
                } else {
                    false
                }
            }
            SnailfishNumber::Pair(p) => p.split(),
        })
    }

    fn magnitude(&self) -> usize {
        3 * match &self.0 {
            SnailfishNumber::Number(x) => *x,
            SnailfishNumber::Pair(p) => p.magnitude(),
        } + 2 * match &self.1 {
            SnailfishNumber::Number(x) => *x,
            SnailfishNumber::Pair(p) => p.magnitude(),
        }
    }
}

#[derive(Debug, PartialEq, Clone)]
enum SnailfishNumber {
    Number(usize),
    Pair(Box<SnailfishPair>),
}

impl SnailfishNumber {
    fn new(pair: Pair<Rule>) -> Self {
        match pair.as_rule() {
            Rule::digit => Self::Number(pair.as_str().parse().unwrap()),
            Rule::array => {
                let mut iter = pair.into_inner();
                let lhs = Self::new(iter.next().unwrap());
                let rhs = Self::new(iter.next().unwrap());
                Self::Pair(Box::new(SnailfishPair(lhs, rhs)))
            }
        }
    }
}

fn part1(input: &str) -> usize {
    let pairs: Vec<SnailfishPair> = parse_input(input)
        .into_iter()
        .map(|n| match n {
            SnailfishNumber::Pair(p) => Ok(*p),
            _ => Err(""),
        })
        .collect::<Result<_, _>>()
        .unwrap();

    pairs.into_iter().sum::<SnailfishPair>().magnitude()
}

fn part2(input: &str) -> usize {
    let pairs: Vec<SnailfishPair> = parse_input(input)
        .into_iter()
        .map(|n| match n {
            SnailfishNumber::Pair(p) => Ok(*p),
            _ => Err(""),
        })
        .collect::<Result<_, _>>()
        .unwrap();

    pairs
        .iter()
        .flat_map(|lhs| {
            pairs
                .iter()
                .map(|rhs| match lhs != rhs {
                    true => (lhs.clone() + rhs.clone()).magnitude(),
                    false => 0,
                })
                .collect::<Vec<_>>()
        })
        .max()
        .unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d18() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 4116);
        assert_eq!(part2(input), 4638);
    }

    #[test]
    fn example() {
        assert_eq!(
            part1(
                "[[[[4,3],4],4],[7,[[8,4],9]]]
[1,1]"
            ),
            1384
        );

        assert_eq!(
            part1(
                "[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]
[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]
[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]
[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]
[7,[5,[[3,8],[1,4]]]]
[[2,[2,2]],[8,[8,1]]]
[2,9]
[1,[[[9,3],9],[[9,0],[0,7]]]]
[[[5,[7,4]],7],1]
[[[[4,2],2],6],[8,7]]"
            ),
            3488
        );

        assert_eq!(
            part2(
                "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]
[[[5,[2,8]],4],[5,[[9,9],0]]]
[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]
[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]
[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]
[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]
[[[[5,4],[7,7]],8],[[8,3],8]]
[[9,3],[[9,9],[6,[4,9]]]]
[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]
[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"
            ),
            3993
        );
    }
}
