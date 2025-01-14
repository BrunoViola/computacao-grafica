#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


void desenha(){ 

        glColor3f(0.0f, 1.0f, 0.0f);
        glLineWidth(5.0f); // espessura da linha

        //corpo da casa
        glBegin(GL_QUAD_STRIP);
            glColor3f(0.5,0.5,0.5); // cor cinza

            glVertex2f(10, 0); 
            glVertex2f(210, 0); 
            glVertex2f(10, 200);
            glVertex2f(210, 200);
        glEnd();

        //chamine
        glBegin(GL_QUAD_STRIP);
            glColor3f(0.545,0.27,0.075); // cor marrom
            glVertex2f(40, 200);
            glVertex2f(70, 200);
            glVertex2f(40, 350);
            glVertex2f(70, 350);
        glEnd();

        //telhado
        glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0);
            glVertex2f(10, 200);
            glVertex2f(210, 200);
            glVertex2f(110, 320);
        glEnd();
        
        //porta
        glBegin(GL_QUAD_STRIP);
            glColor3f(0.678,0.847,0.902);  // cor parecida com skyblue

            glVertex2f(20, 0); 
            glVertex2f(70, 0); 
            glVertex2f(20, 90);
            glVertex2f(70, 90);
        glEnd();

        //janela primeiro andar
        glBegin(GL_QUAD_STRIP);
            glColor3f(0.678,0.847,0.902); // cor parecida com skyblue

            glVertex2f(120, 60); 
            glVertex2f(180, 60); 
            glVertex2f(120, 120);
            glVertex2f(180, 120);
        glEnd();
       
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    /* Cria uma nova janela de 640x480 */
    /* O NULL passado como parâmetros indica que a janela não terá uma janela
    de compartilhamento de contexto e que não é criada com um monitor específico. */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
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
    glViewport(0, 0, 640, 480);               // Ajusta o viewport para o tamanho da janela
    glMatrixMode(GL_PROJECTION);              // Muda para a matriz de projeção
    glLoadIdentity();                         // Reseta a matriz de projeção para identidade
    glOrtho(0, 640, 0, 480, -1, 1);           // Define uma projeção ortográfica 2D

    /* Loop de execução da janela enquanto não for fechada */
    while (!glfwWindowShouldClose(window))
    {
        /* Limpeza da tela */
        glClear(GL_COLOR_BUFFER_BIT);

        desenha();

        /* Troca os buffers (Mas veremos mais adiante a importância desta parte) */
        glfwSwapBuffers(window);

        /* Chamada para verificar e processar todos os eventos que ocorreram,
        como entradas do teclado, mouse, ... Isso mantém a janela responsiva. */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}