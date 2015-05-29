#include <iostream>
#include<GL/glut.h>

#define outcode int

using namespace std;

double xwmin,xwmax,ywmin,ywmax,x0,y0,x1,y1;
double xvmin,xvmax,yvmin,yvmax,sx,sy,vx0,vy0,vx1,vy1;
const int RIGHT=2,LEFT=1,TOP=8,BOTTOM=4;
int n;

outcode coc(double x,double y)
{
    outcode code=0;
    if(y>ywmax)
        code|=TOP;
    else if(y<ywmin)
        code|=BOTTOM;
    if(x>xwmax)
        code|=RIGHT;
    else if(x<xwmin)
        code|=LEFT;
    return code;
}

void cs(double x0,double y0,double x1,double y1)
{
    outcode oc0,oc1,ocout;
    bool accept=false,done=false;
    oc0=coc(x0,y0);
    oc1=coc(x1,y1);
    do
    {
        if(!(oc0|oc1))
            accept=done=true;
        else if(oc0&oc1)
            done=true;
        else
        {
            double x,y;
            ocout=oc0?oc0:oc1;
            if(ocout&TOP)
            {
                y=ywmax;
                x=x0+(x1-x0)*(ywmax-y0)/(y1-y0);
            }
            else if(ocout&BOTTOM)
            {
                y=ywmin;
                x=x0+(x1-x0)*(ywmin-y0)/(y1-y0);
            }
            else if(ocout&LEFT)
            {
                x=xwmin;
                y=y0+(y1-y0)*(xwmin-x0)/(x1-x0);
            }
            else if(ocout&RIGHT)
            {
                x=xwmax;
                y=y0+(y1-y0)*(xwmax-x0)/(x1-x0);
            }
            if(ocout==oc0)
            {
                x0=x;
                y0=y;
                oc0=coc(x0,y0);
            }
            else
            {
                x1=x;
                y1=y;
                oc1=coc(x1,y1);
            }
        }
    }while(!done);
    if(accept)
    {
        sx=(xvmax-xvmin)/(xwmax-xwmin);
        sy=(yvmax-yvmin)/(ywmax-ywmin);
        vx0=xvmin+(x0-xwmin)*sx;
        vx1=xvmin+(x1-xwmin)*sx;
        vy0=yvmin+(y0-ywmin)*sy;
        vy1=yvmin+(y1-ywmin)*sy;
        glColor3f(0,0,1);
        glBegin(GL_LINES);
            glVertex2d(vx0,vy0);
            glVertex2d(vx1,vy1);
        glEnd();
        glColor3f(1,0,0);
        glBegin(GL_LINE_LOOP);
            glVertex2d(xvmin,yvmin);
            glVertex2d(xvmin,yvmax);
            glVertex2d(xvmax,yvmax);
            glVertex2d(xvmax,yvmin);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex2d(x0,y0);
        glVertex2d(x1,y1);
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2d(xwmin,ywmin);
        glVertex2d(xwmin,ywmax);
        glVertex2d(xwmax,ywmax);
        glVertex2d(xwmax,ywmin);
    glEnd();
    cs(x0,y0,x1,y1);
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the coordinates of the window(xmin,ymin,xmax,ymax):- ";
    cin>>xwmin>>ywmin>>xwmax>>ywmax;
    cout<<"Enter the coordinates of the viewport(xmin,ymin,xmax,ymax):- ";
    cin>>xvmin>>yvmin>>xvmax>>yvmax;
    cout<<"Enter the coordinates of the line(x0,y0.x1,y1):- ";
    cin>>x0>>y0>>x1>>y1;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cohen-Sutherland");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
