import itertools
import sys

input_file = "data1.bin"

with open(input_file, "rb") as f:
    data = f.read()

def is_digit(byte):
    return 0x30 <= byte <= 0x39

# Brute-force keys
print("")
for b1 in range(256):
    for b2 in range(256):
        if is_digit(b1) or is_digit(b2):
            print(f"Trying key: {b1:02x}{b2:02x}", end='\r')
            sys.stdout.flush()

            key = bytes([b1, b2])
            
            # Decrypt
            decrypted = bytearray()
            for i in range(len(data)):
                decrypted.append(data[i] ^ key[i % 2])
            
            output_file = f"o/output_{b1:02x}_{b2:02x}.bin"
            with open(output_file, "wb") as out:
                out.write(decrypted)
            print(f"[+] Saved {output_file} with key {b1:02x}{b2:02x}")
