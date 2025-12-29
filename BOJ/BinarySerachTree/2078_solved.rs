/*
    BOJ 2078

    다음의 룰에 의해서 만들어지는 무한한 2진트리에서
    한 노드가 주어지고, root에서 해당 노드까지 이동하는 최단 경로를 구하는 문제.

    ----

    root 1,1에서 시작

    현재 노드가 a,b이면
    왼쪽 노드는 a+b, b
    오른쪽 노드는 a, a+b

    ---

    문제의 요점은 보다 큰 노드가 직전 이동 방향임.
    따라서, 더 작은 값으로 빼주면 이전 노드의 좌표가 나옴.

    왜 계속 빼줘야 함? 빼기를 나눗셈으로 가속할 수 있음.

    ---

    뭔가 발상이 유클리드 알고리즘같음.
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
    let mut a = input_itr.next().unwrap();
    let mut b = input_itr.next().unwrap();

    // kind of euclidian algorithm
    let mut l = 0;
    let mut r = 0;
    while a > 0 && b > 0 {
        // divide each other
        if a > b {
            l += a / b;
            a %= b;
        } else if b > a {
            r += b / a;
            b %= a;
        } else {
            break;
        }
    }

    // root is 1,1
    if a == 1 {
        r -= 1;
    } else if b == 1 {
        l -= 1;
    }

    // print
    let mut output_buffer = String::new();
    write!(&mut output_buffer, "{} {}", l, r).unwrap();
    println!("{}", output_buffer);
}
