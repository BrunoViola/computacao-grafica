#include "torcedores.h"

float torcedorY = 0.0f;
int sentido = 1;

void desenhaTroncoGavioes() {
   glEnable(GL_TEXTURE_2D); // Ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisaGavioes); // Aplica a textura carregada
   glBegin(GL_QUADS);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, -0.26f); // Inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, -0.26f); // Inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, -0.26f); // Superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, -0.26f); // Superior esquerdo
   glEnd();
   glPushMatrix();

   glTranslatef(0.0f, 0.8f, 0.0f);  //posiciona o tronco
   glScalef(0.8f, 1.0f, 0.5f);  //escala para criar o tronco
   glutSolidCube(1.0);  //tronco em forma de cubo
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void desenhaTroncoTorcedor() {
   glEnable(GL_TEXTURE_2D); // Ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisaTorcedor); // Aplica a textura carregada
   glBegin(GL_QUADS);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, -0.26f); // Inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, -0.26f); // Inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, -0.26f); // Superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, -0.26f); // Superior esquerdo
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
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);  //roda para posição correta
   glScalef(0.5f, 0.5f, -1.0f);
   glutSolidCube(1);  //braco esquerdo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.75f, 1.0f, 0.0f);  //posicao do braço direito
   glRotatef(90.0f, 0.0f, 1.0f, 0.0f);  //roda para posicao correta
   glScalef(0.5f, 0.5f, 1.0f);
   glutSolidCube(1);  //braco direito
   glPopMatrix();
}

void desenhaTorcedor(int x, int y, int z, int rotacao, int tipo){
   glPushMatrix();
   glTranslatef(x, y+torcedorY, z);
   if(rotacao==1)
      glRotatef(90, 0.0f, 1.0f, 0.0f);
   else
      glRotatef(0, 0.0f, 1.0f, 0.0f);
   desenhaCabeca();
   
   if(tipo==1){
      desenhaBracosGavioes();
      desenhaTroncoGavioes();
   }else if(tipo==0){
      desenhaBracos();
      desenhaTronco();
   }else{
      desenhaBracos();
      desenhaTroncoTorcedor();
   }
   desenhaPernas();
   glPopMatrix();
}

void movimentaTorcedor(){
   if(sentido == 1){
      torcedorY += 0.015f;
   }else{
      torcedorY -= 0.015f;
   }

   if(torcedorY <= -0.5f){
      sentido = 1;
   }else if(torcedorY >= 0.0f){
      sentido = 0;
   }
}

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