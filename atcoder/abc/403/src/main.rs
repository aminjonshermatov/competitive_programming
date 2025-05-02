use proconio::{input};

fn solve() {
  input! { q: usize, }

  for _ in 0..q {
    input! { t: usize, s: String, }
    if t == 1 {
      // x.add(s)
    } else if t == 2 {
      // y.add(s)
    } else {
      assert!(false)
    }
  }
}

mod rolling_hash {

  pub trait Modulus {
    const VALUE: u32;
  }

  pub trait MonoidModulo<T, M: Modulus> {
  }

  pub enum Mod1000000007 {}
  impl Modulus for Mod1000000007 {
    const VALUE: u32 = 1000000007;
  }

  pub enum Mod1000000009 {}
  impl Modulus for Mod1000000009 {
    const VALUE: u32 = 1000000007;
  }

  struct RollingHash {
    hashes007: Vec<u64>,
    hashes009: Vec<u64>,
  }

  impl RollingHash {
    fn new(s: &String) -> RollingHash {
      fn build<M: Modulus>(&s: &String) -> Vec<u64> {
        let mut hashes = vec![0u64; s.len() + 1];
        for i in 0..s.len() {
          hashes[i + 1] = (hashes[i] + s[i]) % M::VALUE;
        }
        hashes
      }
      RollingHash {
        hashes007: build::<Mod1000000007>(s),
        hashes009: build::<Mod1000000009>(s),
      }
    }

    fn add<M: Modulus>(a: u64, b: u64) -> u64 {
      let mut ret = a + b
    }
  }

} // namespace rolling_hash

fn main() {
  solve()
}
