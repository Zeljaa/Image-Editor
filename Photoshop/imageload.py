def convert(name):

    import matplotlib.image as img
    import numpy as nmp
    apple = img.imread(name)
    l = len(name)
    res = name[:l-4]
    output = res + ".txt"

    file = open(output, 'w')

    file.write(str(apple.shape[1]))
    file.write("\n")
    if apple.shape[1] != apple.shape[0]:
        file.write(str(apple.shape[0]))
        file.write("\n")
    file.write("-")
    file.write("\n")
    for apple2D in apple:
        for apple1D in apple2D:
            for apple0D in apple1D:
                file.write(str(apple0D))
                file.write("\n")

    file.close()
    return res
