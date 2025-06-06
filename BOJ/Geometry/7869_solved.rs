#![allow(unused)]

use std::fmt::Write;
use std::io::{Read, stdin};

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input_itr = input
        .split_ascii_whitespace()
        .into_iter()
        .flat_map(str::parse::<f64>);

    // input
    let x1 = input_itr.next().unwrap();
    let y1 = input_itr.next().unwrap();
    let r1 = input_itr.next().unwrap();
    let x2 = input_itr.next().unwrap();
    let y2 = input_itr.next().unwrap();
    let r2 = input_itr.next().unwrap();

    let d = f64::sqrt(f64::powi(x1 - x2, 2) + f64::powi(y1 - y2, 2));

	// no common area
    if ((r1 + r2) <= d) {
        println!("0.000");
        return;
    }

	// perfect overlap
    if (d + f64::min(r1, r2) <= f64::max(r1, r2)) {
        println!(
            "{:.3}",
            std::f64::consts::PI * f64::powi(f64::min(r1, r2), 2)
        );
        return;
    }

	// partial overlap
    // calculate
    let get_angle = |a: f64, b: f64, c: f64| {
        ((f64::powi(a, 2) + f64::powi(b, 2) - f64::powi(c, 2)) / (2.0f64 * a * b)).acos()
    };
    let theta1 = get_angle(r1, d, r2);
    let theta2 = get_angle(r2, d, r1);

    // heron
    let s = (r1 + r2 + d) / 2.0f64;
    let area = f64::sqrt(s * (s - r1) * (s - r2) * (s - d));
    let result = f64::powi(r1, 2) * theta1 + f64::powi(r2, 2) * theta2 - 2.0 * area;
    println!("{:.3}", result);
}
