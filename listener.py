import socket

# Define the host and port to listen on
HOST = '0.0.0.0'  # Listen on all available network interfaces
PORT = 8080       # Port to listen on (must match the IRC server and client)

def start_listener():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as listener:
        listener.bind((HOST, PORT))
        listener.listen()

        print(f"Listening on {HOST}:{PORT}...")

        # Accept incoming connections
        conn, addr = listener.accept()
        print(f"Connected by {addr}")

        try:
            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received: {data.decode('utf-8', 'ignore')}")
        except KeyboardInterrupt:
            print("Listener terminated by user.")

if __name__ == "__main__":
    start_listener()