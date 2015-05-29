#include<iostream>
#include<GL/glut.h>

using namespace std;

int steps;
float v[4][3]={{0,0,0.1},{0,0.942809,-0.33},{-0.816497,-0.471405,-0.33},{0.816497,-0.471405,-0.33}};

void triangle(float* a,float* b,float* c)
{
    glBegin(GL_POLYGON);
        glVertex3fv(a);
        glVertex3fv(b);
        glVertex3fv(c);
    glEnd();
}

void divide_triangle(float* a,float* b,float* c,int p)
{
    float v1[3],v2[3],v3[3];
    int j;
    if(p>0)
    {
        for(j=0;j<3;j++)
        {
            v1[j]=(a[j]+b[j])/2;
            v2[j]=(a[j]+c[j])/2;
            v3[j]=(b[j]+c[j])/2;
        }
        divide_triangle(a,v1,v2,p-1);
        divide_triangle(c,v2,v3,p-1);
        divide_triangle(b,v3,v1,p-1);
    }
    else
        triangle(a,b,c);
}

void tetrahederon()
{
    glColor3f(1,0,0);
    divide_triangle(v[0],v[1],v[2],steps);
    glColor3f(0,1,0);
    divide_triangle(v[3],v[2],v[1],steps);
    glColor3f(0,0,1);
    divide_triangle(v[0],v[3],v[1],steps);
    glColor3f(1,0,1);
    divide_triangle(v[0],v[2],v[3],steps);

}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    tetrahederon();
    glFlush();
}

void myinit()
{
    glClearColor(1,1,1,1);
    glOrtho(-2,2,-2,2,-2,2);
}

int main(int argc,char** argv)
{
    cout<<"Enter the nuber of recursive steps to be done:- ";
    cin>>steps;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Sierpinski");
    myinit();
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
