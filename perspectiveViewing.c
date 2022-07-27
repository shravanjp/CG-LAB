#include<stdio.h>
#include<GL/freeglut.h>

float viewer[3]={0.0,0.0,500.0};
float v[8][3] = {{-100,-100,100},{100,-100,100},{100,100,100},{-100,100,100},
					{-100,-100,-100},{100,-100,-100},{100,100,-100},{-100,100,-100}};
					
void myKey(unsigned char key,int x,int y){
	if(key == 'x')
		viewer[0]-=10.0;
	if(key == 'X')
		viewer[0]+=10.0;
	if(key == 'y')
		viewer[1]+=10.0;
	if(key == 'Y')
		viewer[1]-=10.0;
	if(key == 'z')
		viewer[2]+=10.0;
	if(key == 'Z')
		viewer[2]-=10.0;
	glutPostRedisplay();
}

void drawCube(GLfloat *a,GLfloat *b,GLfloat *c,GLfloat *d){
	glBegin(GL_POLYGON);
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
	glVertex3fv(d);
	glEnd();
}

void myDisplay(){
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-200,200,-200,200,200,800);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],0,0,0,0,1,0);
	
	glColor3f(1,0,0);
	drawCube(v[4],v[7],v[6],v[5]);
	glColor3f(0,1,0);
	drawCube(v[6],v[5],v[1],v[2]);
	glColor3f(0,0,1);
	drawCube(v[4],v[5],v[1],v[0]);
	glColor3f(1,1,0);
	drawCube(v[4],v[0],v[3],v[7]);
	glColor3f(1,0,1);
	drawCube(v[0],v[1],v[2],v[3]);
	glColor3f(0,1,1);
	drawCube(v[3],v[2],v[6],v[7]);
	glFlush();
}
int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Perspective Viewing");
	glutDisplayFunc(myDisplay);
	glutKeyBoardFunc(myKey);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}