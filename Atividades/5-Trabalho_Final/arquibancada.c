#include "arquibancada.h"
#include <GL/glut.h>


void desenhaArquibancadaFrente(){
   glPushMatrix(); //primeiro degrau
   glDisable(GL_LIGHTING);
   glColor3f(0.1f, 0.1f, 0.1f);
   glTranslatef(0.5f, -1.0f, 7.0f);
   glScalef(11.0f, 1.0f, 1.0f);
   glutSolidCube(1.0);
   glEnable(GL_LIGHTING);
   glPopMatrix();
   
   glPushMatrix(); //segundo degrau
   glTranslatef(1.0f, 0.0f, 8.0f);
   glScalef(12.0f, 1.0f, 1.0f);
   glutSolidCube(1.0);
   glPopMatrix();

   glPushMatrix(); //terceiro degrau
   glDisable(GL_LIGHTING);
   glColor3f(0.1f, 0.1f, 0.1f);
   glTranslatef(1.75f, 1.0f, 9.0f);
   glScalef(13.5f, 1.0f, 1.0f);
   glutSolidCube(1.0);
   glEnable(GL_LIGHTING);
   glPopMatrix();

   glPushMatrix(); //quarto degrau
   glTranslatef(1.75f, 2.0f, 10.0f);
   glScalef(13.5f, 1.0f, 1.0f);
   glutSolidCube(1.0);
   glPopMatrix();
}


void desenhaArquibancadaDireita(){
   glPushMatrix(); //primeiro degrau
   glDisable(GL_LIGHTING);
   glColor3f(0.1f, 0.1f, 0.1f);
   glTranslatef(5.0f, -1.0f, 0.5f);
   glScalef(1.0f, 1.0f, 14.0f);
   glutSolidCube(1.0);
   glEnable(GL_LIGHTING);
   glPopMatrix();

   glPushMatrix(); //segundo degrau
   glTranslatef(6.0f, 0.0f, 1.5f);
   glScalef(1.0f, 1.0f, 16.0f);
   glutSolidCube(1.0);
   glPopMatrix();

   glPushMatrix(); //terceiro degrau
   glDisable(GL_LIGHTING);
   glColor3f(0.1f, 0.1f, 0.1f);
   glTranslatef(7.0f, 1.0f, 1.5f);
   glScalef(1.0f, 1.0f, 16.0f);
   glutSolidCube(1.0);
   glEnable(GL_LIGHTING);
   glPopMatrix();
   
   glPushMatrix(); //quarto degrau
   glTranslatef(8.0f, 2.0f, 1.5f);
   glScalef(1.0f, 1.0f, 16.0f);
   glutSolidCube(1.0);
   glPopMatrix();
}