use std::ffi::{c_char, CStr};
use std::io::Read;
use std::net::{TcpListener, TcpStream};

fn handle_client(mut stream: TcpStream) {
    loop {
        let mut a: String = String::new();
        stream.read_to_string(&mut a).expect("No message");
        if a.len() == 0 {
            break;
        }
        println!("Message: {}", a);
    }
}

#[no_mangle]
pub extern "C" fn rs_network(raw_bind: *const c_char) {
    let bind: &str =
        unsafe { &String::from_utf8_lossy(CStr::from_ptr(raw_bind).to_bytes()).to_string() };

    let listener = TcpListener::bind(bind).expect(&format!("Unable to bind to {}.", bind));

    for stream in listener.incoming() {
        handle_client(stream.expect("Stream broke."));
    }
}