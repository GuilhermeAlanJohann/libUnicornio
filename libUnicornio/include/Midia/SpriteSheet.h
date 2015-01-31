#ifndef UNI_SPRITESHEET_H
#define UNI_SPRITESHEET_H

#include "SDL.h"
#include <vector>

using namespace std;

enum TipoQualidadeEscala
{
	QUALIDADE_ESCALA_BAIXA,
	QUALIDADE_ESCALA_MEDIA,
	QUALIDADE_ESCALA_ALTA
};

struct Frame
{
	Frame() :x0(0), y0(0), larg(0), alt(0){};
	Frame(int _x0, int _y0, int _larg, int _alt):
		x0(_x0), y0(_y0), larg(_larg), alt(_alt){};
	~Frame()
	{};

	bool operator==(const Frame &r)
	{
		return (x0 == r.x0 && y0 == r.y0 && larg == r.larg && alt == r.alt);
	};

	bool operator==(const Frame &r) const
	{
		return (x0 == r.x0 && y0 == r.y0 && larg == r.larg && alt == r.alt);
	};

	int x0;
	int y0;
	int larg;
	int alt;
};

class SpriteSheet
{
public:
	SpriteSheet(const SpriteSheet &cp);
	SpriteSheet();
	~SpriteSheet();

	SpriteSheet& operator=(const SpriteSheet &r);
	bool operator==(const SpriteSheet &r);
	bool operator!=(const SpriteSheet &r);

	bool carregar(string arquivo, int num_animacoes, int num_max_frames, TipoQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	void descarregar();
	bool estaCarregado();

	int adicionarAnimacao(Frame frame_inicial);									//	retorna o indice da animacao
	int adicionarAnimacao(int x0, int y0, int larg, int alt);					//	retorna o indice da animacao
	int adicionarFrameNaAnimacao(int anim, Frame frame);						//	retorna o indice do frame (-1 se nao existir a animacao)
	int adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt);	//	retorna o indice do frame (-1 se nao existir a animacao)

	bool removerAnimacao(int anim);
	bool removerFrameDaAnimacao(int anim, int frame);

	int getNumAnimacoes();
	int getNumFramesDaAnimacao(int anim);

	Frame *getFrame(int anim, int frame);

	void setNumFramesDaAnimacao(int anim, int num_frames);

	SDL_Texture* getSDL_Texture();

	string getCaminhoDoArquivo();
	SpriteSheet clonar();

private:
	SDL_Texture *sdl_tex;
	vector<vector<Frame>> frames;
	int largura_total;
	int altura_total;
	string caminhoArquivo;
	bool carregado;

	TipoQualidadeEscala qualidade_escala;
};

#endif