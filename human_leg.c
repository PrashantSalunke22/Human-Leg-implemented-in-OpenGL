#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
void display();
//void specialKeys();
float pnt_part1[250][3];
float pnt_part2[250][3];
float pnt_part3[250][3];
float pnt_part4[250][3];
float pnt_part5[250][3];
float pnt_part6[250][3];
float curv_pnt1[250][250][3];
float curv_pnt2[250][250][3];
float curv_pnt3[250][250][3];
/*
double rotate_y=0; 
double rotate_x=0;
double rotate_z=0;
GLfloat xRotated, yRotated, zRotated;
*/
void init()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,150.0);
}
float cal_val_4_point(float p1,float p2,float p3,float p4,float m)
{
  return( p1*pow((1-m),3) + p2*3*pow((1-m),2)*m + p3*3*pow(m,2)*(1-m) + p4*pow(m,3));
}
float cal_val_3_point(float p1,float p2,float p3,float m)
{
  return( p1*pow((1-m),2) + p2*2*(1-m)*m + p3*pow(m,2));
}
void find_points_4(float p1[3],float p2[3],float p3[3],float p4[3],float pnt_part[250][3])
{
  float m = 0.0, step = 0.004;
  int i;
  for(i=0;i<=250;i++)
  {
    if(m>1)
      break;
    pnt_part[i][0] = cal_val_4_point(p1[0],p2[0],p3[0],p4[0],m);
    pnt_part[i][1] = cal_val_4_point(p1[1],p2[1],p3[1],p4[1],m);
    pnt_part[i][2] = cal_val_4_point(p1[2],p2[2],p3[2],p4[2],m);
    m += step;
  }
}
void plot_curve(float points_arr[250][250][3])
{
  for(int j=0;j<=250;j++)
  {
    glBegin(GL_POINTS);
    for(int i=0;i<=250;i++)
    {
      glVertex3f(points_arr[j][i][0],points_arr[j][i][1],points_arr[j][i][2]);
    }
    glEnd();    
  }
}
void display()
{
  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  gluPerspective(20.0, 2.0, 2.0, 15.0);
  gluLookAt( 4.0, 0.0, 1.0,  0.0, 0.0, 0.2,  0.7, 0.7, 1.0);
  glTranslatef(0.0, 0.0, 0.0);
  glRotatef(20, 0.2, 0.0, 0.0);
  glRotatef(40, 0.0, 0.0, 0.2);
  glRotatef( 55, 0.1, 0.0, 0.0 );
  glRotatef( 55, 0.0, 0.1, 0.0 );
  glRotatef( 55, 0.0, 0.0, 0.1 );
  float p11[3]={0.0,0.6,0.0},p12[3]={0.6,0.6,0.0},p13[3]={0.4,0.7,0.8},p14[3]={0.7,0.4,0.0};
  float p21[3]={0.2,0.5,-0.1},p22[3]={0.2,0.5,0.2},p23[3]={0.8,0.7,0.2},p24[3]={0.3,0.6,0.0};
  float p31[3]={0.1,0.6,0.0},p32[3]={0.2,0.6,0.0},p33[3]={0.4,0.7,0.0},p34[3]={0.6,0.6,0.0};  
  float p41[3]={-0.1,1.1,0.1},p42[3]={0.2,0.6,0.0},p43[3]={0.4,0.7,0.0},p44[3]={0.6,0.5,0.0};  
  float p51[3]={0.0,0.5,0.3},p52[3]={0.2,0.5,0.0},p53[3]={0.4,0.4,0.0},p54[3]={0.6,0.5,0.0};
  float p61[3]={0.5,0.6,-0.3},p62[3]={0.4,0.6,0.0},p63[3]={0.5,0.8,0.2},p64[3]={1.0,0.7,-0.2};
  glColor3f(0.8,0.7,0.3);
  find_points_4(p11,p12,p13,p14,pnt_part1);
  find_points_4(p21,p22,p23,p24,pnt_part2);
  find_points_4(p31,p32,p33,p34,pnt_part3);  
  find_points_4(p41,p42,p43,p44,pnt_part4);  
  find_points_4(p51,p52,p53,p54,pnt_part5);  
  find_points_4(p61,p62,p63,p64,pnt_part6);
  for(int i=0;i<=250;i++)
  {
   float m = 0.0 ,step = 0.004;
   for(int j=0;j<250;j++)
   {
     for(int k=0;k<4;k++)
     {
       curv_pnt1[i][j][k]=cal_val_3_point(pnt_part1[i][k],pnt_part2[i][k],pnt_part3[i][k],m);
       curv_pnt2[i][j][k]=cal_val_3_point(pnt_part3[i][k],pnt_part4[i][k],pnt_part5[i][k],m);
       curv_pnt3[i][j][k]=cal_val_3_point(pnt_part5[i][k],pnt_part6[i][k],pnt_part1[i][k],m);
     }
     m+=step;
   } 
  } 
  plot_curve(curv_pnt1);
  plot_curve(curv_pnt2);
  plot_curve(curv_pnt3);
  glFlush();
  glutSwapBuffers();
}
 /*
void specialKeys( int key, int x, int y ) 
{
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 5;
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 5;
  else if (key == GLUT_KEY_UP)
    rotate_x += 5;
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 5;
  glutPostRedisplay();
}
 */
int main(int argc, char* argv[])
{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition (100, 100);
  glutInitWindowSize (1000, 800);
  glutCreateWindow("Human Leg");
  glEnable(GL_DEPTH_TEST);
  glutDisplayFunc(display);
 // glutSpecialFunc(specialKeys);
  glutMainLoop();
  return 0;
}
