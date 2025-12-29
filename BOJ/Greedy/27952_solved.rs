/*
    BOJ 27952

    굳이 미리 깎을 필요가 있는가?

    스텝이 진행됨에 따라서 B만큼 늘어나고, 적어도 A이상이어야 함.

    문제는 단계별로 X의 배수만큼 줄일 수 있는데,
*/

use std::fmt::Write;
use std::io::{stdin, Read};

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<u64>);

    // input
    let n = input_itr.next().unwrap();
    let x = input_itr.next().unwrap();
    let mut a = vec![0; n as usize]; // lower bound
    for val in &mut a {
        *val = input_itr.next().unwrap();
    }
    let mut b = vec![0; n as usize]; // amount of increase
    for val in &mut b {
        *val = input_itr.next().unwrap();
    }

    // greedy
    let mut result = 0i64;
    let mut cur_weight = 0u64;
    for i in 0..n as usize {
        // increase
        cur_weight += b[i];

        // check
        if cur_weight < a[i] {
            result = -1;
            break;
        }
    }

    if result != -1 {
        result = ((cur_weight - a.last().unwrap()) / x) as i64;
    }

    let mut output_buffer = String::new();
    write!(&mut output_buffer, "{}", result).unwrap();
    println!("{}", output_buffer);
}
