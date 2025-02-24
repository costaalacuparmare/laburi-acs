def decrypt(cipher, key):
    message = ""
    for i in range(len(cipher)):
        message += chr(ord(cipher[i]) ^ ord(key[i]))
    return message

with open("isc-lab02-otp.txt") as file:
    # uses OTP where the key is from 0 to 255
    cipher = file.read()
    for i in range(256):
        key = chr(i) * len(cipher)
        message = decrypt(cipher, key)
        if i == 62:
            print(message)
        # print(message, "for bit ", i) bit 62
