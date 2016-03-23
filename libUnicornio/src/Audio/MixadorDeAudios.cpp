#include "MixadorDeAudios.h"
#include "Global.h"
#include "Som.h"
#include <algorithm>

void canalTerminouDeTocar(int indice_canal) 
{
	gAudios.liberarCanalDeAudio(indice_canal);
}

MixadorDeAudios::MixadorDeAudios()
{
	inicializado = false;
}

MixadorDeAudios::~MixadorDeAudios()
{
}

bool MixadorDeAudios::inicializar()
{
	// Audio: SDL_Mixer
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MODPLUG);
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024; 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{
		return false;
	}

	numMaxCanais = 256;
	poolDeCanais = new CanalDeAudio[numMaxCanais];

	unsigned int i;
	for(i = 0; i < numMaxCanais; ++i)
	{
		poolDeCanais[i].livre = true;
		poolDeCanais[i].somDestruido = false;
		poolDeCanais[i].som = NULL;
	}

	numCanaisOcupados = 0;

	Mix_ChannelFinished(canalTerminouDeTocar);

	volumeGlobal = 100.0f;

	inicializado = true;
	return true;
}

bool MixadorDeAudios::finalizar()
{
	delete[] poolDeCanais;
	poolDeCanais = NULL;

	numMaxCanais = 0;
	numCanaisOcupados = 0;
	
	Mix_CloseAudio();
	while(Mix_Init(0)) 
		Mix_Quit();

	inicializado = false;
	return true;
}

bool MixadorDeAudios::estaInicializado()
{
	return inicializado;
}

void MixadorDeAudios::reservarCanalDeAudio(int indice_canal, Som *som)
{
	if(inicializado)
	{
		if (indice_canal < 0 || indice_canal >= numMaxCanais)
			return;

		if(poolDeCanais[indice_canal].livre)
			numCanaisOcupados += 1;

		poolDeCanais[indice_canal].livre = false;
		poolDeCanais[indice_canal].somDestruido = false;
		poolDeCanais[indice_canal].som = som;
	}
}

void MixadorDeAudios::liberarCanalDeAudio(int indice_canal)
{
	if(inicializado)
	{
		if (indice_canal < 0 || indice_canal >= numMaxCanais)
			return;

		if(!poolDeCanais[indice_canal].livre)
			numCanaisOcupados -= 1;

		if (!poolDeCanais[indice_canal].somDestruido)
		{
			poolDeCanais[indice_canal].som->quandoTerminarDeTocar();
		}

		poolDeCanais[indice_canal].livre = true;
		poolDeCanais[indice_canal].somDestruido = false;
		poolDeCanais[indice_canal].som = NULL;
	}
}

void MixadorDeAudios::liberarTodosCanaisDeAudio()
{
	if(inicializado)
	{
		for(unsigned int i = 0; i < numMaxCanais; ++i)
		{
			if(!poolDeCanais[i].livre)
			{
				if(!poolDeCanais[i].somDestruido)
					poolDeCanais[i].som->quandoTerminarDeTocar();

				poolDeCanais[i].livre = true;
				poolDeCanais[i].somDestruido = false;
				poolDeCanais[i].som = NULL;
			}
		}

		numCanaisOcupados = 0;

		Mix_HaltChannel(-1);
	}
}

void MixadorDeAudios::marcarSomComoDestruido(int indice_canal)
{
	if (indice_canal >= 0 && indice_canal < numMaxCanais)
	{
		poolDeCanais[indice_canal].somDestruido = true;
		poolDeCanais[indice_canal].som = NULL;
	}
}

void MixadorDeAudios::pararTodosCanais()
{
	if(inicializado)
	{
		Mix_HaltChannel(-1);
	}
}

int MixadorDeAudios::getNumMaxCanaisDeAudio()
{
	return numMaxCanais;
}

int MixadorDeAudios::getNumCanaisOcupados()
{
	return numCanaisOcupados;
}

int MixadorDeAudios::getNumCanaisLivres()
{
	return numMaxCanais - numCanaisOcupados;
}

void MixadorDeAudios::setNumMaxCanaisDeAudio(unsigned int max)
{
	if (max == numMaxCanais)
		return;

	CanalDeAudio* novoPool = new CanalDeAudio[max];
	unsigned int tam = min(max, numMaxCanais);
	unsigned int i;
	for (i = 0; i < tam; ++i)
	{
		novoPool[i] = poolDeCanais[i];
	}
	if (max > numMaxCanais)
	{
		for ( ; i < max; ++i)
		{
			novoPool[i].livre = true;
			novoPool[i].somDestruido = true;
			novoPool[i].som = NULL;
		}
	}

	delete[] poolDeCanais;
	poolDeCanais = novoPool;
	numMaxCanais = max;
}

float MixadorDeAudios::getVolumeGlobal()
{
	return volumeGlobal;
}

void MixadorDeAudios::setVolumeGlobal(float volume)
{
	if(volume > 100.0f)
		volume = 100.0f;
	if(volume < 0.0f)
		volume = 0.0f;

	volumeGlobal = volume;

	if(inicializado)
	{
		for(unsigned int i = 0; i < numMaxCanais; ++i)
		{
			if(!poolDeCanais[i].livre && !poolDeCanais[i].somDestruido)
			{
				float vol = 128*((poolDeCanais[i].som->getVolume()/100.0f) * (volumeGlobal/100.0f));
				Mix_Volume(i, vol);
			}
		}
	}
}

int MixadorDeAudios::tocar(Mix_Chunk* mix_chunk, bool repetir, float tempo_fadein, float volume, Sint16 angulo, Sint8 distancia)
{
	int canal = Mix_FadeInChannel(-1, mix_chunk, repetir ? -1 : 0, tempo_fadein*1000);
	if (canal != -1)
	{
		int vol = 128 * ((volume / 100.0f) * (volumeGlobal / 100.0f));
		if (vol < 0)
			vol = 0;
		Mix_Volume(canal, vol);
		Mix_SetPosition(canal, angulo, distancia);
	}
	return canal;
}