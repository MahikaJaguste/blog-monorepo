use std::net::TcpListener;
use tokio::io::unix::AsyncFd;

#[tokio::main]
async fn main() {
    // Spawn the accept loop onto a worker thread
    let join = tokio::spawn(async move {
        // Create a raw fd
        let listener = TcpListener::bind("127.0.0.1:9000").unwrap();
        listener.set_nonblocking(true).unwrap();

        // Register fd with Tokio's IO driver/reactor
        let async_fd = AsyncFd::new(listener).unwrap();

        loop {
            // Wait until kernel says fd is readable
            let mut guard = async_fd.readable().await.unwrap();

            // Try accepting
            match guard.get_inner().accept() {
                Ok((_stream, _addr)) => {
                    println!("Accepted connection");
                    drop(guard); // consume readiness
                }
                Err(e) if e.kind() == std::io::ErrorKind::WouldBlock => {
                    guard.clear_ready(); // re-register interest
                }
                Err(e) => panic!("unexpected error: {e}"),
            }
        }
    });

    // Main thread just waits forever or spawns other tasks
    join.await.unwrap();
}
