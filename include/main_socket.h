#include "../include/main.h"
#include "../include/shader.h"

#define WIDTH 1200
#define HEIGHT 800


int gl_Init();
int gl_Loop();
int gl_Close();

extern GLFWwindow* window;
extern Shader shader;

extern int img_index;
extern char * pixelData;

extern GLsizei nrChannels;
extern GLsizei stride;
extern GLsizei bufferSize;

extern char pixels[2880000];
