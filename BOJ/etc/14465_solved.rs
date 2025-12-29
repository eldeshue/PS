/*
    BOJ 14465

    1~=N 범위가 주어지고, 해당 범위 안에 망가진 신호등이 주어짐.

    우리가 필요한 것은 정상 신호등이 연속 k개 있기 위해서 수리해야 하는 최소 신호등 수

    즉, 윈도우 크기는 k, 해당 윈도우 안에 망가진 신호등 개수가 최소가 되어야 함

    ======

    슬라이딩 윈도우가 생각이 안나서 주어진 배열을 뒤집어 정상 신호등 배열을 만든 다음,
    이 배열에 대한 two-pointer를 수행했는데, 옳지 못한 접근이었다.
*/

use std::fmt::Write;
use std::io::{stdin, Read};

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<u32>);

    // input
    let n = input_itr.next().unwrap();
    let k = input_itr.next().unwrap();
    let b = input_itr.next().unwrap();
    let mut wrong_signals = vec![0; b as usize];
    for p in &mut wrong_signals {
        *p = input_itr.next().unwrap();
    }

    // filp, get good signals
    wrong_signals.sort_unstable();
    wrong_signals.push(n + 1);
    let mut signals = Vec::<u32>::with_capacity((n - b) as usize);
    let mut cur_val = 1;
    for v in wrong_signals {
        while cur_val < v {
            signals.push(cur_val);
            cur_val += 1;
        }
        cur_val = v + 1;
    }

    // two pointer
    let mut result = k;
    let mut cnt = 0u32;
    let mut lpos = 0;
    for rpos in 0..signals.len() {
        // proceed, increase
        cnt += 1;

        // move left, decrease
        while lpos <= rpos && k < (signals[rpos] - signals[lpos] + 1) {
            lpos += 1;
            cnt -= 1;
        }

        // update result
        result = result.min(k - cnt);
    }

    // print
    let mut output_buffer = String::new();
    write!(&mut output_buffer, "{}", result).unwrap();
    println!("{}", output_buffer);
}
