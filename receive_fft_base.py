import serial
import time


def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def receive_fft_info():
    arduino = start_serial("COM5", 115200)
    dictionary_set = {}

    amp_list = []

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
                
                # if not data.isdigit():
                #     print("DATA: ", data)
                #     data = arduino.readline().decode('utf-8').strip()

                print("DATA: ", data)
                freq_amp_pair = data.split(",")
                freq = freq_amp_pair[0]
                amp = freq_amp_pair[1]

                ## put freq, amp into dictionary
                dictionary_set[freq] = float(amp)

                ## there are 64 freq,amp pairs each timestamp
                if len(dictionary_set) == 64:
                    amp_counter = 0

                    ## got rid of freq: 0.0 and 15.6 because their amp was absurdly big
                    del dictionary_set["0.0"]
                    del dictionary_set["15.6"]
                    # del dictionary_set["46.9"]
                    # del dictionary_set["62.5"]
                    # del dictionary_set["78.1"]

                    ## find three freq w/ max amp
                    while amp_counter < 5:
                        freq_with_max_amp = max(dictionary_set, key=dictionary_set.get)
                        amp_list.append(dictionary_set[freq_with_max_amp])
                        dictionary_set.pop(freq_with_max_amp)
                        amp_counter += 1
                    print(amp_list)

                    ## scale the amplitudes since they are big -> TODO: scale them only if they are bigger than a threshold?
                    amp_list[0] = round(amp_list[0] * 5.0)
                    amp_list[1] = round(amp_list[1] * 5.0) 
                    amp_list[2] = round(amp_list[2] * 5.0) 
                    amp_list[3] = round(amp_list[3] * 5.0) 
                    amp_list[4] = round(amp_list[4] * 5.0) 

                    amplitudes = str(amp_list[0]) + "," + str(amp_list[1]) + "," + str(amp_list[2]) + "," + str(amp_list[3]) + "," + str(amp_list[4]) + "\0"
                    print(amplitudes)
                    arduino.write(amplitudes.encode())

                    dictionary_set.clear()
                    amp_list.clear()
                

receive_fft_info()
