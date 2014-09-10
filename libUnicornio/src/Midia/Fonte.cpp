#include "Fonte.h"
#include "libUnicornio.h"

Fonte::Fonte()
{
	font = NULL;
	tamanho = 0;
}

Fonte::~Fonte()
{
	if(estaCarregado())
	{
		descarregar();
	}
}

bool Fonte::carregar(string arquivo, int tamanho, EstiloFonte estilo)
{
	if(!uni_init) 
	{
		uniErro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		uniErro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Fonte ja carregou o arquivo " + caminhoArquivo + ".");
		return false;
	}
	
	font = TTF_OpenFont(arquivo.c_str(), tamanho);
	if(!estaCarregado()) 
	{
		uniErro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

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
	if(!rwops)
	{
		uniErro("Erro ao carregar fonte da memoria.");
		return false;
	}

	font = TTF_OpenFontIndexRW(rwops,1,tamanho,0);
	if(!estaCarregado()) 
	{
		uniErro("Erro ao carregar fonte da memoria.");
		return false;
	}

	this->tamanho = tamanho;

	setEstilo(estilo);

	return true;
}

void Fonte::descarregar()
{
	TTF_CloseFont(font);
	font = NULL;
	caminhoArquivo = "";
	tamanho = 0;
	estilo = FONTE_ESTILO_NORMAL;
}

bool Fonte::estaCarregado()
{
	return (font);
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