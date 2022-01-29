
tst1: main.cpp  Makefile
	emcc main.cpp  --closure 1 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-O3 -std=c++17 -o test.html \
--post-js library_js2.js -s LLD_REPORT_UNDEFINED=1


all:  tst1
	echo 'Built 1ink.us Textures.'
