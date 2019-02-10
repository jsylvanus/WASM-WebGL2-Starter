NAME=project
CC=emcc
CFLAGS= -std=c11 -Wall -Wextra -Werror -Wno-missing-field-initializers \
		-Wno-unused-function -DDEBUG -s WASM=1 -s USE_WEBGL2=1 -s FULL_ES3=1
RELEASEFLAGS= -Os -s ALLOW_MEMORY_GROWTH=1 # -s MODULARIZE=1 --closure 1 ## Could enable these if we fix closure compiler locally...
	# NOTE: we want to switch ALLOW_MEMORY_GROWTH to TOTAL_MEMORY=X when we nail down the RAM we need
DEBUGFLAGS= -O0 -g -s ALLOW_MEMORY_GROWTH=1
IFLAGS= -I/Users/james/emsdk/emscripten/1.38.26/system/include
LFLAGS= -w -s OFFSCREEN_FRAMEBUFFER=1 -s OFFSCREENCANVAS_SUPPORT=1


debug: clean
	$(CC) $(CFLAGS) $(DEBUGFLAGS) $(IFLAGS) $(LFLAGS) src/$(NAME).c -o dist/$(NAME).js

release: clean
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $(IFLAGS) $(LFLAGS) src/$(NAME).c -o dist/$(NAME).js

clean:
	@rm -f ./dist/project*

run: debug

.phony: clean
