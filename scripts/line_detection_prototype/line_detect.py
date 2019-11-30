import matplotlib.pyplot as plt
import numpy as np

import cv2

def rgb2gray(rgb):

    r, g, b = rgb[:,:,0], rgb[:,:,1], rgb[:,:,2]
    gray = 0.2989 * r + 0.5870 * g + 0.1140 * b

    return gray

def process_image(filename): 

    fig, (ax1, ax2) = plt.subplots(1,2)

    with open(filename, "rb") as image_dat_file:
        image = np.load(image_dat_file)

    grey = np.array(rgb2gray(image), dtype=np.uint8)

    # Canny edge detection
    #edges = cv2.Canny(grey,50,150)
    #imgplot = plt.imshow(edges, cmap='Greys')

    edges = np.zeros(np.shape(grey))

    # Simple edge detection
    for x in range(3, 637):
        for y in range(480):
            kernel_result = np.abs(float(grey[y-1][x-3]) - float(grey[y-1][x+3]))
            edges[y][x] = kernel_result
            #print(kernel_result)

    _, edges_thresh = cv2.threshold(edges, 20, 20, cv2.THRESH_BINARY)

    _, grey_thresh = cv2.threshold(grey, 140, 140, cv2.THRESH_BINARY)

    # Bin
    bins = [0]*16
    for x in range(640):
        for y in range(480):
            bin = int(np.floor(x / (640/16)))
            if(edges_thresh[y][x] > 0):
                bins[bin] = bins[bin] + 1

    biggest_bin_value = 0
    biggest_bin_index = 0
    for i in range(len(bins)):
        if biggest_bin_value < bins[i]:
            biggest_bin_value = bins[i]
            biggest_bin_index = i

    biggest_bin_center = biggest_bin_index * (640/16) + (640/16/2)

    ax1.imshow(image)
    ax2.imshow(grey_thresh, cmap='Greys')

    ax2.annotate('Line', xy=(biggest_bin_center, 240),  xycoords='data',
            xytext=(0.8, 0.95), textcoords='axes fraction',
            arrowprops=dict(facecolor='red', shrink=0.05),
            horizontalalignment='right', verticalalignment='top',
            )

    plt.show()
    
process_image("image.dat")