use std::cmp::{max};
use proconio::{input};

fn solve() {
  input! {
    n: usize,
    d: u32,
    a: [u32; n],
  }

  let max_a = *a.iter().max().unwrap_or(&(0u32));
  let mut qty = vec![0u32; (max_a + 1) as usize];
  for x in a {
    qty[x as usize] += 1;
  }

  if d == 0 {
    println!("{}", n - qty.iter().map(|&x| { if x > 0 { 1 } else { 0 } }).sum::<usize>());
    return;
  }

  let mut ret = 0;
  for x in 0..d {
    let mut take = 0;
    let mut dont = 0;
    for y in (x..max_a + 1).step_by(d as usize) {
      let new_take = dont + qty[y as usize];
      let new_dont = max(take, dont);
      take = new_take;
      dont = new_dont;
    }
    ret += max(take, dont);
  }
  println!("{}", n - (ret as usize));
}

fn main() {
  solve()
}
