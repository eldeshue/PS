#![allow(unused)]
/*
    Crate for PS in Rust
*/
use std::fmt::Write;
use std::io::{Read, stdin};

/*
    solution :
*/
const INF: i64 = 1_000_000_000_000_000_000;
const START: usize = 1;

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<i32>);

    let n = input_itr.next().unwrap() as usize;
    let m = input_itr.next().unwrap() as usize;
    let mut edges: Vec<(usize, usize, i32)> = vec![(0, 0, 0); m];
    edges.iter_mut().for_each(|edge| {
        edge.0 = input_itr.next().unwrap() as usize;
        edge.1 = input_itr.next().unwrap() as usize;
        edge.2 = input_itr.next().unwrap();
    });

    let mut parents: Vec<usize> = vec![0; n + 1];
    let mut costs: Vec<i64> = vec![INF; n + 1];
    parents[START] = START;
    costs[START] = 0;
    for _ in 0..n {
        for (s, e, c) in &edges {
            if parents[*s] > 0 && ((costs[*s] + *c as i64) < costs[*e]) {
                parents[*e] = *s;
                costs[*e] = costs[*s] + *c as i64;
            }
        }
    }

    // check negative cycle
    if {
        let mut is_negative_cycle = false;
        for (s, e, c) in &edges {
            if parents[*s] > 0 && (costs[*s] + *c as i64) < costs[*e] {
                is_negative_cycle = true;
                break;
            }
        }
        is_negative_cycle
    } {
        println!("-1");
    } else {
        let mut result = String::new();
        for i in 2..=n {
            if costs[i] == INF {
                writeln!(result, "-1");
            } else {
                writeln!(result, "{}", costs[i]);
            }
        }
        println!("{}", result);
    }
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
