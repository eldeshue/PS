/*
    Crate for PS in Rust
*/
use std::io::{Read, stdin};

/*
    solution : 3D DP

    current pos : i
    current color : j
    start color : k

    adj color must be different
*/

fn main() {
    // get input by multiple lines, numbers
    let mut input_buffer = String::new();
    let mut cin = stdin();
    cin.read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<u32>);

    // input processing
    let n = input_itr.next().unwrap() as usize;
    let mut dist = vec![[0; 3]; n];
    for i in 0..n as usize {
        for j in 0..3 as usize {
            dist[i][j] = input_itr.next().unwrap();
        }
    }

    // dp
    let max_cost: u32 = 2000_000_000;
    let mut cache = vec![[[max_cost; 3]; 3]; n];
    for i in 0..3 as usize {
        cache[0][i][i] = dist[0][i];
    }
    for cur_pos in 1..n {
        for start_pos in 0..3 {
            for cur_color in 0..3 {
                for prev_color in 0..3 {
                    if prev_color != cur_color {
                        cache[cur_pos][start_pos][cur_color] = cache[cur_pos][start_pos][cur_color]
                            .min(
                                cache[cur_pos - 1][start_pos][prev_color]
                                    + dist[cur_pos][cur_color],
                            );
                    }
                }
            }
        }
    }

    // collect min value
    let mut min_rgb_cost = 2000_000_000;
    for i in 0..3 as usize {
        for j in 0..3 as usize {
            if i != j {
                min_rgb_cost = min_rgb_cost.min(cache[n - 1][i][j]);
            }
        }
    }

    println!("{min_rgb_cost}");
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
