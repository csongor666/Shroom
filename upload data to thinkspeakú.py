#! python
# -*- coding: cp1250 -*-
import serial
import httplib2
import time

ser = serial.Serial('COM3', 9600)
temp = ''
hum = ''
a = 0
b = 0
x = 0
while True:
    ch = ser.read(1)
    if ch == '\n':
        print temp
        a,b = temp.split(";")
        print a
        print b
        if a == '':
            a = prea
            print 'a nothing'
            print a
        else:
            a = float(a)
            print 'None else a'
            print a
        if b == '':
            b = preb
        else:
            b = float(b)
        if a is not None:
            a = float(a)
            print 'not None else a'
            print a
        if b is not None:
            b = float(b)
        if a == 0.0:
            a = prea
            print 'a=0'
            print a
        if b == 0.0:
            b = prea
        if x == 1 and a != 0.0:
            prea = a
            preb = b
            print prea
            print preb
        conn = httplib2.Http()
        conn.request("http://api.thingspeak.com/update?key=***********&field1=%f&field2=%f"%(a,b))
        temp = ''
        x = 1
    else:
        temp +=ch
