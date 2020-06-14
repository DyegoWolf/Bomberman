#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include<time.h>
#include "character.cpp"
#include "bomb.cpp"
//#include <SFML/Audio.hpp>

// Controle de bombas do usuário
int bombaPlayer1 = 0;
int bombaPlayer2 = 0;

int b1x = 0;
int b1y = 0;
int b2x = 0;
int b2y = 0;

// Variáveis para controle da direção do jogador 1
int up1 = 0;
int down1 = 0;
int left1 = 0;
int right1 = 0;

// Variáveis para controle da direção do jogador 2
int up2 = 0;
int down2 = 0;
int left2 = 0;
int right2 = 0;

// Movimentos do Jogador 2
int Jog1_X = -15;
int Jog1_Y = -10;

// Movimentos do Jogador 1
int Jog2_X = 13;
int Jog2_Y = 10;

// Vetor de texturas
GLuint texture[3];

// Extremidades do cenário principal
int XMax = 13;
int XMin = -15;
int YMax = 10;
int YMin = -10;

#include "textures/obstacle.c"
#include "textures/floor.c"
#include "textures/box.c"

#define WIDTH 1340
#define HEIGHT 680

// Para dest:
// 1 - destrutível
// 0 - obstáculos


typedef struct bloco Bloco;

struct bloco{
    int x;
    int y;
    int dest;
};

Bloco bloco[15][11];

void init();
void display();
void makeTextures();
void drawBox();
void drawObstacles();
void drawScenario();
void chao();
void caixasDestrutiveis();
void carregaObstaculos();
void espacoBranco();
void keyboardPlayer1(unsigned char key, int x, int y);
void keyboardPlayer2(int key, int x, int y);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(5, 5);
    glutCreateWindow("Bomberman - Battle Game");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardPlayer1);
    glutSpecialFunc(keyboardPlayer2);
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
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluPerspective(45.0f,
                  (float)WIDTH / (float)HEIGHT,
                   1.0f, 100.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);

    carregaObstaculos();
    espacoBranco();
    makeTextures();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // Jogador 1
    glPushMatrix();
        glTranslatef(Jog1_X, Jog1_Y, -30.0f);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        // Controle da direção do personagem
        if(up1 == 1)
            glRotatef(-180.0, 0.0, 1.0, 0.0);
        if(down1 == 1)
            glRotatef(360.0, 0.0, 1.0, 0.0);
        if(left1 == 1)
            glRotatef(-90.0, 0.0, 1.0, 0.0);
        if(right1 == 1)
            glRotatef(90.0, 0.0, 1.0, 0.0);

        drawCharacter1();
    glPopMatrix();

    // Jogador 2
    glPushMatrix();
        glTranslatef(Jog2_X, Jog2_Y, -30.0f);
        glRotatef(90.0, 1.0, 0.0, 0.0);

        // Controle da direção do personagem
        if(up2 == 1)
            glRotatef(-180.0, 0.0, 1.0, 0.0);
        if(down2 == 1)
            glRotatef(360.0, 0.0, 1.0, 0.0);
        if(left2 == 1)
            glRotatef(-90.0, 0.0, 1.0, 0.0);
        if(right2 == 1)
            glRotatef(90.0, 0.0, 1.0, 0.0);

        drawCharacter2();
    glPopMatrix();

    // Definição de bomba no atual ponto do jogador 1
    if(bombaPlayer1 == 1)
    {
        b1x = Jog1_X;
        b1y = Jog1_Y;
        glPushMatrix();
            glTranslatef(b1x, b1y, -30.0f);
            glScalef(0.8, 0.8, 0.8);
            drawBomb();
        glPopMatrix();
    }

    // Definição de bomba no atual ponto do jogador 2
    if(bombaPlayer2 == 1)
    {
        b2x = Jog2_X;
        b2y = Jog2_Y;
        glPushMatrix();
            glTranslatef(b2x, b2y, -30.0f);
            glScalef(0.8, 0.8, 0.8);
            drawBomb();
        glPopMatrix();

    }

    // Obstáculos do cenário
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        drawObstacles();
    glPopMatrix();

    // Cenário
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        drawScenario();
    glPopMatrix();

    // Chão
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        chao();
    glPopMatrix();

    // Blocos de tijolo
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
        caixasDestrutiveis();
    glPopMatrix();

    glutSwapBuffers();
}

// Mapeamento de texturas
void makeTextures()
{
    glGenTextures(3, texture); // Gera 4 nomes de textura e salva no vetor texture

    // Obstáculo
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, OBSTACLE_WIDTH, OBSTACLE_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, OBSTACLE);

    // Chão
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, FLOOR_WIDTH, FLOOR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, FLOOR);

    // Tijolo
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BOX_WIDTH, BOX_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, BOX);
}

// Função que carrega espaços em branco e os representa na matriz
void espacoBranco()
{
    int x, y;
    srand(time(NULL));
    for(int k = 0; k < 100; k++)
    {
        x = rand() % 15;
        y = rand() % 10;
        if((x%2 == 0  && y%2 != 0) || (x%2 != 0  && y%2 == 0))
        {
            bloco[x][y].x = 2*x - 15;
            bloco[x][y].y = 2*y - 10;

            bloco[x][y].dest = 0;
        }
    }
}

// Função que carrega valores para a matriz que representa o jogo
void carregaObstaculos()
{
    for(int i = 0; i < 15; i++)
    {
        for (int j = 0; j<11; j++)
        {
            // Configuração de obstáculos
            if(i%2 != 0  && j%2 != 0)
            {
                bloco[i][j].x = 2*i - 15;
                bloco[i][j].y = 2*j - 10;
                bloco[i][j].dest = 2;
            }

            // Configuração dos pontos iniciais
            else if((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) ||
                    (i == 14 && j == 10) || (i == 13 && j == 10) || (i == 14 && j == 9))
            {
               bloco[i][j].x = 2*i - 15;
               bloco[i][j].y = 2*j - 10;
               bloco[i][j].dest = 0;
            }

            // Configuração das caixas destrutíveis
            else
            {
               bloco[i][j].x = 2*i - 15;
               bloco[i][j].y = 2*j - 10;
               bloco[i][j].dest = 0;
            }
        }
    }
}

void drawObstacles()
{
    for(int i = 0; i < 15; i++)
    {
        // Número de colunas
        for(int j = 0; j < 11; j++)
        {
            if(bloco[i][j].dest == 2)
            {
                glPushMatrix();
                    glTranslatef(bloco[i][j].x, bloco[i][j].y, -30.0f);
                    drawBox();
                glPopMatrix();
            }
        }
    }
}

void drawScenario()
{
    float Tx = -15.0f;
    float Ty = 14.0f;

    /* SUPERIOR */
    // Número de linhas
    for(int i = 0; i < 2; i++, Ty -= 2.0f)
    {
        // Número de colunas
        for(int j = 0; j < 15; j++, Tx += 2.0f)
        {
            glPushMatrix();
                glTranslatef(Tx, Ty, -30.0f);
                drawBox();
            glPopMatrix();
        }

        Tx = -15.0f;
    }

    Ty = -12.0f;

    /* INFERIOR */
    // Número de linhas
    for(int i = 0; i < 2; i++, Ty -= 2.0f)
    {
        // Número de colunas
        for(int j = 0; j < 15; j++, Tx += 2.0f)
        {
            glPushMatrix();
                glTranslatef(Tx, Ty, -30.0f);
                drawBox();
            glPopMatrix();
        }

        Tx = -15.0f;
    }

    Ty = 14.0f;
    Tx = -21.0f;

    /* ESQUERDO */
    // Número de linhas
    for(int i = 0; i < 15; i++, Ty -= 2.0f)
    {
        // Número de colunas
        for(int j = 0; j < 3; j++, Tx += 2.0f)
        {
            glPushMatrix();
                glTranslatef(Tx, Ty, -30.0f);
                drawBox();
            glPopMatrix();
        }

        Tx = -21.0f;
    }

    Ty = 14.0f;
    Tx = 15.0f;

    /* DIREITO */
    // Número de linhas
    for(int i = 0; i < 15; i++, Ty -= 2.0f)
    {
        // Número de colunas
        for(int j = 0; j < 3; j++, Tx += 2.0f)
        {
            glPushMatrix();
                glTranslatef(Tx, Ty, -30.0f);
                drawBox();
            glPopMatrix();
        }

        Tx = 15.0f;
    }
}

void chao()
{
    float Tx = -29.0f;
    float Ty = 14.0f;

    /* SUPERIOR */
    // Número de linhas
    for(int i = 0; i < 15; i++, Ty -= 2.0f)
    {
        // Número de colunas
        for(int j = 0; j < 30; j++, Tx += 2.0f)
        {
            glPushMatrix();
                glTranslatef(Tx, Ty, -32.0f);
                drawBox();
            glPopMatrix();
        }

        Tx = -29.0f;
    }

}

void caixasDestrutiveis()
{
    for(int i = 0; i < 15; i++)
    {
        // Número de colunas
        for(int j = 0; j < 11; j++)
        {
            if(bloco[i][j].dest == 1)
            {
                glPushMatrix();
                    glTranslatef(bloco[i][j].x, bloco[i][j].y, -30.0f);
                    drawBox();
                glPopMatrix();
            }
        }
    }
}

// Desenho de Caixas
void drawBox()
{
    int i;

    for(i = 0; i < 6; i++)
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
}

// Movimento do Jogador 1
void keyboardPlayer1(unsigned char key, int x, int y)
{
    int i = (Jog1_X+15)/2;
    int j = (Jog1_Y+10)/2;
    switch(key)
    {
        case 'w':
            if(Jog1_Y + 2 <= YMax && bloco[i][j+1].dest == 0)
            {
                Jog1_Y += 2;
                up1 = 1;
                down1 = 0;
                left1 = 0;
                right1 = 0;
                //j++;
            }
            break;
        case 's':
            if(Jog1_Y - 2 >= YMin && bloco[i][j-1].dest == 0){
                Jog1_Y -= 2;
                down1 = 1;
                up1 = 0;
                left1 = 0;
                right1 = 0;
                //j--;
            }
            break;
        case 'a':
            if(Jog1_X - 2 >= XMin && bloco[i-1][j].dest == 0)
            {
                Jog1_X -= 2;
                left1 = 1;
                right1 = 0;
                up1 = 0;
                down1 = 0;
                //i--;
            }
            break;
        case 'd':
            if(Jog1_X + 2 <= XMax && bloco[i+1][j].dest == 0)
            {
                Jog1_X += 2;
                right1 = 1;
                left1 = 0;
                up1 = 0;
                down1 = 0;
                //i++;
            }
            break;
        case 'e':
            bombaPlayer1 = 1;
            break;
        case 'q':
            bombaPlayer1 = 0;
            break;
    }
    glutPostRedisplay();
}

// Movimento do Jogador 1
void keyboardPlayer2(int key, int x, int y)
{
    int i = (Jog2_X+15)/2;
    int j = (Jog2_Y+10)/2;
    switch(key)
    {
        case GLUT_KEY_UP:
            if(Jog2_Y + 2 <= YMax && bloco[i][j+1].dest == 0)
            {
                Jog2_Y += 2;
                up2 = 1;
                down2 = 0;
                left2 = 0;
                right2 = 0;
                //j++;
            }
            break;
        case GLUT_KEY_DOWN:
            if(Jog2_Y - 2 >= YMin && bloco[i][j-1].dest == 0)
            {
                Jog2_Y -= 2;
                up2 = 0;
                down2 = 1;
                left2 = 0;
                right2 = 0;
                //j--;
            }
            break;
        case GLUT_KEY_LEFT:
            if(Jog2_X - 2 >= XMin && bloco[i-1][j].dest == 0)
            {
                Jog2_X -= 2;
                up2 = 0;
                down2 = 0;
                left2 = 1;
                right2 = 0;
                //i--;
            }
            break;
        case GLUT_KEY_RIGHT:
            if(Jog2_X + 2 <= XMax && bloco[i+1][j].dest == 0)
            {
                Jog2_X += 2;
                up2 = 0;
                down2 = 0;
                left2 = 0;
                right2 = 1;
                //i++;
            }
            break;
        case GLUT_KEY_END:
            bombaPlayer2 = 1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            bombaPlayer2 = 0;
            break;
    }
    glutPostRedisplay();
}
