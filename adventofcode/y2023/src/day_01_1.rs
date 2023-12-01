use std::io::stdin;

fn main() {
    println!("{:?}", stdin().lines().map(|line| -> u32 {
        let digits: Vec<_> = line.unwrap().chars().filter(|c| c.is_digit(10)).map(|c| c.to_digit(10).unwrap()).collect();
        return digits.first().unwrap_or(&0) * 10 + digits.last().unwrap_or(&0);
    }).into_iter().reduce(|acc, el| acc + el).unwrap_or(0))
}
