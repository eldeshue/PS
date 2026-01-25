/*
    BOJ 18186

    기본적으로 181815와 동일한 문제임.

    차이가 있다면 A와 N의 범위가 10^6으로 확장
    각 묶음의 비용이 b, b + c, b + 2 * c로 확장된 것이다

    문제를 확장하는 과정에서
    총 비용 = (b - c) * (묶음의 수) + c * (총 블럭의 수)

    가 되는데, 여기서 b-c가 0 이하가 되면 단순 1 크기 블럭으로 채우는 것이 최적해가 된다.
*/
use std::io::{Read, Write, stdin, stdout};

fn main() {
    // fast IO
    let stdout = stdout();
    let mut output = std::io::BufWriter::new(stdout.lock());

    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut iter = input.split_ascii_whitespace();

    // input
    let n = iter.next().unwrap().parse::<usize>().unwrap(); // row
    let b = iter.next().unwrap().parse::<u64>().unwrap();
    let c = iter.next().unwrap().parse::<u64>().unwrap();
    let mut total_block_cnt = 0u64; // 주어진 조건에 의해서 invariant임. 고정값.
    let mut a = vec![0u64; n];
    for a in &mut a {
        *a = iter.next().unwrap().parse::<u64>().unwrap();
        total_block_cnt += *a;
    }

    // no need to make partition, single block is the best choice
    if b <= c {
        write!(&mut output, "{}", b * total_block_cnt);
        return;
    }

    // greedy
    let mut total_partition_cnt = 0u64; // 우리가 최소화 시켜야 하는 값. 최적화 대상.
    let mut single_partition_cnt = 0u64;
    let mut double_partition_cnt = 0u64;
    for mut cur_block_cnt in a {
        if cur_block_cnt == 0 {
            total_partition_cnt += single_partition_cnt + double_partition_cnt;
            single_partition_cnt = 0;
            double_partition_cnt = 0;
        } else {
            // cur_block_cnt는 기존의 1짜리 partition과 결합할 수 있음
            // 최대한 next double을 많이 남겨줘야 함, 이 것이 single partition을 최소화 하는 방법
            let next_double_partition_cnt = single_partition_cnt.min(cur_block_cnt);
            let left_single_partition_cnt = single_partition_cnt - next_double_partition_cnt;
            cur_block_cnt -= next_double_partition_cnt;

            // 결합되지 못하고 남은 single partition은 total로 결합
            total_partition_cnt += left_single_partition_cnt;

            // 남은 cur_block_cnt는 기존의 2짜리 partition과 결합할 수 있음
            cur_block_cnt -= double_partition_cnt.min(cur_block_cnt);

            // 기존의 남은 2짜리는 3으로 결합되건 2로 남건 추가될 partition의 개수는 불변임.
            // 2개짜리로 남건, 3개짜리로 남건 어쨋건 여기서 끝
            total_partition_cnt += double_partition_cnt;

            // update next
            double_partition_cnt = next_double_partition_cnt;
            single_partition_cnt = cur_block_cnt;
        }
    }
    total_partition_cnt += single_partition_cnt + double_partition_cnt;

    // print
    write!(
        &mut output,
        "{}",
        (b - c) * total_partition_cnt + c * total_block_cnt
    );
}
