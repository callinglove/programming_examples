import socket 
import time

ANY = '0.0.0.0'
MCAST_ADDR = '239.255.255.250'
MCAST_PORT = 1900

# 建立UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
# 允许端口复用
sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR, 1)
# 绑定监听多播数据包的端口
sock.bind((ANY, MCAST_PORT))
# 告诉内核这是一个多播类型的socket
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 255)
# 告诉内核把自己加入指定的多播组，组地址由第三个参数指定
status = sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP,
                        socket.inet_aton(MCAST_ADDR) + socket.inet_aton(ANY));
# 非阻塞模式
sock.setblocking(0) 
ts = time.time() 
while 1: 
    try: 
        data, addr = sock.recvfrom(1024) 
    except socket.error: 
        pass 
    else: 
        print("got data from: %s\n" % (addr,))
        print(data.decode())
