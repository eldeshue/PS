/*
    BOJ 181815

    이 문제는 타일링 문제임. 근데, 타일로 덮을 공간이 수직 방향으로 조정 가능한
    타일링 문제임

    블록의 개수를 size라 하면, 한 묶음partition의 비용은 다음과 같음.

    cost(size) = 1 + 2 * size

    이를 바탕으로 전체 비용을 생각하면 다음과 같음.

    total_cost(size) = 1 * total_partition_cnt + 2 * total_block_cnt

    전체 블록의 갯수는 정해져 있으므로, 총 cost의 최소화를 위해서
    partition의 갯수를 줄이는게 답임

    즉, 최대한 적은 수로 분할하는게 문제의 목표.

    ========================

    처음에는 dp 풀이를 고려함

    라면의 개수를 구성하는 A 배열의 인덱스 i에 대해서
    각 step에서 길이 1짜리 타일과 2짜리 타일의 수를 상태로 삼고,
    그에 따른 최소 타일 갯수를 고민함.

    -> 하지만 계산량의 이슈로 인해서 주어진 조건에서 실행이 불가능하다 판단.

    타일 갯수에 따른 상태 컨셉만 가지고 여러 케이스에 대입하면서 경향성을 찾음,

    =========================

    최종 풀이는 다음과 같은 greedy 솔루션임.

    타일의 수를 줄이기 위해서는 1 혹은 2짜리 타일을 확장하여 2혹은 3으로 만들어야 함.
    따라서 i번째 경계에 존재하는 길이 1 혹은 2인 타일의 갯수를 저장하여 이를 활용함.

    즉, 새롭게 만나는 Ai의 블록을 이전까지 만든 1짜리 혹은 2짜리에 투자하여 확장이 필요.
    병합이 안되고 남은 것은 1짜리 partition이 되어 다음으로 넘어감.

    이 풀이의 핵심은 타일 수 최소화를 위해 2개 짜리를 우선해서 만든다는 것임.

    ======================================

    왜 2개를 우선해서 만드는가? 3짜리는 확장이 불가능 하지만, 2짜리는 추후 확장 가능함.
    즉, 새롭게 얻는 Ai개의 블록을 최대한 병합시켜야 하는데, 추후의 병합 가능성을
    고려하여 기존 1개짜리에 병합하는게 이득이 됨.

    어차피 Ai를 소모해야 하는데, 미래에 병합 가능성을 남기는게 이득이 되는 것.
    기존에 존재하는 길이 1 혹은 2짜리 파티션은 이미 바꿀 수 없음. 어차피 지불할 비용임.

    즉, 길이 2짜리 파티션을 우선해서 만드는 것이 항상 이득이 되는 것.
    길이 3을 우선해서 만들면 나중에 확장 가능성을 포기하게 됨. 3은 추가 확장이 불가능함.

    3을 우선해서 만든다고 당장에 파티션이 덜생기지 않음. 이미 만든 파티션에 합류할 뿐임.
    하지만, 추후 확장 가능성이 없으므로, 손해 가능성은 커지는 것.

    -> 3을 우선 생성했을 때, 더 이득이 있는지 고려했어야 함.
    -> 즉, 미래의 기회비용을 고려하는 문제인 것.
    -> 최적해의 기초 증명법 중 교환증명(exchange argument)를 연구할 필요 있음.
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
    let mut a = vec![0u32; n];
    for a in &mut a {
        *a = iter.next().unwrap().parse::<u32>().unwrap();
    }

    let b = 1;
    let c = 2;

    // greedy
    let mut total_block_cnt = 0u32; // 주어진 조건에 의해서 invariant임. 고정값.
    let mut total_partition_cnt = 0u32; // 우리가 최소화 시켜야 하는 값. 최적화 대상.
    let mut single_partition_cnt = 0u32;
    let mut double_partition_cnt = 0u32;
    for mut cur_block_cnt in a {
        if cur_block_cnt == 0 {
            total_partition_cnt += single_partition_cnt + double_partition_cnt;
            single_partition_cnt = 0;
            double_partition_cnt = 0;
        } else {
            total_block_cnt += cur_block_cnt;

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
        b * total_partition_cnt + c * total_block_cnt
    );
}
