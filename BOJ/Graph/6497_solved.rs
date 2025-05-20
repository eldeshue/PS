#![allow(unused)]
/*
    Crate for PS in Rust
*/
use std::fmt::Write;
use std::io::{Read, stdin};

/*
    solution :
*/
struct DisjointSet {
    parents: Vec<i32>,
}

impl DisjointSet {
    pub fn new(size: usize) -> Self {
        DisjointSet {
            parents: vec![-1; size],
        }
    }

    pub fn find(&mut self, node: usize) -> usize {
        if self.parents[node] < 0 {
            return node;
        }
        self.parents[node] = self.find(self.parents[node] as usize) as i32;
        self.parents[node] as usize
    }

    pub fn unite(&mut self, node1: usize, node2: usize) {
        let node1 = self.find(node1);
        let node2 = self.find(node2);

        if node1 == node2 {
            return;
        }

        if self.parents[node1] < self.parents[node2] {
            self.parents[node1] += self.parents[node2];
            self.parents[node2] = node1 as i32;
        } else {
            self.parents[node2] += self.parents[node1];
            self.parents[node1] = node2 as i32;
        }
    }
}

fn main() {
    let mut input_buffer = String::new();
    let mut output_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<usize>);
    loop {
        let m = input_itr.next().unwrap();
        let n = input_itr.next().unwrap();

        if (m == 0 && n == 0) {
            break;
        }

        let mut total_cost: u32 = 0;
        let mut edges: Vec<(u32, usize, usize)> = vec![(0, 0, 0); n];
        for i in 0..n {
            let x = input_itr.next().unwrap();
            let y = input_itr.next().unwrap();
            let z = input_itr.next().unwrap() as u32;
            edges[i] = (z, x, y);
            total_cost += z;
        }
        edges.sort_unstable();

        let mut uf = DisjointSet::new(m);
        let mut mst_cost: u32 = 0;
        for (z, x, y) in edges {
            if uf.find(x) != uf.find(y) {
                uf.unite(x, y);
                mst_cost += z;
            }
        }
        writeln!(&mut output_buffer, "{}", total_cost - mst_cost);
    }
    print!("{output_buffer}");
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
