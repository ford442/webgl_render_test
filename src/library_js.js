mergeInto(LibraryManager.library, {
  upload_unicode_char_to_texture: function(unicodeChar, charSize, applyShadow) {
    var canvas = document.createElement('canvas');
    canvas.width = canvas.height = charSize;
//  document.body.appendChild(canvas); // Enable for debugging
    var ctx = canvas.getContext('2d');
    ctx.fillStyle = 'black';
    ctx.globalCompositeOperator = 'copy';
    ctx.globalAlpha = 0;
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    ctx.globalAlpha = 1;
    ctx.fillStyle = 'white';
    ctx.font = charSize + 'px Arial Unicode';
    if (applyShadow) {
      ctx.shadowColor = 'black';
      ctx.shadowOffsetX = 2;
      ctx.shadowOffsetY = 2;
      ctx.shadowBlur = 3;
      ctx.strokeStyle = 'gray';
      ctx.strokeText(String.fromCharCode(unicodeChar), 0, canvas.height-7);
    }
    ctx.fillText(String.fromCharCode(unicodeChar), 0, canvas.height-7);
    GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, true);
    GLctx.texImage2D(GLctx.TEXTURE_2D, 0, GLctx.RGBA, GLctx.RGBA, GLctx.UNSIGNED_BYTE, canvas);
    GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, false);
  },
  load_texture_from_url: function(glTexture, url, outW, outH) {
    var img = new Image();
    img.onload = function() {
      HEAPU32[outW>>2] = img.width;
      HEAPU32[outH>>2] = img.height;
      GLctx.bindTexture(GLctx.TEXTURE_2D, GL.textures[glTexture]);
      GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, true);
      GLctx.texImage2D(GLctx.TEXTURE_2D, 0, GLctx.RGBA, GLctx.RGBA, GLctx.UNSIGNED_BYTE, img);
      GLctx.pixelStorei(GLctx.UNPACK_FLIP_Y_WEBGL, false);
    };
    img.src = Pointer_stringify(url);
  },
  play_audio: function(url, loop) {
    var a = new Audio(Pointer_stringify(url));
    a.loop = !!loop;
    a.play();
  }
});
