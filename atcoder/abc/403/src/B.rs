use proconio::{input, marker::Chars};

fn solve() {
  input! {
    t: Chars,
    u: Chars,
  }

  let n = t.len();
  let m = u.len();
  for i in 0..n-m+1 {
    let mut used = 0_usize;
    let mut ok = true;
    for j in 0..m {
      if t[i + j] == u[j] {
        continue
      }
      if t[i + j] == '?' && used < 4 {
        used += 1;
        continue
      }
      ok = false;
      break
    }
    if ok {
      println!("Yes");
      return
    }
  }

  println!("No")
}

fn main() {
  solve()
}
