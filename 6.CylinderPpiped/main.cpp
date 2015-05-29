#include <iostream>
#include<GL/glut.h>

using namespace std;

double radius,cx,cy,bx,by,dx,dy;
int n,m;

void draw_pixel(double x,double y)
{
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2d(x,y);
    glEnd();
}

void plotpixels(double h,double k,int x,int y)
{
    draw_pixel(h+x,k+y);
    draw_pixel(h-x,k+y);
    draw_pixel(h-x,k-y);
    draw_pixel(h+x,k-y);
    draw_pixel(h+y,k+x);
    draw_pixel(h-y,k+x);
    draw_pixel(h-y,k-x);
    draw_pixel(h+y,k-x);
}

void cylinder()
{
    int d,x,y;
    d=1-radius;
    y=radius;
    x=0;
    while(y>x)
    {
        plotpixels(cx,cy,x,y);
        if(d<0)
            d+=(2*x)+3;
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        x++;
    }
}

void parallelopiped()
{
    double x=bx,y=by;
    for(int i=0;i<m;i++)
    {
        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
            glVertex2d(x,y);
            glVertex2d(x,y+dy);
            glVertex2d(x+dx,y+dy);
            glVertex2d(x+dx,y);
        glEnd();
        x++;
        y++;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<n;i++,cy++)
        cylinder();
    parallelopiped();
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the radius of the circle:- ";
    cin>>radius;
    cout<<"Enter the center of the circle(x,y):- ";
    cin>>cx>>cy;
    cout<<"Enter the number of circles:- ";
    cin>>n;
    cout<<"Enter the base of the rectangle(xmin,ymin):- ";
    cin>>bx>>by;
    cout<<"Enter the width and height of the rectangle(dx,dy):- ";
    cin>>dx>>dy;
    cout<<"Enter the number of rectangles:- ";
    cin>>m;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Cylinder-Parallelopiped");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
