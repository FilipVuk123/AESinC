from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
from Crypto.Random import get_random_bytes
import base64

BLOCK_SIZE = 16  # AES block size in bytes

key = get_random_bytes(BLOCK_SIZE)  # Generate a random AES key

def encrypt(plaintext):
    """
    Encrypt the plaintext using AES in CBC mode with a random IV.
    """
    iv = get_random_bytes(BLOCK_SIZE)  # Generate a random IV
    cipher = AES.new(key, AES.MODE_CBC, iv)  # Create a new AES cipher
    ciphertext = cipher.encrypt(pad(plaintext, BLOCK_SIZE))  # Pad and encrypt the plaintext
    return iv + ciphertext  # Prepend IV to ciphertext

def is_padding_ok(ciphertext):
    """
    Check if the decrypted ciphertext has valid padding.
    """
    iv = ciphertext[:BLOCK_SIZE]  # Extract the IV
    ciphertext = ciphertext[BLOCK_SIZE:]  # Extract the ciphertext
    cipher = AES.new(key, AES.MODE_CBC, iv)  # Create a new AES cipher
    try:
        unpad(cipher.decrypt(ciphertext), BLOCK_SIZE)  # Decrypt and check padding
        return True  # Padding is valid
    except ValueError:
        return False  # Padding is invalid

def attack(ciphertext):
    """
    Perform the padding oracle attack to decrypt the ciphertext.
    """
    guessed_clear = b''
    split_string = lambda x, n: [x[i:i+n] for i in range(0, len(x), n)]  # Split the data into blocks
    blocks = split_string(ciphertext, BLOCK_SIZE)
    
    for block_n in range(len(blocks) - 1, 0, -1):  # Process each pair of blocks
        spliced_ciphertext = blocks[block_n - 1] + blocks[block_n]  # Pair of blocks to attack
        decoded_bytes = b'a' * BLOCK_SIZE  # Placeholder for decrypted bytes

        for byte in range(BLOCK_SIZE - 1, -1, -1):  # Process each byte in the block
            new_pad_len = BLOCK_SIZE - byte
            hacked_ciphertext_tail = b''

            for pad_index in range(1, new_pad_len):
                hacked_ciphertext_tail += bytearray([new_pad_len ^ decoded_bytes[byte + pad_index]])
            
            for i in range(256):  # Try all possible byte values
                attack_str = bytearray([(i ^ spliced_ciphertext[byte])])
                hacked_ciphertext = spliced_ciphertext[:byte] + attack_str + hacked_ciphertext_tail + spliced_ciphertext[byte + 1 + new_pad_len - 1:]

                if is_padding_ok(hacked_ciphertext):  # Check if padding is valid
                    test_correctness = hacked_ciphertext[:byte - 1] + bytearray([(1 ^ hacked_ciphertext[byte])]) + hacked_ciphertext[byte:]
                    if not is_padding_ok(test_correctness):  # Check if padding is correct
                        continue
                    
                    decoded_bytes = decoded_bytes[:byte] + bytearray([hacked_ciphertext[byte] ^ new_pad_len]) + decoded_bytes[byte + 1:]
                    guessed_clear = bytearray([i ^ new_pad_len]) + guessed_clear
                    break
    
    return guessed_clear[:-guessed_clear[-1]]  # Remove padding

if __name__ == '__main__':
    messages = [b'Attack at dawn', 
                b'', 
                b'Filip',
                b"In symmetric cryptography, the padding oracle attack can be applied to the CBC mode of operation, where the \"oracle\" (usually a server) leaks data about whether the padding of an encrypted message is correct or not. Such data can allow attackers to decrypt (and sometimes encrypt) messages through the oracle using the oracle's key, without knowing the encryption key"
                ]

    for msg in messages:
        ciphertext = encrypt(msg)
        cracked_ct = attack(ciphertext)
        print('Success:', cracked_ct)
