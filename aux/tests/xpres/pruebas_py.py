for x in range (5):
    for y in range (5):
        a = (1 << (5+x)) | (1 << y)
        print (f"case {bin (a)}:")
        print ("break;")
