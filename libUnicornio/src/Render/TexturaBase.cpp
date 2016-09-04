#include "TexturaBase.h"
#include "Global.h"

TexturaBase::TexturaBase()
{
	sdl_texture = NULL;
	largura = 0;
	altura = 0;
	criada = false;
	qualidadeEscala = QUALIDADE_ESCALA_BAIXA;
}

TexturaBase::TexturaBase(const TexturaBase& t)
{
	sdl_texture = t.sdl_texture;
	largura = t.largura;
	altura = t.altura;
	criada = t.criada;
	qualidadeEscala = t.qualidadeEscala;
}

TexturaBase::~TexturaBase()
{
}

TexturaBase& TexturaBase::operator=(const TexturaBase& t)
{
	if (*this != t)
	{
		sdl_texture = t.sdl_texture;
		largura = t.largura;
		altura = t.altura;
		criada = t.criada;
		qualidadeEscala = t.qualidadeEscala;
	}
	return *this;
}

bool TexturaBase::operator==(const TexturaBase& t)
{
	//	Não precisa testar o resto
	return (sdl_texture == t.sdl_texture);
}

bool TexturaBase::operator==(const TexturaBase& t) const
{
	//	Não precisa testar o resto
	return (sdl_texture == t.sdl_texture);
}

bool TexturaBase::operator!=(const TexturaBase& t)
{
	return !(*this == t);
}

bool TexturaBase::operator!=(const TexturaBase& t) const
{
	return !(*this == t);
}

bool TexturaBase::estaCriada()
{
	return criada;
}

int TexturaBase::getTipo()
{
	if (!criada)
		return -1;

	int access;
	SDL_QueryTexture(sdl_texture, NULL, &access, NULL, NULL);
	return access;	//	enum textureaccess é igual ao EnumTipoTextura
}

int TexturaBase::getLargura()
{
	return largura;
}

int TexturaBase::getAltura()
{
	return altura;
}

Uint8 TexturaBase::getQualidadeDeEscala()
{
	return qualidadeEscala;
}

SDL_Texture* TexturaBase::getSDL_Texture()
{
	return sdl_texture;
}

void TexturaBase::obterTamanho(int& larg, int& alt)
{
	larg = largura;
	alt = altura;
}

bool TexturaBase::desenhar(int x, int y, float rot, float ancora_x, float ancora_y, float escala_x, float escala_y, Cor cor, EnumInverterDesenho inverter)
{
	Quad q(0, 0, largura, altura);
	return desenhar(q, x, y, rot, ancora_x, ancora_y, escala_x, escala_y, cor, inverter);
}

bool TexturaBase::desenhar(int x, int y, float rot, const Vetor2D ancora, const Vetor2D& escala, Cor cor, EnumInverterDesenho inverter)
{
	return desenhar(x, y, rot, ancora.x, ancora.y, escala.x, escala.y, cor, inverter);
}

bool TexturaBase::desenhar(const Quad& retangulo, int x, int y, float rot, float ancora_x, float ancora_y, float escala_x, float escala_y, Cor cor, EnumInverterDesenho inverter)
{
	if (!criada)
		return false;

	return gGraficos.desenharTextura(this, retangulo, x, y, rot, ancora_x, ancora_y, escala_x, escala_y, cor, inverter);
}

bool TexturaBase::desenhar(const Quad& retangulo, int x, int y, float rot, const Vetor2D ancora, const Vetor2D& escala, Cor cor, EnumInverterDesenho inverter)
{
	return desenhar(retangulo, x, y, rot, ancora.x, ancora.y, escala.x, escala.y, cor, inverter);
}

bool TexturaBase::desenhar(const Quad& retangulo, const Quad& destino, Cor cor)
{
	if (!criada)
		return false;

	return gGraficos.desenharTextura(this, retangulo, destino, cor);
}

bool TexturaBase::_criar(int largura, int altura, int qualidade_escala, EnumTipoTextura tipo)
{
	if (criada)
		return false;

	char buffer[2];
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_itoa((int)qualidade_escala, buffer, 10));
	sdl_texture = SDL_CreateTexture(gGraficos.sdl_renderer, SDL_PIXELFORMAT_ARGB8888, (int)tipo, largura, altura);

	if (!sdl_texture)
		return false;

	SDL_SetTextureBlendMode(sdl_texture, SDL_BLENDMODE_BLEND);
	this->largura = largura;
	this->altura = altura;
	qualidadeEscala = qualidade_escala;

	criada = true;
	return true;
}

bool TexturaBase::_criarDoArquivo(const string& arquivo, int qualidade_escala)
{
	if (criada)
		return false;

	char buffer[2];
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, SDL_itoa((int)qualidade_escala, buffer, 10));
	sdl_texture = IMG_LoadTexture(gGraficos.sdl_renderer, arquivo.c_str());

	if (!sdl_texture)
		return false;

	int l, a;
	SDL_QueryTexture(sdl_texture, NULL, NULL, &l, &a);
	largura = l;
	altura = a;
	qualidadeEscala = qualidade_escala;

	criada = true;
	return true;
}

bool TexturaBase::_destruir()
{
	if (!criada)
		return true;

	SDL_DestroyTexture(sdl_texture);
	sdl_texture = NULL;
	largura = 0;
	altura = 0;

	criada = false;
	qualidadeEscala = QUALIDADE_ESCALA_BAIXA;
	return true;
}
