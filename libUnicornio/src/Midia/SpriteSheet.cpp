#include "SpriteSheet.h"
#include "libUnicornio.h"

SpriteSheet::SpriteSheet()
	:largura_celula(0), altura_celula(0), largura_total(30), altura_total(30), tex(NULL)
{

}

SpriteSheet::SpriteSheet(const SpriteSheet& cp)
{
	tex = cp.tex;
	largura_celula = cp.largura_celula;
	altura_celula = cp.altura_celula;
	maxframes = cp.maxframes;
	largura_total = cp.largura_total;
	altura_total = cp.altura_total;
	caminhoArquivo = cp.caminhoArquivo;
}

SpriteSheet::~SpriteSheet()
{
	apagarTextura();
}

SpriteSheet& SpriteSheet::operator=(const SpriteSheet &r)
{
	if(*this != r)
	{
		tex = r.tex;
		largura_celula = r.largura_celula;
		altura_celula = r.altura_celula;
		maxframes = r.maxframes;
		largura_total = r.largura_total;
		altura_total = r.altura_total;
		caminhoArquivo = r.caminhoArquivo;
	}

	return *this;
}

bool SpriteSheet::operator==(const SpriteSheet &r)
{
	return (maxframes == r.maxframes 
		&& tex == r.tex 
		&& largura_celula == r.largura_celula 
		&& altura_celula == r.altura_celula 
		&& largura_total == r.largura_total 
		&& altura_total == r.altura_total);
}

bool SpriteSheet::operator!=(const SpriteSheet &r)
{
	return !(*this == r);
}

SDL_Texture* SpriteSheet::getTextura()
{
	return tex;
}

int SpriteSheet::getNumAnimacoes()
{
	return maxframes.size();
}

int SpriteSheet::getNumFramesAnimacao(int anim)
{
	if(anim > maxframes.size())
	{
		return 0;
	}

	return maxframes[anim];
}

void SpriteSheet::obterTamanhoCelula(int &w, int &h)
{
	w = largura_celula;
	h = altura_celula;
}

void SpriteSheet::obterTamanhoTotal(int &w, int &h)
{
	w = largura_total;
	h = altura_total;
}

void SpriteSheet::setNumFramesAnimacao(int anim, int max_frames)
{
	if(anim >= maxframes.size())
		return;

	if(max_frames > largura_total/largura_celula)
		return;

	maxframes[anim] = max_frames;
}

bool SpriteSheet::carregar(string arquivo, int num_celulas_x, int num_celulas_y)
{
	if(!uni_init)
	{
		uniDesenharTexto("sem uniInicializar() antes de tentar carregar:" + arquivo, 10, 10);
		return false;
	}

	if(tex)
	{
		SDL_DestroyTexture(tex);
	}

	tex = IMG_LoadTexture(renderer, arquivo.c_str());
	
	if(!tex) 
	{
		string s_err = "Erro carreg. arq: " + arquivo;
		uniErro(s_err);
		uni_debug = true;
		tex = NULL;
		return false;
	}

	SDL_QueryTexture(tex, NULL, NULL, &largura_total, &altura_total);

	largura_celula = largura_total/num_celulas_x;
	altura_celula = altura_total/num_celulas_y;

	maxframes.resize(altura_total/altura_celula);
	for(int i = 0; i < maxframes.size(); ++i)
	{
		maxframes[i] = largura_total/largura_celula;
	}

	caminhoArquivo = arquivo;

	return true;
}

string SpriteSheet::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

SpriteSheet SpriteSheet::clonar()
{
	SpriteSheet r(*this);
	r.carregar(caminhoArquivo, largura_total/largura_celula, altura_total/altura_celula);
	return r;
}

void SpriteSheet::apagarTextura()
{
	if(tex)
	{
		SDL_DestroyTexture(tex);
		caminhoArquivo = "";
	}
}