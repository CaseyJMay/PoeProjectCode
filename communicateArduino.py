import serial
import time


def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def control_motor():
    arduino = start_serial("COM5", 115200)

    while True:
        # print("---")
        # data = arduino.readline().decode().strip("\r\n")
        data = arduino.readline().decode('utf-8').strip("\r\n")
        print(data)
        # print("Enter: ")
        # var = input()
        # print(data)
        # arduino.write("h".encode())


        # for i in range(10):
            # if i%2 == 0:
            #     string = "\n1,2\n"
            #     arduino.write(string.encode())
            # if i%2 == 1:
            #     string = "\n3,4\n"
            #     arduino.write(string.encode())

        # string = "1.1,2.2\0"
        # arduino.write(var.encode())
        # string = "3,4\0"
        # arduino.write(string.encode())

        # arduino.write(string.encode())
        # arduino.write("ih".encode())
        # try:
        #     if int(data) >= 450:
        #         # print("SUCCESS")
        #         print(data)
        #         arduino.write("274.6, 87.8, 58.0, 44.1, 46.7".encode())
        #     elif int(data) < 450: 
        #         # print("SUCCESS")
        #         print(data)
        #         arduino.write("274.6, 87.8, 58.0, 44.1, 46.7".encode())
        # except ValueError:
        #     print("FAIL")
        #     pass

control_motor()