#include <iostream>
#include<GL/glut.h>

using namespace std;

float xvmin,xvmax,yvmin,yvmax,sx,sy,vx0,vy0,vx1,vy1;
float xwmin,xwmax,ywmin,ywmax,x0,x1,y0,y1;
float xx0,yy0,xx1,yy1;

int cliptest(float p,float q,float* t1,float* t2)
{
    float t=q/p;
    cout<<"t= "<<t<<endl;
    if(p<0)
    {
        if(t>*t1)
            *t1=t;
        if(t>*t2)
            return 0;
    }
    else if(p>0)
    {
        if(t<*t2)
            *t2=t;
        if(t<*t1)
            return 0;
    }
    else if(p==0)
    {
        if(q<0)
            return 0;
    }
    return 1;
}

void liang(float x0,float y0,float x1,float y1)
{
    float dx,dy,te,tl;
    dx=x1-x0;
    dy=y1-y0;
    te=0;
    tl=1;
    xx1=x1;
    yy1=y1;
    xx0=x0;
    yy0=y0;
    if(cliptest(-dx,x0-xwmin,&te,&tl));
        if(cliptest(dx,xwmax-x0,&te,&tl));
            if(cliptest(-dy,y0-ywmin,&te,&tl));
                if(cliptest(dy,ywmax-y0,&te,&tl));
                {
                    cout<<"te= "<<te<<" tl= "<<tl<<endl;
                    if(tl<1)
                    {
                        xx1=x0+tl*dx;
                        yy1=y0+tl*dy;
                    }
                    if(te>0)
                    {
                        xx0=x0+te*dx;
                        yy0=y0+te*dy;
                    }
                    cout<<"xx0= "<<xx0<<" yy0= "<<yy0<<" xx1= "<<xx1<<" yy1= "<<yy1<<endl;
                    sx=(xvmax-xvmin)/(xwmax-xwmin);
                    sy=(yvmax-yvmin)/(ywmax-ywmin);
                    vx0=xvmin+(xx0-xwmin)*sx;
                    vy0=yvmin+(yy0-ywmin)*sy;
                    vx1=xvmin+(xx1-xwmin)*sx;
                    vy1=yvmin+(yy1-ywmin)*sy;
                    glColor3f(1,0,0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(xvmin,yvmin);
                        glVertex2f(xvmin,yvmax);
                        glVertex2f(xvmax,yvmax);
                        glVertex2f(xvmax,yvmin);
                    glEnd();
                    glColor3f(0,1,0);
                    glBegin(GL_LINES);
                        glVertex2f(vx0,vy0);
                        glVertex2f(vx1,vy1);
                    glEnd();
                    glColor3f(1,0,0);
                    glBegin(GL_LINE_LOOP);
                        glVertex2f(xwmin,ywmin);
                        glVertex2f(xwmin,ywmax);
                        glVertex2f(xwmax,ywmax);
                        glVertex2f(xwmax,ywmin);
                    glEnd();
                    glColor3f(0,1,0);
                    glBegin(GL_LINES);
                        glVertex2f(x0,y0);
                        glVertex2f(x1,y1);
                    glEnd();
                }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    liang(x0,y0,x1,y1);
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the xmin,xmax,ymin,ymax of the window:- ";
    cin>>xwmin>>xwmax>>ywmin>>ywmax;
    cout<<"Enter the xmin,xmax,ymin,ymax of the viewport:- ";
    cin>>xvmin>>xvmax>>yvmin>>yvmax;
    cout<<"Enter the coordinates of the line(x0,y0,x1,y1):- ";
    cin>>x0>>y0>>x1>>y1;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Liang-Barsky");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
