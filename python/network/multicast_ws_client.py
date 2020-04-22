import socket 
import time

ANY = '0.0.0.0'
SENDERPORT=3703
MCAST_ADDR = '239.255.255.250'
MCAST_PORT = 3702
MESSAGE = '<soap:Envelope xmlns:soap="http://www.w3.org/2003/05/soap-envelope" ' \
          'xmlns:wsa="http://schemas.xmlsoap.org/ws/2004/08/addressing" ' \
          'xmlns:tns="http://schemas.xmlsoap.org/ws/2005/04/discovery">' \
          '<soap:Header>' \
          '<wsa:Action>http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe</wsa:Action>' \
          '<wsa:MessageID>urn:uuid:235b4a24-fa30-4550-b355-d8cbc9901b8a</wsa:MessageID>' \
          '<wsa:To>urn:schemas-xmlsoap-org:ws:2005:04:discovery</wsa:To>' \
          '</soap:Header><soap:Body><tns:Probe/></soap:Body></soap:Envelope>'

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
        response, peer_addr = sock.recvfrom(4096)
        print("from ", peer_addr, "\n")
        print(response.decode())
    except socket.timeout:
        break
