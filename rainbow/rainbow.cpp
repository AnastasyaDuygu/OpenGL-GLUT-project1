/*********
CTIS164 - Template Source Program
----------
STUDENT : ANASTASYA DUYGU KILIC
SECTION : 001
HOMEWORK: HW1
----------
PROBLEMS:
----------
ADDITIONAL FEATURES:
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600

#define TIMER_PERIOD  60 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

#define START 0
#define COMPLEX 1
#define MOVE 2


/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth = 300, winHeight = 300; // current Window width and height
int x1 = 0, x2 = 0, x3 = 0, xA = 0, yA = 0;
int* cloud[3] = { &x1,&x2,&x3 };
int rainbowColor[7][3] = { 255, 0, 0 ,
255, 128, 0 ,
255, 255, 0 ,
0, 255, 0 ,
0, 128, 255 ,
0, 0, 204 ,
178, 102, 255 };
int mode = START;
char direction[10] = ""; //decides the direction and displays it
bool activeTimer = true;
bool f1Key = true; //if true Mode = MANUAL
bool rainbow = false; //if true (autonomous) rainbow appears
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
	float angle;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
	float angle;

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 100; i++)
	{
		angle = 2 * PI * i / 100;
		glVertex2f(x + r * cos(angle), y + r * sin(angle));
	}
	glEnd();
}

void print(int x, int y, const char* string, void* font)
{
	int len, i;

	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, string[i]);
	}
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len, i;
	len = (int)strlen(str);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}

//void drawClouds()
//{
//	glColor3f(1, 1, 1);
//	for (int i = 0; i < 3; i++)
//	{
//		circle(-200 + x1, 100, 30);
//		circle(-180 + x1, 130, 20);
//		circle(-150 + x1, 120, 30);
//		circle(-130 + x1, 98, 25);
//		circle(-165 + x1, 100, 30);
//	}
//}
//
// To display onto window using OpenGL commands
//
void drawClouds()
{
	int distx = 175, disty[3] = { 0,50,-10 };
	//basic cloud
	glColor3f(1, 1, 1);
	for (int i = 0; i < 3; i++)
	{
		circle(-200 + *cloud[i] + i * distx, 100 + i * disty[i], 30);
		circle(-180 + *cloud[i] + i * distx, 130 + i * disty[i], 20);
		circle(-150 + *cloud[i] + i * distx, 120 + i * disty[i], 30);
		circle(-130 + *cloud[i] + i * distx, 98 + i * disty[i], 25);
		circle(-165 + *cloud[i] + i * distx, 100 + i * disty[i], 30);
	}
}
void drawRainbow() {
	if (rainbow)
	{
		int width = 7;
		
		glLineWidth(width);
		
		glBegin(GL_LINES);
		for (int i = 0; i < 7; i++)
		{
			glColor3ub(rainbowColor[i][0], rainbowColor[i][1], rainbowColor[i][2]);
			glVertex2d(-45 + xA, 30 - i * width + yA);
			glVertex2d(-120 + i * 10 + xA, 30 - i * width + yA);
			glVertex2d(-110 + i * 10 + xA, 24 - i * width + yA);
			glVertex2d(-135 + xA, 24 - i * width + yA);
		}
		glEnd();

	}
}
void display() {
	//
	// clear window to black
	//
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//gradient background (purple + blue)
	glColor3ub(163, 197, 255);
	glBegin(GL_POLYGON);
	glVertex2d(-800, 800);
	glVertex2d(800, 800);
	glColor3ub(255, 150, 204);
	glVertex2d(800, -800);
	glVertex2d(-800, -800);
	glEnd();
	glColor3f(1, 1, 1);
	vprint(148, 270, GLUT_BITMAP_9_BY_15, " ANASTASYA KILIC");
	vprint(188, 250, GLUT_BITMAP_9_BY_15, "22102142");
	vprint(-290, 280, GLUT_BITMAP_9_BY_15, "Mode: ");
	vprint(-290, 260, GLUT_BITMAP_9_BY_15, "Direction: ");
	if (mode == START) {
		glColor3f(0, 1, 1);
		vprint(-130, 0, GLUT_BITMAP_9_BY_15, "Click");
		glColor3f(1, 1, 1);
		vprint(-80, 0, GLUT_BITMAP_9_BY_15, "to create/relocate the Cat.");
	}

	//on screen manual for user
	glColor3f(1, 1, 1);
	vprint(-290, -270, GLUT_BITMAP_9_BY_15, "Press <F1> to switch the mode and Arrow Keys to control the Cat.");
	glColor3f(0, 1, 1);
	vprint(-290, -270, GLUT_BITMAP_9_BY_15, "      <F1>                        Arrow Keys");

	if (f1Key == true)
		vprint(-230, 280, GLUT_BITMAP_9_BY_15, "MANUAL");
	else
		vprint(-230, 280, GLUT_BITMAP_9_BY_15, "AUTONOMOUS");

	if (f1Key == false) //shows direction in autonomous mode
	{
		if (strcmp(direction, "") != 0)
			vprint(-190, 260, GLUT_BITMAP_9_BY_15, "%s", direction);
		else vprint(-190, 260, GLUT_BITMAP_9_BY_15, "NOT SET");
	}
	else { //shows direction in manual mode
		if (right == true)
			vprint(-190, 260, GLUT_BITMAP_9_BY_15, "RIGHT");
		else if (left == true)
			vprint(-190, 260, GLUT_BITMAP_9_BY_15, "LEFT");
		else if (up == true)
			vprint(-190, 260, GLUT_BITMAP_9_BY_15, "UP");
		else if (down == true)
			vprint(-190, 260, GLUT_BITMAP_9_BY_15, "DOWN");
		else vprint(-190, 260, GLUT_BITMAP_9_BY_15, "NOT SET");
	}
	//end of onscreen manual
	drawClouds();

	if (mode == COMPLEX) {
		//nyan cat (complex shape)
		// body(bread)
		glColor3ub(253, 183, 128);
		glRectf(-40 + xA, -30 + yA, 50 + xA, 50 + yA);
		glRectf(-45 + xA, -25 + yA, 55 + xA, 45 + yA);
		//body(jam)
		glColor3ub(244, 171, 200);
		glRectf(-35 + xA, -20 + yA, 45 + xA, 40 + yA);
		glColor3ub(247, 100, 158);
		glPointSize(5);
		glBegin(GL_POINTS);
		glVertex2d(-15 + xA, -10 + yA);
		glVertex2d(-28 + xA, 0 + yA);
		glVertex2d(-20 + xA, 15 + yA);
		glVertex2d(-25 + xA, 30 + yA);
		glVertex2d(-7 + xA, 8 + yA);
		glVertex2d(0 + xA, 30 + yA);
		glVertex2d(5 + xA, 15 + yA);
		glVertex2d(4 + xA, -5 + yA);
		glVertex2d(25 + xA, 30 + yA);
		glEnd();
		//feet
		glColor3ub(132, 134, 138);
		glRectf(-35 + xA, -30 + yA, -22 + xA, -38 + yA);
		glRectf(35 + xA, -30 + yA, 22 + xA, -38 + yA);
		//rainbow
		drawRainbow();
		//tail
		glColor3ub(132, 134, 138);
		glRectf(-45 + xA, 0 + yA, -59 + xA, 10 + yA);
		glRectf(-50 + xA, 10 + yA, -65 + xA, 20 + yA);
		glRectf(-56 + xA, 20 + yA, -71 + xA, 30 + yA);
		//head
		circle(40 + xA, 0 + yA, 30);
		//earleft
		glBegin(GL_TRIANGLES);
		glVertex2d(9 + xA, 6 + yA);
		glVertex2d(6 + xA, 30 + yA);
		glVertex2d(32 + xA, 20 + yA);
		//earright
		glVertex2d(58 + xA, 25 + yA);
		glVertex2d(70 + xA, 7 + yA);
		glVertex2d(75 + xA, 30 + yA);
		glEnd();
		//eyes
		glColor3f(0, 0, 0);
		circle(23 + xA, -2 + yA, 3);
		circle(57 + xA, -2 + yA, 3);
		//blush
		glColor3ub(244, 171, 200);
		circle(23 + xA, -13 + yA, 5);
		circle(57 + xA, -13 + yA, 5);
	}

	

	glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
	// exit when ESC is pressed.
	if (key == 27)
		exit(0);

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = true;
		if (f1Key == true)
			yA += 5;
		else strcpy(direction, "UP");
		break;
	case GLUT_KEY_DOWN: down = true;
		if (f1Key == true)
			yA -= 5;
		else strcpy(direction, "DOWN");
		break;
	case GLUT_KEY_LEFT: left = true;
		if (f1Key == true)
			xA -= 5;
		else strcpy(direction, "LEFT");
		break;
	case GLUT_KEY_RIGHT: right = true;
		if (f1Key == true)
			xA += 5;
		else strcpy(direction, "RIGHT");
		break;

	}


	if (f1Key == false) //rainbow appears only in autonomous mode
	{
		rainbow = true;
	}
	else rainbow = false;

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{
	// Write your codes here.
	switch (key) {
	case GLUT_KEY_UP: up = false; break;
	case GLUT_KEY_DOWN: down = false; break;
	case GLUT_KEY_LEFT: left = false; break;
	case GLUT_KEY_RIGHT: right = false; break;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y)
{
	// Write your codes here.
	if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN)
	{
		mode = COMPLEX;

		switch (mode) {
		case COMPLEX:
			xA = x - winWidth / 2;
			yA = winHeight / 2 - y;
			break;
		}

		//locate where mouse is
		// mouseCoordinate_x = x - winWidth / 2
		// mouseCoordinate_7 = y - winHeight / 2
		// if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		//relocate;
	}
	if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN)
	{
		if (f1Key == false)
			f1Key = true;
		else f1Key = false;
	}

	// to refresh the window it calls display() function
	glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	display(); // refresh window.
}

void onMoveDown(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function   
	glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove(int x, int y) {
	// Write your codes here.



	// to refresh the window it calls display() function
	glutPostRedisplay();
}

#if TIMER_ON == 1
void onTimer(int v) {

	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
	// Write your codes here.

	if (activeTimer)
	{
		if (-x1 + 105 < winWidth / 2)
			x1--;
		else x1 = 550;
		if (-x2 - 70 < winWidth / 2)
			x2--;
		else x2 = 375;
		if (-x3 - 270 < winWidth / 2)
			x3--;
		else x3 = 175;
		if (f1Key == false) { //autonomous movement
			if (strcmp(direction, "UP") == 0)
				if (yA + 52 < winHeight / 2)
					yA += 4;
				else strcpy(direction, "DOWN"); //for the cat to bounce to the opposite side when it reaches the border
			if (strcmp(direction, "DOWN") == 0)
				if (-yA + 38 < winHeight / 2)
					yA -= 4;
				else strcpy(direction, "UP"); //for the cat to bounce to the opposite side when it reaches the border
			if (strcmp(direction, "LEFT") == 0)
				if (-xA + 72 < winWidth / 2)
					xA -= 4;
				else strcpy(direction, "RIGHT"); //for the cat to bounce to the opposite side when it reaches the border
			if (strcmp(direction, "RIGHT") == 0)
				if (xA + 76 < winWidth / 2)
					xA += 4;
				else strcpy(direction, "LEFT"); //for the cat to bounce to the opposite side when it reaches the border
		}

	}


	// to refresh the window it calls display() function
	glutPostRedisplay(); // display()

}
#endif

void Init() {

	// Smoothing shapes
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//glutInitWindowPosition(100, 100);
	glutCreateWindow("CTIS 164 HW 1");

	glutDisplayFunc(display);
	glutReshapeFunc(onResize);

	//
	// keyboard registration
	//
	glutKeyboardFunc(onKeyDown);
	glutSpecialFunc(onSpecialKeyDown);

	glutKeyboardUpFunc(onKeyUp);
	glutSpecialUpFunc(onSpecialKeyUp);

	//
	// mouse registration
	//
	glutMouseFunc(onClick);
	glutMotionFunc(onMoveDown);
	glutPassiveMotionFunc(onMove);

#if  TIMER_ON == 1
	// timer event
	glutTimerFunc(TIMER_PERIOD, onTimer, 0);
#endif

	Init();

	glutMainLoop();
}