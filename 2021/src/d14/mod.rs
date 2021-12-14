use std::collections::HashMap;

fn parse_input(input: &str) -> Formula {
    let mut iter = input.lines();
    let template = iter.next().unwrap().to_string();
    iter.next();

    let insertion_rules: Vec<_> = iter
        .map(|s| {
            let (elements, inserted) = s.split_once(" -> ").unwrap();
            (elements.to_string(), inserted.chars().next().unwrap())
        })
        .collect();

    Formula::new(template, insertion_rules)
}

#[derive(Debug)]
struct Formula {
    template: String,
    insertion_rules: HashMap<String, char>,
}

impl Formula {
    fn new(template: String, insertion_rules: Vec<(String, char)>) -> Self {
        Self {
            template,
            insertion_rules: HashMap::from_iter(insertion_rules),
        }
    }

    fn count(
        &self,
        needle: &str,
        memo: &mut HashMap<(String, usize), HashMap<char, usize>>,
        iterations: usize,
    ) -> HashMap<char, usize> {
        if iterations == 0 {
            let mut counts = HashMap::new();
            let mut chars = needle.chars();

            *counts.entry(chars.next().unwrap()).or_default() += 1;
            *counts.entry(chars.next().unwrap()).or_default() += 1;

            return counts;
        }

        if let Some(result) = memo.get(&(needle.to_string(), iterations)) {
            return result.clone();
        }

        if let Some(inserted) = self.insertion_rules.get(needle) {
            let mut counts = HashMap::new();
            let mut chars = needle.chars();

            let l = chars.next().unwrap();
            let r = chars.next().unwrap();

            for (c, count) in
                self.count(format!("{}{}", l, inserted).as_str(), memo, iterations - 1)
            {
                *counts.entry(c).or_default() += count;
            }

            for (c, count) in
                self.count(format!("{}{}", inserted, r).as_str(), memo, iterations - 1)
            {
                *counts.entry(c).or_default() += count;
            }

            *counts.entry(*inserted).or_default() -= 1;
            memo.insert((needle.to_string(), iterations), counts.clone());

            counts
        } else {
            let mut counts = HashMap::new();
            let mut chars = needle.chars();

            *counts.entry(chars.next().unwrap()).or_default() += 1;
            *counts.entry(chars.next().unwrap()).or_default() += 1;

            counts
        }
    }

    fn derive(&self, steps: u8) -> String {
        let mut polymer = self.template.clone();

        for _ in 0..steps {
            let mut modifications: Vec<(usize, char)> = Vec::new();

            for i in 1..polymer.len() {
                let needle = &polymer[i - 1..=i];
                if let Some(inserted) = self.insertion_rules.get(needle) {
                    modifications.push((i, *inserted));
                }
            }

            for (position, inserted) in modifications.into_iter().rev() {
                polymer.insert(position, inserted)
            }
        }

        polymer
    }

    fn fast_derive(&self, steps: usize) -> usize {
        let mut memo: HashMap<(String, usize), HashMap<char, usize>> = HashMap::new();
        let mut counts: HashMap<char, usize> = HashMap::new();

        for _ in 0..steps {
            for i in 1..self.template.len() {
                let needle = &self.template[i - 1..=i];

                for (c, count) in self.count(needle, &mut memo, steps) {
                    *counts.entry(c).or_default() += count;
                }

                if i != 1 {
                    *counts.entry(needle.chars().next().unwrap()).or_default() -= 1;
                }
            }
        }

        let max = counts.values().max().unwrap();
        let min = counts.values().min().unwrap();
        max - min
    }
}

fn count_occurences(polymer: String) -> usize {
    let mut counts: HashMap<char, usize> = HashMap::new();

    for c in polymer.chars() {
        *counts.entry(c).or_default() += 1;
    }

    let max = counts.iter().max_by_key(|(_, count)| *count).unwrap().1;
    let min = counts.iter().min_by_key(|(_, count)| *count).unwrap().1;
    max - min
}

fn part1(input: &str) -> usize {
    let formula = parse_input(input);
    let derived = formula.derive(10);

    count_occurences(derived)
}

fn part2(input: &str) -> usize {
    let formula = parse_input(input);

    formula.fast_derive(40)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d14() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 2549);
        assert_eq!(part2(input), 2516901104210);
    }

    #[test]
    fn example() {
        let input = "NNCB

CH -> B
HH -> N
CB -> H
NH -> C
HB -> C
HC -> B
HN -> C
NN -> C
BH -> H
NC -> B
NB -> B
BN -> B
BB -> N
BC -> B
CC -> N
CN -> C";

        assert_eq!(part1(input), 1588);
        assert_eq!(part2(input), 2188189693529);
    }
}
