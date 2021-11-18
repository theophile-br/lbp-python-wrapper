import subprocess
import os

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
        proc = subprocess.Popen([clbp_program, img_path, COLOR], stdout=subprocess.PIPE)
        img_hist = proc.stdout.readline()
        img_hist = img_hist.decode("utf-8").split(",")
        ################################################################################
        f.write(','.join(str(x) for x in img_hist) + ":" + str(label_index) + "\n")
        proc.wait()

f.close()
