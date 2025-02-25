#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "personagem.h"
#include "variaveisGlobais.h"

extern float goleiroX;
extern int orientacao;

void desenhaGoleiro();
void movimentaGoleiroX();
void colisaoBolaGoleiro();
void movimentaBracoGoleiro();
void desenhaBracosGoleiro();