
tst1: main.cpp  Makefile
	emcc main.cpp  --closure 0 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
-O3 -o test.js \
--js-library library_js2.js --extern-pre-js setUp.js


tst2: main2.cpp  Makefile
	emcc main2.cpp  --closure 0 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
-O3 -o test2.js \
--js-library library_js2.js --extern-pre-js setUp.js


all:  tst1 tst2
	echo 'Built 1ink.us Textures.'
