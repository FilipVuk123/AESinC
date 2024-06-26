from Crypto.Cipher import AES
from Crypto import Random

KEY_LENGTH = 16  # Length of the AES key in bytes (128 bits)
BLOCK_SIZE = 16  # AES block size in bytes

_random_gen = Random.new()  # Random number generator
_key = _random_gen.read(KEY_LENGTH)  # Generate a random AES key


def _add_padding(msg):
    """
    Add PKCS7 padding to the message to make its length a multiple of BLOCK_SIZE.
    """
    pad_len = BLOCK_SIZE - (len(msg) % BLOCK_SIZE)
    padding = bytes([pad_len]) * pad_len
    return msg + padding


def _remove_padding(data):
    """
    Remove PKCS7 padding from the message.
    """
    pad_len = data[-1]  # Last byte indicates the length of the padding
    
    if pad_len < 1 or pad_len > BLOCK_SIZE:
        return None  # Invalid padding length
    for i in range(1, pad_len):
        if data[-i-1] != pad_len:
            return None  # Padding bytes do not match
    return data[:-pad_len]  # Remove padding


def encrypt(msg):
    """
    Encrypt the message using AES in CBC mode with a random IV.
    """
    iv = _random_gen.read(AES.block_size)  # Generate a random IV
    cipher = AES.new(_key, AES.MODE_CBC, iv)  # Create a new AES cipher
    return iv + cipher.encrypt(_add_padding(msg))  # Prepend IV to ciphertext


def _decrypt(data):
    """
    Decrypt the message and remove padding.
    """
    iv = data[:BLOCK_SIZE]  # Extract the IV
    cipher = AES.new(_key, AES.MODE_CBC, iv)  # Create a new AES cipher
    return _remove_padding(cipher.decrypt(data[BLOCK_SIZE:]))  # Decrypt and remove padding


def is_padding_ok(data):
    """
    Check if the decrypted message has valid padding.
    """
    return _decrypt(data) is not None  # True if padding is valid, False otherwise
