CFLAGS=`pkg-config --cflags --libs sdl2`

default:
	${CC} song.c gui.c -o gui -g -std=c99 -lm -lraylib -Wall ${CFLAGS}

# default:
# 	${CC} -g -std=c99 -lm -Wall ${CFLAGS} song.c main.c
