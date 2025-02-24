import sys
import random


def decrypt_file(encrypted_contents, random_byte):
    N = len(encrypted_contents)
    rng = random.Random(random_byte)
    tkey = rng.sample(list(range(N)), k=N)

    # Reverse the scrambling order
    unscrambled = [0] * N
    for i, pos in enumerate(tkey):
        unscrambled[pos] = encrypted_contents[i]

    # Undo the XOR operation
    return bytes([b ^ random_byte for b in unscrambled])


if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python decrypt.py <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    # Read the encrypted file
    with open(input_file, "rb") as f:
        encrypted_contents = f.read()

    # Attempt all possible values of RANDOM_BYTE (0-255)
    for random_byte in range(256):
        try:
            decrypted_contents = decrypt_file(encrypted_contents, random_byte)

            # Check for readable content or the flag format
            if b"ISC{" in decrypted_contents:
                print(f"Decryption successful with RANDOM_BYTE = {random_byte}")

                # Save the decrypted content to the output file
                with open(output_file, "wb") as f:
                    f.write(decrypted_contents)

                print(f"Output saved to {output_file}")
                break
        except Exception as e:
            continue