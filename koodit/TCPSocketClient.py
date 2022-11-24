import socket
import sys
import pandas as pd
client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

server_address = ('172.20.241.9', 20000)
client_socket.connect(server_address)

try:
    client_socket.sendall('59\n'.encode())
except socket.error as e: 
    print ("Socket error: %s" %str(e)) 
except Exception as e: 
    print ("Other exception: %s" %str(e)) 

reply = bytearray()
n = 15000
while len(reply) < n:
    packet = client_socket.recv(n - len(reply))
    if not packet: 
        break
    reply.extend(packet)


client_socket.close() 

data = reply.decode()

with open('data.csv', 'w') as f:
    f.write(data) 

df = pd.read_csv('data.csv', delim_whitespace=True, header=None)
print(df)
df.to_csv('data.csv')