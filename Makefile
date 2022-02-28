
tst1: main.cpp  Makefile
	em++ main.cpp  -sUSE_SDL=2 \
-sUSE_WEBGL2=1 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sFORCE_FILESYSTEM=1 \
-ffast-math -flto=thin -DNDEBUG -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb -sENVIRONMENT=web \
-O2 -std=c++17 -o test.html -sEXPORTED_FUNCTIONS='["_main","_load_texture_from_url"]' -sEXPORTED_RUNTIME_METHODS=ccall \
--js-library library_js.js


all:  tst1
	echo 'Built 1ink.us Textures.'
