fn parse_input(input: &str) -> Vec<usize> {
    input
        .split_whitespace()
        .map(str::parse)
        .map(Result::unwrap)
        .collect()
}

fn count_measurement_increases(measurements: Vec<usize>) -> usize {
    measurements
        .windows(2)
        .flat_map(<&[usize; 2]>::try_from)
        .filter(|[a, b]| b > a)
        .count()
}

fn part1(input: &str) -> usize {
    count_measurement_increases(parse_input(input))
}

fn part2(input: &str) -> usize {
    let input = parse_input(input)
        .windows(3)
        .map(|w| w.iter().sum())
        .collect();

    count_measurement_increases(input)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d01() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 1466);
        assert_eq!(part2(input), 1491);
    }

    #[test]
    fn example() {
        let test_case = "199 200 208 210 200 207 240 269 260 263";

        assert_eq!(part1(test_case), 7);
        assert_eq!(part2(test_case), 5);
    }
}
