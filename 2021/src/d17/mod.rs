use std::cmp::max;

fn parse_input(input: &str) -> (i64, i64, i64, i64) {
    let line = input.lines().next().unwrap();
    let (_, coords) = line.split_once(": ").unwrap();
    let (x, y) = coords.split_once(", ").unwrap();
    let (lx, hx) = x[2..].split_once("..").unwrap();
    let (ly, hy) = y[2..].split_once("..").unwrap();

    (
        lx.parse().unwrap(),
        hx.parse().unwrap(),
        ly.parse().unwrap(),
        hy.parse().unwrap(),
    )
}

fn measurements(coordinates: (i64, i64, i64, i64)) -> impl Iterator<Item = i64> {
    let delta_x = ((1.0 + 8.0 * coordinates.0 as f64).sqrt() / 2.0 - 0.5).ceil() as i64;

    (delta_x..=coordinates.1).flat_map(move |x| {
        (coordinates.2..=-coordinates.2).filter_map(move |y| max_height(coordinates, x, y))
    })
}

fn max_height((lx, hx, ly, hy): (i64, i64, i64, i64), mut dx: i64, mut dy: i64) -> Option<i64> {
    let mut x = 0;
    let mut y = 0;
    let mut max_y = 0;

    while y >= ly {
        if lx <= x && x <= hx && ly <= y && y <= hy {
            return Some(max_y);
        }

        x += dx;
        y += dy;
        max_y = max(max_y, y);
        dx = max(0, dx - 1);
        dy -= 1;
    }

    None
}

fn part1(input: &str) -> i64 {
    let coordinates = parse_input(input);

    measurements(coordinates).max().unwrap()
}

fn part2(input: &str) -> usize {
    let coordinates = parse_input(input);

    measurements(coordinates).count()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d17() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 11175);
        assert_eq!(part2(input), 3540);
    }

    #[test]
    fn example() {
        let input = "target area: x=20..30, y=-10..-5";

        assert_eq!(part1(input), 45);
        assert_eq!(part2(input), 112);
    }
}
