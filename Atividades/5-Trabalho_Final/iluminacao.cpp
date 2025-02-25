#include "iluminacao.h"

void configurarIluminacao() {
   GLfloat luzAmbiente[] = { 0.5f, 0.5f, 0.5f, 1.0f };  // (R, G, B, OPACIDADE), coloquei branca
   GLfloat luzDifusa[] = {  0.5f, 0.5f, 0.5f, 1.0f };  // (R, G, B, OPACIDADE), coloquei branca
   GLfloat luzPosicao[] = { -5.0f, 10.0f, 9.0f, 1.0f };  // (X, Y, Z, TIPO)
   GLfloat segundaLuzPosicao[] = { 8.0f, 10.0f, 9.0f, 1.0f };  // (X, Y, Z, TIPO)
   
   glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
   glLightfv(GL_LIGHT0, GL_POSITION, luzPosicao);

   glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
   glLightfv(GL_LIGHT1, GL_POSITION, segundaLuzPosicao);
   
   glEnable(GL_LIGHTING);

   if(desligarIluminacaoEsquerda == 0){
       glEnable(GL_LIGHT0);
   }else{
       glDisable(GL_LIGHT0);
   }

   if(desligarIluminacaoDireita == 0){
       glEnable(GL_LIGHT1);
   }else{
       glDisable(GL_LIGHT1);
   }
}

//representacao de onde a iluminacao esta posicionada
void desenhaPosicaoIluminacao(){
   glPushMatrix();
   glTranslatef(-5.0f, 10.0f, 9.0f);
   glutSolidSphere(0.5, 30, 30);
   glPopMatrix();

   glPushMatrix();
   glTranslatef(8.0f, 10.0f, 9.0f);
   glutSolidSphere(0.5, 30, 30);
   glPopMatrix();
}