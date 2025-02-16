#include <GL/glut.h>
#include <stb_image.h>
#include "texturas.h"


GLuint texturaID;
GLuint texturaCampo;
GLuint texturaPatrocionios;
GLuint texturaPatrocioniosDireita;
GLuint texturaCamisa;
GLuint texturaCamisaVerso;


void carregarTextura() {
    int largura, altura, canais;
    int larguraPatrocinios, alturaPatrocinios, canaisPatrocinios;
    int larguraPatrociniosDireita, alturaPatrociniosDireita, canaisPatrociniosDireita;
    int larguraCamisa, alturaCamisa, canaisCamisa;
    int larguraCamisaVerso, alturaCamisaVerso, canaisCamisaVerso;

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

    stbi_image_free(imagem);
    stbi_image_free(imagemPatrocinios);
    stbi_image_free(imagemPatrociniosDireita);
    stbi_image_free(imagemCamisa);
    stbi_image_free(imagemCamisaVerso);
}