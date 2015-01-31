#include "SpriteSheet.h"
#include "libUnicornio.h"

SpriteSheet::SpriteSheet()
	:largura_total(30), altura_total(30), sdl_tex(NULL), carregado(false)
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

bool SpriteSheet::carregar(string arquivo, int num_animacoes, int num_max_frames, TipoQualidadeEscala qualidade_escala)
{
	if(!uni_init)
	{
		uniErro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		uniErro("Arquivo '" + arquivo + "' nao pode ser carregado, pois SpriteSheet ja carregou o arquivo " + caminhoArquivo + ".");
		return false;
	}

	switch(qualidade_escala)
	{
	case QUALIDADE_ESCALA_BAIXA:
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
		break;

	case QUALIDADE_ESCALA_MEDIA:
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
		break;

	case QUALIDADE_ESCALA_ALTA:
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
		break;
	}

	sdl_tex = IMG_LoadTexture(renderer, arquivo.c_str());
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	
	if(!sdl_tex) 
	{
		uniErro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
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
	for(unsigned int i = 0; i < frames.size(); ++i)
	{
		frames[i].resize(num_max_frames);
		for(unsigned int j = 0; j < num_max_frames; ++j)
		{
			frames[i][j] = Frame(j*largura_frame, i*altura_frame, largura_frame, altura_frame);
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

int SpriteSheet::adicionarAnimacao(Frame frame_inicial)
{
	vector<Frame> anim;
	anim.push_back(frame_inicial);
	frames.push_back(anim);
	return frames.size()-1;
}

int SpriteSheet::adicionarAnimacao(int x0, int y0, int larg, int alt)
{
	return adicionarAnimacao(Frame(x0, y0, larg, alt));
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, Frame frame)
{
	if(frames.size() <= anim)
		return -1;

	frames[anim].push_back(frame);
	return frames[anim].size()-1;
}

int SpriteSheet::adicionarFrameNaAnimacao(int anim, int x0, int y0, int larg, int alt)
{
	return adicionarFrameNaAnimacao(anim, Frame(x0, y0, larg, alt));
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

int SpriteSheet::getNumAnimacoes()
{
	return frames.size();
}

int SpriteSheet::getNumFramesDaAnimacao(int anim)
{
	return frames[anim].size();
}

Frame *SpriteSheet::getFrame(int anim, int frame)
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
		Frame f = frames[anim][frames[anim].size()-1];
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
	SpriteSheet r(*this);
	r.carregar(caminhoArquivo, 1, 1, qualidade_escala);
	r.frames = frames;
	return r;
}