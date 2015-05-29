#include <iostream>
#include<GL/glut.h>
#include<math.h>

using namespace std;

float house[3][9]={{100,100,175,250,250,150,150,200,200},{100,300,400,300,100,100,150,150,100},{1,1,1,1,1,1,1,1,1}};
float rotmat[3][3]={{0},{0},{0}};
float result[3][9];
int h=100,k=100;
float theta=0,rtheta=0;

void multiply()
{
    int i,j,l;
    for(i=0;i<3;i++)
        for(j=0;j<9;j++)
        {
            result[i][j]=0;
            for(l=0;l<3;l++)
                result[i][j]=result[i][j]+rotmat[i][l]*house[l][j];
        }
}

void rotatehouse()
{
    float m,n;
    cout<<"cos = "<<cos(rtheta)<<endl;
    cout<<"sin = "<<sin(rtheta)<<endl;
    m=h*(1-cos(rtheta))+k*(sin(rtheta));
    n=k*(1-cos(rtheta))-h*(sin(rtheta));
    rotmat[0][0]=cos(rtheta);
    rotmat[0][1]=-sin(rtheta);
    rotmat[0][2]=m;
    rotmat[1][0]=sin(rtheta);
    rotmat[1][1]=cos(rtheta);
    rotmat[1][2]=n;
    rotmat[2][0]=0;
    rotmat[2][1]=0;
    rotmat[2][2]=1;
    multiply();
}

void drawhouse(float fig[3][9])
{
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(fig[0][0],fig[1][0]);
        glVertex2i(fig[0][1],fig[1][1]);
        glVertex2i(fig[0][3],fig[1][3]);
        glVertex2i(fig[0][4],fig[1][4]);
    glEnd();
    glColor3f(1,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(fig[0][5],fig[1][5]);
        glVertex2i(fig[0][6],fig[1][6]);
        glVertex2i(fig[0][7],fig[1][7]);
        glVertex2i(fig[0][8],fig[1][8]);
    glEnd();
    glColor3f(1,0,1);
    glBegin(GL_LINE_LOOP);
        glVertex2i(fig[0][1],fig[1][1]);
        glVertex2i(fig[0][2],fig[1][2]);
        glVertex2i(fig[0][3],fig[1][3]);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawhouse(house);
    rotatehouse();
    drawhouse(result);
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    gluOrtho2D(0,500,0,500);
}

int main(int argc,char** argv)
{
    cout<<"Enter the degree of rotation:- ";
    cin>>theta;
    rtheta=(22*theta)/(180*7);
    cout<<"rtheta= "<<rtheta<<endl;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("house");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
