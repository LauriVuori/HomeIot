import ctypes as C

lib = C.CDLL("./Cfunc.so")

l = [[1],[1,2],[1,2,3]]
entrylist = []
lengths = []

for sub_l in l:
    entrylist.append((C.c_int*len(sub_l))(*sub_l))
    lengths.append(C.c_int(len(sub_l)))

c_l = (C.POINTER(C.c_int) * len(entrylist))(*entrylist)
c_lengths = ( C.c_int * len(l))(*lengths)

lib.test(c_l, c_lengths, len(l))  #here we also pass the sizes of all the arrays