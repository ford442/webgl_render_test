#include <math.h>
#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/html5.h>
#include <string.h>
#include <cstdio>

extern "C" {
void init_webgl(int width,int height);
void set_animation_frame_callback(void(*func)(double t,double dt));
double rand01(void);
void clear_screen(float r,float g,float b,float a);
void fill_solid_rectangle(float x0,float y0,float x1,float y1,float r,float g,float b,float a);
void fill_image(float x0,float y0,float scale,float r,float g,float b,float a,const char *url);
void request_animation_frame_loop(EM_BOOL(*cb)(float time,void *userData),void *userData);
void load_texture_from_url(GLuint texture,const char *url,int *outWidth,int *outHeight);
}
static int S;
static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE glContext;
static GLuint quad,colorPos,matPos,solidColor;
static float pixelWidth,pixelHeight;
static GLuint compile_shader(GLenum shaderType,const char *src){
GLuint shader=glCreateShader(shaderType);
glShaderSource(shader,1,&src,NULL);
glCompileShader(shader);
return shader;
}
static GLuint create_program(GLuint vertexShader,GLuint fragmentShader){
GLuint program=glCreateProgram();
glAttachShader(program,vertexShader);
glAttachShader(program,fragmentShader);
glBindAttribLocation(program,0,"pos");
glLinkProgram(program);
glUseProgram(program);
return program;
}
static GLuint create_texture(){
GLuint texture;
glGenTextures(1,&texture);
glBindTexture(GL_TEXTURE_2D,texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
return texture;
}
void EMSCRIPTEN_KEEPALIVE init_webgl(int width,int height){
double dpr=emscripten_get_device_pixel_ratio();
emscripten_set_element_css_size("canvas",width/dpr,height/dpr);
emscripten_set_canvas_element_size("canvas",width,height);
EmscriptenWebGLContextAttributes attrs;
emscripten_webgl_init_context_attributes(&attrs);
attrs.alpha=0;
attrs.majorVersion=2;
glContext=emscripten_webgl_create_context("canvas",&attrs);
emscripten_webgl_make_context_current(glContext);
pixelWidth=2.f/width;
pixelHeight=2.f/height;
static const char vertex_shader[]=
"attribute vec4 pos;"
"varying vec2 uv;"
"uniform mat4 mat;"
"void main(){"
"uv=pos.xy;"
"gl_Position=mat*pos;"
"}";
GLuint vs=compile_shader(GL_VERTEX_SHADER,vertex_shader);
static const char fragment_shader[]=
"precision lowp float;"
"uniform sampler2D tex;"
"varying vec2 uv;"
"uniform vec4 color;"
"void main(){"
"gl_FragColor=color*texture2D(tex,uv);"
"}";
GLuint fs=compile_shader(GL_FRAGMENT_SHADER,fragment_shader);
GLuint program=create_program(vs,fs);
colorPos=glGetUniformLocation(program,"color");
matPos=glGetUniformLocation(program,"mat");
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glGenBuffers(1,&quad);
glBindBuffer(GL_ARRAY_BUFFER,quad);
const float pos[]={0,0,1,0,0,1,1,1};
glBufferData(GL_ARRAY_BUFFER,sizeof(pos),pos,GL_STATIC_DRAW);
glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,0);
glEnableVertexAttribArray(0);
solidColor=create_texture();
unsigned int whitePixel=0xFFFFFFFFu;
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,1,1,0,GL_RGBA,GL_UNSIGNED_BYTE,&whitePixel);
}
double EMSCRIPTEN_KEEPALIVE rand01(){
return emscripten_random();
}
typedef void(*tick_func)(double t,double dt);
static EM_BOOL tick(double time,void *userData){
static double t0;
double dt=time-t0;
t0=time;
tick_func f=(tick_func)(userData);
f(time,dt);
return EM_TRUE;
}
void EMSCRIPTEN_KEEPALIVE clear_screen(float r,float g,float b,float a){
glClearColor(r,g,b,a);
glClear(GL_COLOR_BUFFER_BIT);
}
static void fill_textured_rectangle(float x0,float y0,float x1,float y1,float r,float g,float b,float a,GLuint texture){
float mat[16]={(x1-x0)*pixelWidth,0,0,0,0,(y1-y0)*pixelHeight,0,0,0,0,1,0,x0*pixelWidth-1.f,y0*pixelHeight-1.f,0,1};
glUniformMatrix4fv(matPos,1,0,mat);
glUniform4f(colorPos,r,g,b,a);
glBindTexture(GL_TEXTURE_2D,texture);
glDrawArrays(GL_TRIANGLE_STRIP,0,4);
}
void EMSCRIPTEN_KEEPALIVE fill_solid_rectangle(float x0,float y0,float x1,float y1,float r,float g,float b,float a)
{fill_textured_rectangle(x0,y0,x1,y1,r,g,b,a,solidColor);
}
typedef struct Texture{
char *url;
int w,h;
GLuint texture;
}Texture;
#define MAX_TEXTURES 256
static Texture textures[MAX_TEXTURES]={};
static Texture *find_or_cache_url(const char *url){
for(int i=0;i<MAX_TEXTURES;++i)
if(!strcmp(textures[i].url,url))
return textures+i;
else if(!textures[i].url){
textures[i].url=strdup(url);
textures[i].texture=create_texture();
load_texture_from_url(textures[i].texture,url,&textures[i].w,&textures[i].h);
return textures+i;
}
return 0;
}
void EMSCRIPTEN_KEEPALIVE fill_image(float x0,float y0,float scale,float r,float g,float b,float a,const char *url){
Texture *t=find_or_cache_url(url);
fill_textured_rectangle(x0,y0,x0+t->w*scale,y0+t->h* scale,r,g,b,a,t->texture);
}
void draw_frame(double t,double dt){
clear_screen(0.1f,0.2f,0.3f,1.f);
#define FPX 50.f
#define FPW 25.f
#define FPH (S-75.f)
fill_solid_rectangle(FPX,0.f,FPX+FPW,FPH,0,0,0,1.f);
#define FX 80
#define FH 200
#define FY (FPH-FH)
#define FW (18.f/11.f*FH)
#define GX 18
#define GY 11
#define BX ((double)FW/GX)
#define BY ((double)FH/GY)
#define COLOR(gx,gy)(((gx>=5&&gx<=7)||(gy>=4&&gy<=6))?1:0)
#define MIN(x,y)(((x)<(y))?(x):(y))
for(int y=0;y<GY;++y){
for(int x=0;x<GX;++x){
int c=COLOR(x,y);
float wy=sinf(0.3f*(x+t*0.01f))*GY*0.5f*(MIN((float)x*3.f/GX,1.f));
fill_solid_rectangle(FX+x*BX,FY+y*BY+wy,FX+(x+1)*BX,FY+(y+1)*BY+wy,c?0.f:1.f,c?47/255.f:1.f,c?108/255.f:1.f,1.f);
}}
fill_image(250.f,10.f,1.f,1.f,1.f,1.f,1.f,"reindeer.png");
}
int main(){
S=EM_ASM_INT({return parseInt(document.getElementById('pmhig').innerHTML,10);});
init_webgl(S,S);
printf("%u \n",S);
printf("%s \n","Test.");
emscripten_set_main_loop((void(*)())draw_frame,0,0);
}
