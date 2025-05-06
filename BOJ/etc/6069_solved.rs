/*
    Crate for PS in Rust
*/
use std::fmt::Write;
use std::io::{Read, stdin};

/*
    solution :
*/

fn main() {
    // get input by multiple lines, numbers
    let mut input_buffer = String::new();
    let mut cin = stdin();
    cin.read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<u32>);

    let n = input_itr.next().unwrap();
    let m = input_itr.next().unwrap();
    let mut lights: Vec<bool> = vec![false; (n + 1) as usize];
    let mut output_buffer = String::new();
    for _ in 0..m {
        let id = input_itr.next().unwrap();
        let l = input_itr.next().unwrap() as usize;
        let r = input_itr.next().unwrap() as usize;

        match id {
            0 => {
                // update query
                for i in l..=r {
                    lights[i] = !lights[i];
                }
            }
            1 => {
                // result query
                let count = lights[l..=r].iter().fold(0, |acc, bulb| {
                    acc + match bulb {
                        true => 1u32,
                        false => 0u32,
                    }
                });
                writeln!(output_buffer, "{count}").unwrap();
            }
            _ => {
                unreachable!();
            }
        }
    }

    println!("{output_buffer}");
}

/*
// input
// single line input
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).unwrap();

// multi line input
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();	// 입력 스트림 전체를 파일처럼 한 번에 읽음
    let mut input = input.split_ascii_whitespace();	// 공백으로 분리

    let n = input.next().unwrap().parse::<usize>().unwrap();	// usize로 파싱해서 획득
    let line = input.next().unwrap();							// 파싱을 안했으므로, 문자열 획득

// multi number input
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().flat_map(str::parse::<usize>);	// flat map으로 String을 usize로 해체

    let n = input.next().unwrap() as usize;	// 파싱을 이미 다 했으므로, 숫자로 획득하게 됨.

// out

// use string as buffer
    let mut output = String::new();

    for i in 0..100_000 {
        writeln!(output, "{i}").unwrap();
    }

    println!("{output}");
*/
