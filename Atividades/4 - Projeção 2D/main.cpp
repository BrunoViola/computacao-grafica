#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void desenhaTriangulo(){
    glBegin(GL_TRIANGLES);
        glVertex2i(0, 50);
        glVertex2i(50, -50);
        glVertex2i(-50, -50);
    glEnd();
}

void desenhaLimiteHorizontal(){
    glBegin(GL_LINES);
        glVertex2i(0, 300);
        glVertex2i(600, 300);
    glEnd();
}

void desenhaLimiteVertical(){
    glLineWidth(5);

    glBegin(GL_LINES);
        glVertex2i(300, 0);
        glVertex2i(300, 600);
    glEnd();
}

int main(void)
{
    GLFWwindow* window;
    float x, y;
    int panningHorizontal=0, controlePanningHorizontal=1; //variaveis para animacoes do triangulo do canto superior direito

    int panningVertical=0, controlePanningVertical=1; //variaveis para animacoes do triangulo do canto inferior esquerdo

    int zoomInOut=0, controleZoom=1; //variaveis para animacoes do triangulo do canto inferior direito

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* O NULL passado como parâmetros indica que a janela não terá uma janela
    de compartilhamento de contexto e que não é criada com um monitor específico. */
    window = glfwCreateWindow(600, 600, "Atividade 4 - Projeção 2D", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Definição do Contexto Atual:
    Torna o contexto OpenGL da janela criada como sendo o contexto atual.
    Quer dizer que qualquer chamada seguinte ao OpenGL irá afetar esta janela. */
    glfwMakeContextCurrent(window);

    /* Configura o viewport e a projeção ortográfica */
    glMatrixMode(GL_PROJECTION);              // Muda para a matriz de projeção
    glLoadIdentity();                         // Reseta a matriz de projeção para identidade
               // Define uma projeção ortográfica 2D

    /* Define a função de callback para o teclado */ 

    /* Loop de execução da janela enquanto não for fechada */
    while (!glfwWindowShouldClose(window))
    {
        // Define a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);

        // Triangulo Canto Superior Esquerdo (Estatico)
        glLoadIdentity();
        glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -1, 1);
        glViewport(0, 300, 300, 300);
        glColor3f(1.0f, 0.0f, 0.0f);
        desenhaTriangulo();

        // Triangulo Canto Superior Direito
        glLoadIdentity();
        if(panningHorizontal==-160.0){//vai para a direita
            controlePanningHorizontal=1;
        }else if(panningHorizontal==160.0){//vai para a esquerda
            controlePanningHorizontal=-1;
        }
        panningHorizontal+=controlePanningHorizontal;
        glOrtho(panningHorizontal-100, panningHorizontal+100, -100.0f, 100.0f, -1, 1);
        glViewport(300, 300, 300, 300);
        glColor3f(0.0f, 1.0f, 0.0f);
        desenhaTriangulo();

        // Triangulo Canto Inferior Esquerdo
        glLoadIdentity();
        if(panningVertical==-160.0){//desce
            controlePanningVertical=1;
        }else if(panningVertical==160.0){//sobe
            controlePanningVertical=-1;
        }
        panningVertical+=controlePanningVertical;
        glOrtho(-100.0f, 100.0f, panningVertical-100.0, panningVertical+100.0, -1, 1);
        glViewport(0, 0, 300, 300);
        glColor3f(0.0f, 0.0f, 1.0f);
        desenhaTriangulo();

        // Triangulo Canto Inferior Direito
        glLoadIdentity();
        if(zoomInOut==-150.0){//zoom out
            controleZoom=1;
        }else if(zoomInOut==100.0){//zoom in
            controleZoom=-1;
        }
        zoomInOut+=controleZoom;
        glOrtho(zoomInOut-100.0, (-zoomInOut)+100.0, zoomInOut-100.0, (-zoomInOut)+100.0, -1, 1);
        glViewport(300, 0, 300, 300);
        glColor3f(0.5f, 0.5f, 0.5f);
        desenhaTriangulo();

        // limite horizontal
        glLoadIdentity();
        glOrtho(0.0f, 600.0f, 0.0f, 600.0f, -1, 1);
        glViewport(0, 0, 600, 600);
        glColor3f(1.0f, 1.0f, 1.0f);
        desenhaLimiteHorizontal();

        // limite vertical
        glLoadIdentity();
        glOrtho(0.0f, 600.0f, 0.0f, 600.0f, -1, 1);
        glViewport(0, 0, 600, 600);
        glColor3f(1.0f, 1.0f, 1.0f);
        desenhaLimiteVertical();

        #ifdef _WIN32
        Sleep(1);
        #else
        usleep(1000);
        #endif
        /* Troca os buffers (Mas veremos mais adiante a importância desta parte) */
        glfwSwapBuffers(window);

        /* Chamada para verificar e processar todos os eventos que ocorreram,
        como entradas do teclado, mouse, ... Isso mantém a janela responsiva. */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}