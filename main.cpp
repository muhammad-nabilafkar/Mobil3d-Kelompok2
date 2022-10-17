#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define ESCAPE 27

GLint window;
GLint window2;
GLint Xsize=1000;
GLint Ysize=800;
float i,theta;
GLint nml=0,day=1;

char name3[]="PROJECT:  3D CAR  ANIMATION";

GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0;
GLfloat xs=1.0,ys=1.0,zs=1.0;
GLfloat xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0;

GLfloat r=0,g=0,b=1;
GLint light=1;
int count=1,flg=1;
int view=0;
int flag1=0,aflag=1;            //to switch car driving mode
int flag2=0,wheelflag=0;   //to switch fog effect
GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y );

GLvoid Transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,Width/Height,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid InitGL(GLfloat Width, GLfloat Height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0);              /* Add line width,   ditto */
    Transform( Width, Height ); /* Perform the transformation */
    t=gluNewQuadric();
        gluQuadricDrawStyle(t, GLU_FILL);

    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void init()
{
    glClearColor(0,0,0,0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
	glutPostRedisplay();
}

void display_string(int x, int y, char *string, int font)
{
    int len,i;
	glColor3f(0.8,0.52,1.0);
	glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
    if(font==1)
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	if(font==2)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
	if(font==3)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
	if(font==4)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
	}
}

void display1(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	display_string(150,540,"Jurusan Teknik Informatika, Fakultas Teknik, Universitas Halu Oleo",1);
	display_string(280,500,name3,1);
	display_string(10,440,"MOUSE",2);
	display_string(10,410,"PRESS RIGHT BUTTON FOR MENU",3);
	display_string(10,370,"KEYBOARD",2);
	display_string(10,340,"X-Y-Z KEYS FOR CORRESPONDING ROTATION",3);
	display_string(10,280+30,"U-F FOR CAMERA VIEW SETTINGS",3);
	display_string(10,250+30,"USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR",3);
	display_string(10,220+30,"ESCAPE TO EXIT",3);
	display_string(325,150+30,"PRESS SPACE BAR TO ENTER",2);
	glutPostRedisplay();
	glutSwapBuffers();
}

GLvoid DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(view==0)
    {
        init();
        display1();
    }
    else
    {
    if(count==1)
    InitGL(Xsize,Ysize);
    if(aflag==1)/* Initialize our window. */
    glClearColor(1,1,1,1);
    else
    glClearColor(0.1,0.1,0.1,0);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(xangle,1.0,0.0,0.0);
    glRotatef(yangle,0.0,1.0,0.0);
    glRotatef(zangle,0.0,0.0,1.0);
    glTranslatef(xt,yt,zt);
    glScalef(xs,ys,zs);
    glEnable(GL_COLOR_MATERIAL);

    if(flag2==1)
    {
    GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};
    glFogfv(GL_FOG_COLOR,fogcolour);
    glFogf(GL_FOG_DENSITY,0.1);
    glFogi(GL_FOG_MODE,GL_EXP);
    glFogf(GL_FOG_START,3.0);
    glFogf(GL_FOG_END,100.0);
    glHint(GL_FOG_HINT, GL_FASTEST);
    glEnable(GL_FOG);
    }

    if(flag2==0)
    {
        glDisable(GL_FOG);
    }

    if(!aflag)
    {
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glPointSize(200.0);
        int ccount=0;
        float x=10,y=10;
        while(ccount<20)
    {
        glVertex2f(x,y);
        x+=10;
        y+=10;
        if(y>Ysize) y-=10;
        if(x>Xsize) x-=10;
        ccount++;
    }
    glEnd();}

    glColor3f(1.0,.75,0.0);
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex3f(0.2,0.3,0.3);
    glVertex3f(0.2,0.3,0.5);
    glEnd();
    glPointSize(200.0);

    /* OBJECT MODULE*/

    /* top of cube*/

    //************************BODY MOBIL DEPAN****************************************

    //******************BODY MOBIL TENGAH************************************

    //*********************JENDELA MOBIL**********************************

    //**************************************************************

    //*****************************JALANAN DAN EFEK RODA***********************************
    if(flag1)
    {

    }
    glEnd();

    //************JENDELA SUDUT

    //************KNALPPOT

    //********************BAN MOBIL

    //*************************************************************
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glutPostRedisplay();
    glutSwapBuffers();
    }
}

//------function
void NormalKey(GLubyte key, GLint x, GLint y)
{
    switch ( key )
    {
        case ESCAPE : printf("ESC pressed. Exit.\n");
        glutDestroyWindow(window);
        exit(0);
        break;

        case ' ':view=1;
        DrawGLScene();
        break;

        case 'x':
        xangle += 5.0;
        glutPostRedisplay();
        break;

        case 'X':
        xangle -= 5.0;
        glutPostRedisplay();
        break;

        case 'y':
        yangle += 5.0;
        glutPostRedisplay();
        break;

        case 'Y':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

        case 'z':
        zangle += 5.0;
        glutPostRedisplay();
        break;

        case 'Z':
        zangle -= 5.0;
        glutPostRedisplay();
        break;

        case 'u':                          /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;

        case 'U':
        yt -= 0.2;                      /* Move down */
        glutPostRedisplay();
        break;

        case 'f':                          /* Move forward */
        zt += 0.2;
        glutPostRedisplay();
        break;

        case 'F':
        zt -= 0.2;                      /* Move away */
        glutPostRedisplay();
        break;

        default:
        break;
    }

}

//----------------MOBIL BERGERAK
static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key )
    {
        case GLUT_KEY_RIGHT:
        if(!wheelflag)
        xt += 0.2;
        if(wheelflag)
    {
        angle+=5;
		xw+=0.2;
    }
    glutPostRedisplay();
    break;

    case GLUT_KEY_LEFT:
    if(!wheelflag)
    xt -= 0.2;
    if(wheelflag)
    {
        angle+=5;
		xw-=0.2;
    }
    glutPostRedisplay();
    break;
	}
}

void myMenu(int id)
{
     if (id==1)
	{
		flag1=0;
        wheelflag=0;
        glutPostRedisplay();
	}
	if(id ==2)
	{
		flag1=1;
		flag2=0;
		wheelflag=0;
		xangle += 5.0;
		glutPostRedisplay();
	}
	if (id==4)
	{
        wheelflag=1;
        glutPostRedisplay();
	}
    if(id==12)
	{
        aflag=1;
        day=1;
        glClearColor(1,1,1,1);
        glDisable(GL_FOG);
        glutPostRedisplay();
	}
	if(id==13)
	{
        aflag=0;
        day=0;
        flag2=2;
        glClearColor(0.1,0.1,0.1,0);
        GLfloat fogcolour[4]={0.0,0.0,0.0,1.0};

        glFogfv(GL_FOG_COLOR,fogcolour);
        glFogf(GL_FOG_DENSITY,0.5);
        glFogi(GL_FOG_MODE,GL_EXP);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);

        glutPostRedisplay();
    }
}

void colorMenu(int id)
{
    if (id==6)
	{
        r=g=0;
		b=1;
        glutPostRedisplay();
	}
    if(id ==7)
	{
		r=0.8;
		b=g=0;
		glutPostRedisplay();
	}
	if(id==8)
	{
	    g=1;
		r=b=0;
		glutPostRedisplay();
	}
	if (id==9)
	{
        r=b=g=0;
        glutPostRedisplay();
	}
	if(id==10)
	{
		b=0;
		r=g=1;
        glutPostRedisplay();
	}
	if(id==11)
	{
		b=r=g=.7;
        glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(Xsize,Ysize);
    glutInitWindowPosition(50,50);
    glutCreateWindow("3D CAR ANIMATION");
    glutDisplayFunc(DrawGLScene);
    glutKeyboardFunc(NormalKey);
    glutSpecialFunc( SpecialKeyFunc );
    InitGL(Xsize,Ysize);

    int submenu=glutCreateMenu(colorMenu);
    glutAddMenuEntry("blue", 6);
    glutAddMenuEntry("red", 7);
    glutAddMenuEntry("green",8);
    glutAddMenuEntry("black",9);
    glutAddMenuEntry("yellow",10);
    glutAddMenuEntry("grey",11);

    glutCreateMenu(myMenu);
    glutAddMenuEntry("car model mode", 1);
    glutAddMenuEntry("car driving mode", 2);
    glutAddMenuEntry("wheel effect",4);
    glutAddSubMenu("car colors",submenu);
    glutAddMenuEntry("daymode",12);
    glutAddMenuEntry("Night mode",13);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 1;
}
