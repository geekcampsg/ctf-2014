all: inject.so

inject.so: inject.c
	cc -std=c99 -shared -fPIC -o $@ $<

clean:
	rm inject.so
