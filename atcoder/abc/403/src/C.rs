use std::collections::BTreeSet;
use proconio::{input, marker::Chars};

fn solve() {
  input! {
    n: usize,
    m: usize,
    q: usize,
  }

  let mut can_any = vec![false; n];
  let mut granted = vec![BTreeSet::new(); n];
  for _ in 0..q {
    input! {
      cmd: usize,
      x: usize,
    }
    match cmd {
      1 => {
        input! {
          y: usize,
        }
        granted[x - 1].insert(y - 1);
      },
      2 => {
        can_any[x - 1] = true
      },
      3 => {
        input! {
          y: usize,
        }
        println!("{}", if can_any[x - 1] || granted[x - 1].contains(&(y - 1)) { "Yes" } else { "No" })
      }
      _ => {
        println!("fuck")
      }
    }
  }
}

fn main() {
  solve()
}
