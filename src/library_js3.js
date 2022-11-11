mergeInto(LibraryManager.library, {
  uploadFlipped: function(img) {
    GLctx.pixelStorei(0x9240/*GLctx.UNPACK_FLIP_Y_WEBGL*/, true);
    GLctx.texImage2D(0x0DE1/*GLctx.TEXTURE_2D*/, 0, 0x1908/*GLctx.RGBA*/, 0x1908/*GLctx.RGBA*/, 0x1401/*GLctx.UNSIGNED_BYTE*/, img);
    GLctx.pixelStorei(0x9240/*GLctx.UNPACK_FLIP_Y_WEBGL*/, false);
  },
  load_texture_from_url__deps: ['uploadFlipped'],
  load_texture_from_url: function(glTexture, url, outW, outH) {
    var img = new Image();
    img.onload = function() {
      HEAPU32[outW>>2] = img.width;
      HEAPU32[outH>>2] = img.height;
      GLctx.bindTexture(0x0DE1/*GLctx.TEXTURE_2D*/, GL.textures[glTexture]);
      _uploadFlipped(img);
    };
    img.src = UTF8ToString(url);
  },
});
