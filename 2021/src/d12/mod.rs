use std::collections::{HashMap, HashSet};

fn parse_input(input: &str) -> Vec<(Cave, Cave)> {
    input
        .lines()
        .map(|s| s.split_once('-').unwrap())
        .map(|(from, to)| (Cave::new(from), Cave::new(to)))
        .collect()
}

#[derive(Debug, PartialEq, Eq, Hash, Clone)]
struct Cave {
    value: String,
}

impl Cave {
    fn new(text: &str) -> Self {
        Self {
            value: text.to_string(),
        }
    }

    fn is_small(&self) -> bool {
        self.value.chars().all(|c| c.is_ascii_lowercase())
    }
}

#[derive(Debug)]
struct Graph {
    adjacency_list: HashMap<Cave, Vec<Cave>>,
}

impl Graph {
    fn new() -> Self {
        Self {
            adjacency_list: HashMap::new(),
        }
    }

    fn from_nodes(nodes: Vec<(Cave, Cave)>) -> Self {
        let mut graph = Graph::new();

        for (from, to) in nodes {
            graph.add(from.clone(), to.clone());
            graph.add(to, from);
        }

        graph
    }

    fn add(&mut self, from: Cave, to: Cave) {
        self.adjacency_list.entry(from).or_default().push(to);
    }

    fn walk_count(
        &self,
        current: Option<Cave>,
        small_caves_visited: Option<HashSet<Cave>>,
    ) -> usize {
        let current = current.unwrap_or_else(|| Cave::new("start"));
        let small_caves_visited =
            small_caves_visited.unwrap_or_else(|| HashSet::from_iter(vec![current.clone()]));

        if current.value == "end" {
            return 1;
        }

        self.adjacency_list
            .get(&current)
            .unwrap()
            .iter()
            .filter(|c| !(c.is_small() && small_caves_visited.contains(c)))
            .map(|to| {
                let mut small_caves_visited = small_caves_visited.clone();
                if to.is_small() {
                    small_caves_visited.insert(to.clone());
                }
                self.walk_count(Some(to.clone()), Some(small_caves_visited))
            })
            .sum()
    }

    fn walk_revisit_count(
        &self,
        current: Option<Cave>,
        small_caves_visited: Option<HashSet<Cave>>,
        revisited: bool,
    ) -> usize {
        let current = current.unwrap_or_else(|| Cave::new("start"));
        let small_caves_visited =
            small_caves_visited.unwrap_or_else(|| HashSet::from_iter(vec![current.clone()]));

        if current.value == "end" {
            return 1;
        }

        self.adjacency_list
            .get(&current)
            .unwrap()
            .iter()
            .map(|to| {
                let mut small_caves_visited = small_caves_visited.clone();
                let mut revisited = revisited;

                if to.is_small() {
                    if small_caves_visited.contains(to) {
                        if revisited && to.value != "start" && to.value != "end" {
                            revisited = false;
                        } else {
                            return 0;
                        }
                    } else {
                        small_caves_visited.insert(to.clone());
                    }
                }

                self.walk_revisit_count(Some(to.clone()), Some(small_caves_visited), revisited)
            })
            .sum()
    }
}

fn part1(input: &str) -> usize {
    let nodes = parse_input(input);
    let graph = Graph::from_nodes(nodes);

    graph.walk_count(None, None)
}

fn part2(input: &str) -> usize {
    let nodes = parse_input(input);
    let graph = Graph::from_nodes(nodes);

    graph.walk_revisit_count(None, None, true)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d12() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 5457);
        assert_eq!(part2(input), 128506);
    }

    #[test]
    fn example() {
        let input = "fs-end
he-DX
fs-he
start-DX
pj-DX
end-zg
zg-sl
zg-pj
pj-he
RW-he
fs-DX
pj-RW
zg-RW
start-pj
he-WI
zg-he
pj-fs
start-RW";

        assert_eq!(part1(input), 226);
        assert_eq!(part2(input), 3509);
    }
}
