# zero

## access

```
nc localhost 4100
```

## solve

```python
from pwn import *

io = remote("0.0.0.0", 4100)
```

前回の授業でやったのと同じで0x30を0とcmpしてるので、そこを0じゃなくするとsym.winが呼ばれる
