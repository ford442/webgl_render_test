#pragma once
extern "C" {
void init_webgl(int width,int height);
void set_animation_frame_callback(void(*func)(double t,double dt));
double rand01(void);
void clear_screen(float r,float g,float b,float a);
void fill_solid_rectangle(float x0,float y0,float x1,float y1,float r,float g,float b,float a);
void fill_text(float x0,float y0,float r,float g,float b,float a,const char *str,float spacing,int charSize,int shadow);
void fill_image(float x0,float y0,float scale,float r,float g,float b,float a,const char *url);
void play_audio(const char *url,int loop);
}
