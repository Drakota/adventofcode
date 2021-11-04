#[cfg(test)]
mod tests {
    #[test]
    fn part1() {
        let content = include_str!("./input/data.txt");
        let lines = content.lines().collect::<Vec<_>>();
        dbg!(lines);
    }

    #[test]
    fn part2() {}
}
