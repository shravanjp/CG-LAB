#include<stdio.h>
#include<stdbool.h>
#include<stdbool.h>
#include<GL/freeglut.h>

float x0,y0,x1,y1;
float xmin,ymin,xmax,ymax;
float xvmin=200,xvmax=300,yvmin=200,yvmax=300;
bool accept=false,done=false;
int outcode0,outcode1,outcodeout;
int TOP=8,BOTTOM=4,LEFT=1,RIGHT=2;

void drawLine(){
	glBegin(GL_LINES);
	glVertex2f(x0,y0);
	glVertex2f(x1,y1);
	glEnd();	
}

void drawRectangle(){
	glBegin(GL_LINE_LOOP);
	glVertex2f(xmin,ymin);
	glVertex2f(xmax,ymin);
	glVertex2f(xmax,ymax);
	glVertex2f(xmin,ymax);
	glEnd();
}

int computeOutcode(float x,float y){
	int outcode=0;
	if(y>ymax)
		outcode = outcode|TOP;
    else if(y<ymin)
		outcode = outcode|BOTTOM;
	if(x>xmax)
		outcode = outcode|RIGHT;
	else if(x<xmin)
		outcode = outcode|LEFT;		
	
	return outcode;
}

void CSLCAD(){
	outcode0  = computeOutcode(x0,y0);
	outcode1  = computeOutcode(x1,y1);
	int x,y;
	
	do{
		if((outcode0 || outcode1) == 0){
			accept = true;
			done= true;
		}
		else if(outcode0&outcode1){
			done = true;
		}
		else{
			outcodeout = outcode0?outcode0:outcode1;
			
			if(outcodeout&TOP){
				x=x0+(ymax-y0)*(x1-x0)/(y1-y0);
				y=ymax;
			}
			else if(outcodeout&BOTTOM){
				x=x0+(ymin-y0)*(x1-x0)/(y1-y0);
				y=ymin;
			}
			else if(outcodeout&LEFT){
				y=y0+(xmin-x0)*(y1-y0)/(x1-x0);
				x=xmin;
			}
			else if(outcodeout&RIGHT){
				y=y0+(xmax-x0)*(y1-y0)/(x1-x0);
				x=xmax;
			}
			
			if(outcodeout == outcode0){
				x0 = x;
				y0 = y;
				outcode0= computeOutcode(x0,y0);
			}
			else{
				x1=x;
				y1=y;
				outcode1= computeOutcode(x1,y1);
			}
		}
		
	}while(!done);
	
	if(accept){
		float Sx = (xvmax-xvmin)/(xmax-xmin);
		float Sy = (yvmax-yvmin)/(ymax-ymin);
		float vx0= xvmin +(x0-xmin)*Sx;
		float vy0= yvmin +(y0-xmin)*Sy;
		float vx1= xvmin +(x1-xmin)*Sx;
		float vy1= yvmin +(y1-xmin)*Sx;	
		
		glBegin(GL_LINES);
		glVertex2f(vx0,vy0);
		glVertex2f(vx1,vy1);
		glEnd();	
		
		
	}
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(xvmin,yvmin);
	glVertex2f(xvmax,yvmin);
	glVertex2f(xvmax,yvmax);
	glVertex2f(xvmin,yvmax);
	glEnd();
}


void myDisplay(){
	glColor3f(1,0,0);
	drawLine();
	glColor3f(0,0,1);
	drawRectangle();
	CSLCAD();
	glFlush();
}


void myInit(){
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,500,0,500);
}
int main(int argc,char *argv[]){
	printf("Enter the clipping window coordinates:\n");
	scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
	printf("Enter the line endpoints:\n");
	scanf("%f%f%f%f",&x0,&y0,&x1,&y1);	
	glutInit(&argc,argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Cohen-Sutherland Line Clipping");
	myInit();
	glutDisplayFunc(myDisplay);
	glutMainLoop();
	return 0;
}