# CODE
import subprocess
import os

GRAYSCALE = "0"
COLOR = "1"
dir_path = os.path.dirname(os.path.realpath(__file__))
prgm = os.path.join(dir_path ,"clbp")

def lbp_hist(img_path, color):
    proc = subprocess.Popen([prgm, img_path, color], stdout=subprocess.PIPE)
    img_hist = proc.stdout.readline()
    proc.wait()
    return img_hist.decode("utf-8").split(',')