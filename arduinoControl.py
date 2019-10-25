import serial
import time

def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def control_motor():
    arduino = start_serial("COM5", 9600)
    
    while True:
        data = arduino.readline().decode() 
        print(data)
        print("Enter: ")
        var = input()
        if var == "1":
            arduino.write("1".encode())
        elif var == "0":
            arduino.write("0".encode())
        else:
            arduino.write("0".encode())

control_motor()