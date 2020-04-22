import socket 
import time

ANY = '0.0.0.0'
SENDERPORT=1901
MCAST_ADDR = '239.255.255.250'
MCAST_PORT = 1900
MESSAGE = 'M-SEARCH * HTTP/1.1\r\n' \
          'HOST: 239.255.255.250:1900\r\n' \
          'MAN: "ssdp:discover"\r\n' \
          'MX: 3\r\n' \
          'ST: ssdp:all\r\n\r\n'

# 建立UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
# 绑定发送端口
sock.bind((ANY, SENDERPORT))
# 设置使用多播发送
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 255)
# 设置超时间
sock.settimeout(5)

# 将'ssdp:discover消息'发送到多播地址的指定端口，属于这个多播组的成员都可以收到这个信息
ret = sock.sendto(MESSAGE.encode(), (MCAST_ADDR, MCAST_PORT));
print("send to %s:%d %d bytes: \n%s" %(MCAST_ADDR, MCAST_PORT, ret, MESSAGE))
while True:
    try:
        response, peer_addr = sock.recvfrom(1024)
        print("from ", peer_addr, "\n")
        print(response.decode())
    except socket.timeout:
        break
