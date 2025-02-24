# ISC2024 Challenge Write-Up

## Challenge 1: Encrypted Cipher

### Objective:
Decrypt the given ciphertext and retrieve the plaintext and flag.

### Steps:
1. **Connect to the Server**  
   - Used `nc` to connect to the server:
     ```bash
     nc isc2024.1337.cx 11091
     ```
   - Saved the received ciphertext into a file `ciphertext`.

2. **Reverse Engineer Encryption Algorithm**  
   - Analyzed the encryption logic provided (or deduced) to create a decryption script:
     - `decrypt.py`: Reversed the transformations applied to the plaintext.
   - Decrypted the ciphertext:
     ```bash
     python decrypt.py
     ```
   - Output:
     ```
     Found parameters: a=3015, b=2830
     Decrypted plaintext:
     Ia si nevasta da ia si amanta
     Da ca e frumoasa viata
     Salam! Florin Salam, Salam da
     SpeishFlag{2iFJCDMYIi2bqO21rUro9BXXEDKb5xUi}
     ```

### Tools Used:
- Python
- Custom Decryption Script (`decrypt.py`)

---

## Challenge 2: SSH Authentication and Password Cracking

### Objective:
Gain access to a restricted SSH account and extract useful hints.

### Steps:
1. **Connect to the Server via SSH**  
   - Used `ssh` with the provided `id_rsa.pub` key:
     ```bash
     chmod 600 id_rsa.pub
     ssh -i id_rsa.pub hacker@isc2024.1337.cx
     ```

2. **Password Cracking for Another Account**  
   - Found a hash (`password.txt`) associated with the `hr_que3n` account.
   - Generated a wordlist using `crunch` with the pattern `,@%%`:
     ```bash
     crunch 4 4 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 -t ,@%% > wordlist.txt
     ```
   - Cracked the hash using `john`:
     ```bash
     john --format=cypher --wordlist=wordlist.txt password.txt
     ```

3. **Find Sensitive Scripts**  
   - Located `generate_report.sh` under `bo55man`.
   - Identified it as a potential target for privilege escalation.

### Tools Used:
- `ssh`
- `crunch`
- `john`

---

## Challenge 3: Command Injection Exploitation

### Objective:
Abuse command injection in `generate_report.sh` to extract hidden files.

### Steps:
1. **Command Injection in `generate_report.sh`**  
   - Ran the script with injected commands:
     ```bash
     sudo -u bo55man ./generate_report.sh
     ```
   - Injected commands:
     - List directory contents:
       ```bash
       ; ls -la;
       ```
     - Output:
       ```
       .pleasedont/
       ```
     - Read flag from the discovered directory:
       ```bash
       ; cat .pleasedont/der_flag.flag;
       ```

### Tools Used:
- Shell Scripting
- Linux Utilities (`ls`, `cat`)

---

## Challenge 4: Binary Exploitation

### Objective:
Exploit a buffer overflow vulnerability in a binary to extract a flag.

### Steps:
1. **Reverse Engineering with Ghidra**  
   - Loaded the binary in Ghidra.
   - Found the `db_first_flag` function, which was not directly accessible but could be reached by overwriting the return address.

2. **Analyze Stack Behavior with GDB**  
   - Identified logic for two `recv` calls in `process_loop`:
     - First `recv`: Checks `len` as `int` and then reads data as `unsigned char`.
     - Second `recv`: Uses data length to allocate and read into the buffer.

   - Determined the stack offset between the buffer and return address:
     ```bash
     pwndbg> info frame
     ```
     - Calculated offset: `0xffffce1d - 0xffffcddc = 0x41 (65)`.

3. **Payload Crafting**  
   - Sent `len` value as:
     - A valid `int` (e.g., `< 0x39` or `57`) that was interpreted as `unsigned char`.
   - Overwrote the return address with the address of `db_first_flag`.

4. **Extract `global_magix` and Use Correct Padding**  
   - Extracted the value of `global_magix` using `GDB` and verified its stack location.
   - Constructed the payload:
     - Offset padding.
     - Return address pointing to `db_first_flag`.
     - `global_magix` value.

5. **Exploit Execution**  
   - Used the provided Python script (`exploit.py`) to send the payload and trigger the exploit:
     ```bash
     python exploit.py
     ```

### Tools Used:
- **Ghidra**: For static analysis and disassembly.
- **GDB**: For debugging and memory analysis.
- **Python**: For crafting and sending the exploit.