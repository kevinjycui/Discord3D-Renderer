// #include "../inc/main.h"
// #include "../inc/shader.h"

// #define STBI_MSC_SECURE_CRT
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include <stb/stb_image_write.h>


// int g_iWindowWidth = 512;
// int g_iWindowHeight = 512;
// int g_iGLUTWindowHandle = 0;

// int g_iErrorCode = 0;

// void InitGL(int argc, char* argv[]);
// void DisplayGL();
// void IdleGL();
// void KeyboardGL(unsigned char c, int x, int y);
// void MouseGL(int button, int state, int x, int y);
// void MotionGL(int x, int y);
// void ReshapeGL(int x, int h);

// float g_fRotate = 0.0f;
// float fRotationRate = 200.0f;

// std::clock_t g_PreviousTicks;
// std::clock_t g_CurrentTicks;

// void RenderScene();

// void Cleanup(int exitCode, bool bExit = true);

// /*
// void display()
// {
// 	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
// 	glClear(GL_COLOR_BUFFER_BIT);

// 	glBegin(GL_QUADS);
// 	glColor3f(1.0f, 0.0f, 0.0f);
// 	glVertex2f(-0.5f, -0.5f);
// 	glVertex2f( 0.5f, -0.5f);
// 	glVertex2f( 0.5f,  0.5f);
// 	glVertex2f(-0.5f,  0.5f);
// 	glEnd();

// 	glBegin(GL_TRIANGLE_FAN);
// 	glColor3f(0.0f, 0.0f, 1.0f);
// 	glVertex2f(0.0f, 0.0f);
// 	glVertex2f(1.0f, 1.0f);
// 	glVertex2f(0.5f, 0.0f);
// 	glVertex2f(-1.0f, 0.0f);
// 	glVertex2f(0.0f, 1.0f);
// 	glEnd();

// 	glFlush();
// }*/

// int main(int argc, char** argv) {
// 	g_PreviousTicks = std::clock();

// 	InitGL(argc, argv);
// 	glutMainLoop();
// 	/*
// 	glutInit(&argc, argv);
// 	glutCreateWindow("OpenGL Setup Test");
// 	glutInitWindowSize(320, 320);
// 	glutInitWindowPosition(50, 50);
// 	glutDisplayFunc(display);
// 	glutMainLoop();
// 	*/
// 	return 0;
// }

// void Cleanup(int errorCode, bool bExit)
// {
// 	if (g_iGLUTWindowHandle != 0)
// 	{
// 		glutDestroyWindow(g_iGLUTWindowHandle);
// 		g_iGLUTWindowHandle = 0;
// 	}
// 	if (!bExit) exit(errorCode);
// }

// void InitGL(int argc, char* argv[])
// {
// 	glutInit(&argc, argv);
// 	int iScreenWidth = glutGet(GLUT_SCREEN_WIDTH);
// 	int iScreenHeight = glutGet(GLUT_SCREEN_HEIGHT);

// 	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
// 	glutInitWindowPosition((iScreenWidth - g_iWindowWidth)/2, (iScreenHeight - g_iWindowHeight)/2);
// 	glutInitWindowSize(g_iWindowWidth, g_iWindowHeight);
// 	g_iGLUTWindowHandle = glutCreateWindow("OpenGL test");

// 	// glutDisplayFunc(DisplayGL);
// 	// glutIdleFunc(IdleGL);
// 	// glutMouseFunc(MouseGL);
// 	// glutMotionFunc(MotionGL);
// 	// glutKeyboardFunc(KeyboardGL);
// 	// glutReshapeFunc(ReshapeGL);

// 	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	// glClearDepth(1.0f);

// 	// glShadeModel(GL_SMOOTH);

// 	glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);
	

// 	InitShader();
// }

// void DisplayGL()
// {
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
// 	// RenderScene();
	
// 	glutSwapBuffers();
// 	glutPostRedisplay();
	
	
// 	GLsizei nrChannels = 3;
// 	GLsizei stride = nrChannels * g_iWindowWidth;
// 	stride += (stride % 4) ? (4 - stride % 4) : 0;
// 	GLsizei bufferSize = stride * g_iWindowHeight;
// 	std::vector<char> buffer(bufferSize);
// 	glPixelStorei(GL_PACK_ALIGNMENT, 4);
// 	glReadBuffer(GL_FRONT);	
// 	glReadPixels(0, 0, g_iWindowWidth, g_iWindowHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer.data());
// 	stbi_flip_vertically_on_write(true);
// 	stbi_write_png("sample.png", g_iWindowWidth, g_iWindowHeight, nrChannels, buffer.data(), stride);
// }

// void IdleGL()
// {
// 	g_CurrentTicks = std::clock();
// 	float deltaTicks = (g_CurrentTicks - g_PreviousTicks);
// 	g_PreviousTicks = g_CurrentTicks;

// 	float fDeltaTime = deltaTicks / (float) CLOCKS_PER_SEC;

// 	g_fRotate += fmodf(fRotationRate * fDeltaTime, 360.0f);
// 	if (g_fRotate < 0) g_fRotate += 360.0f;

// 	glutPostRedisplay();
	
// }

// void KeyboardGL(unsigned char c, int x, int y)
// {
// 	switch (c)
// 	{
// 		case '\033':
// 		case '\015':
// 		case 'Q':
// 		case 'q':
// 			Cleanup(0);
// 			break;
// 	}

// 	glutPostRedisplay();
// }

// void MouseGL(int button, int state, int x, int y)
// {

// }

// void MotionGL(int x, int y)
// {

// }

// void ReshapeGL(int w, int h)
// {
// 	if (h == 0) h =1;

// 	g_iWindowWidth = w;
// 	g_iWindowHeight = h;

// 	glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);

// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	gluPerspective(60.0, (GLdouble) g_iWindowWidth/(GLdouble) g_iWindowHeight, 0.1, 100.0);

// 	glutPostRedisplay();
// }

// void RenderScene()
// {
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	glEnable(GL_DEPTH_TEST);

// 	glTranslatef(0.0f, 0.0f, -6.0f);

// 	glPushMatrix();
// 	glRotatef(g_fRotate, 1.0f, 1.0f, 1.0f);
// 	glBegin(GL_QUADS);

// 	glColor3f(0.0f, 1.0f, 0.0f);
// 	glVertex3f( 1.0f, 1.0f,-1.0f);
// 	glVertex3f(-1.0f, 1.0f,-1.0f);
// 	glVertex3f(-1.0f, 1.0f, 1.0f);
// 	glVertex3f( 1.0f, 1.0f, 1.0f);

// 	glColor3f(1.0f, 0.5f, 0.0f);
// 	glVertex3f( 1.0f,-1.0f,-1.0f);
// 	glVertex3f(-1.0f,-1.0f,-1.0f);
// 	glVertex3f(-1.0f,-1.0f, 1.0f);
// 	glVertex3f( 1.0f,-1.0f, 1.0f);

// 	glColor3f(1.0f, 0.0f, 0.0f);
// 	glVertex3f( 1.0f, 1.0f, 1.0f);
// 	glVertex3f(-1.0f, 1.0f, 1.0f);
// 	glVertex3f(-1.0f,-1.0f, 1.0f);
// 	glVertex3f( 1.0f,-1.0f, 1.0f);

// 	glColor3f(1.0f, 1.0f, 0.0f);
// 	glVertex3f( 1.0f,-1.0f,-1.0f);
// 	glVertex3f(-1.0f,-1.0f,-1.0f);
// 	glVertex3f(-1.0f, 1.0f,-1.0f);
// 	glVertex3f( 1.0f, 1.0f,-1.0f);

// 	glColor3f(0.0f, 0.0f, 1.0f);
//         glVertex3f(-1.0f, 1.0f, 1.0f);
//         glVertex3f(-1.0f, 1.0f,-1.0f);
//         glVertex3f(-1.0f,-1.0f,-1.0f);
//         glVertex3f(-1.0f,-1.0f, 1.0f);
 
//         glColor3f(1.0f, 0.0f, 1.0f);
//         glVertex3f( 1.0f, 1.0f, 1.0f);
//         glVertex3f( 1.0f, 1.0f,-1.0f);
//         glVertex3f( 1.0f,-1.0f,-1.0f);
//         glVertex3f( 1.0f,-1.0f, 1.0f);

// 	glEnd();
// 	glPopMatrix();
// }
