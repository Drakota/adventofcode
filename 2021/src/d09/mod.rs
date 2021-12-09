fn parse_input(input: &str) -> Vec<Vec<u32>> {
    input
        .lines()
        .map(|l| l.chars().map(|c| c.to_digit(10).unwrap()).collect())
        .collect()
}

fn find_low_points(input: &[Vec<u32>]) -> Vec<(usize, usize)> {
    let dimensions = (input.get(0).unwrap().len(), input.len());

    (0..dimensions.1)
        .flat_map(|y| (0..dimensions.0).map(move |x| (x, y)))
        .into_iter()
        .filter(|(x, y)| {
            [(-1, 0), (1, 0), (0, -1), (0, 1)]
                .iter()
                .filter(|(dx, dy)| {
                    let neighbor = input
                        .get((*y as isize + dy) as usize)
                        .and_then(|r| r.get((*x as isize + dx) as usize));

                    if let Some(neighbor) = neighbor {
                        neighbor <= &input[*y][*x]
                    } else {
                        false
                    }
                })
                .count()
                == 0
        })
        .collect()
}

fn part1(input: &str) -> u32 {
    let input = parse_input(input);

    find_low_points(&input)
        .into_iter()
        .map(|(x, y)| input[y][x] + 1)
        .sum()
}

fn part2(input: &str) -> usize {
    let input = parse_input(input);

    let mut bassins: Vec<_> = find_low_points(&input)
        .into_iter()
        .map(|low_point| {
            let mut flood = vec![low_point];
            let mut visited = vec![low_point];

            while let Some((x, y)) = flood.pop() {
                let height = input[y][x];

                for (dx, dy) in [(-1, 0), (1, 0), (0, -1), (0, 1)] {
                    let (nx, ny) = ((x as isize + dx) as usize, (y as isize + dy) as usize);
                    let neighbor = input.get(ny).and_then(|r| r.get(nx));

                    match neighbor {
                        Some(neighbor)
                            if *neighbor != 9
                                && *neighbor > height
                                && !visited.contains(&(nx, ny)) =>
                        {
                            flood.push((nx, ny));
                            visited.push((nx, ny));
                        }
                        _ => {}
                    }
                }
            }

            visited.len()
        })
        .collect();

    bassins.sort_by(|a, b| b.cmp(a));
    bassins.iter().take(3).product()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d09() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 506);
        assert_eq!(part2(input), 931200);
    }

    #[test]
    fn example() {
        let input = "2199943210
3987894921
9856789892
8767896789
9899965678";

        assert_eq!(part1(input), 15);
        assert_eq!(part2(input), 1134);
    }
}
