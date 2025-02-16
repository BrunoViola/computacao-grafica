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
float speedYBoneco = 0.0f;
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

int backupUltimoMovimentoEsquerda = 0;
int backupUltimoMovimentoDireita = 0;
int backupUltimoMovimentoCima = 0;
int backupUltimoMovimentoBaixo = 0;

float reboteEmX = 0.0f;
float reboteEmZ = 0.0f;

int reboteEmAndamento = 0;

float angulo = -0.5f;  // Ângulo de rotação
float raio = 5.0f;    // Distância da câmera até o objeto
float cameraY = 2.0f; // Altura da câmera

// ======================== Protótipos de funções ========================
void ultimoMovimento(int opcao);
void configurarIluminacaoCampo();

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

    configurarIluminacaoCampo();  // Configuração da iluminação do campo
    glDisable(GL_LIGHTING);  // Desativa a iluminação para a plataforma
    
    glColor3f(0.0f, 0.5f, 0.1f);
    glTranslatef(0.0f, -2.0f, 0.0f);
    glScalef(10.0f, 1.0f, 13.0f);  // Aumenta o tamanho da plataforma
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);  // Ativa a iluminação novamente
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
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(5.0f, -1.0f, 0.5f);
    glScalef(1.0f, 1.0f, 14.0f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPushMatrix(); //segundo degrau
    glTranslatef(6.0f, 0.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //terceiro degrau
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(7.0f, 1.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    glPushMatrix(); //quarto degrau
    glTranslatef(8.0f, 2.0f, 1.5f);
    glScalef(1.0f, 1.0f, 16.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void desenhaArquibancadaFrente(){
    glPushMatrix(); //primeiro degrau
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(0.5f, -1.0f, 7.0f);
    glScalef(11.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    
    glPushMatrix(); //segundo degrau
    glTranslatef(1.0f, 0.0f, 8.0f);
    glScalef(12.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix(); //terceiro degrau
    glDisable(GL_LIGHTING);
    glColor3f(0.1f, 0.1f, 0.1f);
    glTranslatef(1.75f, 1.0f, 9.0f);
    glScalef(13.5f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glEnable(GL_LIGHTING);
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
void atualizaPosicaoBolaY() {
    speedY += gravity;
    ballY += speedY;

    // Verifica se a bola tocou a plataforma
    if (ballY <= -1.0f) {
        ballY = -1.0f;
        speedY = -speedY * 0.8f;  // Faz a bola quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}

void atualizaPosicaoBonecoY() {
    speedYBoneco += gravity;
    bonecoY += speedYBoneco;

    // Verifica se o boneco tocou a plataforma
    if (bonecoY <= 0.0f) {
        bonecoY = 0.0f;
        speedYBoneco = -speedYBoneco * 0.8f;  // Faz a bola quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}

void atualizaPosicaoZ(){
    if(speedZ==0 && !reboteEmAndamento){
        backupUltimoMovimentoBaixo = 0;
        backupUltimoMovimentoCima = 0; 
    }

    if((ultimoMovimentoBaixo || backupUltimoMovimentoBaixo) && !reboteEmAndamento){
        backupUltimoMovimentoBaixo = 1;
        if(ballZ >= -6.0f && speedZ > 0){
            ballZ -= 0.09f;
            speedZ-=0.1f;
        }
    }else if((ultimoMovimentoCima || backupUltimoMovimentoCima) && !reboteEmAndamento){
        backupUltimoMovimentoCima = 1;
        if(ballZ <= 7.0f && speedZ > 0){
            ballZ += 0.09f;
            speedZ-=0.1f;
        }
    }    
    glutPostRedisplay();
}

void atualizaPosicaoX(){
    if(speedX==0 && !reboteEmAndamento){
        backupUltimoMovimentoDireita = 0;
        backupUltimoMovimentoEsquerda = 0; 
    }

    if((ultimoMovimentoEsquerda || backupUltimoMovimentoEsquerda) && !reboteEmAndamento){
        backupUltimoMovimentoEsquerda = 1;
        if(ballX >= -5.0f && speedX > 0){
            ballX -= 0.09f;
            speedX-=0.1f;
        }
    }else if((ultimoMovimentoDireita || backupUltimoMovimentoDireita) && !reboteEmAndamento){
        backupUltimoMovimentoDireita = 1;
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
        reboteEmZ = speedZ;
        ultimoMovimento(0);//corta o efeito do toque na bola
        ballZ += 0.5f;
    }else if(paredeFrente-ballZ<=raioBola){
        printf("bateu\n");
        reboteEmZ = speedZ;
        ultimoMovimento(0);
        ballZ-= 0.5f;
    }else if(paredeEsquerda-ballX>=raioBola){
        printf("bateu\n");
        reboteEmX = speedX;
        ultimoMovimento(0);
        ballX+=0.5f;
    }else if(paredeDireita-ballX<=raioBola){
        printf("bateu\n");
        reboteEmX = speedX;
        ultimoMovimento(0);
        ballX-=0.5f;
    }
    glutPostRedisplay();
}
// ======================================================================
void rebote(){
    if(reboteEmX > 0.1 ){
        printf("rebote: %.2f\n", reboteEmX);
        if(backupUltimoMovimentoDireita){
            ballX -= 0.05f;
            reboteEmX -= 0.1f;
        }else if(backupUltimoMovimentoEsquerda){
            ballX += 0.05f;
            reboteEmX -= 0.1f;
        }
    }else if(reboteEmZ > 0.1){
        printf("rebote: %.2f\n", reboteEmZ);
        if(backupUltimoMovimentoCima){
            ballZ -= 0.05f;
            reboteEmZ -= 0.1f;
        }else if(backupUltimoMovimentoBaixo){
            ballZ += 0.05f;
            reboteEmZ -= 0.1f;
        }

    }
    if(reboteEmX > 0.1 || reboteEmZ > 0.1){
        reboteEmAndamento = 1;
    }else{
        reboteEmAndamento = 0;
    }
    glutPostRedisplay();
}
// Função timer para atualizar a posição da bola
void timer(int) {
    atualizaPosicaoBolaY();
    atualizaPosicaoBonecoY();
    glutTimerFunc(16, timer, 0);  // Atualiza a cada 16 ms (aproximadamente 60 FPS)
}

// Configuração da iluminação
void configurarIluminacao() {
    GLfloat luzAmbiente[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Luz ambiente
    GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Luz difusa
    GLfloat luzPosicao[] = { 0.0f, 10.0f, 0.0f, 1.0f };  // Posição da luz

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
}

void configurarIluminacaoCampo() {
    GLfloat luzAmbiente[] = { 0.0f, 1.0f, 0.0f, 1.0f };  // Luz ambiente
    GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // Luz difusa
    GLfloat luzPosicao[] = { 0.0f, 10.0f, 0.0f, 1.0f };  // Posição da luz

    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT1, GL_POSITION, luzPosicao);
    
    glEnable(GL_LIGHTING);
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
        case '+':
            if(forca<14.0f){ 
                forca += 0.5f; 
                printf("Força: %.2f\n", forca);
            }else{
                printf("Força maxima atingida\n");
            }
            break;   // Aumenta a força
        case '-':
            if(forca > 2.0f){
                forca -= 0.5f; 
                printf("Força: %.2f\n", forca);
            }else{
                printf("Força minima atingida\n");
            }
            break;   // Diminui a força
        case ' ': // Pula
            bonecoY+=2.0f;
            break;
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
    glViewport(0, 0, 1200, 900);  // Define a janela de visualização
    configurarCamera();  // Configuração da câmera
    configurarIluminacao();  // Configuração da iluminação
    desenhaPlataforma();  // Desenha a plataforma
    desenhaParede();
    desenhaArquibancadaDireita();
    desenhaArquibancadaFrente();
    desenhaBola();  // Desenha a bola
    desenhaBoneco();  // Desenha o boneco
    
    
    atualizaPosicaoZ();
    atualizaPosicaoX();
    
    colisaoBolaParede();

    // ========= Exibição de Textos =========
    char texto[50];
    char texto2[50];
    char texto3[50];
    sprintf(texto, "ballZ: %.2f", ballZ);
    sprintf(texto2, "ballX: %.2f", ballX);
    sprintf(texto3, "Forca: %.2f", forca);
    glColor3f(1.0, 1.0, 1.0);
    renderText(10, 10, texto);
    renderText(10, 8, texto2); 
    renderText(10, 6, texto3);

    rebote();    

    colisaoBolaBoneco();
    // =====================================

    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0); 

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
