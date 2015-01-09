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

#ifndef UNI_CALL_CONV
	#define UNI_CALL_CONV _cdecl
#endif

extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern int res_x; 
extern int res_y;

extern bool uni_init;
extern double deltaTempo;


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

bool UNI_CALL_CONV uniInicializar(int resolucao_x, int resolucao_y, bool tela_cheia = false, string titulo_janela = "libUNICORNIO");
void UNI_CALL_CONV uniFinalizar();

void UNI_CALL_CONV uniIniciarFrame(bool sleep_loop = true);
void UNI_CALL_CONV uniTerminarFrame();

unsigned int UNI_CALL_CONV uniGetFPS();
void UNI_CALL_CONV uniSetFPS(unsigned int fps);

string UNI_CALL_CONV uniGetTituloJanela();
void UNI_CALL_CONV uniSetTituloJanela(string titulo_janela);

void UNI_CALL_CONV uniSetIconeJanela(string arquivo);

bool UNI_CALL_CONV uniEstaEmModoTelaCheia();

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
void UNI_CALL_CONV uniDesenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharTexto(string txt, int x, int y, int cR=255, int cG=255, int cB=255, bool centralizar = false);
void UNI_CALL_CONV uniDesenharFrame(bool limpa = true);

///////////////////////////////////////////////////////////////////////////////////////

//	colisao
#include "uniColisoes.h"
#include "uniColisoesSprite.h"

//	midia
#include "SpriteSheet.h"
#include "Fonte.h"
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