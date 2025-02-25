#include "goleiro.h"

float goleiroX = 0.0f;
int orientacao = 1;

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

void desenhaBracosGoleiro() {
   glPushMatrix();
   glTranslatef(-0.75f, 1.0f, 0.0f);  //posicao do braço esquerdo
   glRotatef(70.0f, 0.0f, 1.0f, 0.0f);  //roda para posição correta
   glScalef(0.5f, 0.5f, -1.0f);
   glutSolidCube(1);  //braco esquerdo
   glPopMatrix();

   glPushMatrix();
   glTranslatef(0.75f, 1.0f, 0.0f);  //posicao do braço direito
   glRotatef(110.0f, 0.0f, 1.0f, 0.0f);  //roda para posicao correta
   glScalef(0.5f, 0.5f, 1.0f);
   glutSolidCube(1);  //braco direito
   glPopMatrix();
}

void desenhaGoleiro(){
   glPushMatrix();
   glTranslatef(goleiroX, 0, -5);
   glRotatef(180, 0, 1, 0);
   desenhaCabeca();
   desenhaTroncoGoleiro();
   desenhaBracosGoleiro();
   desenhaPernas();
   glPopMatrix();
}

//========== movimentacao do goleiro ==========
void movimentaGoleiroX(){
   
   if(orientacao == 1){
      goleiroX += 0.01f;
   }else{
      goleiroX -= 0.01f;
   }

   if(goleiroX <= -1.5f){
      orientacao = 1;
   }else if(goleiroX >= 1.5f){
      orientacao = 0;
   }
}
//========== colisao bola com o goleiro ========
void colisaoBolaGoleiro(){
   float dx = ballX - goleiroX;  //diferenca no eixo X
   float dz = ballZ + 5; //diferenca no eixo Z
   float distancia = sqrt(dx * dx + dz * dz);  // calculo da distancia euclidiana

   float raioBoneco = 0.3f;
   float raioBola = 0.3f;
   
   if (distancia < (raioBoneco + raioBola)){
      printf("Defendeu\n");
      ballX = 0.0f;
      ballZ = 3.0f;
      ballY = 2.0f;
      speedX = 0.0f;
      speedZ = 0.0f;
      defesas ++;
   }
   
   glutPostRedisplay();
}