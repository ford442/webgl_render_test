
tst1: main.cpp  Makefile
	em++ main.cpp  --closure 0 -sUSE_SDL=2 \
-sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto=thin -sSUPPORT_LONGJMP=0 -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
-O3 -std=c++17 -o test.html -sEXPORTED_FUNCTIONS='["_main","_load_texture_from_url"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--extern-js-library library_js.js


all:  tst1
	echo 'Built 1ink.us Textures.'
