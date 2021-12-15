use std::{cmp::Reverse, collections::BinaryHeap};

fn parse_input(input: &str) -> Vec<Vec<i32>> {
    input
        .lines()
        .map(|l| l.chars().map(|c| c.to_digit(10).unwrap() as i32).collect())
        .collect()
}

trait Wrap {
    fn wrap(self, max: Self) -> Self;
}

impl Wrap for i32 {
    fn wrap(self, max: Self) -> Self {
        if self < max {
            self
        } else {
            self - (max - 1)
        }
    }
}

fn find_lowest_total_risk_path(maze: Vec<Vec<i32>>) -> i32 {
    let dimensions = (maze[0].len() as isize, maze.len() as isize);
    let mut best_to_point = vec![vec![i32::MAX; maze[0].len()]; maze.len()];
    let mut queue = BinaryHeap::new();
    queue.push((Reverse(0), 0_isize, 0_isize));

    while let Some((Reverse(cost), x, y)) = queue.pop() {
        if cost < best_to_point[y as usize][x as usize] {
            best_to_point[y as usize][x as usize] = cost;

            for (dx, dy) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
                let x = x + dx;
                let y = y + dy;
                if x >= 0 && x < dimensions.1 && y >= 0 && y < dimensions.0 {
                    queue.push((Reverse(cost + maze[(y) as usize][(x) as usize]), x, y));
                }
            }
        }
    }

    best_to_point[(dimensions.0 - 1) as usize][(dimensions.1 - 1) as usize]
}

fn part1(input: &str) -> i32 {
    let maze = parse_input(input);

    find_lowest_total_risk_path(maze)
}

fn part2(input: &str) -> i32 {
    let maze = parse_input(input);
    let (height, width) = (maze[0].len() as isize, maze.len() as isize);

    let zoomed = (0..(5 * height))
        .map(|x| {
            (0..(5 * width))
                .map(|y| {
                    (maze[(y % height) as usize][(x % width) as usize]
                        + (x / width) as i32
                        + (y / height) as i32)
                        .wrap(10)
                })
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    find_lowest_total_risk_path(zoomed)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d15() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 790);
        assert_eq!(part2(input), 2998);
    }

    #[test]
    fn example() {
        let input = "1163751742
1381373672
2136511328
3694931569
7463417111
1319128137
1359912421
3125421639
1293138521
2311944581";

        assert_eq!(part1(input), 40);
        assert_eq!(part2(input), 315);
    }
}
