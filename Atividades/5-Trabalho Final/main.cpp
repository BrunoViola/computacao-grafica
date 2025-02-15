#include <GL/glut.h>

float ballY = 2.0f;
float ballX = 0.0f;
float ballZ = 0.0f;
float speedY = 0.0f;
const float gravity = -0.01f;

// Função para desenhar a bola
void desenhaBola() {
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
}

// Função para desenhar a cabeça (esfera)
void desenhaCabeca() {
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, 0.0f);  // Posiciona a cabeça
    glutSolidSphere(0.5, 30, 30);  // Cabeça com raio 0.5
    glPopMatrix();
}

// Função para desenhar o tronco (cilindro)
void desenhaTronco() {
    glPushMatrix();
    glTranslatef(0.0f, 0.8f, 0.0f);  // Posiciona o tronco
    glScalef(0.8f, 1.0f, 0.5f);  // Escala para criar o tronco
    glutSolidCube(1.0);  // Tronco em forma de cubo
    glPopMatrix();
}

// Função para desenhar os braços (cilindros)
void desenhaBracos() {
    glPushMatrix();
    glTranslatef(-0.75f, 1.5f, 0.0f);  // Posição do braço esquerdo
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Roda para posição correta
    glScalef(0.5f, 0.5f, -1.0f);
    glutSolidCube(1);  // Braço esquerdo
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.75f, 1.5f, 0.0f);  // Posição do braço direito
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Roda para posição correta
    glScalef(0.5f, 0.5f, 1.0f);
    glutSolidCube(1);  // Braço direito
    glPopMatrix();
}

// Função para desenhar as pernas (cilindros)
void desenhaPernas() {
    glPushMatrix();
    glTranslatef(0.2f, -0.5f, 0.0f);  // Posição da perna esquerda
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Roda para posição correta
    glScalef(0.5f, 0.5f, 1.5f);
    glutSolidCube(1.0);  // Perna esquerda
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.2f, -0.5f, 0.0f);  // Posição da perna direita
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  // Roda para posição correta
    glScalef(0.5f, 0.5f, 1.5f);
    glutSolidCube(1.0);  // Perna direita
    glPopMatrix();
}

// Função para desenhar o boneco
void desenhaBoneco() {
    glPushMatrix();
    glTranslatef(ballX, ballY+1, ballZ);
    desenhaCabeca();
    desenhaTronco();
    desenhaBracos();
    desenhaPernas();
    glPopMatrix();
}
// Função para desenhar a plataforma
void desenhaPlataforma() {
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, -1.0f);
    glScalef(10.0f, 1.0f, 10.0f);  // Aumenta o tamanho da plataforma
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaParede(){
    glPushMatrix();
    glTranslatef(0.0f, 2.0f, -6.0f);
    glScalef(10.0f, 7.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

// Atualiza a posição da bola
void atualizaPosicao() {
    speedY += gravity;
    ballY += speedY;

    // Verifica se a bola tocou a plataforma
    if (ballY <= -1.0f) {
        ballY = -1.0f;
        speedY = -speedY * 0.8f;  // Faz a bola quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}

// Função timer para atualizar a posição da bola
void timer(int) {
    atualizaPosicao();
    glutTimerFunc(16, timer, 0);  // Atualiza a cada 16 ms (aproximadamente 60 FPS)
}

// Configuração da iluminação
void configurarIluminacao() {
    GLfloat luzAmbiente[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // Luz ambiente
    GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Luz difusa
    GLfloat luzPosicao[] = { 0.0f, 10.0f, 0.0f, 1.0f };  // Posição da luz

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
}

// Função para configurar a câmera
void configurarCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);  // Projeção perspectiva
    glTranslatef(0.0f, -2.0f, -20.0f);  // Posiciona a câmera atrás do jogador
    glMatrixMode(GL_MODELVIEW);
}

void teclasEspeciais(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        ballX-=0.1f;  // Move para a esquerda
    } else if (key == GLUT_KEY_RIGHT) {
        ballX+=0.1f; // Move para a direita
    } else if (key == GLUT_KEY_UP) {
        ballZ += 0.1f;  // Pula
    } else if (key == GLUT_KEY_DOWN) {
        ballZ-=0.1f;  // Move para baixo
    }
    glutPostRedisplay();  // Atualiza a tela após o movimento
}

// Função para exibir a cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpa a tela
    glLoadIdentity();
    gluLookAt(
        -1.0f, 1.0f, 0.0f,  // Posição da câmera
        0.0f, 0.0f, -1.0f,  // Ponto de visão
        0.0f, 1.0f, 0.0f   // Vetor Up
    );
    configurarCamera();  // Configuração da câmera
    configurarIluminacao();  // Configuração da iluminação
    desenhaPlataforma();  // Desenha a plataforma
    desenhaParede();
    desenhaBola();  // Desenha a bola
    desenhaBoneco();  // Desenha o boneco

    glutSwapBuffers();  // Troca os buffers
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("Trabalho - Computação Gráfica");

    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
    glutDisplayFunc(display);  // Função de exibição
    glutTimerFunc(16, timer, 0);  // Inicia o timer para atualizar a posição da bola
    glutSpecialFunc(teclasEspeciais);  // Função para capturar teclas especiais
    glutMainLoop();  // Inicia o loop principal do GLUT

    return 0;
}
