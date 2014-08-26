#include "Som.h"
#include "libUnicornio.h"
#include <algorithm>

Som::Som()
:smp(0), volume(128), angulo(0), distancia(0), canal(-1), loop(false)
{
}

Som::Som(const Som &r)
{
	volume = r.volume;
	angulo = r.angulo;
	distancia = r.distancia;
	caminhoArquivo =  r.caminhoArquivo;
	smp->volume = r.smp->volume;
	canal = r.canal;
	loop = r.loop;
}

Som& Som::operator=(const Som &r)
{
	if(*this != r)
	{
		volume = r.volume;
		angulo = r.angulo;
		distancia = r.distancia;
		caminhoArquivo =  r.caminhoArquivo;
		smp->volume = r.smp->volume;
		canal = r.canal;
		loop = r.loop;
	}
	return *this;
}

bool Som::operator==(const Som &r)
{
	return (volume == r.volume && angulo == r.angulo && distancia == r.distancia && caminhoArquivo ==  r.caminhoArquivo && loop == r.loop);
}

bool Som::operator!=(const Som &r)
{
	return !(*this == r);
}

Som::~Som()
{
	if(canal != -1)
	{
		Mix_HaltChannel(canal);
		canal = -1;
	}

	if(smp) Mix_FreeChunk(smp);
}

bool Som::carregar(string arquivo)
{
	if(!uni_init) 
		return false;
	
	if(smp)
	{
		Mix_FreeChunk(smp);
		canal = -1;
	}
	smp = Mix_LoadWAV(arquivo.c_str());
	
	if(!smp) 
	{
		uniErro("Erro carregando arquivo: " + arquivo + " - " + SDL_GetError());
		uni_debug = true;
		return false;
	}

	caminhoArquivo = arquivo;

	return true;
}
void Som::tocar(bool repetir)
{
	if(!smp) return;

	/*if (canal != -1)	//	se estiver tocando som em um canal, libera o canal
	{
		Mix_HaltChannel(canal);
		canal = -1;
	}*/

	if(!loop)
	{
		canal = Mix_PlayChannel(-1, smp, repetir == 0 ? 0 : -1);
		loop = repetir;

		Mix_SetPosition(canal, angulo, distancia);
		Mix_Volume(canal, volume);
	}
}
void Som::parar()
{
	if(!smp) return;
	
	if(canal != -1)
	{
		Mix_HaltChannel(canal);
		canal = -1;
		loop = false;
	}
}

void Som::pausar()
{
	if(!smp) return;
	
	if(canal != -1)
	{
		Mix_Pause(canal);
	}
}

void Som::continuar()
{
	if(!smp) return;
	
	if(canal != -1)
	{
		Mix_Resume(canal);
	}
}

void Som::ajustar(int vol, int dist, int ang)
{		
	if(!smp) return;

	volume = vol;
	angulo = ang;
	distancia = dist;

	if(canal != -1 && Mix_Playing(canal))
	{
		Mix_SetPosition(canal, angulo, distancia);
		Mix_Volume(canal, volume);
	}
}

// retornar se o Som terminou de tocar
bool Som::estaTocando()
{
	if(!smp) return false;
	if(canal == -1) return false;

	int status = Mix_Playing(canal);
	if(status != 0) return true;
	
	return false;
}

void Som::setVolume(int vol)
{
	volume = vol;

	if(canal != -1 && Mix_Playing(canal))
	{
		Mix_Volume(canal, volume);
	}
}

void Som::setDistancia(int dist)
{
	distancia = dist;

	if(canal != -1 && Mix_Playing(canal))
	{
		Mix_SetPosition(canal, angulo, distancia);
	}
}

void Som::setAngulo(int ang)
{
	angulo = ang;

	if(canal != -1 && Mix_Playing(canal))
	{
		Mix_SetPosition(canal, angulo, distancia);
	}
}

int	Som::getVolume()
{
	return volume;
}

int Som::getDistancia()
{
	return distancia;
}

int Som::getAngulo()
{
	return angulo;
}

string Som::getCaminhoDoArquivo()
{
	return caminhoArquivo;
}

Som Som::clonar()
{
	Som r(*this);
	r.carregar(caminhoArquivo);
	return r;
}