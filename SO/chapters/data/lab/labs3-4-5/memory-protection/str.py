#!/usr/bin/env python3

# SPDX-License-Identifier: BSD-3-Clause

"""
Demonstrate string immutability in Python.
"""

s = "anaaremere"
print("{:s}, {:d}, {:c}".format(s[1], ord(s[1]), ord(s[1])))
s1 = s[0:3]
"s[1] = 'z'"  # TypeError: 'str' object does not support item assignment
