#include "bolaParedeGol.h"
#include "variaveisGlobais.h"

extern float ballY;
extern float ballX;
extern float ballZ;

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