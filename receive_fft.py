import serial
import time


def start_serial(com,baud):
    serialPort = serial.Serial(com, baud, timeout=1)
    return serialPort

def init_dict():
    dict1 = {}
    dict2 = {}
    dict3 = {}
    dict4 = {}
    dict5 = {}
    all_dict = [dict1, dict2, dict3, dict4, dict5]
    return all_dict

def clear_dict(all_dict):
    for i in range(len(all_dict)):
        all_dict[i].clear()

def receive_fft_info():
    arduino = start_serial("COM5", 115200)
    dictionary_set = init_dict()

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
                print("Second while loop data: ",data)

                freq_amp_pair = data.split(",")

                ## read the next line if an empty line is detected
                if len(freq_amp_pair) == 1:
                    print("==========================================")
                    data = arduino.readline().decode('utf-8').strip()

                freq_amp_pair = data.split(",")
                freq = freq_amp_pair[0]
                amp = freq_amp_pair[1]

                ## put freq, amp into dictionary
                dictionary_set[dict_counter][freq] = float(amp)

                ## there are 64 freq,amp pairs each timestamp
                ## the first four dictionaries contain 13 freq,amp pairs
                if dict_counter < 4:
                    if len(dictionary_set[dict_counter]) == 13:
                        freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                        ## get the second max amplitude if the amplitude > 1000 (happens at very low freq)
                        if dictionary_set[dict_counter][freq_with_max_amp] > 1000:
                            dictionary_set[dict_counter].pop(freq_with_max_amp)
                            freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                        amp_list.append(dictionary_set[dict_counter][freq_with_max_amp])
                        print(amp_list)
                        dict_counter += 1
                
                ## the last dictionaries contain 12 freq,amp pairs
                elif dict_counter == 4: 
                    if len(dictionary_set[dict_counter]) == 12:
                        freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                        ## get the second max amplitude if the amplitude > 1000 (happens at the very end)
                        if dictionary_set[dict_counter][freq_with_max_amp] > 1000:
                            dictionary_set[dict_counter].pop(freq_with_max_amp)
                            freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                        amp_list.append(dictionary_set[dict_counter][freq_with_max_amp])
                        print(amp_list)
                        dict_counter += 1

                        if dict_counter == 5:
                            print(amp_list)
                            # arduino.write("amplitudes!".encode())
                            dict_counter = 0
                            clear_dict(dictionary_set)
                            amp_list.clear()
                

receive_fft_info()