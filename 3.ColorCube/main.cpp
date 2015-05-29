#include <iostream>
#include<GL/glut.h>

using namespace std;

float vertices[][3]={{-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1},{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1}};
float colors[][3]={{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
float theta[]={0,0,0};
int axis=2;

void polygon(int a,int b,int c,int d)
{
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

void colorcube()
{
    polygon(0,3,2,1);
    polygon(1,2,6,5);
    polygon(3,7,6,2);
    polygon(0,4,7,3);
    polygon(4,5,6,7);
    polygon(0,4,5,1);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(theta[0],1,0,0);
    glRotatef(theta[1],0,1,0);
    glRotatef(theta[2],0,0,1);
    colorcube();
    glFlush();
    glutSwapBuffers();
}

void spincube()
{
    theta[axis]+=1;
    if(theta[axis]>360)
        theta[axis]-=360;
    glutPostRedisplay();
}

void mouse(int btn,int state,int x,int y)
{
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
        axis=0;
    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
        axis=1;
    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
        axis=2;
}

void myReshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<h)
        glOrtho(-2,2,-2*(float)h/(float)w,2*(float)h/(float)w,-10,10);
    else
        glOrtho(-2*(float)w/(float)h,2*(float)w/(float)h,-2,2,-10,10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Color Cube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(spincube);
    glutMouseFunc(mouse);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
