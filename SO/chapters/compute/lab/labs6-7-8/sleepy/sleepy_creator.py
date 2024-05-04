# SPDX-License-Identifier: BSD-3-Clause

import subprocess
from sys import exit

NUM_SLEEPS = 10


def main():
    # Create 10 `sleep 1000` processes using `subprocess.Popen`
    # Use the documentation: https://docs.python.org/3/library/subprocess.html#subprocess.Popen
    subprocess.Popen(["sleep", "1000"])

    # Make the current process wait for its child processes.
    subprocess.Popen.wait("sleep", "1000")
    pass


if __name__ == "__main__":
    exit(main())
