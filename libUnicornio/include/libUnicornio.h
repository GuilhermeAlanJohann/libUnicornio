#pragma once

/*
Biblioteca de Desenvolvimento de Jogos Digitais
por Guilherme Alan Johann (2014) - pcista@hotmail.com
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

class Imagem;
class Sprite;
class Fonte;

bool UNI_CALL_CONV uniInicializar(int w, int h, bool tela_cheia = false);

void UNI_CALL_CONV uniFinalizar();

void UNI_CALL_CONV uniIniciarFrame(bool sleep_loop = true);

void UNI_CALL_CONV uniTerminarFrame();

void UNI_CALL_CONV uniSetFPS(unsigned int fps);

Fonte* UNI_CALL_CONV uniGetFontePadrao();

void UNI_CALL_CONV uniProcessarEventos();

void UNI_CALL_CONV uniDormir(int milisec);

void UNI_CALL_CONV uniErro(string mensagem);

void UNI_CALL_CONV uniDepurar(string chave, string valor);
void UNI_CALL_CONV uniDepurar(string chave, int valor);
void UNI_CALL_CONV uniDepurar(string chave, double valor);
void UNI_CALL_CONV uniDepurar(string chave, float valor);
void UNI_CALL_CONV uniDepurar(string chave, char valor);

void UNI_CALL_CONV uniDesenharPixel(int x, int y, int vermelho, int verde, int azul, int opaciade = 255);

void UNI_CALL_CONV uniDesenharLinha(int x1, int y1, int x2, int y2, int vermelho, int verde, int azul, int opaciade = 255);

void UNI_CALL_CONV uniDesenharRetangulo(int x, int y, int largura, int altura, int vermelho, int verde, int azul, int opaciade = 255);

void UNI_CALL_CONV uniDesenharTexto(string txt, int x, int y, int cR=255, int cG=255, int cB=255, bool centralizar = false);

void UNI_CALL_CONV uniDesenharFrame(bool limpa = true);

void UNI_CALL_CONV uniSetCorDeFundo(int vermelho, int verde, int azul);

bool UNI_CALL_CONV uniColisao(int px, int py, Sprite* spr, int spr_x, int spr_y, float spr_rot);
bool UNI_CALL_CONV uniColisao(Sprite* spr1, int x1, int y1, float rot1, Sprite* spr2, int x2, int y2, float rot2);

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