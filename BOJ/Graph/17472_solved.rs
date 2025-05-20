#![allow(unused)]
/*
    Crate for PS in Rust
*/
use std::collections::VecDeque;
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

type Board = Vec<Vec<i32>>;
type AdjMatrix = Vec<Vec<u32>>;
const INF: u32 = 2000_000_000;

fn bfs(board: &mut Board, start_row: usize, start_col: usize, color: i32) {
    type Point = (usize, usize);
    let mut q: VecDeque<Point> = VecDeque::new();
    let dir: [(i32, i32); 4] = [(-1, 0), (1, 0), (0, -1), (0, 1)];

    board[start_row][start_col] = color;
    q.push_back((start_row, start_col));
    while (!q.is_empty()) {
        let (cr, cc) = q.pop_front().unwrap();
        for (dr, dc) in dir {
            let nr = cr as i32 + dr;
            let nc = cc as i32 + dc;
            if 0 <= nr
                && nr < board.len() as i32
                && 0 <= nc
                && nc < board[0].len() as i32
                && board[nr as usize][nc as usize] == -1
            {
                board[nr as usize][nc as usize] = color;
                q.push_back((nr as usize, nc as usize));
            }
        }
    }
}

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<usize>);

    // input, fill board
    let row: usize = input_itr.next().unwrap();
    let col: usize = input_itr.next().unwrap();
    let mut board: Board = vec![vec![0; col]; row];
    for r in 0..row {
        for c in 0..col {
            board[r][c] = input_itr.next().unwrap() as i32;
            board[r][c] *= -1;
        }
    }

    // bfs, paint board
    let mut num_island: usize = 0;
    for r in 0..row {
        for c in 0..col {
            if board[r][c] == -1 {
                num_island += 1;
                bfs(&mut board, r, c, num_island as i32);
            }
        }
    }

    // fill adj matrix
    let mut graph: AdjMatrix = vec![vec![INF; num_island + 1]; num_island + 1];
    for r in 0..row {
        let mut prev = 0;
        let mut prev_isle = board[r][0] as usize;
        for c in 0..col {
            let cur_isle = board[r][c] as usize;
            if cur_isle == 0 {
                continue;
            }

            if prev_isle != 0 && cur_isle != prev_isle && (c - prev) > 2 {
                graph[cur_isle][prev_isle] =
                    std::cmp::min(graph[cur_isle][prev_isle], (c - prev - 1) as u32);
                graph[prev_isle][cur_isle] = graph[cur_isle][prev_isle];
            }
            prev = c;
            prev_isle = cur_isle;
        }
    }
    for c in 0..col {
        let mut prev = 0;
        let mut prev_isle = board[0][c] as usize;
        for r in 0..row {
            let cur_isle = board[r][c] as usize;
            if cur_isle == 0 {
                continue;
            }

            if prev_isle != 0 && cur_isle != prev_isle && (r - prev) > 2 {
                graph[cur_isle][prev_isle] =
                    std::cmp::min(graph[cur_isle][prev_isle], (r - prev - 1) as u32);
                graph[prev_isle][cur_isle] = graph[cur_isle][prev_isle];
            }
            prev = r;
            prev_isle = cur_isle;
        }
    }

    // get edges
    type Edge = (u32, usize, usize);
    let mut edges: Vec<Edge> = Vec::new();
    for r in 1..num_island {
        for c in (r + 1)..=num_island {
            if graph[r][c] != INF {
                edges.push((graph[r][c], r, c));
            }
        }
    }
    edges.sort_unstable();

    // kruskal algorithm
    let mut total_cost = 0;
    let mut ds: DisjointSet = DisjointSet::new(num_island + 1);
    for (cost, n1, n2) in edges {
        if ds.find(n1) != ds.find(n2) {
            ds.unite(n1, n2);
            num_island -= 1;
            total_cost += cost;
        }
    }

    // print result
    if num_island == 1 {
        println!("{total_cost}");
    } else {
        println!("-1");
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
