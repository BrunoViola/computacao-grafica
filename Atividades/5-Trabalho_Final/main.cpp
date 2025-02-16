#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "arquibancada.h"
#include "texturas.h"
#include "personagem.h"
#include "plataforma.h"

float ballY = 2.0f;
float ballX = 0.0f;
float ballZ = 0.0f;

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
// ======================================================================

// ======================== Funções de desenho ========================
// Função para desenhar a bola
void desenhaBola() {
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glutSolidSphere(0.5, 30, 30);
    glPopMatrix();
}



void desenhaParedeGol(){
    // ================== barreira esquerda =====================
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPatrocionios); 
    
    // Desenha o plano texturizado na posição correta
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0, -1.5, -5.45);  // Canto inferior esquerdo
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5, -1.5, -5.45);  // Canto inferior direito
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5, 0.5, -5.45);   // Canto superior direito
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0, 0.5, -5.45);   // Canto superior esquerdo
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
        glTranslatef(-3.25f, -0.5f, -6.0f);
        glScalef(3.5f, 2.0f, 1.0f);
        glutSolidCube(1.0);
    glPopMatrix();
    // ===================================

    // =============== barreira direita ===============
    glPushMatrix();
    glTranslatef(3.25f, -0.5f, -6.0f);
    glScalef(3.5f, 2.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texturaPatrocioniosDireita); 
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(5.0, -1.5, -5.45);  // Canto inferior esquerdo
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5, -1.5, -5.45);  // Canto inferior direito
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5, 0.5, -5.45);   // Canto superior direito
        glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 0.5, -5.45);   // Canto superior esquerdo
    glEnd();
    glDisable(GL_TEXTURE_2D);
    // ===================================
    // trave direita
    glPushMatrix();
    glTranslatef(1.75f, 1.4f, -6.0f);
    glScalef(0.5f, 1.8f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // trave esquerda
    glPushMatrix();
    glTranslatef(-1.75f, 1.4f, -6.0f);
    glScalef(0.5f, 1.8f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // travessao
    glPushMatrix();
    glTranslatef(0.0f, 2.5f, -6.0f);
    glScalef(4.0f, 0.5f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}
// ======================================================================

// ======================== Funções de movimento =======================
// Atualiza a posicao da bola de acordo com a gravidade
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
    if (bonecoY <= -0.25f) {
        bonecoY = -0.25f;
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
        if(ballZ >= -7.0f && speedZ > 0){
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
    float dx = ballX - bonecoX;  //diferenca no eixo X
    float dz = ballZ - bonecoZ; //diferenca no eixo Z
    float distancia = sqrt(dx * dx + dz * dz);  // calculo da distancia euclidiana

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
    
    //verifica se a bola colidiu com alguma parede
    if (paredeTras - ballZ >= raioBola) {
        if(ballX >= -1.75f && ballX <= 1.75f){
            printf("GOOOOOOOOLLL\n");
            ballX = 0.0f;
            ballZ = 3.0f;
            ballY = 2.0f;
            speedX = 0.0f;
            speedZ = 0.0f;

        }else{
            reboteEmZ = speedZ;
            ultimoMovimento(0);//corta o efeito do toque na bola
            ballZ += 0.5f;
        }
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

void timer(int) {
    atualizaPosicaoBolaY();
    atualizaPosicaoBonecoY();
    glutTimerFunc(16, timer, 0);  // Atualiza a cada 16 ms
}

void configurarIluminacao() {
    GLfloat luzAmbiente[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // (R, G, B, OPACIDADE), coloquei branca
    GLfloat luzDifusa[] = {  1.0f, 1.0f, 1.0f, 1.0f };  // (R, G, B, OPACIDADE), coloquei branca
    GLfloat luzPosicao[] = { -4.0f, 10.0f, 6.0f, 1.0f };  // (X, Y, Z, TIPO)

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);  // Ativa o teste de profundidade
}

void configurarCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);
    glTranslatef(0.0f, -2.0f, -20.0f);  //posiciona a camera atras do personagem
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

// ======================== Direcionais para controlar o personagem =========================
void teclasEspeciais(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        if(bonecoX > -4.5f) //esse if verifica a colisao do boneco com a parede
            bonecoX-=0.1f;  //para esquerda
        ultimoMovimento(1);
    } else if (key == GLUT_KEY_RIGHT) {
        if(bonecoX < 4.0f) //esse if verifica a colisao do boneco com a parede
            bonecoX+=0.1f; //para direita
        ultimoMovimento(2);
    } else if (key == GLUT_KEY_DOWN) {
        if(bonecoZ < 6.0f) //mesma coisa dos dois if dos casos acima
            bonecoZ += 0.1f;  //para tras
        ultimoMovimento(3);
    } else if (key == GLUT_KEY_UP) {
        if(bonecoZ > -5.0f) //mesma coisa dos dois if dos casos acima
            bonecoZ-=0.1f;  //para frente
        ultimoMovimento(4);
    }
    glutPostRedisplay();  // Atualiza a tela apos o movimento
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': angulo -= 0.1f; break;  //gira para a esquerda a camera
        case 'd': angulo += 0.1f; break;  //gira para a direita a camera
        case 'w': cameraY += 0.5f; break; //sobe a camera
        case 's': cameraY -= 0.5f; break; //desce a camera
        case 'q': raio -= 0.5f; break;    //aproxima a camera
        case 'e': raio += 0.5f; break;    //afasta a camera
        case '+':
            if(forca<5.0f){ 
                forca += 0.5f; 
                printf("Força: %.2f\n", forca);
            }else{
                printf("Força maxima atingida\n");
            }
            break;   //aumenta a forca do personagem
        case '-':
            if(forca > 2.0f){
                forca -= 0.5f; 
                printf("Força: %.2f\n", forca);
            }else{
                printf("Força minima atingida\n");
            }
            break;   //diminui a força do personagem
        case ' ': //persongem pula
            bonecoY+=2.0f;
            break;
        case 27: exit(0); //esc - fecha o programa
    }
    glutPostRedisplay();
}
// ======================================================================

void renderText(float x, float y, char *string) {
    glRasterPos2f(x, y); //posicao do texto
    for (char *c = string; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

//exibicao da cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //limpeza da tela
    glLoadIdentity();
    float cameraX = raio * sin(angulo);
    float cameraZ = raio * cos(angulo);

    gluLookAt(cameraX, cameraY, cameraZ,  //aqui eu determino a posicao da camera
              0.0f, 0.0f, 0.0f,  //voltada pro centro
              0.0f, 1.0f, 0.0f);

    glViewport(0, 0, 1200, 900);

    configurarCamera();
    configurarIluminacao();

    // ================== desenhos ================
    desenhaPlataforma();
    desenhaParedeGol();
    desenhaArquibancadaDireita();
    desenhaArquibancadaFrente();
    desenhaBola();
    desenhaBoneco();
    // ============================================
    
    atualizaPosicaoZ();
    atualizaPosicaoX();
    
    colisaoBolaParede();

    // ========= exibicao de textos na tela =========
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
    // =====================================

    rebote();    

    colisaoBolaBoneco();
    
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 100.0); 

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 900);
    glutCreateWindow("Trabalho - Computação Gráfica");

    glViewport(0, 0, 1200, 900);
    
    glEnable(GL_DEPTH_TEST);  //ativa o teste de profundidade
    glEnable(GL_TEXTURE_2D);  //ativa o uso de texturas 2D

    carregarTextura();

    //configuracoes relacionadas a projecao
    glMatrixMode(GL_PROJECTION);
    gluPerspective(90.0f, 1.33f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);  // Função de exibição

    glutTimerFunc(16, timer, 0);  // timer que atualiza a posY da bola e personagem

    glutSpecialFunc(teclasEspeciais);  //teclas direcionais
    glutKeyboardFunc(teclado); //letras e simbolos

    glutMainLoop();  //loop do GLUT

    return 0;
}
