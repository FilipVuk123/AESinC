from Crypto.Cipher import AES
from Crypto.Util import Counter
import os

# Generate a random 128-bit AES key
KEY = os.urandom(16)

def encrypt(plain_text):
    """
    Encrypt the plain_text using AES in CTR mode with a random counter.
    """
    cipher = AES.new(KEY, mode=AES.MODE_CTR, counter=Counter.new(128))  # Create a new AES cipher in CTR mode
    cipher_text = cipher.encrypt(plain_text)  # Encrypt the plaintext
    return cipher_text.hex()  # Return the ciphertext as a hex string

# Read the known test message from 'test_message.txt'
with open("test_message.txt", "rb") as f:
    test = f.read().strip()

# Encrypt the test message
encrypted_test = encrypt(test)

# Example usage: encrypt the contents of 'flag.txt'
with open('flag.txt', 'rb') as f:
    flag = f.read().strip()  # Read and strip the contents of 'flag.txt'

encrypted_flag = encrypt(flag)

# Write both encrypted texts to 'output.txt'
with open('output.txt', 'w') as f:
    f.write(encrypted_test + "\n")
    f.write(encrypted_flag + "\n")
