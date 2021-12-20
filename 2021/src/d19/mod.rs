use itertools::Itertools;
use std::collections::HashSet;

fn parse_input(input: &str) -> Vec<Vec<(i32, i32, i32)>> {
    input
        .split("\n\n")
        .map(|s| {
            let mut iter = s.split('\n');
            iter.next();

            iter.map(|r| {
                let mut r = r.split(',');
                let x = r.next().unwrap();
                let y = r.next().unwrap();
                let z = r.next().unwrap();

                (x.parse().unwrap(), y.parse().unwrap(), z.parse().unwrap())
            })
            .collect()
        })
        .collect()
}

fn rotations((x, y, z): (i32, i32, i32)) -> Vec<(i32, i32, i32)> {
    vec![
        (x, y, z),
        (x, z, -y),
        (x, -y, -z),
        (x, -z, y),
        (y, x, -z),
        (y, z, x),
        (y, -x, z),
        (y, -z, -x),
        (z, x, y),
        (z, y, -x),
        (z, -x, -y),
        (z, -y, x),
        (-x, y, -z),
        (-x, z, y),
        (-x, -y, z),
        (-x, -z, -y),
        (-y, x, z),
        (-y, z, -x),
        (-y, -x, -z),
        (-y, -z, x),
        (-z, x, -y),
        (-z, y, x),
        (-z, -x, y),
        (-z, -y, -x),
    ]
}

fn merge_scan(
    acc_scanner: &mut HashSet<(i32, i32, i32)>,
    scanner: &[(i32, i32, i32)],
) -> Option<(i32, i32, i32)> {
    for i in 0..24 {
        let rotated_reports = scanner
            .iter()
            .map(|&coords| rotations(coords)[i])
            .collect::<Vec<_>>();

        let distances = acc_scanner
            .iter()
            .cartesian_product(&rotated_reports)
            .map(|((x1, y1, z1), (x2, y2, z2))| (x1 - x2, y1 - y2, z1 - z2));

        for (dx, dy, dz) in distances {
            let translation = rotated_reports
                .iter()
                .map(|(x, y, z)| (x + dx, y + dy, z + dz));

            if translation
                .clone()
                .filter(|v| acc_scanner.contains(v))
                .count()
                >= 12
            {
                acc_scanner.extend(translation);
                return Some((dx, dy, dz));
            }
        }
    }
    None
}

fn solve(input: &str) -> (usize, usize) {
    let mut scanners = parse_input(input);

    let mut acc_scanner = scanners.remove(0).into_iter().collect::<HashSet<_>>();
    let mut positions = Vec::new();

    while !scanners.is_empty() {
        for i in (0..scanners.len()).rev() {
            if let Some(d) = merge_scan(&mut acc_scanner, &scanners[i]) {
                positions.push(d);
                scanners.remove(i);
            }
        }
    }

    (
        acc_scanner.len(),
        positions
            .iter()
            .tuple_combinations()
            .map(|((x1, y1, z1), (x2, y2, z2))| (x1 - x2).abs() + (y1 - y2).abs() + (z1 - z2).abs())
            .max()
            .unwrap() as usize,
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d19() {
        let input = include_str!("./input/data.txt");

        let (p1, p2) = solve(input);
        assert_eq!(p1, 408);
        assert_eq!(p2, 13348);
    }
}
