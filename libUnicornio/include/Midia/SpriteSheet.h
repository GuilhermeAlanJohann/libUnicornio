#ifndef UNI_SPRITESHEET_H
#define UNI_SPRITESHEET_H

#include "SDL.h"
#include <vector>

using namespace std;

class SpriteSheet
{
private:
	SDL_Texture* tex;
	vector<int> maxframes;	// o indice representa a linha no SpriteSheet, e o valor representa o numero max de frames
	int largura_celula;
	int altura_celula;
	int largura_total;
	int altura_total;
	string caminhoArquivo;

public:
	SpriteSheet(const SpriteSheet& cp);
	SpriteSheet();
	~SpriteSheet();

	SpriteSheet& operator=(const SpriteSheet &r);
	bool operator==(const SpriteSheet &r);
	bool operator!=(const SpriteSheet &r);

	bool carregar(string arquivo, int num_animacoes, int num_max_frames);
	void descarregar();
	bool estaCarregado();

	SDL_Texture* getTextura();
	int getNumAnimacoes();
	int getNumFramesAnimacao(int anim);
	void obterTamanhoCelula(int &w, int &h);
	void obterTamanhoTotal(int &w, int &h);
	void setNumFramesAnimacao(int anim, int max_frames);

	string getCaminhoDoArquivo();
	SpriteSheet clonar();
};

#endif