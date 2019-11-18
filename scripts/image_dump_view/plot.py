import matplotlib.pyplot as plt
import numpy as np

image = []

IMAGE_WIDTH = 640
IMAGE_HEIGHT = 480

with open("image.log", "r") as image_file:

    image_line = []

    try:
        for line in image_file:

            values = line.strip().split(" ")
            for val in values:

                n_val = int(val, 16)

                r = (n_val & 0x00FF0000) >> 16
                g = (n_val & 0x0000FF00) >> 8
                b = (n_val & 0x000000FF) >> 0

                image_line.append([r, g, b])
                
                if len(image_line) >= IMAGE_WIDTH:
                    image.append(image_line)
                    image_line = []
    except:
        pass

image = np.array(image)

print(np.shape(image))

imgplot = plt.imshow(image)
plt.show()
