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

void desenhaBase(){
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.678,0.847,0.902);
        glVertex2f(260, 0); 
        glVertex2f(360, 0);

        glVertex2f(260, 90);
        glVertex2f(360, 90);
    glEnd();
}

void desenhaInferior(){
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.978, 0.947,0.902);
        glVertex2f(290, 110); 
        glVertex2f(330, 110);

        glVertex2f(290, 210);
        glVertex2f(330, 210);
    glEnd();
}

void desenhaSuperior(){
    glBegin(GL_QUAD_STRIP);
        glColor3f(0.378,0.747,0.402);
        glVertex2f(300, 230); 
        glVertex2f(320, 230);

        glVertex2f(300, 330);
        glVertex2f(320, 330);
    glEnd();
}

int main(void)
{
    GLFWwindow* window;
    float x, y;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* O NULL passado como parâmetros indica que a janela não terá uma janela
    de compartilhamento de contexto e que não é criada com um monitor específico. */
    window = glfwCreateWindow(1240, 1480, "Atividade 3 - Braço Mecânico", NULL, NULL);
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
    glViewport(0, 0, 1240, 1480);               // Ajusta o viewport para o tamanho da janela
    glMatrixMode(GL_PROJECTION);              // Muda para a matriz de projeção
    glLoadIdentity();                         // Reseta a matriz de projeção para identidade
    glOrtho(0, 640, 0, 480, -1, 1);           // Define uma projeção ortográfica 2D

    /* Define a função de callback para o teclado */ 

    /* Loop de execução da janela enquanto não for fechada */
    while (!glfwWindowShouldClose(window))
    {
        // Define a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        desenhaBase();

        glTranslatef(310, 90, 0);
        glRotatef(sin(glfwGetTime()) * 45, 0, 0, 1);
        glTranslatef(-310, -90, 0);
        desenhaInferior();

        glTranslatef(310, 210, 0);
        glRotatef(sin(glfwGetTime()) * 50, 0, 0, 1);
        glTranslatef(-310, -210, 0);
        desenhaSuperior();

        #ifdef _WIN32
        Sleep(50);
        #else
        usleep(50);
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