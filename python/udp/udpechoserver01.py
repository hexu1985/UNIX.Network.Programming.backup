#!/usr/bin/env python
# UDP Echo Server - Chapter 3 - udpechoserver.py
import socket, traceback
import sys

host = ''                               # Bind to all interfaces
port = 51423

if len(sys.argv) >= 2 and sys.argv[1][0:2] == '-h':
    print "usage: udpechoserver01.py"
    print "       udpechoserver01.py <service>"
    print "       udpechoserver01.py <hostname> <service>"
    sys.exit(1)

if len(sys.argv) == 2:
    port = int(sys.argv[1])
elif len(sys.argv) == 3:
    host = sys.argv[1]                               # Bind to all interfaces
    port = int(sys.argv[2])

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))

while 1:
    try:
        message, address = s.recvfrom(8192)
        print "Got data from", address
        # Echo it back
        s.sendto(message, address)
    except (KeyboardInterrupt, SystemExit):
        raise
    except:
        traceback.print_exc()

