//! Offers safe wrappers for the C functions used for the interaction between the modules and the Silverline runtime.

use std::{ffi::{CString, CStr}, time::Duration};

const BUFFER_LEN : usize = 8192;

extern "C" {
    fn ch_open(char_name: *const i8, flags: i32, mode: i32) -> i32;
    fn ch_write_msg(channel_id: i32, buffer: *const i8, size: i32) -> i32;
    fn ch_read_msg(channel_id: i32, buffer: *mut i8, size: i32) -> i32;
    fn ch_poll(channels: *const i32, channel_num: i32, timeout_ms: i32) -> i32;
}

#[derive(Clone, Copy)]
pub struct ChannelHandle{
    channel_id: i32
}

///
/// Opens the channel for reading and returns the channel handle.
/// 
/// channel_name: the name of the channel
/// 
/// RETURNS: the ChannelHandle which is used for reading from the channel
///
pub fn channel_open_read(channel_name: String) -> ChannelHandle {
    channel_open(channel_name, 0)
}

///
/// Opens the channel for writing and returns the channel handle.
/// 
/// channel_name: the name of the channel
/// 
/// RETURNS: the ChannelHandle which is used for writing to the channel
///
pub fn channel_open_write(channel_name: String) -> ChannelHandle {
    channel_open(channel_name, 1)
}

///
/// Opens the channel for reading and writing and returns the channel handle.
/// 
/// channel_name: the name of the channel
/// 
/// RETURNS: the ChannelHandle which is used for reading from and writing to the channel
///
pub fn channel_open_read_write(channel_name: String) -> ChannelHandle {
    channel_open(channel_name, 2)
}

fn channel_open(channel_name: String, open_flag: i32) -> ChannelHandle{
    let channel_id;
    unsafe {
        channel_id = ch_open(to_c_ptr(channel_name).as_ptr(), open_flag, 0);
    }
    ChannelHandle{channel_id}
}

///
/// Polls the specified channel for a message and returns it as String
/// 
/// channel: the handle to the channel to read from
/// timeout: the timeout for polling
/// 
/// RETURNS: the message read from the channel as String
/// 
pub fn wait_for_message(channel: ChannelHandle, timeout: Duration) -> String{
    let channel_id = channel.channel_id;
    let mut rust_vec : Vec<u8> = vec![0; BUFFER_LEN];
    let c_buffer = rust_vec.as_mut_ptr() as *mut i8;
    let channel_ptr = &channel_id as *const i32;
    let timeout_ms = timeout.as_millis() as i32;
    let c_str;

    unsafe{
        ch_poll(channel_ptr, 1, timeout_ms);
        ch_read_msg(channel_id, c_buffer, BUFFER_LEN as i32);
        c_str = CStr::from_ptr(c_buffer);
    }
    let rust_str : &str = c_str.to_str().expect("Error creating string slice from c buffer.");
    rust_str.to_owned()        
}

///
/// Writes the given message to the given channel
/// 
/// channel: the handle to the channel to write to
/// message: the message which shall be written
/// 
pub fn channel_write(channel: ChannelHandle, message: String) {
    let channel_id = channel.channel_id;
    let length = message.len() as i32;
    unsafe {
        ch_write_msg(channel_id, to_c_ptr(message).as_ptr(), length);
    }
}

fn to_c_ptr(rust_string: String) -> CString {
    CString::new(rust_string).unwrap()
}
