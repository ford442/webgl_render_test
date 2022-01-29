
tst1: main.cpp  Makefile
	em++ main.cpp  --closure 0 -sUSE_SDL=2 -s ABORTING_MALLOC=0 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-O3 -std=c++17 -o test.html \
--post-js library_js.js -s LLD_REPORT_UNDEFINED=1


all:  tst1
	echo 'Built 1ink.us Textures.'
