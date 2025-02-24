import base64


def xor(xor_a, xor_b):
    return bytes([x ^ y for x, y in zip(xor_a, xor_b)])


class LCG:
    def __init__(self, a, b):
        self.a = a
        self.b = b
        self.mod = 2 ** 16
        self.state = 0

    def next(self):
        self.state = (self.a * self.state + self.b) % self.mod
        return self.state


# Read from file and decrypt
with open("cyphertext", "rb") as f:
    ciphertext_base64 = f.read()

ciphertext = base64.b64decode(ciphertext_base64)

# Brute-force LCG parameters
for test_a in range(3014, 10001):
    for test_b in range(2829, 10001):
        # Initialize LCG
        lcg = LCG(test_a, test_b)

        # Generate LCG states and reconstruct the key
        key_states = [lcg.next() for _ in range(len(ciphertext) // 2)]
        key = b"".join([state.to_bytes(2, "little") for state in key_states])

        # Decrypt
        plaintext_candidate = xor(ciphertext, key).decode("ASCII",
                                                          errors="ignore")

        # Check if decryption is successful
        if "SpeishFlag" in plaintext_candidate:
            print(f"Found parameters: a={test_a}, b={test_b}")
            print(
                f"Decrypted plaintext:\n{plaintext_candidate}")
            exit()
print("Failed to decrypt the ciphertext.")
