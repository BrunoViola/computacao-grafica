#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

float ballY = 2.0f;
float ballX = 0.0f;
float ballZ = 0.0f;

float bonecoX = 0.0f;
float bonecoY = 2.0f;
float bonecoZ = 1.0f;

float speedY = 0.0f;
float speedZ = 0.0f;
float speedX = 0.0f;
float forca = 2.0f;

float cameraPosX = -2.0f;
float cameraPosY = 2.0f;
float cameraPosZ = 1.0f;

const float gravity = -0.01f;

int ultimoMovimentoEsquerda = 0;
int ultimoMovimentoDireita = 0;
int ultimoMovimentoCima = 0;
int ultimoMovimentoBaixo = 0;

float angulo = 0.0f;  // Ângulo de rotação
float raio = 5.0f;    // Distância da câmera até o objeto
float cameraY = 1.0f; // Altura da câmera

// ======================== Protótipos de funções ========================
void ultimoMovimento(int opcao);

// ======================== Funções de desenho ========================
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
    glTranslatef(bonecoX, bonecoY, bonecoZ);
    desenhaCabeca();
    desenhaTronco();
    desenhaBracos();
    desenhaPernas();
    glPopMatrix();
}
// Função para desenhar a plataforma
void desenhaPlataforma() {
    glPushMatrix();
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(10.0f, 1.0f, 13.0f);  // Aumenta o tamanho da plataforma
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

void desenhaArquibancadaDireita(){
    glPushMatrix(); //primeiro degrau
    glTranslatef(5.0f, -1.0f, 0.5f);
    glScalef(1.0f, 1.0f, 14.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //segundo degrau
    glTranslatef(6.0f, 0.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //terceiro degrau
    glTranslatef(7.0f, 1.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //quarto degrau
    glTranslatef(7.0f, 1.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix(); //quinto degrau
    glTranslatef(8.0f, 2.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaArquibancadaFrente(){
    glPushMatrix(); //primeiro degrau
    glTranslatef(0.5f, -1.0f, 7.0f);
    glScalef(11.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
    
    glPushMatrix(); //segundo degrau
    glTranslatef(1.0f, 0.0f, 8.0f);
    glScalef(12.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //terceiro degrau
    glTranslatef(1.75f, 1.0f, 9.0f);
    glScalef(13.5f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //quarto degrau
    glTranslatef(1.75f, 2.0f, 10.0f);
    glScalef(13.5f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}
// ======================================================================
// ======================== Funções de movimento =======================
// Atualiza a posição da bola de acordo com a gravidade
void atualizaPosicao() {
    speedY += gravity;
    ballY += speedY;
    bonecoY += speedY;

    // Verifica se a bola tocou a plataforma
    if (ballY <= -1.0f) {
        ballY = -1.0f;
        bonecoY = 0.0f;
        speedY = -speedY * 0.8f;  // Faz a bola quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}

void atualizaPosicaoZ(){
    if(ultimoMovimentoBaixo){
        if(ballZ >= -6.0f && speedZ > 0){
            ballZ -= 0.09f;
            speedZ-=0.1f;
        }
    }else if(ultimoMovimentoCima){
        if(ballZ <= 7.0f && speedZ > 0){
            ballZ += 0.09f;
            speedZ-=0.1f;
        }
    }
    glutPostRedisplay();
}

void atualizaPosicaoX(){
    if(ultimoMovimentoEsquerda){
        if(ballX >= -5.0f && speedX > 0){
            ballX -= 0.09f;
            speedX-=0.1f;
        }
    }else if(ultimoMovimentoDireita){
        if(ballX <= 5.0f && speedX > 0){ //o deslocamento final vai ser speedX*10*ballX
            ballX += 0.09f;
            speedX-=0.1f;
        }
    }
    glutPostRedisplay();
}
// ======================================================================
// ======================== Funções de colisão =========================
void colisaoBolaBoneco(){
    float dx = ballX - bonecoX;  // Diferença no eixo X
    float dz = ballZ - bonecoZ; // Diferença no eixo Z
    float distancia = sqrt(dx * dx + dz * dz);  // Distância euclidiana

    float raioBoneco = 0.3f;
    float raioBola = 0.3f;

    if (distancia < (raioBoneco + raioBola)){
        if(ultimoMovimentoDireita == 1){
            speedX = forca;
        }else if(ultimoMovimentoEsquerda == 1){
            speedX = forca;
        }else if(ultimoMovimentoCima == 1){
            speedZ = forca;
        }else if(ultimoMovimentoBaixo == 1){
            speedZ = forca;
        }
    }
    
    glutPostRedisplay();
}

void colisaoBolaParede(){
    float paredeTras = -4.0f;
    float paredeFrente = 7.0f;
    float paredeEsquerda = -4.0f;
    float paredeDireita = 5.0f;
    float raioBola = 1.0f;
    
    // Verifica se a bola colidiu com as paredes
    if (paredeTras - ballZ >= raioBola) {
        printf("bateu\n");
        ultimoMovimento(0);//corta o efeito do toque na bola
        ballZ += 0.5f;
    }else if(paredeFrente-ballZ<=raioBola){
        printf("bateu\n");
        ultimoMovimento(0);
        ballZ-= 0.5f;
    }else if(paredeEsquerda-ballX>=raioBola){
        printf("bateu\n");
        ultimoMovimento(0);
        ballX+=0.5f;
    }else if(paredeDireita-ballX<=raioBola){
        printf("bateu\n");
        ultimoMovimento(0);
        ballX-=0.5f;
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

void ultimoMovimento(int opcao){
    if(opcao == 1){
        ultimoMovimentoEsquerda = 1;
        ultimoMovimentoDireita = 0;
        ultimoMovimentoCima = 0;
        ultimoMovimentoBaixo = 0;
    } else if(opcao==2){
        ultimoMovimentoEsquerda = 0;
        ultimoMovimentoDireita = 1;
        ultimoMovimentoCima = 0;
        ultimoMovimentoBaixo = 0;
    } else if(opcao==3){
        ultimoMovimentoEsquerda = 0;
        ultimoMovimentoDireita = 0;
        ultimoMovimentoCima = 1;
        ultimoMovimentoBaixo = 0;
    } else if(opcao==4){
        ultimoMovimentoEsquerda = 0;
        ultimoMovimentoDireita = 0;
        ultimoMovimentoCima = 0;
        ultimoMovimentoBaixo = 1;
    }else if(opcao==0){ //esse aqui serve para evitar que a bola fique se movendo sozinha perto da parede
        ultimoMovimentoEsquerda = 0;
        ultimoMovimentoDireita = 0;
        ultimoMovimentoCima = 0;
        ultimoMovimentoBaixo = 0;
        speedX = 0.0f;
        speedZ = 0.0f;
    }
}

// ======================== Funções de teclado =========================
void teclasEspeciais(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        bonecoX-=0.1f;  // Move para a esquerda
        ultimoMovimento(1);
    } else if (key == GLUT_KEY_RIGHT) {
        bonecoX+=0.1f; // Move para a direita
        ultimoMovimento(2);
    } else if (key == GLUT_KEY_DOWN) {
        bonecoZ += 0.1f;  // Pula
        ultimoMovimento(3);
    } else if (key == GLUT_KEY_UP) {
        bonecoZ-=0.1f;  // Move para baixo
        ultimoMovimento(4);
    }
    glutPostRedisplay();  // Atualiza a tela após o movimento
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': angulo -= 0.1f; break;  // Gira para a esquerda
        case 'd': angulo += 0.1f; break;  // Gira para a direita
        case 'w': cameraY += 0.5f; break; // Sobe
        case 's': cameraY -= 0.5f; break; // Desce
        case 'q': raio -= 0.5f; break;    // Aproxima a câmera
        case 'e': raio += 0.5f; break;    // Afasta a câmera
        case '+': forca += 0.5f; printf("Força: %.2f\n", forca); break;   // Aumenta a força
        case '-': forca -= 0.5f; printf("Força: %.2f\n", forca); break;   // Diminui a força
        case 27: exit(0); // Tecla ESC fecha o programa
    }
    glutPostRedisplay();
}
// ======================================================================

void renderText(float x, float y, char *string) {
    glRasterPos2f(x, y); // Define a posição do texto
    for (char *c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
// Função para exibir a cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpa a tela
    glLoadIdentity();
    float cameraX = raio * sin(angulo);
    float cameraZ = raio * cos(angulo);

    gluLookAt(cameraX, cameraY, cameraZ,  // Posição da câmera
              0.0f, 0.0f, 0.0f,  // Olha para o centro
              0.0f, 1.0f, 0.0f);
    configurarCamera();  // Configuração da câmera
    configurarIluminacao();  // Configuração da iluminação
    desenhaPlataforma();  // Desenha a plataforma
    desenhaParede();
    desenhaArquibancadaDireita();
    desenhaArquibancadaFrente();
    desenhaBola();  // Desenha a bola
    desenhaBoneco();  // Desenha o boneco
    colisaoBolaBoneco();
    atualizaPosicaoZ();
    atualizaPosicaoX();
    colisaoBolaParede();

    char texto[50];
    char texto2[50];
    sprintf(texto, "ballZ: %.2f", ballZ);
    sprintf(texto2, "ballX: %.2f", ballX);
    glColor3f(1.0, 1.0, 1.0); // Define a cor do texto (branco)
    renderText(-0.9, 0.9, texto); // Posição no canto superior esquerdo
    renderText(-0.9, 0.3, texto2); // Posição no canto superior esquerdo
    glutSwapBuffers();  // Troca os buffers
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("Trabalho - Computação Gráfica");

    // Inicializa o SDL para tocar musica

    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
    glutDisplayFunc(display);  // Função de exibição
    glutTimerFunc(16, timer, 0);  // Inicia o timer para atualizar a posição da bola
    glutSpecialFunc(teclasEspeciais);  // Função para capturar teclas especiais
    glutKeyboardFunc(teclado);
    glutMainLoop();  // Inicia o loop principal do GLUT

    // encerra o SDL
    return 0;
}
