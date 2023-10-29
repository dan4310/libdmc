.PHONY: clean build examples install uninstall

CC = cc
CFLAGS = -Wall
NAME = dmc

SRC = log.c vec.c
OBJ = $(patsubst %.c,%.o,${SRC})

_EXAMPLES = log vec
EXAMPLES = $(patsubst %,examples/%,${_EXAMPLES})

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

lib${NAME}_static.a: ${OBJ}
	ar -rc $@ $^
	ranlib $@

lib${NAME}.so: ${OBJ}
	${CC} ${CFLAGS} --shared -o $@ $^
	chmod 755 $@

examples/%: examples/%.c lib${NAME}_static.a
	${CC} ${CFLAGS} -o $@ $< -L./ -l${NAME}_static

clean:
	rm -fv ${OBJ}
	rm -fv lib${NAME}.so
	rm -fv lib${NAME}_static.a
	rm -fv ${EXAMPLES}

build: lib${NAME}_static.a lib${NAME}.so

examples: ${EXAMPLES}

install: lib${NAME}_static.a lib${NAME}.so
	cp -fv $^ /usr/local/lib
	mkdir -pv /usr/local/include/${NAME}
	cp *.h /usr/local/include/${NAME}/.

uninstall:
	rm -fv /usr/local/lib/lib${NAME}_static.a /usr/local/lib/lib${NAME}.so
	rm -rfv /usr/local/include/${NAME}
