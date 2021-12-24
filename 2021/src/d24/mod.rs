use std::collections::HashMap;

fn parse_input(input: &str) -> Vec<Instruction> {
    input
        .lines()
        .map(ToString::to_string)
        .map(From::from)
        .collect()
}

fn register_to_index(register: char) -> usize {
    match register {
        'w' => 0,
        'x' => 1,
        'y' => 2,
        'z' => 3,
        _ => unreachable!(),
    }
}

#[derive(Debug, Clone, Copy)]
enum Parameter {
    Register(usize),
    Value(isize),
}

impl Parameter {
    fn to_value(&self, alu: &Alu) -> isize {
        match self {
            Parameter::Register(register) => alu.registers[*register],
            Parameter::Value(value) => *value,
        }
    }
}

impl From<&str> for Parameter {
    fn from(parameter: &str) -> Self {
        match parameter.parse::<isize>() {
            Ok(value) => Parameter::Value(value),
            Err(_) => Parameter::Register(register_to_index(parameter.chars().next().unwrap())),
        }
    }
}

#[derive(Debug, Clone, Copy)]
enum Instruction {
    Input(usize),
    Add(usize, Parameter),
    Mul(usize, Parameter),
    Div(usize, Parameter),
    Mod(usize, Parameter),
    Eql(usize, Parameter),
}

impl From<String> for Instruction {
    fn from(line: String) -> Self {
        let (kind, parameters) = line.split_once(' ').unwrap();

        if kind == "inp" {
            return Instruction::Input(register_to_index(parameters.chars().next().unwrap()));
        }

        let (lhs, rhs) = parameters.split_once(' ').unwrap();
        let lhs = register_to_index(lhs.chars().next().unwrap());

        match kind {
            "add" => Instruction::Add(lhs, rhs.into()),
            "mul" => Instruction::Mul(lhs, rhs.into()),
            "div" => Instruction::Div(lhs, rhs.into()),
            "mod" => Instruction::Mod(lhs, rhs.into()),
            "eql" => Instruction::Eql(lhs, rhs.into()),
            _ => unreachable!(),
        }
    }
}

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
struct Alu {
    registers: [isize; 4],
}

impl Alu {
    fn new() -> Self {
        Self {
            registers: [0, 0, 0, 0],
        }
    }

    fn exec(&mut self, instruction: Instruction, input: Option<isize>) {
        match instruction {
            Instruction::Input(register) => {
                self.registers[register] = input.unwrap();
            }
            Instruction::Add(register, parameter) => {
                self.registers[register] += parameter.to_value(self);
            }
            Instruction::Mul(register, parameter) => {
                self.registers[register] *= parameter.to_value(self);
            }
            Instruction::Div(register, parameter) => {
                self.registers[register] /= parameter.to_value(self);
            }
            Instruction::Mod(register, parameter) => {
                self.registers[register] %= parameter.to_value(self);
            }
            Instruction::Eql(register, parameter) => {
                self.registers[register] =
                    (self.registers[register] == parameter.to_value(self)) as isize;
            }
        }
    }
}

fn find_serial_number(
    instructions: &[Instruction],
    mut alu: Alu,
    mut program_counter: usize,
    memo: &mut HashMap<(Alu, usize), Option<isize>>,
    range: Vec<isize>,
) -> Option<isize> {
    if let Some(&result) = memo.get(&(alu, program_counter)) {
        return result;
    }

    'outer: for digit in range.clone() {
        alu.exec(instructions[program_counter], Some(digit));
        program_counter += 1;

        while let Some(instruction) = instructions.get(program_counter) {
            match instructions[program_counter] {
                Instruction::Input(_) => {
                    if let Some(result) =
                        find_serial_number(instructions, alu, program_counter, memo, range.clone())
                    {
                        let result = result * 10 + digit;
                        memo.insert((alu, program_counter), Some(result));
                        return Some(result);
                    } else {
                        continue 'outer;
                    }
                }
                _ => {
                    alu.exec(*instruction, None);
                    program_counter += 1;
                }
            }
        }

        if alu.registers[3] == 0 {
            memo.insert((alu, program_counter), Some(digit));
            return Some(digit);
        }
    }

    memo.insert((alu, program_counter), None);
    None
}

fn part1(input: &str) -> isize {
    let instructions = parse_input(input);

    let mut memo = HashMap::new();
    let answer = find_serial_number(
        &instructions,
        Alu::new(),
        0,
        &mut memo,
        (1..9).rev().collect(),
    );

    answer.unwrap()
}

fn part2(input: &str) -> isize {
    let instructions = parse_input(input);

    let mut memo = HashMap::new();
    let answer = find_serial_number(&instructions, Alu::new(), 0, &mut memo, (1..9).collect());

    answer.unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn d24() {
        let input = include_str!("./input/data.txt");

        assert_eq!(part1(input), 95299897999897);
        assert_eq!(part2(input), 31111121382151);
    }
}
