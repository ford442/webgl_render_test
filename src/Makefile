
tst1: main.cpp  Makefile
	emcc main.cpp  -sUSE_SDL=1 --closure 0 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
-O3 -o test.html \
--js-library library_js2.js


all:  tst1
	echo 'Built 1ink.us Textures.'
