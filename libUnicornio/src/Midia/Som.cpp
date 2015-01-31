#include "Som.h"
#include "libUnicornio.h"

Som::Som()
{
	audio = NULL;

	volume = 100.0f;
	angulo = 0;
	distancia = 0;
	repetindo = false;
	terminou_de_tocar = false;

	indice_canal_atual = -1;
}

Som::Som(const Som& r)
{
	audio = r.audio;
	volume = r.volume;
	angulo = r.angulo;
	distancia = r.distancia;
	repetindo = r.repetindo;
	terminou_de_tocar = r.terminou_de_tocar;

	indice_canal_atual = r.indice_canal_atual;
}

Som::~Som()
{
}

Som& Som::operator=(const Som &r)
{
	if(this != &r)
	{
		audio = r.audio;
		volume = r.volume;
		angulo = r.angulo;
		distancia = r.distancia;
		repetindo = r.repetindo;
		terminou_de_tocar = r.terminou_de_tocar;

		indice_canal_atual = r.indice_canal_atual;
	}
	return *this;
}

bool Som::operator==(const Som &r)
{
	return (audio == r.audio && volume == r.volume && angulo == r.angulo && distancia == r.distancia && indice_canal_atual == r.indice_canal_atual && repetindo == r.repetindo && terminou_de_tocar == r.terminou_de_tocar);
}

bool Som::operator!=(const Som &r)
{
	return !(*this == r);
}

void Som::tocar(bool repetir)
{
	if(!uni_init) return;

	if(!audio)
	{
		uniDesenharTexto("Nao pode tocar Som antes de setar Audio.", 10, 10, 255, 0, 0, 0.0f);
		return;
	}

	if(!repetindo)
	{
		indice_canal_atual = Mix_PlayChannel(-1, audio->getMixChunk(), repetir == 0 ? 0 : -1);
		Mix_Volume(indice_canal_atual, (volume/100.0)*128);
		Mix_SetPosition(indice_canal_atual, angulo, distancia);
		mixador_de_audios.reservarCanalDeAudio(indice_canal_atual, this);
		repetindo = repetir;
		terminou_de_tocar = false;
	}
}

void Som::parar()
{
	if(indice_canal_atual != -1)
		Mix_HaltChannel(indice_canal_atual);

	repetindo = false;
}

void Som::pausar()
{
	if(indice_canal_atual != -1)
		Mix_Pause(indice_canal_atual);
}

void Som::continuar()
{
	if(indice_canal_atual != -1)
		Mix_Resume(indice_canal_atual);
}

bool Som::estaTocando()
{
	if(indice_canal_atual != -1)
		return Mix_Playing(indice_canal_atual);

	return false;
}

bool Som::estaRepetindo()
{
	return repetindo;
}

bool Som::terminouDeTocar()
{
	return terminou_de_tocar;
}

Audio* Som::getAudio()
{
	return audio;
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

void Som::setAudio(Audio* audio)
{
	this->audio = audio;
}

void Som::setAudio(string nome)
{
	setAudio(recursos.getAudio(nome));
}

void Som::setVolume(float vol)
{
	volume = vol;

	if(indice_canal_atual != -1)
		Mix_Volume(indice_canal_atual, (volume/100.0)*128);
}

void Som::setDistancia(Uint8 dist)
{
	distancia = dist;

	if(indice_canal_atual != -1)
		Mix_SetDistance(indice_canal_atual, distancia);
}

void Som::setAngulo(Sint16 ang)
{
	angulo = ang;

	if(indice_canal_atual != -1)
		Mix_SetPosition(indice_canal_atual, angulo, distancia);
}

void Som::setTerminouDeTocar(bool b)
{
	terminou_de_tocar = b;
}

void Som::indefinirCanal()
{
	indice_canal_atual = -1;
	repetindo = false;
}