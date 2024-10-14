import gmpy2

c = 28822365203577929536184039125870638440692316100772583657817939349051546473185
n = 70736025239265239976315088690174594021646654881626421461009089480870633400973
# factorize n => q and p
p = 238324208831434331628131715304428889871
q = 296805874594538235115008173244022912163

e = 3
phi = (p - 1) * (q - 1)

# d * e ≡ 1 mod phi => (d * 11) / phi will give us a remainder of one.
d = gmpy2.invert(e, phi)

# C = M ^ e mod n
# M = C ^ d mod n
message = pow(c, d, n)

print(bytearray.fromhex(hex(message)[2:]))
