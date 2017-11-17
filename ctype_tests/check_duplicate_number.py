#!/usr/bin/env python

import ctypes
import pdb

# TODO: Put this in base class
def listToInt(item):
   arr = (ctypes.c_int * len(item))(*item)
   return arr

hashlib = ctypes.CDLL('/home/akhil/code/gandhana/libtarget.so')
cookie = hashlib.hash_init( 10, 0, 0, 0 );
test = ctypes.CDLL('/home/akhil/code/gandhana/libtest.so')
num = [1,2,3,4]
ret = test.check_duplicate_numbers( cookie, listToInt(num), len(num) )

print "Duplicate items present? %s" %( "YES" if ret else "NO")
