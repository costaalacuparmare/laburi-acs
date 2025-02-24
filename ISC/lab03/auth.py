#!/usr/bin/python3

import grp
import hashlib
import os
import pyotp
import sys


PASSWORD_HASH = "13412ffd6149204f40e546ffa9fbd7124b410198a6ba3924f788622b929c8eb2"
TOTP_SECRET = "dani" # Choose a secret!


def login():
    user = os.environ.get("PAM_USER")

    user_groups = [g.gr_name for g in grp.getgrall() if user in g.gr_mem]

    # (6.1): We want this script to be used only for our special group of users.
    if "hacker" not in user_groups:
        print("Nu esti in grupul potrivit!")
        return False

    user_secret = input()
    user_password = user_secret

    # Extract the password and the TOTP. Hint: you know the length of the TOTP.
    user_password = user_secret[:-6]
    totp = user_secret[-6:]

    # (6.2) Calculate the hash of the provided password.
    user_hash = hashlib.sha256(user_password.encode()).hexdigest()

    if user_hash != PASSWORD_HASH:
        print("Ai gresit buzunarul!")
        return False

    # Check the TOTP from the user and uncomment the code below.
    totp_auth = pyotp.TOTP(TOTP_SECRET)
    totp_correct = totp_auth.verify(totp)

#    if not totp_correct:
#        print("S-a rezolvat, nu se poate!")
#        return False

    print("Ma distrez si bine fac!")
    return True


if __name__ == "__main__":
    sys.tracebacklimit = 0

    if not login():
        raise Exception("Python script rejected login: trying default authentication")
