#include "MixadorDeAudios.h"
#include "libUnicornio.h"

void chanalTerminouDeTocar(int indice_canal) 
{
	mixador.liberarCanalDeAudio(indice_canal);
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
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC);
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024; 
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
	{
		return false;
	}

	pool_de_canais = new CanalDeAudio[NUM_MAX_CANAIS_DE_AUDIO];

	int i;
	for(i = 0; i < NUM_MAX_CANAIS_DE_AUDIO; ++i)
	{
		pool_de_canais[i].livre = true;
		pool_de_canais[i].somDestruido = false;
		pool_de_canais[i].som = NULL;
	}

	num_canais_usados = 0;

	Mix_ChannelFinished(chanalTerminouDeTocar);

	volume_global = 100.0f;

	inicializado = true;
	return true;
}

bool MixadorDeAudios::finalizar()
{
	delete[] pool_de_canais;

	num_canais_usados = 0;
	
	Mix_CloseAudio();
	while(Mix_Init(0)) 
		Mix_Quit();

	inicializado = false;
	return true;
}

void MixadorDeAudios::reservarCanalDeAudio(int indice_canal, Som *som)
{
	if(inicializado)
	{
		if(pool_de_canais[indice_canal].livre)
			num_canais_usados += 1;

		pool_de_canais[indice_canal].livre = false;
		pool_de_canais[indice_canal].somDestruido = false;
		pool_de_canais[indice_canal].som = som;
	}
}

void MixadorDeAudios::liberarCanalDeAudio(int indice_canal)
{
	if(inicializado)
	{
		if(!pool_de_canais[indice_canal].livre)
			num_canais_usados -= 1;

		if(!pool_de_canais[indice_canal].somDestruido)
			pool_de_canais[indice_canal].som->indefinirCanal();

		pool_de_canais[indice_canal].livre = true;
		pool_de_canais[indice_canal].somDestruido = false;
		pool_de_canais[indice_canal].som = NULL;
	}
}

void MixadorDeAudios::liberarTodosCanaisDeAudio()
{
	if(inicializado)
	{
		for(int i = 0; i < NUM_MAX_CANAIS_DE_AUDIO; ++i)
		{
			if(!pool_de_canais[i].livre)
			{
				if(!pool_de_canais[i].somDestruido)
					pool_de_canais[i].som->indefinirCanal();

				pool_de_canais[i].livre = true;
				pool_de_canais[i].somDestruido = false;
				pool_de_canais[i].som = NULL;
			}
		}

		num_canais_usados = 0;

		Mix_HaltChannel(-1);
	}
}

void MixadorDeAudios::marcarSomComoDestruido(int indice_canal)
{
	if(indice_canal >= 0)
		pool_de_canais[indice_canal].somDestruido = true;
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
	return NUM_MAX_CANAIS_DE_AUDIO;
}

int MixadorDeAudios::getNumCanaisUsados()
{
	return num_canais_usados;
}

int MixadorDeAudios::getNumCanaisLivres()
{
	return NUM_MAX_CANAIS_DE_AUDIO - num_canais_usados;
}

float MixadorDeAudios::getVolumeGlobal()
{
	return volume_global;
}

void MixadorDeAudios::setVolumeGlobal(float volume)
{
	if(volume > 100.0f)
		volume = 100.0f;
	if(volume < 0.0f)
		volume = 0.0f;

	volume_global = volume;

	if(inicializado)
	{
		for(int i = 0; i < NUM_MAX_CANAIS_DE_AUDIO; ++i)
		{
			if(!pool_de_canais[i].livre && !pool_de_canais[i].somDestruido)
			{
				float vol = 128*((pool_de_canais[i].som->getVolume()/100.0f) * (volume_global/100.0f));
				Mix_Volume(i, vol);
			}
		}
	}
}