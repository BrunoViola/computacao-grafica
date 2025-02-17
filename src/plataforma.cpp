#include "plataforma.h"

void desenhaPlataforma(){
   glPushMatrix();
   
   glEnable(GL_TEXTURE_2D); //ativa o uso de texturas
   glBindTexture(GL_TEXTURE_2D, texturaCampo); //aplica a textura carregada
   
   //definindo as coordenadas do plano2D para aplicar a textura
   glBegin(GL_QUADS);
       glNormal3f(0.0f, 1.0f, 0.0f);
       glTexCoord2f(0.0f, 0.0f); glVertex3f(-5.0f, -1.5f, -6.5f);  //canto inferior esquerdo
       glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0f, -1.5f, -6.5f);   //canto inferior direito
       glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0f, -1.5f, 6.5f);    //canto superior direito
       glTexCoord2f(0.0f, 1.0f); glVertex3f(-5.0f, -1.5f, 6.5f);   //canto superior esquerdo
   glEnd();
   glTranslatef(0.0f, -2.05f, 0.0f);
   glScalef(10.0f, 1.0f, 13.0f);  //aumenta o tamanho da plataforma
   glutSolidCube(1.0);

   glDisable(GL_TEXTURE_2D); //desativa o uso de textura
   
   glPopMatrix();
}