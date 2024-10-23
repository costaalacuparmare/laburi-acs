#!/usr/bin/python3

import pyotp
import pyqrcode


TOTP_SECRET = "dani" # Choose a secret!

totp_auth = pyotp.totp.TOTP(TOTP_SECRET).provisioning_uri(
    name="Nicolae Guta", issuer_name="Lab ISC"
)

# Generate and display the setup QR code.
qr = pyqrcode.create(totp_auth)
print(qr.terminal(quiet_zone=1))