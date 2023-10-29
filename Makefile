.PHONY: clean build

CC = cc
CFLAGS = -Wall
NAME = dmc

SRC = log.c
OBJ = $(patsubst %.c,%.o,${SRC})

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

lib${NAME}_static.a: ${OBJ}
	ar -rc $@ $^
	ranlib $@

lib${NAME}.so: ${OBJ}
	${CC} ${CFLAGS} --shared -o $@ $^

examples/%: examples/%.c lib${NAME}_static.a
	${CC} ${CFLAGS} -o $@ $< -L./ -l${NAME}_static

clean:
	rm -fv ${OBJ}
	rm -fv lib${NAME}.so
	rm -fv lib${NAME}_static.a

build: lib${NAME}_static.a lib${NAME}.so
