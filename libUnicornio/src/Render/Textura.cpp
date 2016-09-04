#include "Textura.h"
#include "Global.h"


Textura::Textura()
{
	travada = false;
}

Textura::Textura(const Textura& t)
{
	sdl_texture = t.sdl_texture;
	largura = t.largura;
	altura = t.altura;
	criada = t.criada;
	qualidadeEscala = t.qualidadeEscala;
	travada = t.travada;
	caminhoArquivo = t.caminhoArquivo;
}

Textura::~Textura()
{
}

Textura& Textura::operator=(const Textura& t)
{
	if (*this != t)
	{
		sdl_texture = t.sdl_texture;
		largura = t.largura;
		altura = t.altura;
		criada = t.criada;
		qualidadeEscala = t.qualidadeEscala;
		travada = t.travada;
		caminhoArquivo = t.caminhoArquivo;
	}
	return *this;
}

bool Textura::criar(int largura, int altura, int qualidade_escala, bool streaming)
{
	if (_criar(largura, altura, qualidade_escala, streaming ? TEXTURA_DE_STREAMING : TEXTURA_ESTATICA))
	{
		travada = false;
		return true;
	}

	return false;
}

bool Textura::criarDoArquivo(const string& arquivo, int qualidade_escala)
{
	if (_criarDoArquivo(arquivo, qualidade_escala))
	{
		travada = false;
		caminhoArquivo = arquivo;
		return true;
	}

	return false;
}

bool Textura::criarDaSDL_Surface(SDL_Surface* surface, int qualidade_escala)
{
	char buffer[2];
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_itoa((int)qualidade_escala, buffer, 10));
	sdl_texture = SDL_CreateTextureFromSurface(gGraficos.sdl_renderer, surface);
	if (sdl_texture)
	{
		SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
		largura = surface->w;
		altura = surface->h;
		qualidadeEscala = qualidade_escala;
		criada = true;
		return true;
	}

	return false;
}

bool Textura::destruir()
{
	if (_destruir())
	{
		caminhoArquivo.clear();
		travada = false;
		return true;
	}

	return false;
}

bool Textura::eEstatica()
{
	if (!criada)
		return false;

	int access;
	SDL_QueryTexture(sdl_texture, NULL, &access, NULL, NULL);

	return access == SDL_TEXTUREACCESS_STATIC;
}

bool Textura::eDeStreaming()
{
	if (!criada)
		return false;

	int access;
	SDL_QueryTexture(sdl_texture, NULL, &access, NULL, NULL);

	return access == SDL_TEXTUREACCESS_STREAMING;
}

bool Textura::estaTravada()
{
	return travada;
}

string Textura::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

//	Somente para texturas de streaming
bool Textura::travar(void* pixels, int& pitch)
{
	if (eDeStreaming() && !estaTravada())
		travada = (SDL_LockTexture(sdl_texture, NULL, &pixels, &pitch) == 0);

	return travada;
}

//	Somente para texturas de streaming
bool Textura::destravar()
{
	if (eDeStreaming() && estaTravada())
	{
		SDL_UnlockTexture(sdl_texture);
		travada = false;
		return true;
	}

	return false;
}

bool Textura::atualizarPixels(void* pixels, int pitch)
{
	if (!criada)
		return false;

	return (SDL_UpdateTexture(sdl_texture, NULL, &pixels, pitch) == 0);
}

Textura Textura::clonar()
{
	Textura r;

	if (criada)
	{
		if (caminhoArquivo.empty())
		{
			r.criar(largura, altura, qualidadeEscala, eDeStreaming());
			
			if (r.eDeStreaming())
			{
				void* pixels = NULL;
				int pitch;
				if (!travar(pixels, pitch))
					return r;	//	Erro

				Uint32* rPixels = NULL;
				int rPitch;
				r.travar(rPixels, rPitch);
				memcpy(rPixels, pixels, sizeof(Uint32)*largura*altura);
				r.destravar();

				destravar();
			}
			else
			{
				//	Erro
				//	Textura estatica, que não foi criada de arquivo não pode ser copiada
			}
		}
		else
		{
			r.criarDoArquivo(caminhoArquivo, qualidadeEscala);
		}
	}

	return r;
}