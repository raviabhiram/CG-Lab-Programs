#include <iostream>
#include<GL/glut.h>

double x1,x2,x3,x4,y1,y2,y3,y4;

using namespace std;

void drawpixel(double x,double y)
{
    glColor3f(1,0,0);
    glBegin(GL_POINTS);
        glVertex2d(x,y);
    glEnd();
}

void edgedetect(double x1,double y1,double x2,double y2,int* le,int* re)
{
    float mx,x,temp;
    int i;
    if((y2-y1)<0)
    {
        temp=y2;
        y2=y1;
        y1=temp;
        temp=x2;
        x2=x1;
        x1=temp;
    }
    if((y2-y1)!=0)
        mx=(x2-x1)/(y2-y1);
    else
        mx=x2-x1;
    x=x1;
    cout<<"mx= "<<mx<<endl;
    for(i=y1;i<y2;i++)
    {
        if(x<(float)le[i])
        {
            le[i]=(int)x;
        }
        if(x>(float)re[i])
         {
            re[i]=(int)x;
        }
        x+=mx;
    }
}

void scanfill()
{
    int le[500],re[500];
    int i,j;
    for(i=0;i<500;i++)
    {
        le[i]=500;
        re[i]=0;
    }
    edgedetect(x1,y1,x2,y2,le,re);
    edgedetect(x2,y2,x3,y3,le,re);
    edgedetect(x3,y3,x4,y4,le,re);
    edgedetect(x4,y4,x1,y1,le,re);
    for(j=0;j<500;j++)
    {
        if(le[j]<=re[j])
            for(i=le[j];i<=re[j];i++)
            {
                drawpixel(i,j);
                glFlush();
            }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
        glVertex2d(x3,y3);
        glVertex2d(x4,y4);
    glEnd();
    glFlush();
    scanfill();
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    glColor3f(1,0,0);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char**argv)
{
    cout<<"Enter teh coordinates of the quadrilateral(x1,y1,x2,y2,x3,y3,x4,y4):- ";
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Scan-line fill");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
