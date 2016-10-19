#!/usr/bin/python

import datetime
import socket

LISTENPORT=3141

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('0.0.0.0', LISTENPORT))

while True:
  data, addr = sock.recvfrom(1024)
  print '%s: %s' % (datetime.datetime.now(), data)
  with open('temperature.log', 'a') as f:
    f.write('%s,%s\n' % (datetime.datetime.now(), data))
