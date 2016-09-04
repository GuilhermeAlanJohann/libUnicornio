#include "TexturaAlvo.h"
#include "Global.h"


TexturaAlvo::TexturaAlvo()
{
	alvoAnterior = NULL;
}

TexturaAlvo::TexturaAlvo(const TexturaAlvo& t)
{
	sdl_texture = t.sdl_texture;
	largura = t.largura;
	altura = t.altura;
	criada = t.criada;
	qualidadeEscala = t.qualidadeEscala;
	alvoAnterior = t.alvoAnterior;
}

TexturaAlvo::~TexturaAlvo()
{
}

TexturaAlvo& TexturaAlvo::operator=(const TexturaAlvo& t)
{
	if (*this != t)
	{
		sdl_texture = t.sdl_texture;
		largura = t.largura;
		altura = t.altura;
		criada = t.criada;
		qualidadeEscala = t.qualidadeEscala;
		alvoAnterior = t.alvoAnterior;
	}
	return *this;
}

bool TexturaAlvo::criar(int largura, int altura, int qualidade_escala)
{
	return _criar(largura, altura, qualidade_escala, TEXTURA_ALVO);
}

bool TexturaAlvo::destruir()
{
	if (_destruir())
	{
		alvoAnterior = NULL;
		return true;
	}

	return false;
}

bool TexturaAlvo::ativar()
{
	if (!criada)
		return false;

	SDL_Renderer* renderer = gGraficos.sdl_renderer;
	SDL_Texture* texAnt = SDL_GetRenderTarget(renderer);
	if (SDL_SetRenderTarget(renderer, sdl_texture) == 0)
	{
		alvoAnterior = texAnt;
		return true;
	}
	return false;
}

bool TexturaAlvo::desativar()
{
	if (!criada)
		return false;

	SDL_Renderer* renderer = gGraficos.sdl_renderer;
	SDL_Texture* tex = SDL_GetRenderTarget(renderer);
	if (tex == sdl_texture)	//	se está ativa
	{
		SDL_SetRenderTarget(renderer, alvoAnterior);
		alvoAnterior = NULL;
		return true;
	}
	return false;
}

bool TexturaAlvo::estaAtiva()
{
	if (!criada)
		return false;

	SDL_Renderer* renderer = gGraficos.sdl_renderer;
	SDL_Texture* tex = SDL_GetRenderTarget(renderer);
	return (tex == sdl_texture);
}

bool TexturaAlvo::limpar(const Cor& cor)
{
	return limpar(cor.r, cor.g, cor.b, cor.a);
}

bool TexturaAlvo::limpar(int r, int g, int b, int a)
{
	if (!estaAtiva())
	{
		gDebug.erro("Não é possivel limpar um TexturaAlvo que não está ativa no momento.", this);
		return false;
	}

	SDL_Renderer* renderer = gGraficos.sdl_renderer;
	SDL_SetRenderDrawBlendMode(renderer, (a == 255) ? SDL_BLENDMODE_NONE : SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
	return true;
}