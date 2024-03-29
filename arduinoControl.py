import serial
import time

def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def control_motor():
    arduino = start_serial("COM5", 9600)
    
    while True:
        data = arduino.readline().decode('latin-1').strip() 
        print(data)

        print("Enter: ")
        var = input()
        if var == "1":
            # arduino.write("1".encode('utf-8'))
            arduino.write("1".encode())
            # arduino.write(b"1")
        elif var == "0":
            arduino.write("0".encode())
            # arduino.write(b"0")
        else:
            arduino.write("0".encode())
            # arduino.write(b"0")

def check_print():
    arduino = start_serial("COM5", 9600)
    
    while True:
        data = arduino.readline().decode().strip() 
        print(data)

control_motor()