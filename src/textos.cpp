#include "textos.h"

void renderText(float x, float y, char *string) {
   glRasterPos2f(x, y); //posicao do texto
   for (char *c = string; *c != '\0'; c++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
   }
}

void exibirTextos(){
   char taxaForca[50];
   char quantidadeGols[50];
   char quantidadeDefesas[50];

   sprintf(taxaForca, "     Forca: %.2f", forca);
   sprintf(quantidadeGols, "Gols marcados = %d", gols);
   sprintf(quantidadeDefesas, "Defesas feitas = %d", defesas);

   glColor3f(1.0, 1.0, 1.0);
   renderText(-1, 10, taxaForca);
   renderText(-1, 9, quantidadeGols);
   renderText(-1, 8, quantidadeDefesas);
}