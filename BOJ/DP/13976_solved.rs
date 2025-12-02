#![allow(unused)]

/*
    BOJ 13976

    요구조건 N이 10^18으로 매우 큰 상황. 따라서 이 경우에는 점화식을 행렬로 변환한 후, 거듭제곱을 통해서 풀어야 함.
    여기서 점화식을 구하는 것이 핵심이 됨.

    내 경우에는 상황을 열 번호 k와 해당 열에 덮여진 벽돌의 상태로 구성함.
    - 0은 아무것도 덮이지 않음
    - 1은 첫 행의 하나만 덮임
    - 3은 첫 번째, 두 번째 행이 덮임
    ...

    열의 갯수가 홀수이면 타일의 크기가 2라 다 덮을 수 없음
    열의 갯수가 짝수여야만 다 덮을 수 있음

    길이 k를 덮는 상황과 k + 2를 덮는 상황을 두고 점화식 구성
    f(n,0) = f(n-1, 1) + f(n-1, 4) + f(n-2, 0) = 2 * f(n-1, 1) + f(n-2, 0) // 대칭성 적용
    f(n, 1) = f(n-1, 3)
    f(n, 2) = 0
    f(n, 3) = f(n-1, 1) + f(n, 0) = f(n-2, 3) + { 2 * f(n-2, 3) + f(n-2, 0) }
            = 3 * f(n-2, 3) + f(n-2, 0)

    최종적으로
    f(n, 0) = 2 * f(n-2, 3) + f(n-2, 0)
    f(n, 3) = 3 * f(n-2, 3) + f(n-2, 0)

    행렬로 바꾸면

    v(n) = [f(n, 0), f(n, 3)] 라 하면,
    v(n) = T(1) * v(n-2)
    v(n) = T(n / 2) * v(0)

    T(1) = [[1, 2], [1, 3]];

    v(0) = [1, 1] 이므로 T(n/2)의 0번 행의 두 성분의 합으로 구할 수 있다.

    ======================================

    일전에 피보나치 수열을 행렬로 푼 적이 있었는데, 그 때 안해봤으면 절대 못풀었을 문제....

    점화식을 풀어서 행렬로 만드는 부분에서 시간이 대략 3시간 걸렸는데, 답을 알고 풀어도 이렇게 오래 걸리다니, 참 해도 해도 발전이 없구나 도훈아.
*/

use std::fmt::Write;
use std::io::{Read, stdin};
use std::ops::Mul;

const DIV: i64 = 1000000007;

#[derive(Debug, Clone, Copy)]
struct Mat22 {
    data: [i64; 4],
}

// default trait
// do we need this?
impl Default for Mat22 {
    fn default() -> Self {
        // return identity matrix
        Mat22 { data: [1, 0, 0, 1] }
    }
}

// multiply trait
impl Mul for Mat22 {
    type Output = Mat22;
    fn mul(self, rhs: Self) -> Self::Output {
        Mat22 {
            data: [
                (self.data[0] * rhs.data[0] + self.data[1] * rhs.data[2]) % DIV,
                (self.data[0] * rhs.data[1] + self.data[1] * rhs.data[3]) % DIV,
                (self.data[2] * rhs.data[0] + self.data[3] * rhs.data[2]) % DIV,
                (self.data[2] * rhs.data[1] + self.data[3] * rhs.data[3]) % DIV,
            ],
        }
    }
}

fn main() {
    // fast input
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    // input
    let mut n = input.trim().parse::<u64>().unwrap();

    // early return
    if (n & 1) == 1 {
        // no answer, cannot cover all spaces
        println!("0");
        return;
    }

    // divide by 2
    n >>= 1;

    // fill the table of matrix
    let mut matrix_array: [Mat22; 64] = [Mat22::default(); 64];
    // set initial value, can be found from reccurrence formula
    // step size is 2,  (n, n-2)
    matrix_array[0] = Mat22 { data: [1, 2, 1, 3] };
    // multiply
    for i in 1..64 {
        matrix_array[i] = matrix_array[i - 1] * matrix_array[i - 1];
    }

    let mut result = Mat22::default();
    for i in 0..64 {
        let mask = 1u64 << i;
        if (mask & n) != 0 {
            // accumulate matrix multiplication
            result = result * matrix_array[i];
        }
    }

    // print result
    println!("{}", (result.data[0] + result.data[1]) % DIV);
}
