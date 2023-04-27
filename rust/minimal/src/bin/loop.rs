//! Binary compiled to a module printing the output of a counter

#![no_std]
#![no_main]
use core::panic::PanicInfo;
//#![feature(core_panic)]
//use std::alloc::System;
//
//#[global_allocator]
//static A: System = System;

//use std::time::Duration;
//use std::thread;

extern "C" {
	//add any externs, as from drivers, here
    fn default_printf(buff: &[u8; 6], size: isize) -> i32;
}

#[no_mangle]
pub extern "C" fn main(_argc: isize, _argv: *const *const u8) -> isize {
    let mut counter = 0;

    loop {
      unsafe{
        default_printf(b"Count!",7);
        //printf(b"Counter: {counter}\n\0".as_ptr(),counter as u32);
      }
      counter += 1;
      // thread::sleep(Duration::from_secs(1));
    }
}


#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
