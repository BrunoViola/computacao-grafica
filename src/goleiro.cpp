#include "goleiro.h"

void desenhaTroncoGoleiro() {
   glEnable(GL_TEXTURE_2D); // Ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCamisaGoleiro); // Aplica a textura carregada
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

void desenhaGoleiro(){
   glPushMatrix();
   glTranslatef(0, 0, -5);
   glRotatef(180, 0, 1, 0);
   desenhaCabeca();
   desenhaTroncoGoleiro();
   desenhaBracos();
   desenhaPernas();
   glPopMatrix();
}