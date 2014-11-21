#pragma once

/*
========================================================

Biblioteca de Desenvolvimento de Jogos Digitais
por Guilherme Alan Johann (2014) - pcista@hotmail.com

========================================================

The MIT License (MIT)

Copyright (c) 2014 Guilherme Alan Johann

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.


*/
#ifndef UNI_LIBUNICORNIO_H
#define UNI_LIBUNICORNIO_H

#include "versao_lib.h"
#include "json/json.h"
#include <string>
#include <vector>

using namespace std;

#define PI 3.14159265358979

#define UNI_CALL_CONV _cdecl

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern bool telaCheia;

extern bool uni_init;
extern bool uni_debug;

extern double deltaTempo;

extern int res_x; 
extern int res_y;

#include "GerenciadorDeRecursos.h"
extern GerenciadorDeRecursos recursos;

#include "Eventos.h"
extern Eventos eventos;
extern EventosAplicacao aplicacao;
extern EventosMouse mouse;
extern EventosTeclado teclado;
extern EventosJoysticks joysticks;
extern EventosToque toques;

class Sprite;
class Fonte;
class Vetor2D;

bool UNI_CALL_CONV uniInicializar(int w, int h, bool tela_cheia = false, string titulo_janela = "libUNICORNIO");
void UNI_CALL_CONV uniFinalizar();

void UNI_CALL_CONV uniIniciarFrame(bool sleep_loop = true);
void UNI_CALL_CONV uniTerminarFrame();

unsigned int UNI_CALL_CONV uniGetFPS();
void UNI_CALL_CONV uniSetFPS(unsigned int fps);

string UNI_CALL_CONV uniGetTituloJanela();
void UNI_CALL_CONV uniSetTituloJanela(string titulo_janela);

Fonte* UNI_CALL_CONV uniGetFontePadrao();

void UNI_CALL_CONV uniProcessarEventos();

void UNI_CALL_CONV uniDormir(int milisec);

void UNI_CALL_CONV uniErro(string mensagem);

void UNI_CALL_CONV uniDepurar(string chave, string valor);
void UNI_CALL_CONV uniDepurar(string chave, int valor);
void UNI_CALL_CONV uniDepurar(string chave, double valor);
void UNI_CALL_CONV uniDepurar(string chave, float valor);
void UNI_CALL_CONV uniDepurar(string chave, char valor);

void UNI_CALL_CONV uniSetCorDeFundo(int vermelho, int verde, int azul);

void UNI_CALL_CONV uniDesenharPixel(int x, int y, int vermelho, int verde, int azul, int opaciade = 255);
void UNI_CALL_CONV uniDesenharLinha(int x1, int y1, int x2, int y2, int vermelho, int verde, int azul, int opaciade = 255);
void UNI_CALL_CONV uniDesenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharPoligono(int x, int y, float rot, float escala_x, float escala_y, Vetor2D* pontos, int num_pontos, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharTexto(string txt, int x, int y, int cR=255, int cG=255, int cB=255, bool centralizar = false);
void UNI_CALL_CONV uniDesenharFrame(bool limpa = true);

bool UNI_CALL_CONV uniColisao(int px, int py, Sprite* spr, int spr_x, int spr_y, float spr_rot);					//	VAI SER REMOVIDA NO FUTURO
bool UNI_CALL_CONV uniColisao(Sprite* spr1, int x1, int y1, float rot1, Sprite* spr2, int x2, int y2, float rot2);	//	VAI SER REMOVIDA NO FUTURO
bool UNI_CALL_CONV uniColisaoPontoComCirculo(float ponto_x, float ponto_y, float circulo_x, float circulo_y, float raio);	
bool UNI_CALL_CONV uniColisaoPontoComRetangulo(int ponto_x, int ponto_y, int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y);
bool UNI_CALL_CONV uniColisaoPontoComPoligono(float ponto_x, float ponto_y, Vetor2D* pontos, int num_pontos, float x, float y, float rot, float escala_x, float escala_y);
bool UNI_CALL_CONV uniColisaoPontoComSprite(float ponto_x, float ponto_y, Sprite* spr, float x, float y, float rot);
bool UNI_CALL_CONV uniColisaoLinhaComLinha(float linhaA_x0, float linhaA_y0, float linhaA_x1, float linhaA_y1, float linhaB_x0, float linhaB_y0, float linhaB_x1, float linhaB_y1);
bool UNI_CALL_CONV uniColisaoLinhaComCirculo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float circulo_x, float circulo_y, float raio);	
bool UNI_CALL_CONV uniColisaoLinhaComRetangulo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y);
bool UNI_CALL_CONV uniColisaoLinhaComPoligono(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y);
bool UNI_CALL_CONV uniColisaoLinhaComSprite(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Sprite* spr, float x, float y, float rot);
bool UNI_CALL_CONV uniColisaoCirculoComCirculo(float circulo_x1, float circulo_y1, float raio1, float circulo_x2, float circulo_y2, float raio2);
bool UNI_CALL_CONV uniColisaoCirculoComRetangulo(float circulo_x, float circulo_y, float raio, int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoCirculoComPoligono(float circulo_x, float circulo_y, float raio, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoCirculoComSprite(float circulo_x, float circulo_y, float raio, Sprite* spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoRetanguloComRetangulo(int x1, int y1, float rot1, int largura1, int altura1, float ancora_x1, float ancora_y1, int x2, int y2, float rot2, int largura2, int altura2, float ancora_x2, float ancora_y2, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoRetanguloComPoligono(int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoRetanguloComSprite(int retan_x, int retan_y, float retan_rot, int retan_largura, int retan_altura, float retan_ancora_x, float retan_ancora_y, Sprite* spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoPoligonoComPoligono(Vetor2D* pontos1, int num_pontos1, float x1, float y1, float rot1, float escala_x1, float escala_y1, Vetor2D* pontos2, int num_pontos2, float x2, float y2, float rot2, float escala_x2, float escala_y2, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoPoligonoComSprite(Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, float poli_escala_x, float poli_escala_y, Sprite* spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoSpriteComSprite(Sprite* spr1, float x1, float y1, float rot1, Sprite* spr2, float x2, float y2, float rot2, bool testar_dentro = true);


///////////////////////////////////////////////////////////////////////////////////////

//	midia
#include "SpriteSheet.h"
#include "Texto.h"
#include "Som.h"

#include "Sprite.h"
#include "Texto.h"
#include "Musica.h"

//	tilemap
#include "TileMap.h"
#include "AStar.h"

//	interface 
#include "BotaoSprite.h"


#endif