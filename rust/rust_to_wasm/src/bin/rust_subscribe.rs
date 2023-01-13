//! Binary compiled to a module which subscribes to the topic '/ch/rust' and prints out the messages it receives there.

use std::time::Duration;

use rust_to_wasm::{channel_open_read, wait_for_message};

fn main() {
    let channel_name = "/ch/rust".to_owned();
    let channel_handle = channel_open_read(channel_name);

    loop {
        let message = wait_for_message(channel_handle, Duration::from_secs(5));
        println!("I heard: {message}");
    }
}
