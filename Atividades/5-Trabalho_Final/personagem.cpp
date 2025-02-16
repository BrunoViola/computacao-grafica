#include "texturas.h"
#include "personagem.h"

float bonecoX = 0.0f;
float bonecoY = 2.0f;
float bonecoZ = 1.0f;

// ======================= Funções de desenho do personagem =======================
void desenhaCabeca() {
   glPushMatrix();
   glTranslatef(0.0f, 2.0f, 0.0f);  //posiciona a cabeca
   glutSolidSphere(0.5, 30, 30);  //cabeca com raio 0.5
   glPopMatrix();
}

void desenhaTronco() {
   glPushMatrix();
   glTranslatef(0.0f, 0.8f, 0.0f);  //posiciona o tronco
   glScalef(0.8f, 1.0f, 0.5f);  //escala para criar o tronco
   glutSolidCube(1.0);  //tronco em forma de cubo
   glPopMatrix();

   glEnable(GL_TEXTURE_2D); // Ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisa); // Aplica a textura carregada
   glBegin(GL_QUADS);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, -0.26f); // Inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, -0.26f); // Inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, -0.26f); // Superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, -0.26f); // Superior esquerdo
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texturaCamisaVerso);
   glBegin(GL_QUADS);
       glNormal3f(0.0f, 0.0f, 1.0f);
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.4f, 0.3f, 0.26f); // Inferior esquerdo
       glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.4f, 0.3f, 0.26f); // Inferior direito
       glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.4f, 1.3f, 0.26f); // Superior direito
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.4f, 1.3f, 0.26f); // Superior esquerdo
   glEnd();

   glDisable(GL_TEXTURE_2D);
}

void desenhaBracos() {
   glPushMatrix();
   glTranslatef(-0.75f, 1.5f, 0.0f);  //posicao do braço esquerdo
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  //roda para posição correta
   glScalef(0.5f, 0.5f, -1.0f);
   glutSolidCube(1);  //braco esquerdo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.75f, 1.5f, 0.0f);  //posicao do braço direito
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  //roda para posicao correta
   glScalef(0.5f, 0.5f, 1.0f);
   glutSolidCube(1);  //braco direito
   glPopMatrix();
}

void desenhaPernas() {
   glPushMatrix();
   glTranslatef(0.2f, -0.5f, 0.0f);  //posicao da perna esquerda
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  //roda para posição correta
   glScalef(0.5f, 0.5f, 1.5f);
   glutSolidCube(1.0);  //perna esquerda
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-0.2f, -0.5f, 0.0f);  //posicao da perna direita
   glRotatef(90.0f, 1.0f, 0.0f, 0.0f);  //roda para posição correta
   glScalef(0.5f, 0.5f, 1.5f);
   glutSolidCube(1.0);  //perna direita
   glPopMatrix();
}

void desenhaBoneco() {
   glPushMatrix();
   glTranslatef(bonecoX, bonecoY, bonecoZ);
   desenhaCabeca();
   desenhaTronco();
   desenhaBracos();
   desenhaPernas();
   glPopMatrix();
}