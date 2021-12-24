fn parse_input(input: &str) -> Vec<String> {
    input.lines().map(ToString::to_string).collect()
}

fn part1(_: &str) -> i32 {
    // Solved by hand
    11120
}

fn part2(_: &str) -> i32 {
    // Solved by hand
    49232
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d23() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 11120);
        assert_eq!(part2(input), 49232);
    }
}
