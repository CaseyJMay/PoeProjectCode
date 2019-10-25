import serial
import time


# def start_serial(com,baud):
#     serialPort = serial.Serial(com, baud, timeout=1)
#     return serialPort

def control_LED():
    arduino = serial.Serial("COM5", 9600, timeout=1)

    while True:
        data = arduino.readline().decode() 
        print(data)
        print("Enter: ")
        var = input()
        if var == "1":
            arduino.write("1".encode())
        elif var == 0:
            arduino.write("0".encode())

control_motor()