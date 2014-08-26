#include "Musica.h"
#include "libUnicornio.h"
#include <algorithm>

Musica::Musica() : smp(0), volume(128), angulo(0), distancia(0), canal(-1)
{
}

Musica::Musica(const Musica &r)
{
	volume = r.volume;
	canal = r.canal;
	distancia = r.distancia;
	angulo = r.angulo;
	caminhoArquivo =  r.caminhoArquivo;
}

Musica& Musica::operator=(const Musica &r)
{
	if(*this != r)
	{
		volume = r.volume;
		canal = r.canal;
		distancia = r.distancia;
		angulo = r.angulo;
		caminhoArquivo =  r.caminhoArquivo;
	}
	return *this;
}

bool Musica::operator==(const Musica &r)
{
	if(volume == r.volume && canal == r.canal && distancia == r.distancia && angulo == r.angulo && caminhoArquivo ==  r.caminhoArquivo)
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
	Mix_HaltMusic();

	if(smp) Mix_FreeMusic(smp);
}

bool Musica::carregar(string arquivo)
{
	if(!uni_init) 
		return false;
	
	if(smp)
	{
		Mix_FreeMusic(smp);
	}
	smp = Mix_LoadMUS(arquivo.c_str());
	
	if(!smp) 
	{
		uniErro("Erro carregando arquivo: " + arquivo + " - " + SDL_GetError());
		uni_debug = true;
		return false;
	}

	caminhoArquivo = arquivo;

	return true;
}

void Musica::tocar(bool repetir)
{
	if(!smp) return;

	canal = Mix_PlayMusic(smp,repetir == 0 ? 0 : -1);

	Mix_SetPosition(canal, angulo, distancia);
	Mix_VolumeMusic(volume);
}

void Musica::parar()
{
	if(!smp) return;

	Mix_HaltMusic();
}

void Musica::pausar()
{
	if(!smp) return;
	
	if(canal != -1)
	{
		Mix_PauseMusic();
	}
}

void Musica::continuar()
{
	if(!smp) return;
	
	if(canal != -1)
	{
		Mix_ResumeMusic();
	}
}

void Musica::ajustar(int vol, int dist, int ang)
{		
	if(!smp) return;

	volume = vol;
	angulo = ang;
	distancia = dist;

	if(canal != -1 && Mix_PlayingMusic())
	{
		Mix_SetPosition(canal, angulo, distancia);
	}

	Mix_VolumeMusic(volume);
}

// retornar se o Som terminou de tocar
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

void Musica::setDistancia(int dist)
{
	distancia = dist;

	if(canal != -1 && Mix_PlayingMusic())
	{
		Mix_SetPosition(canal, angulo, distancia);
	}
}

void Musica::setAngulo(int ang)
{
	angulo = ang;

	if(canal != -1 && Mix_PlayingMusic())
	{
		Mix_SetPosition(canal, angulo, distancia);
	}
}

int	Musica::getVolume()
{
	return volume;
}

int Musica::getDistancia()
{
	return distancia;
}

int Musica::getAngulo()
{
	return angulo;
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