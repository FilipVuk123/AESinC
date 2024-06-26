import binascii
from pwn import xor

# Read the encrypted test message and encrypted flag from the file
with open("output.txt") as h:
    encrypted_test = binascii.unhexlify(h.readline().strip())  # Read and decode the encrypted test message
    encrypted_flag = binascii.unhexlify(h.readline().strip())  # Read and decode the encrypted flag

# XOR the two encrypted messages to find the XOR difference (blob)
blob = xor(encrypted_test, encrypted_flag)

# The known test message
test = b"No right of private conversation was enumerated in the Constitution. I don't suppose it occurred to anyone at the time that it could be prevented"

# XOR the blob with the known test message to recover the flag
flag = xor(blob, test)[:len(encrypted_flag)]

# Print the recovered flag
print(flag)
