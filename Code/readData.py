import serial
import subprocess
import struct

ser = serial.Serial(port="COM3", baudrate=9600, bytesize=serial.EIGHTBITS, stopbits=serial.STOPBITS_ONE, timeout=1)
line = 0
while (line != b"start\r\n"):
    line = ser.readline()
fileOut = open("readSensorData.csv", "wb")
fileOut.close()
while(1):
    line = ser.read(130)
    if (len(line) > 0):
        a = 0
        for i in range(0, len(line)):
            if (line[i] == ord(b",")):
                a += 1
                if (a == 7):
                    line = line[:i]
                    break
        fileOut = open("readSensorData.csv", "ab")
        fileOut.write(line + b"\n")
        fileOut.close()
ser.close()