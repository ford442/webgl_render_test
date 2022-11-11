
tst1:
	emcc main.cpp  --closure 0 \
  -sUSE_WEBGL2=1 -sMAX_WEBGL_VERSION=2 -sMIN_WEBGL_VERSION=2 \
  -o test.js \
  -sFORCE_FILESYSTEM=1 \
  -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
  --js-library library_js2.js --extern-pre-js setUp.js


tst2:
	emcc main2.cpp  -sFULL_ES2=0 -sFULL_ES3=1 \
  -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
  -sUSE_WEBGL2=1 --closure 1 -s TEXTDECODER=2  -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 \
  -s ENVIRONMENT=web -s GL_SUPPORT_AUTOMATIC_ENABLE_EXTENSIONS=0 -s GL_EXTENSIONS_IN_PREFIXED_FORMAT=0 \
  -s GL_POOL_TEMP_BUFFERS=0 -s AGGRESSIVE_VARIABLE_ELIMINATION=1 --emit-symbol-map \
  -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -s SUPPORT_ERRNO=0 -s GL_TRACK_ERRORS=0 \
  -o test2.js \
  --js-library library_js2.js --extern-pre-js setUp.js

tst3:
	emcc main3.cpp  -sFULL_ES2=0 -sFULL_ES3=1 \
  -sFORCE_FILESYSTEM=1 -sALLOW_MEMORY_GROWTH=0 -sINITIAL_MEMORY=1400mb \
  -sUSE_WEBGL2=1 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 \
  -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 \
  -o test3.js \
  --js-library library_js3.js --pre-js setUp.js


all:  tst3
	echo 'Built 1ink.us Textures.'
