#include "Fonte.h"
#include "libUnicornio.h"

Fonte::Fonte()
{
	font = NULL;
	tamanho = 0;
}

Fonte::~Fonte()
{
	if(font)
	{
		TTF_CloseFont(font);
	}
}

bool Fonte::carregar(string arquivo, int tamanho, EstiloFonte estilo)
{
	if(!uni_init) return false;
	
	font = TTF_OpenFont(arquivo.c_str(), tamanho);
	if(!font) return false;

	this->tamanho = tamanho;
	caminhoArquivo = arquivo;

	setEstilo(estilo);

	return true;
	
}

bool Fonte::carregarMem(unsigned char mem[], int tamanho_mem, int tamanho, EstiloFonte estilo)
{
	if(!uni_init) return false;

	SDL_RWops* rwops = SDL_RWFromMem((void*)mem,tamanho_mem);
	//SDL_RWops* rwops = SDL_RWFromConstMem((const void*)mem,memsize);
	if(!rwops) return false;

	font = TTF_OpenFontIndexRW(rwops,1,tamanho,0);
	if(!font) return false;

	this->tamanho = tamanho;

	setEstilo(estilo);

	return true;
}

int Fonte::getTamanho()
{
	return tamanho;
}

EstiloFonte Fonte::getEstilo()
{
	return estilo;
}

TTF_Font* Fonte::getTTF_Font()
{
	return font;
}

string Fonte::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

void Fonte::setEstilo(EstiloFonte estilo)
{
	this->estilo = estilo;
	TTF_SetFontStyle(font, estilo);
}

Fonte Fonte::clonar()
{
	Fonte r(*this);
	r.carregar(caminhoArquivo, tamanho, estilo);
	return r;
}