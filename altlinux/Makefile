
CC=gcc

CFLAGS=-O2 -fsigned-char -Wall -ansi -pedantic -I.

LDFLAGS=-L. -lhyph

LIBS=libhyph.a

AR=ar rc
RANLIB=ranlib

OBJS = hyphen.o hnjalloc.o csutil.o

all: example
# all: $(LIBS)

libhyph.a: $(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

example: example.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ example.o $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o *~ example libhyph.a 

distclean:	clean

depend:
	makedepend -- $(CFLAGS) -- *.[ch]

# DO NOT DELETE THIS LINE -- make depend depends on it.

hnjalloc.o: hnjalloc.h
hyphen.o: hyphen.h
csutil.o: csutil.h
example.o: hyphen.h
