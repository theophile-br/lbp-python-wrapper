import os

import pylbplib.pylbp as pylbp

GRAYSCALE = "0"
COLOR = "1"

clbp_program = "./build/clbp" # <----- modify the path of the clpb program

label_index = 0 # example !! label classifier index (is an example)

f = open("descriptor.txt", "w")
for subdir, dirs, files in os.walk("images"):
    file_count = len(files)
    for i in range(file_count):
        img_path = os.path.join(subdir, files[i])
        ################################################################################
        #######################     HERE IS THE PROGRAM CALL    ########################
        ################################################################################

        img_hist = pylbp.lbp_hist(img_path, pylbp.GRAYSCALE)
        ################################################################################
        f.write(','.join(str(x) for x in img_hist) + ":" + str(label_index) + "\n")

f.close()
