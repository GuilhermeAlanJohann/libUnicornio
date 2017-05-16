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
	dispositivoAberto = false;
	numMaxCanais = 0;
	numCanaisOcupados = 0;
	volumeGlobal = 100.0f;
}

MixadorDeAudios::~MixadorDeAudios()
{
}

bool MixadorDeAudios::inicializar()
{
	// Audio: SDL_Mixer
	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MODPLUG);

	volumeGlobal = 100.0f;
	abrirDipositivoDeAudio();
	inicializado = true;

	return true;
}

bool MixadorDeAudios::finalizar()
{
	fecharDispositivoDeAudio();
	destruirTodosGrupos();

	while(Mix_Init(0)) 
		Mix_Quit();

	grupos.clear();

	inicializado = false;
	return true;
}

bool MixadorDeAudios::estaInicializado()
{
	return inicializado;
}

bool MixadorDeAudios::abriuDispositivoDeAudio()
{
	return dispositivoAberto;
}

void MixadorDeAudios::processarEvento(const SDL_Event& evento)
{
	if (evento.type == SDL_AUDIODEVICEADDED)
	{
		if (!dispositivoAberto)
		{
			abrirDipositivoDeAudio();
		}
	}
	else if (evento.type == SDL_AUDIODEVICEREMOVED)
	{
		if (dispositivoAberto && !evento.adevice.iscapture)
		{
			//	TODO verificar qual está sendo removido
			fecharDispositivoDeAudio();
		}
	}
}

void MixadorDeAudios::reservarCanalDeAudio(int indice_canal, Sint8 indice_grupo, Som *som)
{
	if(abriuDispositivoDeAudio())
	{
		if (indice_canal < 0 || indice_canal >= numMaxCanais)
			return;

		if(!(poolDeCanais[indice_canal].flags & FLAG_CANALDEAUDIO_OCUPADO))
			numCanaisOcupados += 1;

		poolDeCanais[indice_canal].flags |= FLAG_CANALDEAUDIO_OCUPADO;
		poolDeCanais[indice_canal].indiceDoGrupo = indice_grupo;
		poolDeCanais[indice_canal].som = som;
		if (som)
		{
			poolDeCanais[indice_canal].flags |= FLAG_CANALDEAUDIO_USANDO_SOM;
			poolDeCanais[indice_canal].volume = som->getVolume();
		}
		else
		{
			poolDeCanais[indice_canal].flags &= ~FLAG_CANALDEAUDIO_USANDO_SOM;
		}
		
	}
}

void MixadorDeAudios::reservarCanalDeAudio(int indice_canal, Sint8 indice_grupo, float volume)
{
	if (abriuDispositivoDeAudio())
	{
		if (indice_canal < 0 || indice_canal >= numMaxCanais)
			return;

		if (!(poolDeCanais[indice_canal].flags & FLAG_CANALDEAUDIO_OCUPADO))
			numCanaisOcupados += 1;

		poolDeCanais[indice_canal].flags |= FLAG_CANALDEAUDIO_OCUPADO;
		poolDeCanais[indice_canal].flags &= ~FLAG_CANALDEAUDIO_USANDO_SOM;
		poolDeCanais[indice_canal].indiceDoGrupo = indice_grupo;
		poolDeCanais[indice_canal].volume = volume;
		poolDeCanais[indice_canal].som = NULL;

	}
}

void MixadorDeAudios::liberarCanalDeAudio(int indice_canal)
{
	if(abriuDispositivoDeAudio())
	{
		if (indice_canal < 0 || indice_canal >= numMaxCanais)
			return;

		if(poolDeCanais[indice_canal].flags & FLAG_CANALDEAUDIO_OCUPADO)
			numCanaisOcupados -= 1;

		if (poolDeCanais[indice_canal].flags & FLAG_CANALDEAUDIO_USANDO_SOM)
		{
			poolDeCanais[indice_canal].som->quandoTerminarDeTocar();
		}

		poolDeCanais[indice_canal].flags &= ~FLAG_CANALDEAUDIO_OCUPADO;
		poolDeCanais[indice_canal].flags |= FLAG_CANALDEAUDIO_USANDO_SOM;
		poolDeCanais[indice_canal].som = NULL;
		poolDeCanais[indice_canal].indiceDoGrupo = -1;
		poolDeCanais[indice_canal].volume = 100.0f;
	}
}

void MixadorDeAudios::liberarTodosCanaisDeAudio()
{
	if(abriuDispositivoDeAudio())
	{
		for(unsigned int i = 0; i < numMaxCanais; ++i)
		{
			if(poolDeCanais[i].flags & FLAG_CANALDEAUDIO_OCUPADO)
			{
				if (poolDeCanais[i].flags & FLAG_CANALDEAUDIO_USANDO_SOM)
					poolDeCanais[i].som->quandoTerminarDeTocar();

				poolDeCanais[i] = CanalDeAudio();
			}
		}

		numCanaisOcupados = 0;

		Mix_HaltChannel(-1);
	}
}

void MixadorDeAudios::marcarSomComoDestruido(int indice_canal)
{
	if (abriuDispositivoDeAudio())
	{
		if (indice_canal >= 0 && indice_canal < numMaxCanais)
		{
			poolDeCanais[indice_canal].flags &= ~FLAG_CANALDEAUDIO_USANDO_SOM;
			poolDeCanais[indice_canal].som = NULL;
		}
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
	if (!inicializado || !abriuDispositivoDeAudio())
		return;

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
			novoPool[i] = CanalDeAudio();
		}
	}

	delete[] poolDeCanais;
	poolDeCanais = novoPool;
	numMaxCanais = max;
}

int MixadorDeAudios::criarGrupo(const string& nome)
{
	int i = getIndiceDoGrupo(nome);
	if (i == -1)
	{
		grupos.push_back(pair<string, float>(nome, 100.0f));
		i = grupos.size() - 1;
	}
	return i;
}

void MixadorDeAudios::destruirGrupo(const string& nome)
{
	for (int i = 0; i < grupos.size(); ++i)
	{
		if (nome == grupos[i].first)
		{
			grupos.erase(grupos.begin() + i);
			return;
		}
	}
}

void MixadorDeAudios::destruirTodosGrupos()
{
	grupos.clear();
}

int MixadorDeAudios::getIndiceDoGrupo(const string& nome)
{
	for (int i = 0; i < grupos.size(); ++i)
	{
		if (nome == grupos[i].first)
		{
			return i;
		}
	}

	return -1;
}

string MixadorDeAudios::getNomeDoGrupo(int indice)
{
	if (indice >= 0 && indice < grupos.size())
	{
		return grupos[indice].first;
	}
	return string();
}

int MixadorDeAudios::getNumGrupos()
{
	return grupos.size();
}

float MixadorDeAudios::getVolumeDoGrupo(int indice)
{
	if (indice >= 0 && indice < grupos.size())
	{
		return grupos[indice].second;
	}
	return 100.0f;
}

float MixadorDeAudios::getVolumeDoGrupo(const string& nome)
{
	return getVolumeDoGrupo(getIndiceDoGrupo(nome));
}

void MixadorDeAudios::setVolumeDoGrupo(int indice, float volume)
{
	if (indice >= 0 && indice < grupos.size())
	{
		if (volume < 0.0f) volume = 0.0f;
		else if (volume > 100.0f) volume = 100.0f;

		grupos[indice].second = volume;

		if (abriuDispositivoDeAudio())
		{
			float vol_grupo = volume / 100.0f;
			float vol_global = volumeGlobal / 100.0f;
			float vol = vol_global * vol_grupo;

			for (unsigned int i = 0; i < numMaxCanais; ++i)
			{
				if ((poolDeCanais[i].flags & FLAG_CANALDEAUDIO_OCUPADO) && poolDeCanais[i].indiceDoGrupo == indice)
				{
					float vol_canal;
					if (!(poolDeCanais[i].flags & FLAG_CANALDEAUDIO_USANDO_SOM))
						vol_canal = poolDeCanais[i].volume / 100.0f;
					else
						vol_canal = poolDeCanais[i].som->getVolume() / 100.0f;

					Mix_Volume(i, MIX_MAX_VOLUME * vol * vol_canal);
				}
			}
		}
	}
}

void MixadorDeAudios::setVolumeDoGrupo(const string& nome, float volume)
{
	setVolumeDoGrupo(getIndiceDoGrupo(nome), volume);
}

float MixadorDeAudios::getVolumeGlobal()
{
	return volumeGlobal;
}

void MixadorDeAudios::setVolumeGlobal(float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 100.0f) volume = 100.0f;

	volumeGlobal = volume;

	if(abriuDispositivoDeAudio())
	{
		float vol_grupo = volume / 100.0f;
		float vol_global = volumeGlobal / 100.0f;
		float vol = vol_global * vol_grupo;

		for(unsigned int i = 0; i < numMaxCanais; ++i)
		{
			if(poolDeCanais[i].flags & FLAG_CANALDEAUDIO_OCUPADO)
			{
				float vol_canal;
				if (!(poolDeCanais[i].flags & FLAG_CANALDEAUDIO_USANDO_SOM))
					vol_canal = poolDeCanais[i].volume / 100.0f;
				else
					vol_canal = poolDeCanais[i].som->getVolume() / 100.0f;

				Mix_Volume(i, MIX_MAX_VOLUME * vol * vol_canal);
			}
		}
	}
}

void MixadorDeAudios::setVolumeDoCanal(int canal, float volume)
{
	if (canal < 0 || canal >= numMaxCanais)
		return;

	poolDeCanais[canal].volume = volume;
	int vol = MIX_MAX_VOLUME
		* volume / 100.0f
		* grupos[poolDeCanais[canal].indiceDoGrupo].second / 100.0f
		* volumeGlobal / 100.0f;
	Mix_Volume(canal, vol);
}

void MixadorDeAudios::setVolumeDoCanal(int canal, Som* som)
{
	if (canal < 0 || canal >= numMaxCanais)
		return;

	if (som && poolDeCanais[canal].som == som)
	{
		poolDeCanais[canal].volume = som->getVolume();
		int vol = MIX_MAX_VOLUME
			* poolDeCanais[canal].volume / 100.0f 
			* grupos[poolDeCanais[canal].indiceDoGrupo].second / 100.0f
			* volumeGlobal / 100.0f;
		Mix_Volume(canal, vol);
	}
}

int MixadorDeAudios::tocar(Mix_Chunk* mix_chunk, bool repetir, float volume, Sint16 angulo, Sint8 distancia)
{
	if (!abriuDispositivoDeAudio())
		return -1;

	//int canal = Mix_FadeInChannel(-1, mix_chunk, repetir ? -1 : 0, tempo_fadein*1000);
	int canal = Mix_PlayChannel(-1, mix_chunk, repetir ? -1 : 0);
	if (canal != -1)
	{
		int vol = MIX_MAX_VOLUME * ((volume / 100.0f) * (volumeGlobal / 100.0f));
		if (vol < 0)
			vol = 0;
		Mix_Volume(canal, vol);
		Mix_SetPosition(canal, angulo, distancia);
	}
	return canal;
}

void MixadorDeAudios::tocar(const string& audio, float volume)
{
	tocar(audio, -1, volume);
}

void MixadorDeAudios::tocar(const string& audio, int indice_grupo, float volume)
{
	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 100.0f) volume = 100.0f;

	int canal = tocar(gRecursos.getAudio(audio)->getMix_Chunk(), false, volume, 0, 0);
	if (canal != -1)
	{
		reservarCanalDeAudio(canal, indice_grupo, volume);
	}
}

void MixadorDeAudios::tocar(const string& audio, const string& grupo, float volume)
{
	tocar(audio, getIndiceDoGrupo(grupo), volume);

	if (volume < 0.0f) volume = 0.0f;
	else if (volume > 100.0f) volume = 100.0f;

	int canal = tocar(gRecursos.getAudio(audio)->getMix_Chunk(), false, volume, 0, 0);
	if (canal != -1)
	{
		reservarCanalDeAudio(canal, getIndiceDoGrupo(grupo), volume);
	}
}

bool MixadorDeAudios::abrirDipositivoDeAudio()
{
	if (dispositivoAberto)
		return false;

	int audio_rate = MIX_DEFAULT_FREQUENCY;	//	22050
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 1024;
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
	{
		return false;
	}

	numMaxCanais = 128;
	poolDeCanais = new CanalDeAudio[numMaxCanais];

	for (unsigned int i = 0; i < numMaxCanais; ++i)
	{
		poolDeCanais[i] = CanalDeAudio();
	}

	numCanaisOcupados = 0;

	Mix_ChannelFinished(canalTerminouDeTocar);

	dispositivoAberto = true;
	return true;
}

bool MixadorDeAudios::fecharDispositivoDeAudio()
{
	if (!dispositivoAberto)
		return false;

	delete[] poolDeCanais;
	poolDeCanais = NULL;

	numMaxCanais = 0;
	numCanaisOcupados = 0;

	Mix_CloseAudio();

	dispositivoAberto = false;
	return true;
}