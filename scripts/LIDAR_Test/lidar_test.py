import serial
import time
import binascii

import numpy as np

import matplotlib.pyplot as plt

def stop_scan(ser):
    ser.write(b"\xA5\x25")

def start_scan(ser):
    ser.write(b"\xA5\x20")

def read_scan(ser, callback=None):

    buffer = b""

    syncing = True
    inscan = False

    keepscanning = True

    scandata = []

    while True:

        buffer += ser.read(100)

        if syncing:
            idx = buffer.find(b"\xA5\x5A")

            if idx != -1:
                buffer = buffer[idx + 7:]
                syncing = False

        else:

            while len(buffer) > 5:

                scan_start = False

                sample = buffer[:5]
                buffer = buffer[5:]

                if( ( sample[0] & 0x3 ) == 0x1):
                    scan_start = True

                if scan_start:
                    if inscan:

                        if keepscanning:
                            callback(scandata)
                            scandata = []
                        else:
                            return scandata

                    else:
                        inscan = True

                quality = sample[0] >> 2

                degrees = ( ( sample[1] >> 1 ) + ( sample[2] << 7 ) ) / 64.0
                distance = ( sample[3] + ( sample[4] << 8 ) ) / 4.0

                if inscan:
                    scandata.append((quality, degrees, distance))

def plot_scan(scan):

    x_data = []
    y_data = []

    for scan_entry in scan:

        quality, angle, distance = scan_entry

        if( quality > 3 and distance > 1.0 ):

            x = distance * np.cos( angle * np.pi / 180 )
            y = distance * np.sin( angle * np.pi / 180 )

            x_data.append(x)
            y_data.append(y)

    plt.scatter(x_data, y_data)


def process_scan(scan):

    plt.clf()

    plot_scan(scan)

    plt.ylim( (-2000, 2000) )
    plt.xlim( (-2000, 2000) )

    plt.pause(0.0001)

ser = serial.Serial("COM4", baudrate=115200, timeout=0.1)

ser.setDTR(0)

plt.ion()

start_scan(ser)
#read_scan(ser, process_scan)

stop_scan(ser)
ser.setDTR(1)

time.sleep(10000)

ser.close()