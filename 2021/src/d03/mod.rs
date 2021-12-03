fn parse_input(input: &str) -> Vec<String> {
    input.lines().map(|s| s.to_owned()).collect()
}

fn count_bits(input: &[String], column: usize) -> bool {
    let (mut ones, mut zeroes) = (0, 0);

    for line in input {
        match line.chars().nth(column) {
            Some('1') => ones += 1,
            Some('0') => zeroes += 1,
            _ => unreachable!(),
        }
    }

    (ones - zeroes) >= 0
}

fn part1(input: &str) -> u32 {
    let input = parse_input(input);
    let mut gamma: u32 = 0;
    let mut epsilon: u32 = 0;

    for i in 0..(input.get(0).unwrap().len()) {
        let bit = count_bits(&input[..], i);
        let shift = (input.get(0).unwrap().len()) - (i + 1);
        gamma += if bit { 1 << shift } else { 0 };
        epsilon += if !bit { 1 << shift } else { 0 };
    }

    gamma * epsilon
}

macro_rules! determine_number {
    ($name:ident, $init:expr, $eq:tt) => {
        let mut $name = $init;

        let mut i = 0;
        while $name.len() != 1 {
            let bit = if count_bits(&$name[..], i) { '1' } else { '0' };
            $name.retain(|s| s.chars().nth(i).unwrap() $eq bit);
            i += 1;
        }

        let $name = u32::from_str_radix(&$name[0][..], 2).unwrap();
    };
}

fn part2(input: &str) -> u32 {
    determine_number!(oxygen, parse_input(input), ==);
    determine_number!(co2, parse_input(input), !=);

    oxygen * co2
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d03() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 1092896);
        assert_eq!(part2(input), 4672151);
    }
}
