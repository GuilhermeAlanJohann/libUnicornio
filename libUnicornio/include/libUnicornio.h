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

#include "uniPlataformas.h"
#include "uniConfig.h"
#include "json/json.h"
#include <string>
#include <vector>

using namespace std;

#ifndef UNI_CALL_CONV
	#define UNI_CALL_CONV _cdecl
#endif

extern SDL_Renderer *sdl_renderer;
extern bool uni_init;
extern double deltaTempo;

#include "Janela.h"
extern Janela janela;
extern int res_x;	//	OBSOLETO ( usar janela.getLarguraTela() )
extern int res_y;	//	OBSOLETO ( usar janela.getAlturaTela() )

#include "MixadorDeAudios.h"
extern MixadorDeAudios mixador_de_audios;

#include "GerenciadorDeRecursos.h"
extern GerenciadorDeRecursos recursos;

#include "Eventos.h"
extern Eventos eventos;
extern EventosAplicacao aplicacao;
extern EventosMouse mouse;
extern EventosTeclado teclado;
extern EventosJoysticks joysticks;
extern EventosTelaDeToque telaDeToque;

class Vetor2D;

bool UNI_CALL_CONV uniInicializar(int largura_tela, int altura_tela, bool tela_cheia = false, string titulo_janela = "libUNICORNIO");
void UNI_CALL_CONV uniFinalizar();

void UNI_CALL_CONV uniIniciarFrame(bool sleep_loop = true);
void UNI_CALL_CONV uniTerminarFrame();

unsigned int UNI_CALL_CONV uniGetFPS();
void UNI_CALL_CONV uniSetFPS(unsigned int fps);

Fonte* UNI_CALL_CONV uniGetFontePadrao();

void UNI_CALL_CONV uniProcessarEventos();

string UNI_CALL_CONV uniGetStringDaAreaDeTransferencia();
void UNI_CALL_CONV uniSetStringDaAreaDeTransferencia(string s);
bool UNI_CALL_CONV uniTemStringNaAreaDeTransferencia();

void UNI_CALL_CONV uniDormir(int milisec);

void UNI_CALL_CONV uniErro(string mensagem);

void UNI_CALL_CONV uniDepurar(string chave, string valor);
void UNI_CALL_CONV uniDepurar(string chave, int valor);
void UNI_CALL_CONV uniDepurar(string chave, unsigned int valor);
void UNI_CALL_CONV uniDepurar(string chave, double valor);
void UNI_CALL_CONV uniDepurar(string chave, float valor);
void UNI_CALL_CONV uniDepurar(string chave, char valor);

void UNI_CALL_CONV uniDesenharPixel(int x, int y, int vermelho, int verde, int azul, int opaciade = 255);
void UNI_CALL_CONV uniDesenharLinha(int x1, int y1, int x2, int y2, int vermelho, int verde, int azul, int opaciade = 255);
void UNI_CALL_CONV uniDesenharCirculo(int x, int y, float raio, int num_segmentos, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharRetangulo(int x, int y, float rot, int largura, int altura, float ancora_x, float ancora_y, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharPoligono(int x, int y, float rot, Vetor2D* pontos, int num_pontos, int vermelho = 255, int verde = 255, int azul = 255);
void UNI_CALL_CONV uniDesenharTexto(string txt, int x, int y, int cR=255, int cG=255, int cB=255, float ancora_x = 0.5f, float ancora_y = 0.5f);
void UNI_CALL_CONV uniDesenharFrame(bool limpar = true);

///////////////////////////////////////////////////////////////////////////////////////

//	colisao
#include "uniColisoes.h"
#include "uniColisoesSprite.h"

//	midia
#include "SpriteSheet.h"
#include "Fonte.h"
#include "Audio.h"

#include "Sprite.h"
#include "Texto.h"
#include "Som.h"
#include "Musica.h"

//	tilemap
#include "TileMap.h"
#include "AStar.h"

//	interface 
#include "BotaoSprite.h"


#endif