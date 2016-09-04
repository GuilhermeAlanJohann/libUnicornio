#ifndef UNI_SPRITESHEET_H
#define UNI_SPRITESHEET_H

#include "uniAPI.h"
#include "Textura.h"
#include "SDL.h"
#include <vector>
#include <string>

using namespace std;

class UNI_API SpriteSheet
{
public:
	SpriteSheet(const SpriteSheet &cp);
	SpriteSheet();
	~SpriteSheet();

	SpriteSheet& operator=(const SpriteSheet &cp);
	bool operator==(const SpriteSheet &cp);
	bool operator!=(const SpriteSheet &cp);

	bool carregar(string arquivo, int num_animacoes, int num_max_frames, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	void descarregar();
	bool estaCarregado();

	int adicionarAnimacao(const Quad& frame_inicial);							//	retorna o indice da animacao
	int adicionarAnimacao(int x0, int y0, int larg, int alt);					//	retorna o indice da animacao
	int adicionarFrameNaAnimacao(int anim, const Quad& frame);					//	retorna o indice do frame (-1 se nao existir a animacao)
	int adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt);	//	retorna o indice do frame (-1 se nao existir a animacao)

	bool removerAnimacao(int anim);
	bool removerFrameDaAnimacao(int anim, int frame);

	void juntarAnimacoes(int anim1, int anim2);
	void juntarTodasAnimacoes();

	int getNumAnimacoes();
	int getNumFramesDaAnimacao(int anim);

	Quad* getRetanguloFrame(int anim, int frame);

	void setNumFramesDaAnimacao(int anim, int num_frames);

	Textura* getTextura();
	SDL_Texture* getSDL_Texture();

	string getCaminhoDoArquivo();
	SpriteSheet clonar();

private:
	Textura tex;
	vector<vector<Quad> > frames;
};

#endif