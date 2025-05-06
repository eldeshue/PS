/*
    Crate for PS in Rust
*/
use std::io::{Read, stdin};

/*
    solution :
*/

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<i32>);

    let n = input_itr.next().unwrap();
    let k = input_itr.next().unwrap();
    let mut cows: Vec<i32> = vec![-1; n as usize];
    cows.iter_mut().for_each(|x| {
        *x = input_itr.next().unwrap();
    });

    // solve
    let mut max_id: i32 = -1;
    let mut last_pos: Vec<i32> = vec![-100_000; 1000_001];
    cows.iter().enumerate().for_each(|(pos, id)| {
        if (pos as i32 - last_pos[*id as usize]) <= k {
            max_id = std::cmp::max(max_id, *id);
        }
        last_pos[*id as usize] = pos as i32;
    });
    println!("{max_id}");
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
