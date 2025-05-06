#![allow(unused)]
/*
    Crate for PS in Rust
*/
use std::fmt::Write;
use std::io::{Read, stdin};

/*
    solution :
*/
const INF: u32 = 2_000_000_000;

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<usize>);

    let v = input_itr.next().unwrap();
    let e = input_itr.next().unwrap();
    let mut total_cost: Vec<Vec<u32>> = vec![vec![INF; v + 1]; v + 1];
    for i in 0..=v {
        total_cost[i][i] = 0;
    }
    for _ in 0..e {
        let s = input_itr.next().unwrap();
        let e = input_itr.next().unwrap();
        total_cost[s][e] = input_itr.next().unwrap() as u32;
    }

    for mid in 1..=v {
        // mid
        for start in 1..=v {
            // start
            for end in 1..=v {
                // end
                if (total_cost[start][mid] != INF)
                    && (total_cost[mid][end] != INF)
                    && ((total_cost[start][mid] + total_cost[mid][end]) < total_cost[start][end])
                {
                    total_cost[start][end] = total_cost[start][mid] + total_cost[mid][end];
                }
            }
        }
    }

    // print
    let mut result = INF;
    for goal in 1..=v {
        for turn_point in 1..=v {
            if goal != turn_point {
                result = std::cmp::min(
                    result,
                    total_cost[goal][turn_point] + total_cost[turn_point][goal],
                );
            }
        }
    }

    if result == INF {
        println!("-1");
    } else {
        println!("{result}");
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
