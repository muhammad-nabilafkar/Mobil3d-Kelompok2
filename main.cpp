#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

#define ESCAPE 27

//Mobil3d Kelompok2

GLint window;
GLint window2;
GLint Xsize=1000; //ubah ukuran window
GLint Ysize=800;
float i,theta;
GLint nml=0,day=1;

char name3[]="PROJECT:  3D CAR  ANIMATION";

GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0;
GLfloat xs=1.0,ys=1.0,zs=1.0;
GLfloat xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0;

GLfloat r=0,g=0,b=1; //warna mobil
GLint light=1;
int count=1,flg=1;
int view=0; //tampilan menu/mobil
int cardriving=0,aflag=1;            //to switch car driving mode
int kabut=0,wheelflag=0;   //to switch fog effect
GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y );

GLvoid Transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height); //letak awal mobil
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,Width/Height,0.1,100.0); //jauh atau dekat
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
	glClearColor(1.0,1.0,1.0,1.0); //warna menu
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.8,0.52,1.0);
	display_string(150,540,"Jurusan Teknik Informatika, Fakultas Teknik, Universitas Halu Oleo",1);
	display_string(280,500,name3,1);
	display_string(255,460,"KELOMPOK 2 GRAFIKA KOMPUTER",1);
	display_string(10,410,"MOUSE",2);
	display_string(10,380,"PRESS RIGHT BUTTON FOR MENU",3);
	display_string(10,350,"KEYBOARD",2);
	display_string(10,320,"X-Y-Z KEYS FOR CORRESPONDING ROTATION",3);
	display_string(10,290,"U-F FOR CAMERA VIEW SETTINGS",3);
	display_string(10,260,"USE LEFT ARROW(<-) AND RIGHT ARROW(->) TO MOVE CAR",3);
	display_string(10,230,"ESCAPE TO EXIT",3);
	display_string(325,170,"PRESS SPACE BAR TO ENTER",2);
	glutPostRedisplay();
	glutSwapBuffers();
}

GLvoid DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(view==0) //menampilkan menu
    {
        init();
        display1();
    }
    else
    {
    if(count==1)
    InitGL(Xsize,Ysize);
    if(aflag==1)/* Initialize our window. */
    glClearColor(1,1,1,0); // warna latar
    else
    glClearColor(0.1,0.1,0.1,0); // warna night mode
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(xangle,1.0,0.0,0.0);
    glRotatef(yangle,0.0,1.0,0.0);
    glRotatef(zangle,0.0,0.0,1.0);
    glTranslatef(xt,yt,zt);
    glScalef(xs,ys,zs);
    glEnable(GL_COLOR_MATERIAL);

    if(kabut==1)
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

    if(kabut==0)
    {
        glDisable(GL_FOG);
    }

    if(!aflag)//lampu
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

    glColor3f(1.0,0.75,0.0);
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex3f(0.2,0.3,0.3);
    glVertex3f(0.2,0.3,0.5);
    glEnd();
    glPointSize(200.0);

    /* OBJECT MODULE*/

    glBegin(GL_QUADS);                /* OBJECT MODULE*/

    /* top of cube*/

    //************************BODY MOBIL DEPAN****************************************
    glColor3f(r,g,b);
    glVertex3f( 0.2, 0.4,0.6);
    glVertex3f(0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);

    /* bottom of cube*/
    glVertex3f( 0.2,0.4,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f( 0.2,0.2,0.2);

    /* front of cube*/
    glVertex3f( 0.2,0.2,0.6);
    glVertex3f(0.2, 0.4,0.6);
    glVertex3f(0.2,0.4,0.2);
    glVertex3f( 0.2,0.2,0.2);

    /* back of cube.*/
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.6,0.5,0.2);
    glVertex3f( 0.6,0.2,0.2);

    /* left of cube*/
    glVertex3f(0.2,0.2,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.2,0.4,0.6);

    /* Right of cube */
    glVertex3f(0.2,0.2,0.2);
    glVertex3f( 0.6,0.2,0.2);
    glVertex3f( 0.6,0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);

    //****************************************************************************
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.2);        //ATAP MOBIL
    glVertex3f(1.7,0.65,0.6);

    //***************************BODY MOBIL BELAKANG******************************
    glColor3f(r,g,b);            /* Set The Color To Blue*/
    glVertex3f( 1.8, 0.5,0.6);
    glVertex3f(1.8, 0.5,0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1,0.4,0.6);

    /* bottom of cube*/
    glVertex3f( 2.1,0.2,0.6);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f( 1.8,0.2,0.6);

    /* back of cube.*/
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(2.1,0.2,0.6);

    /* left of cube*/
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);

    /* Right of cube */
    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.5,0.6);
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.2,0.6);

    //******************BODY MOBIL TENGAH************************************
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.2,0.6);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8,0.5,0.6);

    /* bottom of cube*/
    glVertex3f( 0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f( 1.8,0.2,0.6);

    /* back of cube.*/
    glVertex3f(0.6,0.5,0.2);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);

    //*********************JENDELA MOBIL**********************************
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.2);
    glVertex3f(0.75, 0.5,0.2);        //quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f( 1.22,0.63,0.2);

    glVertex3f(1.27,0.63,0.2);
    glVertex3f(1.25,0.5,0.2);        //quad back window
    glVertex3f(1.65,0.5,0.2);
    glVertex3f(1.67,0.63,0.2);

    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(0.7,0.5,0.2);       //first separation
    glVertex3f(0.75,0.5,0.2);
    glVertex3f(0.77,0.65,0.2);

    glVertex3f(1.2,0.65,0.2);
    glVertex3f(1.2,0.5,0.2);       //second separation
    glVertex3f(1.25,0.5,0.2);
    glVertex3f(1.27,0.65,0.2);

    glVertex3f(1.65,0.65,0.2);
    glVertex3f(1.65,0.5,0.2);     //3d separation
    glVertex3f(1.7,0.5,0.2);
    glVertex3f(1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.2);
    glVertex3f(0.75, 0.63,0.2);        //line strip
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f( 1.7,0.65,0.2);

    glVertex3f( 0.75, 0.65,0.6);
    glVertex3f(0.75, 0.63,0.6);        //line strip
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f( 1.7,0.65,0.6);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.6);
    glVertex3f(0.75, 0.5,0.6);        //quad front window
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f( 1.22,0.63,0.6);

    glVertex3f(1.27,0.63,.6);
    glVertex3f(1.25,0.5,0.6);        //quad back window
    glVertex3f(1.65,0.5,0.6);
    glVertex3f(1.67,0.63,0.6);

    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.5,0.6);       //first separation
    glVertex3f(0.75,0.5,0.6);
    glVertex3f(0.77,0.65,0.6);

    glVertex3f(1.2,0.65,0.6);
    glVertex3f(1.2,0.5,0.6);       //second separation
    glVertex3f(1.25,0.5,0.6);
    glVertex3f(1.27,0.65,0.6);

    glVertex3f(1.65,0.65,0.6);
    glVertex3f(1.65,0.5,0.6);
    glVertex3f(1.7,0.5,0.6);
    glVertex3f(1.7,0.65,0.6);
    glEnd();

    //**************************************************************
    glBegin(GL_QUADS);
    /* top of cube*/
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);        //quad front window
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(0.7,0.65,0.6);

    glVertex3f(1.7,0.65,.6);
    glVertex3f(1.7,0.65,0.2);        //quad back window
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(1.8,0.5,0.6);

    //*****************************JALANAN DAN EFEK RODA***********************************
    if(cardriving)
    {
        glPushMatrix();
        glTranslatef(xw,0,0);
        glColor3f(0,1,0);
        glVertex3f(-100,0.1,-100);
        glVertex3f(-100,0.1,0);         //a green surroundings
        glVertex3f(100,0.1,0);
        glVertex3f(100,0.1,-100);

        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0);
        glVertex3f(-100,0.1,0.45);         //a long road
        glVertex3f(100,0.1,0.45);
        glVertex3f(100,0.1,0);

        glColor3f(1.0,0.75,0.0);
        glVertex3f(-100,0.1,0.45);       //a median
        glVertex3f(-100,0.1,0.55);
        glVertex3f(100,0.1,0.55);
        glVertex3f(100,0.1,0.45);

        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0.55);
        glVertex3f(-100,0.1,1);         //a long road
        glVertex3f(100,0.1,1);
        glVertex3f(100,0.1,0.55);

        glColor3f(0,1,0);
        glVertex3f(-100,0.1,1);
        glVertex3f(-100,0.1,100);         //a green surroundings
        glVertex3f(100,0.1,100);
        glVertex3f(100,0.1,1);
        glPopMatrix();
    }
    glEnd();

    if(wheelflag)
    {
        glPushMatrix();
        glTranslatef(xw,0,0);
        glColor3f(0.5,.2,0.3);
        glBegin(GL_QUADS);
        for(i=0;i<200;i+=0.2)
        {
            glVertex3f(-100+i,0,1);
            glVertex3f(-99.9+i,0,1);
            glVertex3f(-99.9+i,0.2,1);
            glVertex3f(-100+i,0.2,1);
            i+=0.5;
        }
        for(i=0;i<200;i+=0.2)
        {
            glVertex3f(-100+i,0,0);
            glVertex3f(-99.9+i,0,0);
            glVertex3f(-99.9+i,0.2,0);
            glVertex3f(-100+i,0.2,0);
            i+=0.5;
        }
        glEnd();
        glPopMatrix();
    }


    //************JENDELA SUDUT
    glBegin(GL_TRIANGLES);                /* start drawing the cube.*/
      /* top of cube*/
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f( 0.7,0.65,0.6);       //tri front window
    glVertex3f(0.7,0.5,0.6);

    glVertex3f( 0.6, 0.5,0.2);
    glVertex3f( 0.7,0.65,0.2);       //tri front window
    glVertex3f(0.7,0.5,0.2);

    glVertex3f( 1.7, 0.65,0.2);
    glVertex3f( 1.8,0.5,0.2);       //tri back window
    glVertex3f( 1.7,0.5,0.2);

    glVertex3f( 1.7, 0.65,0.6);
    glVertex3f( 1.8,0.5,0.6);       //tri back window
    glVertex3f(1.7,0.5,0.6);

    glEnd();


    //************KNALPPOT
    glPushMatrix();
    glColor3f(0.3,0.3,0.7);
    glTranslatef(1.65,0.2,0.3);
    glRotatef(90.0,0,1,0);
    gluCylinder(t,0.02,0.03,.5,10,10);
    glPopMatrix();
    //********************BAN MOBIL
    glColor3f(0.7,0.7,0.7); //warna velg
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(0.6,0.2,0.62);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(0.6,0.2,0.18);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(1.7,0.2,0.18);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
          }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(1.7,0.2,0.62);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();

    glTranslatef(0.6,0.2,0.6);
    glColor3f(0,0,0); //warna ban
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(0,0,-0.4);
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(1.1,0,0);
    glutSolidTorus(0.025,0.07,10,25);

    glTranslatef(0,0,0.4);
    glutSolidTorus(0.025,0.07,10,25);
    glPopMatrix();

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

        case ' ':view=1; //tekan spasi=pindah tampilan
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
     if (id==1) //car model mode
	{
		cardriving=0;
        wheelflag=0;
        glutPostRedisplay();
	}
	if  (id==2) //car driving mode
	{
		cardriving=1;
		kabut=0;
		wheelflag=0;
		xangle += 5.0;
		glutPostRedisplay();
	}
	if (id==4)
	{
        wheelflag=1; //wheel effect
        glutPostRedisplay();
	}
    if  (id==12) //day mode
	{
        aflag=1;
        day=1;
        glClearColor(1,1,1,1);
        glDisable(GL_FOG);
        glutPostRedisplay();
	}
	if  (id==13) //nightmode
	{
        aflag=0;
        day=0;
        kabut=2;
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
    if (id==6) //biru
	{
        r=g=0;
		b=1;
        glutPostRedisplay();
	}
    if(id ==7) //merah
	{
		r=0.8;
		b=g=0;
		glutPostRedisplay();
	}
	if(id==8) //hijau
	{
	    g=1;
		r=b=0;
		glutPostRedisplay();
	}
	if (id==9) //hitam
	{
        r=b=g=0;
        glutPostRedisplay();
	}
	if(id==10) //kuning
	{
		b=0;
		r=g=1;
        glutPostRedisplay();
	}
	if(id==11) //abuabu
	{
		b=r=g=0.7;
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
