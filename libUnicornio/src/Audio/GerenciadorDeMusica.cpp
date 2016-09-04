#include "GerenciadorDeMusica.h"
#include "GerenciadorDeRecursos.h"
#include "Global.h"

GerenciadorDeMusica::GerenciadorDeMusica()
{
	volume_global = 100.0f;
	musica = NULL;
}

GerenciadorDeMusica::~GerenciadorDeMusica()
{
}

bool GerenciadorDeMusica::tocar(Musica* musica, bool repetir, float tempo_fadein, float tempo_inicial)
{
	if (!musica)
		return false;

	if (Mix_FadeInMusicPos(musica->get_Mix_Music(), repetir ? -1 : 1, tempo_fadein * 1000, tempo_inicial) == -1)
		return false;

	this->musica = musica;
	float porcentagem = volume_global / 100.0f;
	int vol = 128 * porcentagem * (musica->getVolume() / 100.0f);
	Mix_VolumeMusic(vol);

	return true;
}

bool GerenciadorDeMusica::tocar(const string& nome, bool repetir, float tempo_fadein, float tempo_inicial)
{
	if (tocar(gRecursos.getMusica(nome), repetir, tempo_fadein, tempo_inicial))
	{
		nome_musica = nome;
		return true;
	}

	return false;
}

void GerenciadorDeMusica::parar(float tempo_fadeout)
{
	if (tempo_fadeout > 0.0f)
		Mix_FadeOutMusic(tempo_fadeout * 1000);
	else
		Mix_HaltMusic();
}

void GerenciadorDeMusica::pausar()
{
	Mix_PauseMusic();
}

void GerenciadorDeMusica::continuar()
{
	Mix_ResumeMusic();
}

bool GerenciadorDeMusica::estaTocando()
{
	if (estaPausado())
		return false;

	return Mix_PlayingMusic();
}

bool GerenciadorDeMusica::estaPausado()
{
	return Mix_PausedMusic();
}

bool GerenciadorDeMusica::estaExecutandoFade()
{
	switch ((int)Mix_FadingMusic())
	{
	case MIX_FADING_OUT:
	case MIX_FADING_IN:
		return true;
	}

	return false;
}

bool GerenciadorDeMusica::estaExecutandoFadeIn()
{
	if (Mix_FadingMusic() == MIX_FADING_IN)
		return true;

	return false;
}

bool GerenciadorDeMusica::estaExecutandoFadeOut()
{
	if (Mix_FadingMusic() == MIX_FADING_OUT)
		return true;

	return false;
}

bool GerenciadorDeMusica::irParaOTempo(float tempo)
{
	if (!estaTocando() && !estaPausado())
		return false;

	Mix_RewindMusic();
	if (Mix_SetMusicPosition(tempo * 1000) != -1)
		return true;

	return false;
}

Musica* GerenciadorDeMusica::getMusica()
{
	return musica;
}

string GerenciadorDeMusica::getNomeMusica()
{
	return nome_musica;
}

float GerenciadorDeMusica::getVolumeGlobal()
{
	return volume_global;
}

void GerenciadorDeMusica::setVolumeGlobal(float volume)
{
	volume_global = volume;

	if (volume_global > 100.0f)
		volume_global = 100.0f;
	else if (volume_global < 0.0f)
		volume_global = 0.0f;

	if (estaTocando())
	{
		float porcentagem = volume_global / 100.0f;
		int vol = 128 * porcentagem * (musica->getVolume() / 100.0f);
		Mix_VolumeMusic(vol);
	}
}