import serial
from git import commit_push
from tweet import tweet

ser = serial.Serial("COM3", 115200)

while True:
    line = ser.readline().decode('utf-8').rstrip()

    print(line)

    if line == "EARTHQUAKE":
        tweet()

    if line == "EARTHQUAKE" or line == "HIGH_TEMPERATURE":
        commit_push()

    if line == "EARTHQUAKE" or line == "HIGH_TEMPERATURE":
        break

ser.close()
