#include "colisao.h"

// ======================== Funcoes de colisao =========================
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
           gols++;
           srand(time(NULL));
           //essas funcoes rand abaixo servem para reposicionar a bola de maneira aleatoria depois de um gol
           ballX = (float)(rand()%8)-4;
           ballZ = (float)(rand()%6);
           ballY = 2.0f;
           speedX = 0.0f;
           speedZ = 0.0f;

       }else{
           reboteEmZ = speedZ;
           ultimoMovimento(0);//corta o efeito do toque na bola
           ballZ += 0.5f;
       }
   }else if(paredeFrente-ballZ<=raioBola){
       //printf("bateu\n");
       reboteEmZ = speedZ;
       ultimoMovimento(0);
       ballZ-= 0.5f;
   }else if(paredeEsquerda-ballX>=raioBola){
       //printf("bateu\n");
       reboteEmX = speedX;
       ultimoMovimento(0);
       ballX+=0.5f;
   }else if(paredeDireita-ballX<=raioBola){
       //printf("bateu\n");
       reboteEmX = speedX;
       ultimoMovimento(0);
       ballX-=0.5f;
   }
   glutPostRedisplay();
}

void rebote(){
   if(reboteEmX > 0.1 ){
       //printf("rebote: %.2f\n", reboteEmX);
       if(backupUltimoMovimentoDireita){
           ballX -= 0.05f;
           reboteEmX -= 0.1f;
       }else if(backupUltimoMovimentoEsquerda){
           ballX += 0.05f;
           reboteEmX -= 0.1f;
       }
   }else if(reboteEmZ > 0.1){
       //printf("rebote: %.2f\n", reboteEmZ);
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