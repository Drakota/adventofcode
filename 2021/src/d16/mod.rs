fn parse_input(input: &str) -> Bits {
    let line = input.lines().next().unwrap();
    let bits = line
        .trim()
        .chars()
        .flat_map(|c| {
            let i = i8::from_str_radix(&String::from_iter([c]), 16).unwrap();
            (0..4).map(move |bit| (i & (8 >> bit)) != 0)
        })
        .collect::<Vec<_>>();
    Bits::new(bits)
}

#[derive(Debug)]
struct Bits {
    bits: Vec<bool>,
    cursor: usize,
}

impl Bits {
    fn new(bits: Vec<bool>) -> Self {
        Self { bits, cursor: 0 }
    }

    fn get(&mut self, n: usize) -> Self {
        Bits {
            bits: self.bits.drain(self.cursor..self.cursor + n).collect(),
            cursor: 0,
        }
    }

    fn take(&mut self, n: usize) -> u64 {
        let value = self
            .bits
            .iter()
            .skip(self.cursor)
            .take(n)
            .rev()
            .enumerate()
            .map(|(i, &bit)| (bit as u64) << i)
            .sum();
        self.cursor += n;

        value
    }

    fn is_empty(&self) -> bool {
        self.cursor == self.bits.len()
    }
}

fn parse_literal(bits: &mut Bits) -> PacketContent {
    let mut sum = 0;
    loop {
        let group_indicator = bits.take(1);
        sum <<= 4;
        sum |= bits.take(4);

        if group_indicator == 0 {
            break (PacketContent::Literal(sum as usize));
        }
    }
}

fn parse_operator(type_id: u64, bits: &mut Bits) -> PacketContent {
    let length_type_id = bits.take(1);

    let subpackets = if length_type_id == 1 {
        (0..bits.take(11))
            .map(|_| Packet::from(&mut *bits))
            .collect()
    } else {
        let length = bits.take(15) as usize;
        let mut bits = bits.get(length);
        let mut subpackets = Vec::new();

        while !bits.is_empty() {
            subpackets.push(Packet::from(&mut bits))
        }

        subpackets
    };

    PacketContent::Operator(type_id, subpackets)
}

#[derive(Debug)]
struct Packet {
    version: u8,
    content: PacketContent,
}

#[derive(Debug)]
enum PacketContent {
    Literal(usize),
    Operator(u64, Vec<Packet>),
}

impl From<&mut Bits> for Packet {
    fn from(bits: &mut Bits) -> Self {
        let version = bits.take(3) as u8;
        let type_id = bits.take(3);

        let content = match type_id {
            4 => parse_literal(bits),
            type_id => parse_operator(type_id, bits),
        };

        Self { version, content }
    }
}

fn version_packet_sum(packet: Packet) -> u32 {
    match packet {
        Packet {
            version,
            content: PacketContent::Literal(_),
        } => version as u32,
        Packet {
            version,
            content: PacketContent::Operator(_, subpackets),
        } => version as u32 + subpackets.into_iter().map(version_packet_sum).sum::<u32>(),
    }
}

fn evaluate_packet(packet: Packet) -> u64 {
    match packet {
        Packet {
            version: _,
            content: PacketContent::Literal(value),
        } => value as u64,
        Packet {
            version: _,
            content: PacketContent::Operator(code, subpackets),
        } => {
            let mut values = subpackets.into_iter().map(evaluate_packet);
            match code {
                0 => values.sum(),
                1 => values.product(),
                2 => values.min().unwrap(),
                3 => values.max().unwrap(),
                5 => (values.next() > values.next()) as u64,
                6 => (values.next() < values.next()) as u64,
                7 => (values.next() == values.next()) as u64,
                _ => todo!(),
            }
        }
    }
}

fn part1(input: &str) -> u32 {
    let mut transmission = parse_input(input);
    let packet = Packet::from(&mut transmission);

    version_packet_sum(packet)
}

fn part2(input: &str) -> u64 {
    let mut transmission = parse_input(input);
    let packet = Packet::from(&mut transmission);

    evaluate_packet(packet)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d16() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 843);
        assert_eq!(part2(input), 5390807940351);
    }

    #[test]
    fn example() {
        assert_eq!(part1("8A004A801A8002F478"), 16);
        assert_eq!(part1("620080001611562C8802118E34"), 12);
        assert_eq!(part1("C0015000016115A2E0802F182340"), 23);
        assert_eq!(part1("A0016C880162017C3686B18A3D4780"), 31);
        assert_eq!(part2("C200B40A82"), 3);
        assert_eq!(part2("04005AC33890"), 54);
        assert_eq!(part2("880086C3E88112"), 7);
        assert_eq!(part2("CE00C43D881120"), 9);
        assert_eq!(part2("D8005AC2A8F0"), 1);
        assert_eq!(part2("F600BC2D8F"), 0);
        assert_eq!(part2("9C005AC2F8F0"), 0);
        assert_eq!(part2("9C0141080250320F1802104A08"), 1);
    }
}
