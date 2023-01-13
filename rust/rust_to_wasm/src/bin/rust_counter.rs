//! Binary compiled to a module printing the output of a counter

use std::time::Duration;
use std::thread;

fn main(){
    let mut counter = 0;

    loop {
        println!("Counter: {counter}\n");
        counter += 1;
        thread::sleep(Duration::from_secs(1));
    }
}