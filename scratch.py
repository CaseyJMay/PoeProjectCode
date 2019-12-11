# import serial
# import time


# def start_serial(com,baud):
#     serialPort = serial.Serial(com, baud, timeout=1)
#     return serialPort

# def init_dict():
#     dict1 = {}
#     dict2 = {}
#     dict3 = {}
#     dict4 = {}
#     dict5 = {}
#     all_dict = [dict1, dict2, dict3, dict4, dict5]
#     return all_dict

# def clear_dict(all_dict):
#     for i in range(len(all_dict)):
#         all_dict[i].clear()

# def receive_fft_info():
#     arduino = start_serial("COM5", 115200)
#     dictionary_set = init_dict()

#     amp_list = []
#     dict_counter = 0

#     while True:
#         data = arduino.readline().decode('utf-8').strip()
#         print("data: " + data)

#         # if bool(data):
#         #     print("caught")
        
#         freq_amp_pair = data.split(",")
#         if len(freq_amp_pair) == 1:
#             print("-------")
#             data = arduino.readline().decode('utf-8').strip()
#         freq_amp_pair = data.split(",")
#         freq = freq_amp_pair[0]
#         amp = freq_amp_pair[1]

#         # print(freq_amp_pair)
#         # print("freq: ", freq)
#         # print("amp: ", amp)

#         if freq == "0.0":
#             while True:
#                 data = arduino.readline().decode().strip() # "\r\n"
#                 print("Second while loop data: ",data)

#                 freq_amp_pair = data.split(",")
#                 if len(freq_amp_pair) == 1:
#                     print("==========================================")
#                     data = arduino.readline().decode('utf-8').strip()
#                 freq_amp_pair = data.split(",")
#                 freq = freq_amp_pair[0]
#                 amp = freq_amp_pair[1]

#                 ## put freq, amp into dictionary
#                 dictionary_set[dict_counter][freq] = float(amp)

#                 ## the first four dictionaries contain 11 freq,amp pairs
#                 if dict_counter < 4:
#                     if len(dictionary_set[dict_counter]) == 13:
#                         freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
#                         if dictionary_set[dict_counter][freq_with_max_amp] > 1000:
#                             dictionary_set[dict_counter].pop(freq_with_max_amp)
#                             freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
#                         amp_list.append(dictionary_set[dict_counter][freq_with_max_amp])
#                         print(amp_list)
#                         dict_counter += 1
                
#                 ## the last two dictionaries contain 10 freq,amp pairs
#                 elif dict_counter == 4: 
#                     if len(dictionary_set[dict_counter]) == 12:
#                         freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
#                         if dictionary_set[dict_counter][freq_with_max_amp] > 1000:
#                             dictionary_set[dict_counter].pop(freq_with_max_amp)
#                             freq_with_max_amp = max(dictionary_set[dict_counter], key=dictionary_set[dict_counter].get)
#                         amp_list.append(dictionary_set[dict_counter][freq_with_max_amp])
#                         print(amp_list)
#                         dict_counter += 1

#                         if dict_counter == 5:
#                             print(amp_list)
#                             dict_counter = 0
#                             clear_dict(dictionary_set)
#                             amp_list.clear()
#                             print("pass")
                

# receive_fft_info()

# dictionary_set = [{"a":"40", "b":"20", "c":"30"},{}]
# del dictionary_set[0]["a"]
# max_val = max(dictionary_set[0], key=dictionary_set[0].get)
# print(dictionary_set[0][max_val])
# print(max_val)

# del dictionary_set[0][max_val]
# max_val = max(dictionary_set[0], key=dictionary_set[0].get)
# print(dictionary_set[0][max_val])
if not "a".isdigit():
    print("UH")
else:
    print("EH")
# print("a".isdigit())