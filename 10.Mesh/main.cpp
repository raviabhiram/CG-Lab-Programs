#include <iostream>
#include<GL/glut.h>

using namespace std;

int nx,ny,sx,sy,dx,dy;

void mesh()
{
    int i,j,x,y;
    x=sx;
    y=sy;
    glColor3f(1,0,0);
    for(i=0;i<nx;i++)
    {
        y=sy;
        for(j=0;j<ny;j++)
        {
            glBegin(GL_LINE_LOOP);
                glVertex2d(x,y);
                glVertex2d(x,y+dy);
                glVertex2d(x+dx,y+dy);
                glVertex2d(x+dx,y);
            glEnd();
            y=y+dy;
        }
        x=x+dx;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    mesh();
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the initial coordinates(xmin,ymin):- ";
    cin>>sx>>sy;
    cout<<"Enter the width and height of each block(dx,dy):- ";
    cin>>dx>>dy;
    cout<<"Enter the number of blocks in x and in y(nx,ny):- ";
    cin>>nx>>ny;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Mesh");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
