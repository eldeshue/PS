#![allow(unused)]

use std::fmt::Write;
use std::io::{Read, stdin};

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut end = u32::from_str_radix(input.trim(), 10u32).unwrap();
    let mut start = 1;
    loop {
        write!(&mut output, "{end} ");
        end -= 1;
        if end < start {
            break;
        }
        write!(&mut output, "{start} ");
        start += 1;
        if end < start {
            break;
        }
    }
    print!("{output}");
}
