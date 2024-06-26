import binascii
from pwn import xor

# Read the encrypted test message and encrypted flag from the file
with open("output.txt") as h:
    encrypted_test = binascii.unhexlify(h.readline().strip())  # Read and decode the encrypted test message
    encrypted_flag = binascii.unhexlify(h.readline().strip())  # Read and decode the encrypted flag

# Read the known test message from 'test_message.txt'
with open("test_message.txt", "rb") as f:
    test = f.read().strip()

# XOR the two encrypted messages to find the XOR difference (blob)
blob = xor(encrypted_test, encrypted_flag)

# XOR the blob with the known test message to recover the flag
flag = xor(blob, test)[:len(encrypted_flag)]

# Print the recovered flag
print(flag)
