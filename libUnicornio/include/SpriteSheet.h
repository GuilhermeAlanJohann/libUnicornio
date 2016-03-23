#ifndef UNI_SPRITESHEET_H
#define UNI_SPRITESHEET_H

#include "Retangulo.h"
#include "EnumQualidadeEscala.h"
#include "SDL.h"
#include <vector>
#include <string>

using namespace std;

class SpriteSheet
{
public:
	SpriteSheet(const SpriteSheet &cp);
	SpriteSheet();
	~SpriteSheet();

	SpriteSheet& operator=(const SpriteSheet &r);
	bool operator==(const SpriteSheet &r);
	bool operator!=(const SpriteSheet &r);

	bool carregar(string arquivo, int num_animacoes, int num_max_frames, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	void descarregar();
	bool estaCarregado();

	int adicionarAnimacao(const Retangulo& frame_inicial);						//	retorna o indice da animacao
	int adicionarAnimacao(int x0, int y0, int larg, int alt);					//	retorna o indice da animacao
	int adicionarFrameNaAnimacao(int anim, const Retangulo& frame);				//	retorna o indice do frame (-1 se nao existir a animacao)
	int adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt);	//	retorna o indice do frame (-1 se nao existir a animacao)

	bool removerAnimacao(int anim);
	bool removerFrameDaAnimacao(int anim, int frame);

	void juntarAnimacoes(int anim1, int anim2);
	void juntarTodasAnimacoes();

	int getNumAnimacoes();
	int getNumFramesDaAnimacao(int anim);

	Retangulo* getRetanguloFrame(int anim, int frame);

	void setNumFramesDaAnimacao(int anim, int num_frames);

	SDL_Texture* getSDL_Texture();

	string getCaminhoDoArquivo();
	SpriteSheet clonar();

private:
	SDL_Texture *sdl_tex;
	vector<vector<Retangulo> > frames;
	int largura_total;
	int altura_total;
	string caminhoArquivo;
	bool carregado;

	EnumQualidadeEscala qualidade_escala;
};

#endif