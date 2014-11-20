#include "Musica.h"
#include "libUnicornio.h"
#include <algorithm>

Musica::Musica() : smp(0), volume(128), canal(-1)
{
}

Musica::Musica(const Musica &r)
{
	volume = r.volume;
	canal = r.canal;
	caminhoArquivo =  r.caminhoArquivo;
}

Musica& Musica::operator=(const Musica &r)
{
	if(*this != r)
	{
		volume = r.volume;
		canal = r.canal;
		caminhoArquivo =  r.caminhoArquivo;
	}
	return *this;
}

bool Musica::operator==(const Musica &r)
{
	if(volume == r.volume && canal == r.canal && caminhoArquivo ==  r.caminhoArquivo)
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
	if(estaCarregado())
	{
		descarregar();
	}
}

bool Musica::carregar(string arquivo)
{
	if(!uni_init) 
	{
		uniErro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		uniErro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Musica ja carregou o arquivo " + caminhoArquivo + ".");
		return false;
	}

	smp = Mix_LoadMUS(arquivo.c_str());
	
	if(!smp) 
	{
		uniErro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	caminhoArquivo = arquivo;

	return true;
}

void Musica::descarregar()
{
	parar();
	Mix_FreeMusic(smp);
	smp = NULL;
	caminhoArquivo = "";
	volume = 128;

	//	ja eh setado no parar();
	//canal = -1;
}

bool Musica::estaCarregado()
{
	return (smp);
}

void Musica::tocar(bool repetir)
{
	if(!estaCarregado()) return;

	canal = Mix_PlayMusic(smp,repetir == 0 ? 0 : -1);

	Mix_VolumeMusic(volume);
}

void Musica::parar()
{
	if(!estaCarregado()) return;

	Mix_HaltMusic();
	canal = -1;
}

void Musica::pausar()
{
	if(!estaCarregado()) return;
	
	if(canal != -1)
	{
		Mix_PauseMusic();
	}
}

void Musica::continuar()
{
	if(!estaCarregado()) return;
	
	if(canal != -1)
	{
		Mix_ResumeMusic();
	}
}

bool Musica::estaTocando()
{
	if(!smp) return false;

	int status = Mix_PlayingMusic();
	if(status != 0) return true;
	
	return false;
}

void Musica::setVolume(int vol)
{
	volume = vol;

	Mix_VolumeMusic(volume);
}

int	Musica::getVolume()
{
	return volume;
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