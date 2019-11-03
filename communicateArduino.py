import serial
import time


def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def control_LED():
    arduino = start_serial("COM5", 9600)

    while True:
        # data = arduino.readline().decode("latin-1") 
        print("---")
        data = arduino.readline().decode().strip("\r\n")
        # print(data)
        # print("Enter: ")
        # var = input()
        # if var == "1":
        try:
            if int(data) >= 500:
                # print("SUCCESS")
                print(data)
                arduino.write("1".encode())
            # elif var == "0":
            elif int(data) < 500: 
                # print("SUCCESS")
                print(data)
                arduino.write("0".encode())
        except ValueError:
            print("FAIL")
            pass

control_LED()