import time
import socket

# 组播组IP和端口
mcast_group_ip = '239.255.255.250'
mcast_group_port = 1900

def sender():
    send_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)

    while True:
        message = '''M-SEARCH * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\nMAN: "ssdp:discover"\r\nMX: 3\r\nssdp:all\r\nUSER-AGENT: Goldencis Prober\r\n\r\n'''

        send_sock.sendto(message.encode(), (mcast_group_ip, mcast_group_port))
        print(f'{time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())}: message send finish')
        time.sleep(10)

if __name__ == "__main__":
    sender()