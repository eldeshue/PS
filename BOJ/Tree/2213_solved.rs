#![allow(unused)]
/*
    Crate for PS in Rust
*/
use std::fmt::Write;
use std::io::{Read, stdin};

// get max sum
fn dfs_get_max(
    graph: &Vec<Vec<usize>>,
    costs: &Vec<usize>,
    cache: &mut Vec<(i32, i32)>,
    cur_node: usize,
) {
    for child_node in graph[cur_node].clone() {
        if cache[child_node].0 == -1 {
            cache[child_node] = (0, 0);
            dfs_get_max(graph, costs, cache, child_node);
            cache[cur_node].0 += std::cmp::max(cache[child_node].0, cache[child_node].1);
            cache[cur_node].1 += cache[child_node].0;
        }
    }
    cache[cur_node].1 += costs[cur_node] as i32;
}

// how to back-track ?
fn dfs_find_set(
    graph: &Vec<Vec<usize>>,
    cache: &mut Vec<(i32, i32)>,
    elems: &mut Vec<usize>,
    cur_node: usize,
    cur_sum: i32,
) {
    // arrive check
    let (include_no, include_yes) = cache[cur_node];
    cache[cur_node] = (-1, -1);
    if cur_sum == include_no {
        for child in graph[cur_node].clone() {
            if cache[child].0 != -1 {
                dfs_find_set(
                    graph,
                    cache,
                    elems,
                    child,
                    std::cmp::max(cache[child].0, cache[child].1),
                );
            }
        }
    } else if cur_sum == include_yes {
        elems.push(cur_node);
        for child in graph[cur_node].clone() {
            if cache[child].0 != -1 {
                dfs_find_set(graph, cache, elems, child, cache[child].0);
            }
        }
    } else {
        unreachable!();
    }
}

fn main() {
    let mut input_buffer = String::new();
    stdin().read_to_string(&mut input_buffer).unwrap();
    let mut input_itr = input_buffer
        .split_ascii_whitespace()
        .flat_map(str::parse::<usize>);

    let n = input_itr.next().unwrap() as usize;
    let mut costs: Vec<usize> = vec![0; n + 1];
    for i in 1..=n {
        costs[i] = input_itr.next().unwrap();
    }
    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); n + 1];
    loop {
        let n1 = match input_itr.next() {
            Some(val) => val,
            None => break,
        };
        let n2 = input_itr.next().unwrap();
        graph[n1].push(n2);
        graph[n2].push(n1);
    }

    // dp, dfs
    let mut result_buffer = String::new();
    let mut cache: Vec<(i32, i32)> = vec![(-1, -1); (n + 1)];
    cache[1] = (0, 0);
    dfs_get_max(&graph, &costs, &mut cache, 1);

    // back track
    let max_cost = std::cmp::max(cache[1].0, cache[1].1);
    let mut independent_set: Vec<usize> = Vec::new();
    dfs_find_set(&graph, &mut cache, &mut independent_set, 1, max_cost);
	independent_set.sort_unstable();

    // print
    writeln!(&mut result_buffer, "{}", max_cost);
    for node in independent_set {
        write!(&mut result_buffer, "{} ", node);
    }
    print!("{result_buffer}");
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
