# column masks
result = []
res = 1 | (1 << 8) | (1 << 16) | (1 << 24) | (1 << 32) | (1 << 40) | (1 << 48) | (1 << 56)
for j in range (8):
    result.append (str(res << j)+"LLU")
print ("column masks")
print (", ".join(result))

# row masks
result = []
res = 1 | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7)
for j in range (8):
    result.append (str(res << (j*8))+"LLU")
print ("\nrow masks")
print (", ".join(result))

# traspose masks 
l = [56, 48, 40, 32, 24, 16, 8, 0, 1, 2, 3, 4, 5, 6, 7]
a = zip (l, (8 - abs(x) for x in range (-7, 8)))
result = []
for i in a:
    r = i[0]
    res = 0
    for j in range (0, 9 * i[1], 9):
        res |= 1 << (r + j)
    result.append (str(res) + "LLU")
print ("\ntranspose masks")
print (", ".join(result))

