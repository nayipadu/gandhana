#!/usr/bin/env python

import ctypes
import pdb

v1 = "sathesh"
v2 = "akhil"
v3 = "geetha"
v4 =  "sharada"

hashlib = ctypes.CDLL('/home/akhil/code/gandhana/libtarget.so')
cookie = hashlib.hash_init( 10, 0, 0, 0 );
# empty hash table, dump it and verify
hashlib.hashtable_dump(cookie)

hashlib.hash_insert(cookie, 1, v1)
hashlib.hash_insert(cookie, 5, v2)
hashlib.hash_insert(cookie, 11, v3)
hashlib.hash_insert(cookie, 55, v4)

hashlib.hashtable_dump(cookie)

#pdb.set_trace()
