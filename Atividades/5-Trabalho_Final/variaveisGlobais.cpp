#include "variaveisGlobais.h"

float ballY = 2.0f;
float ballX = 0.0f;
float ballZ = 0.0f;

float bonecoX = 0.0f;
float bonecoY = 2.0f;
float bonecoZ = 1.0f;

int ultimoMovimentoEsquerda = 0;
int ultimoMovimentoDireita = 0;
int ultimoMovimentoCima = 0;
int ultimoMovimentoBaixo = 0;

int backupUltimoMovimentoEsquerda = 0;
int backupUltimoMovimentoDireita = 0;
int backupUltimoMovimentoCima = 0;
int backupUltimoMovimentoBaixo = 0;

float speedX = 0.0f;
float speedZ = 0.0f;

float reboteEmX = 0.0f;
float reboteEmZ = 0.0f;

int reboteEmAndamento = 0;

float forca = 2.0f; //forca do chute

int gols = 0; //quantidade de gols marcados
int defesas = 0; //quantidade de defesas do goleiro

int desligarIluminacaoEsquerda = 0;
int desligarIluminacaoDireita = 0;