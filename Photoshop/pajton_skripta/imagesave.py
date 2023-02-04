import matplotlib.image as img
import numpy as nmp

file = open('test_out.txt', 'r')

pxl = []
row = []
col = []
m = int(file.readline())
n = file.readline()
if n != "-\n":
    n = int(n)
    file.readline()
else:
    n = m
for i in range(n):
    row = []
    for j in range(m):
        pxl = []
        for x in range(3):
            pxl.append(int(file.readline()))
        row.append(pxl)
    col.append(row)

file.close()
apple = img.imsave('jabuka.jpg', nmp.uint8(col))
