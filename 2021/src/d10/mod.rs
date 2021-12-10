fn parse_input(input: &str) -> Vec<String> {
    input.lines().map(|s| s.to_string()).collect()
}

enum State {
    Valid,
    Corrupted(char),
    Incomplete(Vec<char>),
}

fn analyze_line(line: String) -> State {
    let mut stack = vec![];

    for char in line.chars() {
        match char {
            open @ ('(' | '[' | '{' | '<') => stack.push(open),
            close @ (')' | ']' | '}' | '>') => {
                let open = stack.pop().unwrap();
                match (open, close) {
                    ('(', ')') | ('[', ']') | ('{', '}') | ('<', '>') => continue,
                    _ => return State::Corrupted(close),
                }
            }
            _ => unreachable!(),
        }
    }

    if stack.is_empty() {
        State::Valid
    } else {
        State::Incomplete(stack)
    }
}

fn part1(input: &str) -> u32 {
    let lines = parse_input(input);

    lines
        .into_iter()
        .map(analyze_line)
        .filter_map(|s| match s {
            State::Corrupted(close) => Some(close),
            _ => None,
        })
        .map(|c| match c {
            ')' => 3,
            ']' => 57,
            '}' => 1197,
            '>' => 25137,
            _ => unreachable!(),
        })
        .sum()
}

fn part2(input: &str) -> usize {
    let lines = parse_input(input);

    let mut scores: Vec<_> = lines
        .into_iter()
        .map(analyze_line)
        .filter_map(|s| match s {
            State::Incomplete(remaining) => Some(remaining),
            _ => None,
        })
        .map(|remaining| {
            remaining.into_iter().rev().fold(0, |acc, c| {
                acc * 5
                    + match c {
                        '(' => 1,
                        '[' => 2,
                        '{' => 3,
                        '<' => 4,
                        _ => unreachable!(),
                    }
            })
        })
        .collect();
    scores.sort_unstable();

    scores[scores.len() / 2]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d10() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 369105);
        assert_eq!(part2(input), 3999363569);
    }

    #[test]
    fn example() {
        let input = "[({(<(())[]>[[{[]{<()<>>
[(()[<>])]({[<{<<[]>>(
{([(<{}[<>[]}>{[]{[(<()>
(((({<>}<{<{<>}{[]{[]{}
[[<[([]))<([[{}[[()]]]
[{[{({}]{}}([{[{{{}}([]
{<[[]]>}<{[{[{[]{()[[[]
[<(<(<(<{}))><([]([]()
<{([([[(<>()){}]>(<<{{
<{([{{}}[<[[[<>{}]]]>[]]";

        assert_eq!(part1(input), 26397);
        assert_eq!(part2(input), 288957);
    }
}
