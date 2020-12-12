CFLAGS=`pkg-config --cflags --libs sdl2`

default:
	${CC} -g -std=c99 -lm -lraylib -Wall ${CFLAGS} song.c gui.c

# default:
# 	${CC} -g -std=c99 -lm -Wall ${CFLAGS} song.c main.c
