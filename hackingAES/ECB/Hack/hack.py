from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import os

block_size = 16  # AES block size in bytes

secret_key = os.urandom(16)  # Generate a random 128-bit AES key

def aes_encrypt(data):
    """
    Encrypt the data using AES in ECB mode with the secret key.
    """
    cipher = AES.new(secret_key, AES.MODE_ECB)  # Create a new AES cipher in ECB mode
    padded_data = pad(data, AES.block_size)  # Pad the data to ensure it's a multiple of the block size
    return cipher.encrypt(padded_data)  # Encrypt the padded data

def encrypt_with_secret(data):
    """
    Encrypt the given data concatenated with the secret message from 'flag.txt' using AES in ECB mode.
    """
    with open("flag.txt", "rb") as f:
        secret_message = f.read().strip()  # Read and strip the contents of 'flag.txt'
    return aes_encrypt(data + secret_message)  # Concatenate the input data with the secret message and encrypt

def ecb_attack():
    """
    Perform an ECB byte-at-a-time attack to recover the secret message.
    """
    discovered_data = b""  # Initialize the discovered data as an empty byte string
    while True:
        block_index = len(discovered_data) // block_size  # Determine the current block index
        offset = block_size - 1 - (len(discovered_data) % block_size)  # Calculate the number of padding bytes needed
        input_data = b"A" * offset  # Prepare the padding data to align the blocks
        
        # Encrypt the padding data with the secret to get the target block
        encrypted_block = encrypt_with_secret(input_data)[:block_size * (block_index + 1)]
        
        for i in range(256):
            # Prepare the test data with the discovered data and the current byte guess
            test_data = input_data + discovered_data + bytes([i])
            # Encrypt the test data with the secret
            test_encrypted = encrypt_with_secret(test_data)[:block_size * (block_index + 1)]
            if test_encrypted == encrypted_block:
                # If the encrypted block matches the target block, the guessed byte is correct
                discovered_data += bytes([i])
                break
        else:
            # If no match is found, the entire secret message has been discovered
            break
    
    return discovered_data

# Perform the ECB byte-at-a-time attack and recover the secret message
recovered_message = ecb_attack()
print("Recovered Message:", recovered_message)
