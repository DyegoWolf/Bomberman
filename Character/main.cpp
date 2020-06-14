#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>

// Vetor de texturas
GLuint texture[2];

#include "textures/face.c"

#define WIDTH 1340
#define HEIGHT 680

GLint faces[6][4] = {
  {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
  {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
};

GLfloat v[8][3] = {
	{-1.0, -1.0, 1.0}, {-1.0, -1.0, -1.0},
	{-1.0, 1.0, -1.0}, {-1.0, 1.0, 1.0},
	{1.0, -1.0, 1.0}, {1.0, -1.0, -1.0},
	{1.0, 1.0, -1.0}, {1.0, 1.0, 1.0}
};

void init();
void display();
void makeTextures();
void drawFace();

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(5, 5);
    glutCreateWindow("Bomberman - Boneco");
    glutDisplayFunc(display);
    init();

    glutMainLoop();

    return(0);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.8, 0.8, 0.8, 0.8);
    gluPerspective(45.0f,
                  (float)WIDTH / (float)HEIGHT,
                   1.0f, 100.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -5.0f);
    makeTextures();
}

// LEMBRETE:
// Utilizar texturas no formato .bmp, com proporção 512x512 (preferível)
void makeTextures()
{
    glGenTextures(2, texture); // Gera 4 nomes de textura e salva no vetor texture

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FACEB_WIDTH, FACEB_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, FACEB);
}

// Desenho da face do Bomberman
void drawFace()
{
    int i;

    for(i = 0; i < 6; i++)
    {
        // Apenas a face do cubo que representa o rosto é texturizada
        if(i == 5)
        {
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3fv(&v[faces[i][0]][0]);
                glTexCoord2f(0.0, 1.0);
                glVertex3fv(&v[faces[i][1]][0]);
                glTexCoord2f(1.0, 1.0);
                glVertex3fv(&v[faces[i][2]][0]);
                glTexCoord2f(1.0, 0.0);
                glVertex3fv(&v[faces[i][3]][0]);
            glEnd();
        }
        else
        {
            glColor3f(1.0, 1.0, 1.0); // Branco
            glBegin(GL_QUADS);
                glVertex3fv(&v[faces[i][0]][0]);
                glVertex3fv(&v[faces[i][1]][0]);
                glVertex3fv(&v[faces[i][2]][0]);
                glVertex3fv(&v[faces[i][3]][0]);
            glEnd();
        }
    }
}

// Geração das superfícies
void genSurfaceVertex1(float u, float v, float vertex[3])
{
    float r = 0.4;
    float theta = 2*M_PI*u;
    float z = -1 + 2*v;
    float y = r*sin(theta);
    float x = r*cos(theta);

    vertex[0] = x;
    vertex[1] = z;
    vertex[2] = y;
}

// Cilindro que representa o BRAÇO ESQUERDO
void drawSurface1()
{
    int i,j;
    const int h_div = 10;
    const int v_div = 10;

    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
        glTranslatef(-1.5,0.0,-10.0);
        glRotatef(115.0, 0.0, 0.0, 1.0);

        for(j=0;j<v_div;j++)
            for(i=0;i<h_div;i++)
            {
                glBegin(GL_QUADS);
                    if((i+j)%2)
                    {
                        glColor3f(1.0,1.0,1.0);
                    }
                    else
                    {
                        glColor3f(1.0,1.0,1.0);
                    }

                    float vertex[3];
                    genSurfaceVertex1((float)i/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)i/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);
                glEnd();

            }
    glPopMatrix();
}

// Cilindro que representa o BRAÇO DIREITO
void drawSurface2()
{
    int i,j;
    const int h_div = 10;
    const int v_div = 10;

    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
        glTranslatef(1.5,0.0,-10.0);
        glRotatef(-115.0, 0.0, 0.0, 1.0);

        for(j=0;j<v_div;j++)
            for(i=0;i<h_div;i++)
            {
                glBegin(GL_QUADS);
                    if((i+j)%2)
                    {
                        glColor3f(1.0,1.0,1.0);
                    }
                    else
                    {
                        glColor3f(1.0,1.0,1.0);
                    }

                    float vertex[3];
                    genSurfaceVertex1((float)i/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)i/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);
                glEnd();
            }
    glPopMatrix();
}

// Cilindro que representa a PERNA DIREITA
void drawSurface3()
{
    int i,j;
    const int h_div = 10;
    const int v_div = 10;

    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
        glTranslatef(0.7,-2.2,-10.0);
        glRotatef(15.0, 0.0, 0.0, 1.0);

        for(j=0;j<v_div;j++)
            for(i=0;i<h_div;i++)
            {
                glBegin(GL_QUADS);
                    if((i+j)%2)
                    {
                        glColor3f(1.0,1.0,1.0);
                    }
                    else
                    {
                        glColor3f(1.0,1.0,1.0);
                    }

                    float vertex[3];
                    genSurfaceVertex1((float)i/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)j/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);

                    genSurfaceVertex1((float)i/h_div, (float)(j+1)/v_div, vertex);
                    glVertex3fv(vertex);
                glEnd();
            }
    glPopMatrix();
}


// Cilindro que representa a PERNA ESQUERDA
void drawSurface4(){
int i,j;
const int h_div = 10;
const int v_div = 10;


 glColor3f(0.0,0.0,0.0);
 glPushMatrix();
 glTranslatef(-0.7,-2.2,-10.0);
 glRotatef(-15.0, 0.0, 0.0, 1.0);


for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,1.0,1.0);
 }else{
     glColor3f(1.0,1.0,1.0);
 }

 float vertex[3];
 genSurfaceVertex1((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Cilindro que representa a ANTENA
void drawSurfacea1(){
int i,j;
const int h_div = 10;
const int v_div = 10;


 glColor3f(0.0,0.0,0.0);
 glPushMatrix();
 glTranslatef(0.0,8.5,-25.0);


for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,1.0,1.0);
 }else{
     glColor3f(1.0,1.0,1.0);
 }

 float vertex[3];
 genSurfaceVertex1((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex1((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// ESFERA
void genSurfaceVertex(float u, float v, float vertex[3]){

  float theta = 2*M_PI*u;
  float z = -1 + 2*v;
  float r = sqrt(1.0 - z*z);

  float y = r*sin(theta);
  float x = r*cos(theta);

   vertex[0] = x;
   vertex[1] = z;
   vertex[2] = y;
}

void genSurfaceVertex8(float u, float v, float vertex[3]){

  float theta = 2*M_PI*u;
  float z = -1 + 2*v;
  float r = sqrt(1.0 - z);

  float y = r*sin(theta);
  float x = r*cos(theta);

   vertex[0] = x;
   vertex[1] = z;
   vertex[2] = y;
}

// Esfera representativa da parte de cima do CORPO
void drawSurfacec1(){
int i,j;
const int h_div = 20;
const int v_div = 20;

 glColor3f(0.0,0.0,0.0);
 glPushMatrix();
 glTranslatef(0.0,0.5,-10.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(0.0,0.0,1.0);
 }else{
     glColor3f(0.0,0.0,1.0);
 }

 float vertex[3];
 genSurfaceVertex8((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera representativa da parte debaixo do CORPO
void drawSurfacec2(){
int i,j;
const int h_div = 20;
const int v_div = 20;

 glColor3f(0.0,0.0,0.0);
 glPushMatrix();
 glTranslatef(0.0,-1.5,-10.0);
 glRotatef(180.0, 0.0, 0.0, 1.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(0.0,0.0,1.0);
 }else{
     glColor3f(0.0,0.0,1.0);
 }

 float vertex[3];
 genSurfaceVertex8((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex8((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera que simboliza a mão DIREITA
void drawSurfacem1(){
int i,j;
const int h_div = 20;
const int v_div = 20;


 glPushMatrix();
 glTranslatef(4.8,-1.0,-20.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,0.1098,0.6823);
 }else{
     glColor3f(1.0,0.1098,0.6823);
 }

 float vertex[3];
 genSurfaceVertex((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera que simboliza a mão ESQUERDA
void drawSurfacem2(){
int i,j;
const int h_div = 20;
const int v_div = 20;


 glPushMatrix();
 glTranslatef(-4.8,-1.0,-20.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,0.1098,0.6823);
 }else{
     glColor3f(1.0,0.1098,0.6823);
 }

 float vertex[3];
 genSurfaceVertex((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera que simboliza o pé DIREITO
void drawSurfacep1(){
int i,j;
const int h_div = 20;
const int v_div = 20;


 glPushMatrix();
 glTranslatef(2.0,-6.0,-20.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,0.1098,0.6823);
 }else{
     glColor3f(1.0,0.1098,0.6823);
 }

 float vertex[3];
 genSurfaceVertex((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera que simboliza o pé ESQUERDO
void drawSurfacep2(){
int i,j;
const int h_div = 20;
const int v_div = 20;


 glPushMatrix();
 glTranslatef(-2.0,-6.0,-20.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,0.1098,0.6823);
 }else{
     glColor3f(1.0,0.1098,0.6823);
 }

 float vertex[3];
 genSurfaceVertex((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

// Esfera que simboliza a ponta da ANTENA
void drawSurfacea2(){
int i,j;
const int h_div = 20;
const int v_div = 20;


 glPushMatrix();
 glTranslatef(0.0,9.5,-25.0);

for(j=0;j<v_div;j++)
  for(i=0;i<h_div;i++){
 glBegin(GL_QUADS);
 if((i+j)%2){
    glColor3f(1.0,0.1098,0.6823);
 }else{
    glColor3f(1.0,0.1098,0.6823);
 }

 float vertex[3];
 genSurfaceVertex((float)i/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)j/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)(i+1)/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 genSurfaceVertex((float)i/h_div, (float)(j+1)/v_div, vertex);
 glVertex3fv(vertex);

 glEnd();

 }
 glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glRotatef(-10.0, 0.0, 1.0, 0.0);

    // Cabeça
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTranslatef(0.0, 0.8, 0.0);
        glScalef(0.4, 0.4, 0.4);
        drawFace();
    glPopMatrix();

    // Corpo
    glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(0.0, 0.0, 10.0);
        drawSurfacec1();
        drawSurfacec2();
    glPopMatrix();

    // Pernas e braços
    glPushMatrix();
        glScalef(0.35, 0.35, 0.35);
        glTranslatef(0.0, 0.0, 10.0);
        drawSurface1();
        drawSurface2();
        drawSurface3();
        drawSurface4();
    glPopMatrix();

    // Mãos e pés
    glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
        glTranslatef(0.0, 0.0, 20.0);
        drawSurfacem1();
        drawSurfacem2();
        drawSurfacep1();
        drawSurfacep2();
    glPopMatrix();

    // Antena
    glPushMatrix();
        glScalef(0.2, 0.2, 0.2);
        glTranslatef(0.0, -1.4, 24.5);
        drawSurfacea2();
        drawSurfacea1();
    glPopMatrix();

    glutSwapBuffers();
}
