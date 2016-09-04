#include "SpriteSheet.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "SDL_image.h"

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::SpriteSheet(const SpriteSheet& cp)
{
	tex = cp.tex;
	frames = cp.frames;
}

SpriteSheet::~SpriteSheet()
{
}

SpriteSheet& SpriteSheet::operator=(const SpriteSheet &cp)
{
	if(*this != cp)
	{
		tex = cp.tex;
		frames = cp.frames;
	}

	return *this;
}

bool SpriteSheet::operator==(const SpriteSheet &cp)
{
	return (frames == cp.frames 
		&& tex == cp.tex);
}

bool SpriteSheet::operator!=(const SpriteSheet &cp)
{
	return !(*this == cp);
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
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois SpriteSheet ja carregou o arquivo " + tex.getCaminhoDoArquivo() + ".");
		return false;
	}

	if(!tex.criarDoArquivo(arquivo, qualidade_escala))
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	if(num_animacoes < 1)
		num_animacoes = 1;
	if(num_max_frames < 1)
		num_max_frames = 1;

	int largura_frame = tex.getLargura()/num_max_frames;
	int altura_frame = tex.getAltura()/num_animacoes;

	frames.resize(num_animacoes);
	for(int i = 0; i < frames.size(); ++i)
	{
		frames[i].resize(num_max_frames);
		for(int j = 0; j < num_max_frames; ++j)
		{
			frames[i][j] = Quad(j*largura_frame, i*altura_frame, largura_frame, altura_frame);
		}
	}

	return true;
}

void SpriteSheet::descarregar()
{
	if (tex.destruir())
	{
		frames.clear();
	}
}

bool SpriteSheet::estaCarregado()
{
	return tex.estaCriada();
}

int SpriteSheet::adicionarAnimacao(const Quad& frame_inicial)
{
	vector<Quad> anim;
	anim.push_back(frame_inicial);
	frames.push_back(anim);
	return frames.size()-1;
}

int SpriteSheet::adicionarAnimacao(int x0, int y0, int larg, int alt)
{
	return adicionarAnimacao(Quad(x0, y0, larg, alt));
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, const Quad& frame)
{
	if(frames.size() <= anim)
		return -1;

	frames[anim].push_back(frame);
	return frames[anim].size()-1;
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt)
{
	return adicionarFrameNaAnimacao(anim, Quad(x0, y0, larg, alt));
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

Quad* SpriteSheet::getRetanguloFrame(int anim, int frame)
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
		Quad f = frames[anim][frames[anim].size()-1];
		for(unsigned int i = 0; i < dif; ++i)
			frames[anim].push_back(f);
	}
}

Textura* SpriteSheet::getTextura()
{
	return &tex;
}

SDL_Texture* SpriteSheet::getSDL_Texture()
{
	return tex.getSDL_Texture();
}

string SpriteSheet::getCaminhoDoArquivo()
{
	return tex.getCaminhoDoArquivo();
}

SpriteSheet SpriteSheet::clonar()
{
	SpriteSheet r;
	r.tex = tex.clonar();
	r.frames = frames;
	return r;
}