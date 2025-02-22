#include "torcedores.h"

float torcedorY = 0.0f; //uso essa variavel para alguma animacoes
float torcedorX = 0.0f; //uso essa variavel para deslocar o torcedor
int sentidoY = 1;
int sentidoX = 1;

//funcao que adiciona a textura da gavioes ao torcedor
void desenhaTroncoGavioes() {
   glEnable(GL_TEXTURE_2D); //ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisaGavioes); //aplica a textura carregada
   glBegin(GL_QUADS);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, -0.26f); // inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, -0.26f); // inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, -0.26f); // superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, -0.26f); // superior esquerdo
   glEnd();
   glPushMatrix();

   glTranslatef(0.0f, 0.8f, 0.0f);  //posiciona o tronco
   glScalef(0.8f, 1.0f, 0.5f);  //escala para criar o tronco
   glutSolidCube(1.0);  //tronco em forma de cubo
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

//adiciona a textura de camisa preta ao torcedor
void desenhaTroncoTorcedorComum() {
   glEnable(GL_TEXTURE_2D); //ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisaTorcedor); //aplica a textura carregada
   glBegin(GL_QUADS);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, -0.26f); // inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, -0.26f); // inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, -0.26f); // superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, -0.26f); // superior esquerdo
   glEnd();
   glPushMatrix();
   
   glTranslatef(0.0f, 0.8f, 0.0f);  //posiciona o tronco
   glScalef(0.8f, 1.0f, 0.5f);  //escala para criar o tronco
   glutSolidCube(1.0);  //tronco em forma de cubo
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void desenhaBracosGavioes() {
   glPushMatrix();
   glTranslatef(-0.75f, 1.0f, 0.0f);  //posicao do braço esquerdo
   glRotatef(90.0f, 0.0f +torcedorY, 1.0f, 0.0f);  //uso a variavel 'torcedorY' para animar
   glScalef(0.5f, 0.5f, -1.0f);
   glutSolidCube(1);  //braco esquerdo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.75f, 1.0f, 0.0f);  //posicao do braco direito
   glRotatef(90.0f, 0.0f-torcedorY, 1.0f, 0.0f);  //uso a variavel 'torcedorY' para animar
   glScalef(0.5f, 0.5f, 1.0f);
   glutSolidCube(1);  //braco direito
   glPopMatrix();
}

void desenhaBracosTorcedorComum() {
   glPushMatrix();
   glTranslatef(-0.75f, 1.5f, 0.0f);  //posicao do braço esquerdo
   glRotatef(90.0f, 1.0f, 0.5f, 0.5f);  //roda para posição correta
   glScalef(0.5f, 0.5f, -1.0f);
   glutSolidCube(1);  //braco esquerdo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.75f, 1.5f, 0.0f);  //posicao do braço direito
   glRotatef(90.0f, 1.0f, -0.5f, -0.5f);  //roda para posicao correta
   glScalef(0.5f, 0.5f, 1.0f);
   glutSolidCube(1);  //braco direito
   glPopMatrix();
}

//funcao que desenha um torcedor indivudalmente
void desenhaTorcedor(int x, int y, int z, int rotacao, int tipo){
   glPushMatrix();
   if(tipo==1){
      glTranslatef(x, y+torcedorY, z+torcedorX);
   }else{
      glTranslatef(x, y+torcedorY, z);
   }
   if(rotacao==1)
      glRotatef(90, 0.0f, 1.0f, 0.0f);
   else
      glRotatef(0, 0.0f, 1.0f, 0.0f);
   desenhaCabeca();
   
   if(tipo==1){
      desenhaBracosGavioes();
      desenhaTroncoGavioes();
   }else if(tipo==0){
      desenhaBracosTorcedorComum();
      desenhaTronco();
   }else{
      desenhaBracos();
      desenhaTroncoTorcedorComum();
   }
   desenhaPernas();
   glPopMatrix();
}

//movimenta a Gavioes no eixo Z
void movimentaGavioesZ(){
   if(sentidoX == 1){
      torcedorX += 0.015f;
   }else{
      torcedorX -= 0.015f;
   }

   if(torcedorX <= -1.5f){
      sentidoX = 1;
   }else if(torcedorX >= 1.5f){
      sentidoX = 0;
   }
}

// faz o movimento de pular
void movimentaTorcedorY(){
   if(sentidoY == 1){
      torcedorY += 0.015f;
   }else{
      torcedorY -= 0.015f;
   }

   if(torcedorY <= -0.5f){
      sentidoY = 1;
   }else if(torcedorY >= 0.0f){
      sentidoY = 0;
   }
}

//funcao que determina a posicao de cada um dos torcedores
void desenhaTorcedores(){
   desenhaTorcedor(8, 4, -2, 1, 1);
   desenhaTorcedor(8, 4, 0, 1, 1);
   desenhaTorcedor(8, 4, 2, 1, 1);
   desenhaTorcedor(8, 4, 4, 1, 1);
   desenhaTorcedor(8, 4, 6, 1, 1);
   desenhaTorcedor(6, 2, 0, 1, 1);
   desenhaTorcedor(6, 2, 2, 1, 1);
   desenhaTorcedor(6, 2, 6, 1, 0);
   desenhaTorcedor(-2, 3, 9, 0, 0);
   desenhaTorcedor(2, 1, 7, 0, 2);
}