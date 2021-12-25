use itertools::Itertools;

fn parse_input(input: &str) -> Vec<Vec<char>> {
    input
        .lines()
        .map(ToString::to_string)
        .map(|l| l.chars().collect_vec())
        .collect()
}

fn part1(input: &str) -> i32 {
    let mut grid = parse_input(input);

    let (width, height) = (grid[0].len(), grid.len());

    for step in 1.. {
        let mut has_moved = false;

        for (cucumber, (dx, dy)) in [('>', (1, 0)), ('v', (0, 1))] {
            let mut changed_grid = grid.clone();

            for row in 0..height {
                for column in 0..width {
                    if grid[row][column] == cucumber
                        && grid[(row + dy) % height][(column + dx) % width] == '.'
                    {
                        changed_grid[(row + dy) % height][(column + dx) % width] = cucumber;
                        changed_grid[row][column] = '.';
                        has_moved = true;
                    }
                }
            }

            grid = changed_grid;
        }

        if !has_moved {
            return step;
        }
    }

    unreachable!()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d25() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 504);
    }

    #[test]
    fn example() {
        let input = "v...>>.vv>
.vv>>.vv..
>>.>v>...v
>>v>>.>.v.
v>v.vv.v..
>.>>..v...
.vv..>.>v.
v.v..>>v.v
....v..v.>";

        assert_eq!(part1(input), 58);
    }
}
