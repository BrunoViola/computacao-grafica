#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "arquibancada.h"
#include "texturas.h"
#include "personagem.h"
#include "plataforma.h"
#include "bolaParedeGol.h"
#include "variaveisGlobais.h"
#include "goleiro.h"
#include "torcedores.h"
#include "iluminacao.h"
#include "textos.h"
#include "colisao.h"

float speedY = 0.0f;
float speedYBoneco = 0.0f;

const float gravity = -0.01f;

float angulo = -0.5f;  //angulo de rotacao da camera
float raio = 5.0f;    //distancia da camera ate o objeto
float cameraY = 2.0f; //altura da camera

// ======================== Funcoes de movimento =======================
//atualiza a posicao da bola de acordo com a gravidade
void atualizaPosicaoBolaY() {
    speedY += gravity;
    ballY += speedY;

    //verifica se a bola tocou a plataforma
    if (ballY <= -1.0f) {
        ballY = -1.0f;
        speedY = -speedY * 0.8f;  //faz a bola quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}
//atualiza a posicao do boneco de acordo com a gravidade
void atualizaPosicaoBonecoY() {
    speedYBoneco += gravity;
    bonecoY += speedYBoneco;

    //verifica se o boneco tocou a plataforma
    if (bonecoY <= -0.25f) {
        bonecoY = -0.25f;
        speedYBoneco = -speedYBoneco * 0.8f;  //faz o personagem quicar com um fator de amortecimento
    }

    glutPostRedisplay();
}

//movimentacao da bola no eixo z
void atualizaPosicaoBolaZ(){
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

//movimentacao da bola no eixo x
void atualizaPosicaoBolaX(){
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
// =====================================================================
//funcao que atualiza a posicao da bola e boneco de acordo com a gravidade
void timer(int) {
    atualizaPosicaoBolaY();
    atualizaPosicaoBonecoY();
    glutTimerFunc(16, timer, 0);  //atualiza a cada 16 ms
}

void configurarCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 1.0f, 100.0f);//(campo de visão, largura/altura, limite proximo visivel, limite distante visivel)
    glTranslatef(0.0f, -2.0f, -20.0f); //essa transformacao eh aplicada sobre os objetos
    glMatrixMode(GL_MODELVIEW);
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
        case 'l': desligarIluminacaoEsquerda=1; break;
        case 'L': desligarIluminacaoEsquerda=0; break;
        case 'r': desligarIluminacaoDireita=1; break;
        case 'R': desligarIluminacaoDireita=0; break;
        case '+':
            if(forca<10.0f){ 
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
    desenhaGoleiro();
    desenhaTorcedores();
    //desenhaPosicaoIluminacao(); //mostra onde estao localizadas as iluminacoes
    // ============================================
    
    atualizaPosicaoBolaX();
    atualizaPosicaoBolaZ();

    movimentaGoleiroX();
    movimentaTorcedorY(); //torcida geral
    movimentaGavioesZ();
    
    colisaoBolaParede(); //verifica se foi gol ou determina o rebote da bola
    rebote(); //executa o rebote determinado pela colisaoBolaParede
    colisaoBolaGoleiro();
    colisaoBolaBoneco();
    
    exibirTextos(); //textos na tela
 
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

    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);  // Função de exibição

    glutTimerFunc(16, timer, 0);  // timer que atualiza a posY da bola e personagem de forma mais suave

    glutSpecialFunc(teclasEspeciais);  //teclas direcionais
    glutKeyboardFunc(teclado); //letras e simbolos

    glutMainLoop();  //loop do GLUT

    return 0;
}