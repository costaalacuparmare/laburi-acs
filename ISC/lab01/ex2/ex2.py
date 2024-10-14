import zipfile

# You are provided with a ZIP file that is encrypted with a password. 
# The goal is to crack the password by trying each one from a list of possible passwords provided in a file called 'passwords.txt'.

# The ZIP file is protected with a password, and you do not know which one is correct.
# You will attempt to open the ZIP file by trying each password in the 'passwords.txt' file, which contains a list of potential passwords.
# The script will iterate over the passwords, trying each one until the correct password is found, at which point the contents of the ZIP file will be extracted.
# If the correct password is found, it will be printed to the console.

zip_file_path = 'crack_me.zip'
passwords_file_path = 'passwords.txt'


def crack_zip(zip_file, passwords_file):
    with zipfile.ZipFile(zip_file) as zf:
        with open(passwords_file, 'r') as pf:
            for line in pf:
                password = line.strip()  # Get rid of any newline characters
                try:
                    # Extract the ZIP file with the current password
                    zf.extractall(pwd=password.encode('utf-8'), path='extracted_files')
                    # If the extraction is successful, print the password found
                    print("Password found:", password)
                    # Exit the function if the password is correct
                    return password
                except (RuntimeError, zipfile.BadZipFile):
                    continue
            print("Password not found")
    return None


crack_zip(zip_file_path, passwords_file_path)