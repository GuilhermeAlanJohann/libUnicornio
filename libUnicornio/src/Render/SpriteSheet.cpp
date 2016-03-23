#include "SpriteSheet.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "SDL_image.h"

SpriteSheet::SpriteSheet()
	:largura_total(0), altura_total(0), sdl_tex(NULL), carregado(false)
{

}

SpriteSheet::SpriteSheet(const SpriteSheet& cp)
{
	sdl_tex = cp.sdl_tex;
	frames = cp.frames;
	largura_total = cp.largura_total;
	altura_total = cp.altura_total;
	caminhoArquivo = cp.caminhoArquivo;
	carregado = cp.carregado;
	qualidade_escala = cp.qualidade_escala;
}

SpriteSheet::~SpriteSheet()
{
}

SpriteSheet& SpriteSheet::operator=(const SpriteSheet &r)
{
	if(*this != r)
	{
		sdl_tex = r.sdl_tex;
		frames = r.frames;
		largura_total = r.largura_total;
		altura_total = r.altura_total;
		caminhoArquivo = r.caminhoArquivo;
		carregado = r.carregado;
		qualidade_escala = r.qualidade_escala;
	}

	return *this;
}

bool SpriteSheet::operator==(const SpriteSheet &r)
{
	return (frames == r.frames 
		&& sdl_tex == r.sdl_tex 
		&& largura_total == r.largura_total 
		&& altura_total == r.altura_total
		&& carregado == r.carregado
		&& qualidade_escala == r.qualidade_escala);
}

bool SpriteSheet::operator!=(const SpriteSheet &r)
{
	return !(*this == r);
}

bool SpriteSheet::carregar(string arquivo, int num_animacoes, int num_max_frames, EnumQualidadeEscala qualidade_escala)
{
	if(!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois SpriteSheet ja carregou o arquivo " + caminhoArquivo + ".");
		return false;
	}

	char buffer[2];
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_itoa((int)qualidade_escala, buffer, 10));
	sdl_tex = IMG_LoadTexture(gJanela.sdl_renderer, arquivo.c_str());
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	
	if(!sdl_tex) 
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		carregado = false;
		return false;
	}

	this->qualidade_escala = qualidade_escala;

	SDL_QueryTexture(sdl_tex, NULL, NULL, &largura_total, &altura_total);

	if(num_animacoes < 1)
		num_animacoes = 1;
	if(num_max_frames < 1)
		num_max_frames = 1;

	int largura_frame = largura_total/num_max_frames;
	int altura_frame = altura_total/num_animacoes;

	frames.resize(num_animacoes);
	for(int i = 0; i < frames.size(); ++i)
	{
		frames[i].resize(num_max_frames);
		for(int j = 0; j < num_max_frames; ++j)
		{
			frames[i][j] = Retangulo(j*largura_frame, i*altura_frame, largura_frame, altura_frame);
		}
	}

	caminhoArquivo = arquivo;

	carregado = true;
	return true;
}

void SpriteSheet::descarregar()
{
	SDL_DestroyTexture(sdl_tex);
	sdl_tex = NULL;
	caminhoArquivo = "";
	frames.clear();
	largura_total = 0;
	altura_total = 0;
	carregado = false;
}

bool SpriteSheet::estaCarregado()
{
	return carregado;
}

int SpriteSheet::adicionarAnimacao(const Retangulo& frame_inicial)
{
	vector<Retangulo> anim;
	anim.push_back(frame_inicial);
	frames.push_back(anim);
	return frames.size()-1;
}

int SpriteSheet::adicionarAnimacao(int x0, int y0, int larg, int alt)
{
	return adicionarAnimacao(Retangulo(x0, y0, larg, alt));
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, const Retangulo& frame)
{
	if(frames.size() <= anim)
		return -1;

	frames[anim].push_back(frame);
	return frames[anim].size()-1;
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt)
{
	return adicionarFrameNaAnimacao(anim, Retangulo(x0, y0, larg, alt));
}

bool SpriteSheet::removerAnimacao(int anim)
{
	if(anim >= frames.size())
		return false;

	frames.erase(frames.begin() + anim);
	return true;
}

bool SpriteSheet::removerFrameDaAnimacao(int anim, int frame)
{
	if(anim >= frames.size())
		return false;

	if(frame >= frames[anim].size())
		return false;

	frames[anim].erase(frames[anim].begin() + frame);
	return true;
}

void SpriteSheet::juntarAnimacoes(int anim1, int anim2)
{
	if(anim1 == anim2)
		return;

	if(anim1 >= 0 && anim1 < frames.size()
		&& anim2 >= 0 && anim2 < frames.size())
	{
		int size1 = frames[anim1].size();
		int size2 = frames[anim2].size();
		frames[anim1].resize(size1 + size2);

		for(int i = 0; i < size2; ++i)
			frames[anim1][size1 + i] = frames[anim2][i];

		removerAnimacao(anim2);
	}
}

void SpriteSheet::juntarTodasAnimacoes()
{
	if(frames.size() <= 1)
		return;

	unsigned int size = 0;
	unsigned int i;
	for(i = 0; i < frames.size(); ++i)
		size += frames[i].size();

	--i;
	frames[0].resize(size);
	for(unsigned int j = 1; j < frames.size(); ++j)
	{
		for(unsigned int k = 0; k < frames[j].size(); ++k)
		{
			frames[0][i] = frames[j][k];
			++i;
		}
	}

	frames.resize(1);
}

int SpriteSheet::getNumAnimacoes()
{
	return frames.size();
}

int SpriteSheet::getNumFramesDaAnimacao(int anim)
{
	return frames[anim].size();
}

Retangulo* SpriteSheet::getRetanguloFrame(int anim, int frame)
{
	return &frames[anim][frame];
}

void SpriteSheet::setNumFramesDaAnimacao(int anim, int num_frames)
{
	if(anim >= frames.size())
		return;

	if(num_frames == frames[anim].size())
		return;

	if(num_frames < frames[anim].size())
	{
		//	remover frames
		if(num_frames <= 0)
		{
			removerAnimacao(anim);
		}
		else
		{
			unsigned int dif = frames[anim].size() - num_frames;
			for(unsigned int i = 0; i < dif; ++i)
				frames[anim].pop_back();
		}
	}
	else
	{
		unsigned int dif = num_frames - frames[anim].size();
		Retangulo f = frames[anim][frames[anim].size()-1];
		for(unsigned int i = 0; i < dif; ++i)
			frames[anim].push_back(f);
	}
}

SDL_Texture* SpriteSheet::getSDL_Texture()
{
	return sdl_tex;
}

string SpriteSheet::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

SpriteSheet SpriteSheet::clonar()
{
	SpriteSheet r;
	r.carregar(caminhoArquivo, 1, 1, qualidade_escala);
	r.frames = frames;
	return r;
}