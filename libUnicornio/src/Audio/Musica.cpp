#include "Musica.h"
#include <algorithm>
#include "uniFuncoesPrincipais.h"
#include "Global.h"

Musica::Musica() : smp(0), volume(100)
{
}

Musica::Musica(const Musica &r)
{
	smp = r.smp;
	volume = r.volume;
	caminhoArquivo =  r.caminhoArquivo;
}

Musica& Musica::operator=(const Musica &r)
{
	if(*this != r)
	{
		smp = r.smp;
		volume = r.volume;
		caminhoArquivo =  r.caminhoArquivo;
	}
	return *this;
}

bool Musica::operator==(const Musica &r)
{
	if(volume == r.volume && caminhoArquivo ==  r.caminhoArquivo && smp == r.smp)
		return true;
	else
		return false;
}

bool Musica::operator!=(const Musica &r)
{
	return !(*this == r);
}

Musica::~Musica()
{
}

bool Musica::carregar(string arquivo)
{
	if(!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Musica ja carregou o arquivo " + caminhoArquivo + ".");
		return false;
	}

	smp = Mix_LoadMUS(arquivo.c_str());
	
	if(!smp) 
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	caminhoArquivo = arquivo;

	return true;
}

void Musica::descarregar()
{
	Mix_FreeMusic(smp);
	smp = NULL;
	caminhoArquivo.clear();
	volume = 100.0f;
}

bool Musica::estaCarregado()
{
	return (smp);
}

void Musica::setVolume(float vol)
{
	volume = vol;
}

float Musica::getVolume()
{
	return volume;
}

_Mix_Music* Musica::get_Mix_Music()
{
	return smp;
}

string Musica::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

Musica Musica::clonar()
{
	Musica r(*this);
	r.carregar(caminhoArquivo);
	return r;
}