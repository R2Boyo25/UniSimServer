use rust_raknet::{RaknetListener, RaknetSocket};
use std::ffi::{c_char, CStr};
use std::net::{IpAddr, Ipv4Addr, SocketAddr};
use tokio;

extern "C" {
    static GAME_RUN: bool;
}

async fn handle_client(socket: RaknetSocket) {
    println!("{} from {}", "New connection", socket.peer_addr().unwrap());

    loop {
        let buf = socket.recv().await.unwrap();
        println!("{:?}", buf);
    }
}

fn serve(bind: &str) {
    let rt = tokio::runtime::Runtime::new().unwrap();

    rt.block_on(async {
        let mut listener = RaknetListener::bind(&SocketAddr::new(
            IpAddr::V4(Ipv4Addr::new(0, 0, 0, 0)),
            6028,
        ))
        .await
        .unwrap();

        listener.listen().await;

        println!("{}", unsafe { GAME_RUN });

        while !(unsafe { GAME_RUN }) {
            handle_client(listener.accept().await.unwrap()).await;
        }

        listener.close().await.unwrap();
    });
}

#[no_mangle]
pub extern "C" fn rs_network(raw_bind: *const c_char) {
    let bind: &str =
        unsafe { &String::from_utf8_lossy(CStr::from_ptr(raw_bind).to_bytes()).to_string() };

    serve(bind);
}
