#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>

// Função da esfera
void drawSurface()
{
    int i,j;
    const int h_div = 20;
    const int v_div = 20;

    float angle = (1.0/0.2)*glutGet(GLUT_ELAPSED_TIME)/15000.0;

    glColor3f(angle,angle,angle);
    glPushMatrix();

    for(j=0;j<v_div;j++)
        for(i=0;i<h_div;i++)
        {
            glBegin(GL_QUADS);
                if((i+j)%2)
                {
                    glColor3f(angle,angle,angle);
                }
                else
                {
                    glColor3f(angle,angle,angle);
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

// Pavio da bomba
void drawSurfaceCilindro()
{
    int i,j;
    const int h_div = 10;
    const int v_div = 10;

    glColor3f(0.0,0.0,0.0);
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glScalef(0.5, 0.5, 0.5);

    for(j=0;j<v_div;j++)
        for(i=0;i<h_div;i++)
        {
            glBegin(GL_QUADS);
                if((i+j)%2)
                {
                    glColor3f(1.0,0.0,0.0);
                }
                else
                {
                    glColor3f(1.0,0.0,0.0);
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

// Exibe as imagens definida na função na janela
void drawBomb()
{
    drawSurfaceCilindro();
    drawSurface();
}
