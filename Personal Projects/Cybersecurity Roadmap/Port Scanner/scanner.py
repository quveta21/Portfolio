import socket
from concurrent.futures.thread import ThreadPoolExecutor


def scan_port(ip, port):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(0.5)   # for efficiency

    # used connect_ex because it doesn't throw an exception like connect
    if s.connect_ex((ip, port)) == 0:
        print(f"Port {port} is open")

    s.close()
    return

def scanner(ip, start, finish):
    with ThreadPoolExecutor(max_workers=50) as executor:
        for port in range(start, finish + 1):
            executor.submit(scan_port, ip, port)

if __name__ == '__main__':
    scanner("104.18.96.219", 1, 1000)