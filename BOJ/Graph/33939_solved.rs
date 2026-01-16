#![allow(unused)]

/*
    BOJ 33939

    z기준, 부모 노드에 대해서 완전탐색하여 연결 관계 있는지 체크
    결국 모든 엣지에 대해서 쌍으로 탐색하게 되므로, M^2
*/

use std::io::{Read, Write, stdin, stdout};
use std::vec::Vec;

fn main() {
    // fast IO
    let stdout = stdout();
    let mut output = std::io::BufWriter::new(stdout.lock());

    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_ascii_whitespace();

    // input
    let n = iter.next().unwrap().parse::<u32>().unwrap(); // row
    let m = iter.next().unwrap().parse::<u32>().unwrap();
    let mut rev_graph = vec![Vec::<u32>::new(); (n + 1) as usize];
    let mut is_connected = vec![vec![false; (n + 1) as usize]; (n + 1) as usize];
    for i in 0..m {
        let u = iter.next().unwrap().parse::<usize>().unwrap();
        let v = iter.next().unwrap().parse::<usize>().unwrap();

        is_connected[u][v] = true;
        is_connected[v][u] = true;
        rev_graph[v].push(u as u32);
    }

    // solve
    // total m^2
    let mut result = 0u32;
    for z in 1..=n as usize {
        for i in 0..(rev_graph[z].len() as i32 - 1) as i32 {
            let x = rev_graph[z][i as usize] as usize;
            for j in (i + 1) as usize..rev_graph[z].len() {
                let y = rev_graph[z][j] as usize;
                if !is_connected[x][y] {
                    result += 1;
                }
            }
        }
    }

    // print
    write!(&mut output, "{}", result);
}
