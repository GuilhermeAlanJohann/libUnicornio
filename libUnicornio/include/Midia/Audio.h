#ifndef UNI_AUDIO_H
#define UNI_AUDIO_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>

using namespace std;

class Audio
{
public:
	Audio();
	Audio(const Audio &r);
	~Audio();

	Audio& operator=(const Audio &r);
	bool operator==(const Audio &r);
	bool operator!=(const Audio &r);

	bool carregar(string arquivo);
	void descarregar();

	bool estaCarregado();

	Mix_Chunk* getMixChunk();
	string getCaminhoDoArquivo();
	Audio clonar();

private:
	Mix_Chunk* mix_chunk;

	bool carregado;
	string caminho_arquivo;
};

#endif