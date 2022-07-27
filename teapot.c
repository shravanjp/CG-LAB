#include<stdio.h>
#include<GL/freeglut.h>

void tableLeg(double legThick,double legLen){
	glPushMatrix();
	glTranslated(0,legLen/2,0);
	glScaled(legThick,legLen,legThick);
	glutSolidCube(1.0);
	glPopMatrix();
}

void table(double topWidth,double topThick,double legThick,double legLen){
	glPushMatrix();
	glTranslated(0,legLen,0);
	glScaled(topWidth,topThick,topWidth);
	glutSolidCube(1.0);
	glPopMatrix();
	
	double dist = 0.95*topWidth/2.0 - legThick/2.0;
	
	glPushMatrix();
	glTranslated(dist,0,dist);
	tableLeg(legThick,legLen);
	glTranslated(0,0,-2*dist);
	tableLeg(legThick,legLen);
	glTranslated(-2*dist,0,2*dist);
	tableLeg(legThick,legLen);
	glTranslated(0,0,-2*dist);
	tableLeg(legThick,legLen);
	glPopMatrix();
}

void displaySolid(){
	GLfloat mat_ambient[]={0.7f,0.7f,0.7f,0.7f};
	GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,0.5f};
	GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat mat_shininess[]={50.0f};
	
	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
	
	GLfloat light_intensity[] = {0.7f,0.7f,0.7f,0.7f};
	GLfloat light_position[] = {10.0f,10.0f,10.0f,10.0f};
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0,2.0,-1.0,1.0,0.1,100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(2.3,1.3,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
	glPushMatrix();
	glTranslated(0.5,0.7,0.5);
	glRotated(30,0,1,0);
	glutSolidTeapot(0.08);
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(0.4,0.0,0.4);
	table(0.6,0.02,0.02,0.6);
	glPopMatrix();
    
	glFlush();
}

int main(int argc,char *argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Tea pot");
	
	glClearColor(1,1,1,1);
	glutDisplayFunc(displaySolid);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glutMainLoop();
	return 0;
}