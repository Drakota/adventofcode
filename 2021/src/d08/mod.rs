fn parse_input(input: &str) -> Vec<(&str, &str)> {
    input.lines().map(|s| s.split_once("|").unwrap()).collect()
}

struct Pattern(String);

impl Pattern {
    fn contains(&self, other: &str) -> bool {
        self.0.chars().all(|c| other.contains(c))
    }

    fn intersections(&self, other: &str) -> usize {
        self.0.chars().filter(|c| other.contains(*c)).count()
    }
}

impl PartialEq<str> for Pattern {
    fn eq(&self, other: &str) -> bool {
        let mut a: Vec<_> = self.0.chars().collect();
        a.sort_unstable();

        let mut b: Vec<_> = other.chars().collect();
        b.sort_unstable();

        a == b
    }
}

fn partition_take_first(
    input: Vec<&'_ str>,
    filter: impl Fn(&&str) -> bool,
) -> (Pattern, Vec<&'_ str>) {
    let (first, rest): (Vec<_>, Vec<_>) = input.into_iter().partition(filter);

    (Pattern(first[0].to_string()), rest)
}

fn calibrate(input: &str) -> Vec<Pattern> {
    let input = input.split_whitespace().collect();
    let (one, input) = partition_take_first(input, |s| s.len() == 2);
    let (seven, input) = partition_take_first(input, |s| s.len() == 3);
    let (four, input) = partition_take_first(input, |s| s.len() == 4);
    let (eight, input) = partition_take_first(input, |s| s.len() == 7);
    let (three, input) = partition_take_first(input, |s| s.len() == 5 && seven.contains(s));
    let (five, input) = partition_take_first(input, |s| s.len() == 5 && four.intersections(s) == 3);
    let (two, input) = partition_take_first(input, |s| s.len() == 5);
    let (nine, input) = partition_take_first(input, |s| s.len() == 6 && four.contains(s));
    let (zero, input) = partition_take_first(input, |s| s.len() == 6 && seven.contains(s));
    let (six, _) = partition_take_first(input, |s| s.len() == 6);

    vec![zero, one, two, three, four, five, six, seven, eight, nine]
}

fn part1(input: &str) -> usize {
    let input = parse_input(input);

    input
        .into_iter()
        .flat_map(|(_, output)| output.split_whitespace())
        .filter(|s| [2, 3, 4, 7].contains(&s.len()))
        .count()
}

fn part2(input: &str) -> usize {
    let patterns = parse_input(input);

    patterns
        .into_iter()
        .map(|(input, output)| {
            let patterns = calibrate(input);

            output
                .split_whitespace()
                .map(|s| patterns.iter().position(|p| p == s).unwrap().to_string())
                .collect::<String>()
                .parse::<usize>()
                .unwrap()
        })
        .sum()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d08() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 342);
        assert_eq!(part2(input), 1068933);
    }
}
