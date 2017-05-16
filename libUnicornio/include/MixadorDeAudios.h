#ifndef UNI_MIXADORDEAUDIOS_H
#define UNI_MIXADORDEAUDIOS_H

#include "uniAPI.h"
#include "SDL_mixer.h"
#include "SDL_events.h"
#include <vector>
#include <string>

using namespace std;

class Som;

enum EnumFlagsCanalDeAudio
{
	FLAG_CANALDEAUDIO_OCUPADO = 1 << 0,
	FLAG_CANALDEAUDIO_USANDO_SOM = 1 << 1
};

struct CanalDeAudio
{
	CanalDeAudio() :
		flags(0),
		indiceDoGrupo(-1),
		volume(100.0f),
		som(NULL)
	{};
	~CanalDeAudio(){};

	Uint8 flags;	//	TODO 
	Sint8 indiceDoGrupo;
	float volume;
	Som *som;
};

class UNI_API MixadorDeAudios
{
public:
	MixadorDeAudios();
	~MixadorDeAudios();

	bool inicializar();
	bool finalizar();
	bool estaInicializado();
	bool abriuDispositivoDeAudio();
	void processarEvento(const SDL_Event& evento);

	void reservarCanalDeAudio(int indice_canal, Sint8 indice_grupo, Som *som);
	void reservarCanalDeAudio(int indice_canal, Sint8 indice_grupo, float volume);
	void liberarCanalDeAudio(int indice_canal);
	void liberarTodosCanaisDeAudio();
	void marcarSomComoDestruido(int indice_canal);

	void pararTodosCanais();

	int getNumMaxCanaisDeAudio();
	int getNumCanaisOcupados();
	int getNumCanaisLivres();

	void setNumMaxCanaisDeAudio(unsigned int max);

	int criarGrupo(const string& nome);
	void destruirGrupo(const string& nome);
	void destruirTodosGrupos();
	int getIndiceDoGrupo(const string& nome);
	string getNomeDoGrupo(int indice);
	int getNumGrupos();

	float getVolumeDoGrupo(int indice);
	float getVolumeDoGrupo(const string& nome);
	void setVolumeDoGrupo(int indice, float volume);
	void setVolumeDoGrupo(const string& nome, float volume);

	float getVolumeGlobal();
	void setVolumeGlobal(float volume);

	void setVolumeDoCanal(int canal, float volume);
	void setVolumeDoCanal(int canal, Som* som);	//	uso interno

	int tocar(Mix_Chunk* mix_chunk, bool repetir, float volume, Sint16 angulo, Sint8 distancia);
	void tocar(const string& audio, float volume);
	void tocar(const string& audio, int indice_grupo, float volume);
	void tocar(const string& audio, const string& grupo, float volume);

private:
	bool abrirDipositivoDeAudio();
	bool fecharDispositivoDeAudio();

	CanalDeAudio* poolDeCanais;
	unsigned int numMaxCanais;
	unsigned int numCanaisOcupados;

	bool inicializado;
	bool dispositivoAberto;

	float volumeGlobal;

	//	vetor contendo o nome e o volume dos grupos.
	vector<pair<string, float> > grupos;
};

#endif

