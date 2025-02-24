from Crypto.Cipher import AES
from Crypto import Random

BLOCK_SIZE = 32
PADDING = b'#'
iv = b"\x00" * 16


# def encrypt(key, iv, data):
#     aes = AES.new(key, AES.MODE_CBC, iv)
#     data = aes.encrypt(data)
#     return data

# reverse the AES Encryption to decrypt the code
def decrypt(key, iv, enc_data):
    aes = AES.new(key, AES.MODE_CBC, iv)
    data = aes.decrypt(enc_data)
    return data


# def pad(s):
#     return s + (BLOCK_SIZE - len(s) % BLOCK_SIZE) * PADDING

key = Random.new().read(BLOCK_SIZE)

with open('isc-lab02-secret.enc', 'rb') as f:
    key = f.read(BLOCK_SIZE)
    enc_data = f.read()

# enc = encrypt(key, iv, pad(data))
data = decrypt(key, iv, enc_data)

f_out = open("plain.jpg", 'wb')
print(key)
f_out.write(data)
f_out.close()
