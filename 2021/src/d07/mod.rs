fn parse_input(input: &str) -> Vec<i32> {
    let line: String = input.lines().collect();
    line.split(',').map(|s| s.parse().unwrap()).collect()
}

fn part1(input: &str) -> i32 {
    let crabs = parse_input(input);

    let min = *crabs.iter().min().unwrap();
    let max = *crabs.iter().max().unwrap();

    (min..=max)
        .map(|align| crabs.iter().map(|crab| (align - crab).abs()).sum::<i32>())
        .min()
        .unwrap()
}

fn part2(input: &str) -> i32 {
    let crabs = parse_input(input);

    let min = *crabs.iter().min().unwrap();
    let max = *crabs.iter().max().unwrap();

    (min..=max)
        .map(|align| {
            crabs
                .iter()
                .map(|crab| (1..=(align - crab).abs()).sum::<i32>())
                .sum()
        })
        .min()
        .unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d07() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 341534);
        assert_eq!(part2(input), 93397632);
    }

    #[test]
    fn example() {
        let input = "16,1,2,0,4,2,7,1,2,14";

        assert_eq!(part1(input), 37);
        assert_eq!(part2(input), 168);
    }
}
