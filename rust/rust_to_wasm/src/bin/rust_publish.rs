//! Binary compiled to a module publishing a string on the 'ch/rust' topic

use std::time::Duration;
use std::thread;

use rust_to_wasm::{channel_open_write, channel_write};

fn main(){
    let mut counter = 0;
    let channel_name = "/ch/rust".to_owned();
    let channel_handle = channel_open_write(channel_name);

    loop {
        let message = format!("Message {counter}");
        channel_write(channel_handle, message);
        counter += 1;
        println!("I wrote: {counter}");
        thread::sleep(Duration::from_secs(1));
    }
}