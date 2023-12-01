use std::io::stdin;

fn main() {
    let digs = Vec::from([
        (Vec::from("one"), 1),
        (Vec::from("two"), 2),
        (Vec::from("three"), 3),
        (Vec::from("four"), 4),
        (Vec::from("five"), 5),
        (Vec::from("six"), 6),
        (Vec::from("seven"), 7),
        (Vec::from("eight"), 8),
        (Vec::from("nine"), 9),
    ]);

    let mut sum = 0u32;
    for line in stdin().lines() {
        let chars: Vec<char> = line.unwrap_or(String::new()).chars().collect();
        let mut loc: Vec<u32> = vec![];
        for i in 0..chars.len() {
            if chars[i].is_digit(10) {
                loc.push(chars[i].to_digit(10).unwrap_or(0));
            } else {
                for it in 0..digs.len() {
                    if i + digs[it].0.len() - 1 < chars.len() && (0..digs[it].0.len()).all(|j| chars[i + j] as u8 == digs[it].0[j]) {
                        loc.push(digs[it].1);
                    }
                }
            }
        }
        sum += loc.first().unwrap_or(&0) * 10 + loc.last().unwrap_or(&0);
    }
    println!("{}", sum)
}
