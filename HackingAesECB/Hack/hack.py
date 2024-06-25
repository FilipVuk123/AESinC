from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import os

block_size = 16

secret_key = os.urandom(16)

def aes_encrypt(data):
    cipher = AES.new(secret_key, AES.MODE_ECB)
    padded_data = pad(data, AES.block_size)
    return cipher.encrypt(padded_data)

def encrypt_with_secret(data):
    with open("flag.txt", "rb") as f:
        secret_message = f.read().strip()
    return aes_encrypt(data + secret_message)

def ecb_attack():
    discovered_data = b""
    while True:
        block_index = len(discovered_data) // block_size
        offset = block_size - 1 - (len(discovered_data) % block_size)
        input_data = b"A" * offset
        
        encrypted_block = encrypt_with_secret(input_data)[:block_size * (block_index + 1)]
        for i in range(256):
            test_data = input_data + discovered_data + bytes([i])
            test_encrypted = encrypt_with_secret(test_data)[:block_size * (block_index + 1)]
            if test_encrypted == encrypted_block:
                discovered_data += bytes([i])
                break
        else:
            break
    
    return discovered_data

recovered_message = ecb_attack()
print("Recovered Message:", recovered_message)
