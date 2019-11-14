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
    dict6 = {}
    all_dict = [dict1, dict2, dict3, dict4, dict5, dict6]
    return all_dict

def receive_fft_info():
    arduino = start_serial("COM5", 115200)
    dictionary_set = init_dict()

    amp_list = []
    dict_counter = 0
    while True:
        try:
            data = arduino.readline().decode().strip("\r\n")
            print(data)

            # put freq, amp into dictionary
            dictionary_set[dict_counter][key] = value # TODO: change the key, value -> freq, amp from data

            # the first four dictionaries contain 21 freq,amp pairs
            if dict_counter <= 4:
                if len(dictionary_set[dict_counter]) == 21:
                    freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                    amp_list.append(freq_with_max_amp)
                    dict_counter += 1
            
            # the last two dictionaries contain 22 freq,amp pairs
            elif dict_counter > 4: 
                if len(dictionary_set[dict_counter]) == 22:
                    freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
                    amp_list.append(freq_with_max_amp)
                    dict_counter += 1

            elif dict_counter == 6:
                # TODO: do serial print of all the amplitudes to arduino here
                dict_counter = 0

        except ValueError:
            pass

receive_fft_info()