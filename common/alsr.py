#!/usr/bin/env python

# Helper to check ALSR enablement

alsr = open ('/proc/sys/kernel/randomize_va_space')

for line in alsr:
    print(line)

alsr.close()
