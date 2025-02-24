#!/usr/bin/python3

import crypt


password = "root"
salt = "22"
hash = crypt.crypt(password, salt)

print(hash)
