import os
import ctypes
import time

import struct

import matplotlib.pyplot as plt
import numpy as np

os.chdir('C:\\intelFPGA_lite\\18.1\\quartus\\bin64')

dll_path = 'jtag_atlantic.dll'

atlantic_dll = ctypes.cdll.LoadLibrary(dll_path)

"""
JTAGATLANTIC * jtagatlantic_open (
    const char * chain,
    int device_index,
    int link_instance,
    const char * app_name);
"""
JAOpen = getattr(atlantic_dll,'?jtagatlantic_open@@YAPEAUJTAGATLANTIC@@PEBDHH0@Z')  # mangled name obtained from dllwalker
JAOpen.argtypes = [ctypes.c_char_p, ctypes.c_int64, ctypes.c_int64, ctypes.c_char_p]
JAOpen.restype = ctypes.c_void_p

"""
int  jtagatlantic_get_error (const char * * other_info);
"""
JAGetError = getattr(atlantic_dll,'?jtagatlantic_get_error@@YA?AW4JATL_ERROR@@PEAPEBD@Z')
JAGetError.argtypes = [ctypes.c_void_p]
JAGetError.restype = ctypes.c_int64

"""
void jtagatlantic_close (JTAGATLANTIC * link);
"""
JAClose = getattr(atlantic_dll,'?jtagatlantic_close@@YAXPEAUJTAGATLANTIC@@@Z')
JAClose.argtypes = [ctypes.c_void_p]
JAClose.restype = None

"""
int  jtagatlantic_write (JTAGATLANTIC * link, const char * data, unsigned int count);
"""
JAWrite = getattr(atlantic_dll,'?jtagatlantic_write@@YAHPEAUJTAGATLANTIC@@PEBDI@Z')
JAWrite.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint64]
JAWrite.restype = ctypes.c_int64

"""
int  jtagatlantic_flush (JTAGATLANTIC * link);
"""
JAFlush = getattr(atlantic_dll,'?jtagatlantic_flush@@YAHPEAUJTAGATLANTIC@@@Z')
JAFlush.argtypes = [ctypes.c_void_p]
JAFlush.restype = ctypes.c_int64

"""
int  jtagatlantic_read (JTAGATLANTIC * link, char * buffer, unsigned int buffsize);
"""
JARead = getattr(atlantic_dll,'?jtagatlantic_read@@YAHPEAUJTAGATLANTIC@@PEADI@Z')
JARead.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint64]
JARead.restype = ctypes.c_int64

# information obtained from running nios2-terminal.exe
cable_name = b"USB-Blaster [USB-0]"  # related to the board you are using
device_index = 1  # related to the JTAG device on the board. 0: to let the DLL determine itself. 
                  #      1: usually the on-board FPGA "burner" chip, 2: the FPGA chip
link_instance = 0 # -1: to let the DLL determine the JTAG instance in the chip. 0: in my case I have only 1 instance
                  #      of JTAG-UART so it is indexed by 0.

# establish the link
link = JAOpen(
    ctypes.c_char_p(cable_name),
    ctypes.c_int64(device_index),
    ctypes.c_int64(link_instance),
    ctypes.c_char_p(b'')
)

string_buffer = ctypes.create_string_buffer(1024)
string_buffer_p = ctypes.c_char_p(ctypes.addressof(string_buffer))

kiss_buffer = b''

KISS_END = b'\xC0'

tx_buffer = ctypes.create_string_buffer(1024)
tx_buffer_p = ctypes.c_char_p(ctypes.addressof(tx_buffer))

tx_buffer[0] = 0xC0
tx_buffer[1] = 0x70
tx_buffer[2] = 0xC0

JAWrite(link, tx_buffer_p, 3)
JAFlush(link)

while 1:

    result = JARead(link, string_buffer_p, 1024)

    kiss_buffer += string_buffer[:result]

    found_packet = True
    while found_packet:

        found_packet = False

        first_end = kiss_buffer.find(KISS_END);
        if first_end != -1:
            second_end = kiss_buffer.find(KISS_END, first_end + 1)
            if second_end != -1:

                kiss_packet = kiss_buffer[:second_end+1]
                kiss_buffer = kiss_buffer[second_end+1:]

                # Remove ends
                kiss_packet = kiss_packet[1:-1]

                kiss_packet = kiss_packet.replace(b'\xDB\xDC', b'\xC0')
                kiss_packet = kiss_packet.replace(b'\xDB\xDD', b'\xDB')

                # Log message
                if kiss_packet[0] == 0x70:
                    print(kiss_packet[1])

                # Log message
                if kiss_packet[0] == 0x81:
                    print(kiss_packet[1:])

                # JPEG Image
                elif kiss_packet[0] == 0x82:
                    print(kiss_packet[1:])

                # RAW Image
                elif kiss_packet[0] == 0x83:

                    image = np.frombuffer(kiss_packet[1:], dtype=np.uint8)
                    image = np.reshape(image, (480, 640, 3))
 
                    with open("image.dat", "wb") as image_dat_file:
                        np.save(image_dat_file, image)
 
                    imgplot = plt.imshow(image)
                    plt.show()

                # State message
                if kiss_packet[0] == 0x90:
                    drive, yaw = struct.unpack("<ff", kiss_packet[1:])
                    print(drive)

                found_packet = True

    time.sleep(0.01)

JAClose(link)
