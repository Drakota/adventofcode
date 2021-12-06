fn parse_input(input: &str) -> [usize; 9] {
    let line: String = input.lines().collect();
    let mut fishes = [0; 9];

    line.split(',')
        .map(str::parse)
        .map(Result::unwrap)
        .for_each(|f: usize| fishes[f] += 1);

    fishes
}

fn solve(input: &str, days: usize) -> usize {
    let mut fishes = parse_input(input);

    for _ in 1..=days {
        fishes.rotate_left(1);
        fishes[6] += fishes[8];
    }

    fishes.iter().sum()
}

fn part1(input: &str) -> usize {
    solve(input, 80)
}

fn part2(input: &str) -> usize {
    solve(input, 256)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d06() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 372300);
        assert_eq!(part2(input), 1675781200288);
    }

    #[test]
    fn example() {
        let input = "3,4,3,1,2";

        assert_eq!(part1(input), 5934);
        assert_eq!(part2(input), 26984457539);
    }
}
