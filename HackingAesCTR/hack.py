#!/usr/bin/python3

import binascii
from pwn import xor

with open("output.txt") as h:
    encrypted_test = binascii.unhexlify(h.readline().strip())
    encrypted_flag = binascii.unhexlify(h.readline().strip())

blob = xor(encrypted_test, encrypted_flag)

test = b"No right of private conversation was enumerated in the Constitution. I don't suppose it occurred to anyone at the time that it could be prevented"

flag = xor(blob, test)[:len(encrypted_flag)]

print(flag)
