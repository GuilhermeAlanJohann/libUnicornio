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

#include "uniAPI.h"

//	Blibliotecas base
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

//	Json
#include "json/json.h"

//	Globais
#include "uniFuncoesPrincipais.h"
#include "Global.h"

//	Utils
#include "uniRand.h"
#include "uniEase.h"

//	Arquivos
#include "uniSistemaDeArquivos.h"
#include "Preferencias.h"

//	Colisao
#include "uniTestarColisao.h"
#include "uniTestarColisaoSprite.h"

//	Recursos
#include "SpriteSheet.h"
#include "Fonte.h"
#include "Audio.h"

//	Utilizadores de recursos
#include "Sprite.h"
#include "Texto.h"
#include "Som.h"

//	Textura
#include "TexturaBase.h"
#include "Textura.h"
#include "TexturaAlvo.h"

//	Outros
#include "Musica.h"

//	Tilemap
#include "TileMap.h"

//	Inteligencia Artificial
#include "AStar.h"
#include "TravessiaAStar.h"
#include "Estado.h"
#include "MaquinaDeEstados.h"
#include "MaquinaDeEstadosComPilha.h"
#include "Neuronio.h"
#include "RedeNeural.h"

//	Interface 
#include "BotaoSprite.h"


#endif