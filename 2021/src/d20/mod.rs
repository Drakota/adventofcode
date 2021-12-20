use itertools::Itertools;
use std::collections::HashSet;

fn parse_input(input: &str) -> (Vec<Vec<char>>, String) {
    let mut iter = input.split("\n\n");
    let algorithm = iter.next().unwrap().to_string();
    let input_image = iter
        .next()
        .unwrap()
        .lines()
        .map(|l| l.chars().collect_vec())
        .collect_vec();

    (input_image, algorithm)
}

fn enhance(image: Vec<Vec<char>>, algorithm: String, steps: u32) -> usize {
    let mut light_pixels: HashSet<(isize, isize)> = HashSet::from_iter(
        image
            .into_iter()
            .enumerate()
            .flat_map(|(j, l)| {
                l.into_iter()
                    .enumerate()
                    .filter(|(_, c)| *c == '#')
                    .map(|(i, _)| (i as isize, j as isize))
                    .collect_vec()
            })
            .collect_vec(),
    );

    for step in 0..steps {
        let mut enhanced_light_pixels: HashSet<(isize, isize)> = HashSet::new();
        let xs = light_pixels.iter().map(|x| x.0).collect::<Vec<_>>();
        let ys = light_pixels.iter().map(|x| x.1).collect::<Vec<_>>();

        let (lx, ux) = (xs.iter().min().unwrap(), xs.iter().max().unwrap());
        let (ly, uy) = (ys.iter().min().unwrap(), ys.iter().max().unwrap());

        for x in (lx - 3)..(ux + 3) {
            for y in (ly - 3)..(uy + 3) {
                let algorithm_index = [
                    (-1, -1),
                    (0, -1),
                    (1, -1),
                    (-1, 0),
                    (0, 0),
                    (1, 0),
                    (-1, 1),
                    (0, 1),
                    (1, 1),
                ]
                .into_iter()
                .map(|(dx, dy)| {
                    let (nx, ny) = ((x + dx), (y + dy));
                    if *lx <= nx && nx <= *ux && *ly <= ny && ny <= *uy {
                        if light_pixels.contains(&(nx, ny)) {
                            "1"
                        } else {
                            "0"
                        }
                    } else if step % 2 == 1 {
                        "1"
                    } else {
                        "0"
                    }
                })
                .collect::<String>();

                if algorithm
                    .chars()
                    .nth(usize::from_str_radix(&algorithm_index, 2).unwrap())
                    .unwrap()
                    == '#'
                {
                    enhanced_light_pixels.insert((x, y));
                }
            }
        }

        light_pixels = enhanced_light_pixels;
    }

    light_pixels.len()
}

fn part1(input: &str) -> usize {
    let (input_image, algorithm) = parse_input(input);

    enhance(input_image, algorithm, 2)
}

fn part2(input: &str) -> usize {
    let (input_image, algorithm) = parse_input(input);

    enhance(input_image, algorithm, 50)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d20() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 5461);
        assert_eq!(part2(input), 18226);
    }
}
