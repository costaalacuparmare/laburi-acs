import base64

# You are given a string that has been encoded multiple times.
# Your goal is to repeatedly decode it until you reveal the hidden flag.
# You do not know how many times the text has been encoded.

encoded_text = b'VmxSR1lWUXhTa2hXYWxwV1ZrVkthRlpyVm1GamJHUlhWV3RhVG1FemFGWldWbWhyVjJ4YVNGUnFRbFZoTVVwVFdsZHpOVlpGTVZoaVJuQlhUVVJGZWxaRldtdFVNa3BIWWtoR1YySlhlRTlaVjNSTFlqRmtjMVZzU2s5U1ZFWmFWRlZSZDFCUlBUMD0='
decoded_text = ''

while True:
    try:
        decoded_text = base64.b64decode(encoded_text).decode('utf-8')
        encoded_text = decoded_text.encode('utf-8')
    except:
        break
print("Final decoded text:", decoded_text)
