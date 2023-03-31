# Laborator 1

def reverse(s):
    return s[::-1]


def alternate(s):
    a = ""
    if not len(s):
        return ""
    for i in range(len(s)):
        if not i % 2:
            a += s[i].upper()
        else:
            a += s[i].lower()
    return a


s = input('Type the string: ')
print('Reversed string: ', reverse(s))
print('Alternate string: ', alternate(s))

