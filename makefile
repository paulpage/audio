CFLAGS=`pkg-config --cflags --libs sdl2`

default:
	${CC} -g -std=c99 -lm -Wall ${CFLAGS} main.c
