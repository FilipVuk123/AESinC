from Crypto.Cipher import AES
from Crypto.Util import Counter
import os

KEY = os.urandom(16)

def encrypt(plain_text):
    cipher = AES.new(KEY, mode=AES.MODE_CTR, counter=Counter.new(128))
    cipher_text = cipher.encrypt(plain_text)
    return cipher_text.hex()

test = b"No right of private conversation was enumerated in the Constitution. I don't suppose it occurred to anyone at the time that it could be prevented"
print(encrypt(test))


with open('flag.txt', 'rb') as f:
    flag = f.read().strip()

print(encrypt(flag))