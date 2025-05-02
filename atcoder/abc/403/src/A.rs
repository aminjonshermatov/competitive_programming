use proconio::input;

fn solve() {
  input! {
    n: usize,
    a: [usize; n],
  }

  let mut ans = 0;
  for i in 0..n {
    if i % 2 == 0 {
      ans += a[i]
    }
  }
  println!("{}", ans)
}

fn main() {
  solve()
}
