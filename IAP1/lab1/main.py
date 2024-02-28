# Laborator 1

# Task 1
def reverse(s):
    return s[::-1]


def alternate(s):
    alt = ""
    if not len(s):
        return ""
    for char, i in zip(s, range(len(s))):
        if not i % 2:
            alt += char.upper()
        else:
            alt += char.lower()
    return alt

def  caesar_encrypt(s, shift):
    encrypted = ""
    if not len(s):
        return ""
    for char in s:
        if char.isalpha():
            e_char = chr((ord(char) - ord('A') + shift) % 26 + ord('A'))
            encrypted += e_char
        else:
            encrypted += char
    return encrypted

def caesar_decrypt(s, shift):
    decrypted = ""
    if not len(s):
        return ""
    for char in s:
        if char.isalpha():
            d_char = chr((ord(char) - ord('A') - shift) % 26 + ord('A'))
            decrypted += d_char
        else:
            decrypted += char
    return decrypted
str = input('Type the string: ')
print('Reversed string: ', reverse(str))
print('Alternate string: ', alternate(str))
shift = input('Desired shift for Caesar\'s Cypher: ')
print('Encrypted string: ', caesar_encrypt(str,shift))
print('Decrypted string: ', caesar_decrypt(str,shift))

