use std::fmt::Write;
use std::io::{stdin, Read};

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<usize>);

    let n = input_itr.next().unwrap();
    let m = input_itr.next().unwrap();
    let mut light_pos = Vec::<u32>::with_capacity(m);
    for i in 0..m {
        let pos = input_itr.next().unwrap();
        light_pos.push(pos as u32);
    }
    light_pos.sort();

    let mut max_slice = 0;
    for i in 1..light_pos.len() {
        let slice_len = light_pos[i] - light_pos[i - 1];
        max_slice = max_slice.max(slice_len);
    }

    let result = ((max_slice >> 1) + (max_slice & 1))
        .max(light_pos[0])
        .max(n as u32 - light_pos.last().unwrap());

    let mut output_buffer = String::new();
    write!(&mut output_buffer, "{}", result).unwrap();
    println!("{}", output_buffer);
}
