import serial
import time


def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def receive_fft_info():
    arduino = start_serial("COM5", 115200)
    dictionary_set = {}

    amp_list = []
    dict_counter = 0

    ## first while loop is to catch the start of a timestamp 
    ## because the first freq,amp pair passed from Arduino varies depending on when this script is executed
    ## this loop catches "0.0" freq, which is the first frequency given each timestamp
    while True:
        data = arduino.readline().decode('utf-8').strip()
        print("data: ", data)
        
        freq_amp_pair = data.split(",")

        ## read the next line if an empty line is detected
        if len(freq_amp_pair) == 1:
            print("-------")
            data = arduino.readline().decode('utf-8').strip()

        freq_amp_pair = data.split(",")
        freq = freq_amp_pair[0]
        amp = freq_amp_pair[1]


        if freq == "0.0":
            ## second while loop for formatting data to dictionaries and getting the max amplitude
            while True:
                data = arduino.readline().decode().strip() # "\r\n"
                # print("Second while loop data: ",data)

                freq_amp_pair = data.split(",")

                ## read the next line if an empty line is detected
                if len(freq_amp_pair) == 1:
                    print("==========================================")
                    data = arduino.readline().decode('utf-8').strip()

                # print("DATA: ", data)
                freq_amp_pair = data.split(",")
                freq = freq_amp_pair[0]
                amp = freq_amp_pair[1]

                ## put freq, amp into dictionary
                dictionary_set[freq] = float(amp)

                ## there are 64 freq,amp pairs each timestamp
                if len(dictionary_set) == 64:
                    del dictionary_set["0.0"]
                    del dictionary_set["15.6"]

                    freq_with_max_amp = max(dictionary_set, key=dictionary_set.get)
                    amp_list.append(dictionary_set[freq_with_max_amp])

                    dictionary_set.pop(freq_with_max_amp)
                    freq_with_max_amp = max(dictionary_set, key=dictionary_set.get)
                    amp_list.append(dictionary_set[freq_with_max_amp])

                    print(amp_list)

                    amp_list[0] = amp_list[0] * 0.6
                    amp_list[1] = amp_list[1] * 0.6 

                    # if amp_list[0] > 2000:
                    #     amp_list[0] * 0.3
                    # if amp_list[1] > 2000:
                    #     amp_list[1] * 0.3

                    amplitudes = str(amp_list[0]) + "," + str(amp_list[1]) + "\0"
                    print(amplitudes)
                    arduino.write(amplitudes.encode())

                    dict_counter = 0
                    dictionary_set.clear()
                    amp_list.clear()
                

receive_fft_info()
