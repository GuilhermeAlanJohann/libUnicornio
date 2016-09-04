#ifndef UNI_GERENCIADORDEMUSICA_H
#define UNI_GERENCIADORDEMUSICA_H

#include "uniAPI.h"
#include <string>
#include "SDL_mixer.h"

using namespace std;

class Musica;

class UNI_API GerenciadorDeMusica
{
public:
	GerenciadorDeMusica();
	~GerenciadorDeMusica();

	bool tocar(Musica* musica, bool repetir = true, float tempo_fadein = 0.0f, float tempo_inicial = 0.0f);
	bool tocar(const string& nome, bool repetir, float tempo_fadein = 0.0f, float tempo_inicial = 0.0f);
	void parar(float tempo_fadeout = 0.0f);
	void pausar();
	void continuar();
	bool estaTocando();
	bool estaPausado();
	bool estaExecutandoFade();
	bool estaExecutandoFadeIn();
	bool estaExecutandoFadeOut();
	bool irParaOTempo(float tempo);		//	Funciona apenas para MP3, OGG e FLAC. A musica deve estar tocando. 

	Musica* getMusica();
	string getNomeMusica();
	float getVolumeGlobal();

	void setVolumeGlobal(float volume);

private:
	string nome_musica;
	Musica* musica;
	float volume_global;
};

#endif