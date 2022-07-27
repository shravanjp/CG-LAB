#include<stdio.h>
#include<GL/freeglut.h>

int axis=0;
float theta[3] = {0.0,0.0,0.0};

float vertices[8][3] = {
	{-1.0,-1.0,-1.0},
	{1.0,-1.0,-1.0},
	{1.0,1.0,-1.0},
	{-1.0,1.0,-1.0},
	{-1.0,-1.0,1.0},
	{1.0,-1.0,1.0},
	{1.0,1.0,1.0},
	{-1.0,1.0,1.0}
};

float colors[8][3]={
	{0.0,0.0,0.0},
	{1.0,0.0,0.0},
	{1.0,1.0,0.0},
	{0.0,1.0,0.0},
	{0.0,0.0,1.0},
	{1.0,0.0,1.0},
	{1.0,1.0,1.0},
	{0.0,1.0,1.0}
};

void myDisplay();
void spinCube();
void myMouse(int btn,int state,int x,int y);
void myReshape(int w,int h);


void polygon(int a,int b,int c,int d){
	glBegin(GL_POLYGON);
	glColor3fv(colors[a]);
	glVertex3fv(vertices[a]);
	glColor3fv(colors[b]);
	glVertex3fv(vertices[b]);
	glColor3fv(colors[c]);
	glVertex3fv(vertices[c]);
	glColor3fv(colors[d]);
	glVertex3fv(vertices[d]);
	glEnd();
}

void colorCube(){
//	polygon(0,3,2,1);
//	polygon(2,3,7,6);
//	polygon(0,4,7,3);
//	polygon(1,2,6,5);
//	polygon(4,5,6,7);
//	polygon(0,1,5,4);
	polygon(0,3,2,1);
	polygon(2,6,5,1);
	polygon(0,1,5,4);
	polygon(2,3,7,6);
	polygon(7,3,0,4);
	polygon(6,7,4,5);
}

void myDisplay(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(theta[0],1.0,0.0,0.0);
	glRotatef(theta[1],0.0,1.0,0.0);
	glRotatef(theta[2],0.0,0.0,1.0);
	colorCube();
	glFlush();
	glutSwapBuffers();
}

void spinCube(){
	theta[axis]+=0.1;
	if(theta[axis]>=360){
		theta[axis]=0;
	}
	glutPostRedisplay();
}

void myMouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
		axis = 0;
	if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
		axis = 1;
	if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
		axis = 2;
	spinCube();
}

void myReshape(int w,int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if(w<=h){
		glOrtho(-5.0,5.0,-5.0*(float)h/(float)w,5.0*(float)h/(float)w,-10.0,10.0);
	}
	else{
		glOrtho(-5.0*(float)w/(float)h,5.0*(float)w/(float)h,-5.0,5.0,-10.0,10.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Cube spin");
	
	glutMouseFunc(myMouse);
	glutIdleFunc(spinCube);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}