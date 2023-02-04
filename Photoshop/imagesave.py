def toimage(name):


    import matplotlib.image as img
    import numpy as nmp

    rd = name + "izmenjeno.txt"
    l = len(name)

    output = name + "izmenjeno.jpg"

    file = open(rd, 'r')

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
    apple = img.imsave(output, nmp.uint8(col))
