
Challenge #1 (lgc_otp)

1. Connect to the Server: nc isc2024.1337.cx 11091
2. Saved the received ciphertext into a file `ciphertext`.
3. Analyzed the encryption logic provided to create decryption script decrypt.py
4. Ran the decryption script to get the flag, output:
     Found parameters: a=3015, b=2830
     Decrypted plaintext:
     Ia si nevasta da ia si amanta
     Da ca e frumoasa viata
     Salam! Florin Salam, Salam da
     SpeishFlag{2iFJCDMYIi2bqO21rUro9BXXEDKb5xUi}
5. tools used: nc, python, decrypt.py | files: ciphertext, decrypt.py

Challenge #2 (unexpected-ceo)

1. Modified permissions of id_rsa.pub to 600: chmod 600 id_rsa.pub
1. Connect to the Server via SSH: ssh -i id_rsa.pub hacker@isc2024.1337.cx
3. Found a hash associated with the hr_que3n account in /etc/shadow (stored in password.txt).
4. Generated a wordlist using crunch with the pattern ,@%%:
    crunch 4 4 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 -t ,@%% > wordlist.txt
5. Cracked the hash using john:
    john --format=cypher --wordlist=wordlist.txt password.txt
6. Found a sensitive script generate_report.sh under bo55man based on info in her_que3n's home directory.
7. Used user privilege escalation to read the flag from the hidden directory .pleasedont:
    sudo -u bo55man ./generate_report.sh
    ; cat .pleasedont/der_flag.flag;
8. tools used: ssh, john, crunch | files: id_rsa.pub, password.txt, wordlist.txt

Challenge #3 (binary-database)

1. Loaded the binary in Ghidra and found the db_first_flag function and process_loop logic.
2. Identified logic for two recv calls in process_loop:
    - First recv: Checks len as int;
    - Second recv: Uses len as unsigned char to read data.
3. Determined the stack offset between the buffer and return address:
    pwndbg> info frame
     Stack level 0, frame at 0xffffcde0:
     eip = 0x8049306 in recv_bytes (server.c:86); saved eip = 0x8049aa3
     called by frame at 0xffffce60
     source language c.
     Arglist at 0xffffcdd8, args: fd=4, buf=0xffffce1d "\316\377\377\204\317\377\377\200\313\377\367\270\316\377\377\213\332\334", <incomplete sequence \367>, n=0 '\000'
     Locals at 0xffffcdd8, Previous frame's sp is 0xffffcde0
     Saved registers:
      eip at 0xffffcddc
    - Offset: 0xffffce1d - 0xffffcddc = 0x41 (65)
3. Send len value as:
    - a valid int and unsigned char to bypass the first recv check.
    - value in unsigned char (65) to overwrite the return address with db_first_flag.
4. extract global_magix and use correct padding to get the flag.
    - magic parameter stored in esp+0x1c
    - value of global_magix: 0x31337f41
    - padding: 4 Z's to check in gdb where the value given to magic in payload is stored
    - updated len value to include magic value and padding
5. overall exploit execution:
    - sent payload to the server containing padding, db_first_flag address, and magic value
    - used the python script provided to send the payload and trigger the exploit
6. tools used: ghidra, gdb, python | files: exploit.py, test.py