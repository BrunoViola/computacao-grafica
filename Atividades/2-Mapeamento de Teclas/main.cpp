#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_W:
                glScalef(2, 1, 1);
                break;
            case GLFW_KEY_S:
                glScalef(0.5, 1, 1);
                break;
            case GLFW_KEY_A:
                glRotated(45, 0, 0, 1);
                break;
            case GLFW_KEY_D:
                glRotated(-45, 0, 0, 1);
                break;
            case GLFW_KEY_RIGHT:
                glTranslatef(10, 0, 0);
                break;
            case GLFW_KEY_LEFT:
                glTranslatef(-10, 0, 0);
                break;
            case GLFW_KEY_UP:
                glTranslatef(0, 10, 0);
                break;
            case GLFW_KEY_DOWN:
                glTranslatef(0, -10, 0);
                break;
            case GLFW_KEY_ESCAPE:
                glfwSetWindowShouldClose(window, true);
                break;
            default:
                break;
        }
    }
}

void desenhaTriangulo(){

        glPointSize(5.0f);
        glBegin(GL_TRIANGLES);
            glVertex2i(100, 100); //vértice A
            glVertex2i(300, 100); //vértice B
            glVertex2i(200,300); //vértice C
        glEnd();
        glFlush();
}

int main(void)
{
    GLFWwindow* window;
    float x, y;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Cria uma nova janela de 640x480 */
    /* O NULL passado como parâmetros indica que a janela não terá uma janela
    de compartilhamento de contexto e que não é criada com um monitor específico. */
    window = glfwCreateWindow(1240, 1480, "Hello World", NULL, NULL);
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
    glfwSetKeyCallback(window, key_callback);

    /* Loop de execução da janela enquanto não for fechada */
    while (!glfwWindowShouldClose(window))
    {
        // Define a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);

        desenhaTriangulo();

        /* Troca os buffers (Mas veremos mais adiante a importância desta parte) */
        glfwSwapBuffers(window);

        /* Chamada para verificar e processar todos os eventos que ocorreram,
        como entradas do teclado, mouse, ... Isso mantém a janela responsiva. */
        glfwPollEvents();
        
    }

    glfwTerminate();
    return 0;
}