#include <GL/glut.h>
#include <stb_image.h>
#include "texturas.h"


GLuint texturaID;
GLuint texturaCampo;
GLuint texturaPatrocionios;
GLuint texturaPatrocioniosDireita;
GLuint texturaCamisa;
GLuint texturaCamisaVerso;
GLuint texturaCamisaGoleiro;
GLuint texturaCamisaGavioes;
GLuint texturaCamisaTorcedor;


void carregarTextura() {
    int largura, altura, canais;
    int larguraPatrocinios, alturaPatrocinios, canaisPatrocinios;
    int larguraPatrociniosDireita, alturaPatrociniosDireita, canaisPatrociniosDireita;
    int larguraCamisa, alturaCamisa, canaisCamisa;
    int larguraCamisaVerso, alturaCamisaVerso, canaisCamisaVerso;
    int larguraCamisaGoleiro, alturaCamisaGoleiro, canaisCamisaGoleiro;
    int larguraCamisaGavioes, alturaCamisaGavioes, canaisCamisaGavioes;
    int larguraCamisaTorcedor, alturaCamisaTorcedor, canaisCamisaTorcedor;

    unsigned char* imagem = stbi_load("campo.jpg", &largura, &altura, &canais, 0);
    if (imagem == NULL ) {
        printf("Erro ao carregar a textura da plataforma\n");
        return;
    }

    unsigned char* imagemPatrocinios = stbi_load("patrocinadorEsquerda.jpg", &larguraPatrocinios, &alturaPatrocinios, &canaisPatrocinios, 0);
    if (imagemPatrocinios == NULL ) {
        printf("Erro ao carregar a textura do patrocinador da Esquerda\n");
        return;
    }

    unsigned char* imagemPatrociniosDireita = stbi_load("patrocinadorDireita.jpg", &larguraPatrociniosDireita, &alturaPatrociniosDireita, &canaisPatrociniosDireita, STBI_rgb);
    if (imagemPatrocinios == NULL ) {
        printf("Erro ao carregar a textura do patrocinador da Direita\n");
        return;
    }
    
    unsigned char* imagemCamisa = stbi_load("camisa.jpg", &larguraCamisa, &alturaCamisa, &canaisCamisa, STBI_rgb);
    if (imagemCamisa == NULL ) {
        printf("Erro ao carregar a textura da camisa\n");
        return;
    }

    unsigned char* imagemCamisaVerso = stbi_load("camisaVerso.jpg", &larguraCamisaVerso, &alturaCamisaVerso, &canaisCamisaVerso, STBI_rgb);
    if (imagemCamisaVerso == NULL ) {
        printf("Erro ao carregar a textura da camisaVerso\n");
        return;
    }

    unsigned char* imagemCamisaGoleiro = stbi_load("camisaGoleiro.jpg", &larguraCamisaGoleiro, &alturaCamisaGoleiro, &canaisCamisaGoleiro, STBI_rgb);
    if (imagemCamisaGoleiro == NULL ) {
        printf("Erro ao carregar a textura da camisaGoleiro\n");
        return;
    }

    unsigned char* imagemCamisaGavioes = stbi_load("camisaGavioes.jpg", &larguraCamisaGavioes, &alturaCamisaGavioes, &canaisCamisaGavioes, STBI_rgb);
    if (imagemCamisaGavioes == NULL ) {
        printf("Erro ao carregar a textura da camisaGavioes\n");
        return;
    }

    unsigned char* imagemCamisaTorcedor = stbi_load("segundaCamisaTorcedor.jpg", &larguraCamisaTorcedor, &alturaCamisaTorcedor, &canaisCamisaTorcedor, STBI_rgb);

    glGenTextures(1, &texturaCampo);
    glBindTexture(GL_TEXTURE_2D, texturaCampo);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, imagem);
    
    glGenTextures(1, &texturaPatrocionios);
    glBindTexture(GL_TEXTURE_2D, texturaPatrocionios);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraPatrocinios, alturaPatrocinios, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemPatrocinios);

    glGenTextures(1, &texturaPatrocioniosDireita);
    glBindTexture(GL_TEXTURE_2D, texturaPatrocioniosDireita);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraPatrociniosDireita, alturaPatrociniosDireita, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemPatrociniosDireita);

    glGenTextures(1, &texturaCamisa);
    glBindTexture(GL_TEXTURE_2D, texturaCamisa);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraCamisa, alturaCamisa, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemCamisa);

    glGenTextures(1, &texturaCamisaVerso);
    glBindTexture(GL_TEXTURE_2D, texturaCamisaVerso);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraCamisaVerso, alturaCamisaVerso, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemCamisaVerso);

    glGenTextures(1, &texturaCamisaGoleiro);
    glBindTexture(GL_TEXTURE_2D, texturaCamisaGoleiro);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraCamisaGoleiro, alturaCamisaGoleiro, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemCamisaGoleiro);

    glGenTextures(1, &texturaCamisaGavioes);
    glBindTexture(GL_TEXTURE_2D, texturaCamisaGavioes);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraCamisaGavioes, alturaCamisaGavioes, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemCamisaGavioes);

    glGenTextures(1, &texturaCamisaTorcedor);
    glBindTexture(GL_TEXTURE_2D, texturaCamisaTorcedor);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, larguraCamisaTorcedor, alturaCamisaTorcedor, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemCamisaTorcedor);

    stbi_image_free(imagem);
    stbi_image_free(imagemPatrocinios);
    stbi_image_free(imagemPatrociniosDireita);
    stbi_image_free(imagemCamisa);
    stbi_image_free(imagemCamisaVerso);
    stbi_image_free(imagemCamisaGoleiro);
    stbi_image_free(imagemCamisaGavioes);
    stbi_image_free(imagemCamisaTorcedor);
}