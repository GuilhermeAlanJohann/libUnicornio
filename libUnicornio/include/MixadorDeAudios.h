#ifndef UNI_MIXADORDEAUDIOS_H
#define UNI_MIXADORDEAUDIOS_H

#include "uniAPI.h"
#include "SDL_mixer.h"

class Som;

struct CanalDeAudio
{
	CanalDeAudio():
		livre(true), 
		somDestruido(false),
		som(NULL)
	{};
	~CanalDeAudio(){};

	bool livre;
	bool somDestruido;
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

	void reservarCanalDeAudio(int indice_canal, Som *som);
	void liberarCanalDeAudio(int indice_canal);
	void liberarTodosCanaisDeAudio();
	void marcarSomComoDestruido(int indice_canal);

	void pararTodosCanais();

	int getNumMaxCanaisDeAudio();
	int getNumCanaisOcupados();
	int getNumCanaisLivres();

	void setNumMaxCanaisDeAudio(unsigned int max);

	float getVolumeGlobal();
	void setVolumeGlobal(float volume);

	int tocar(Mix_Chunk* mix_chunk, bool repetir, float volume, Sint16 angulo, Sint8 distancia);

private:
	CanalDeAudio* poolDeCanais;
	unsigned int numMaxCanais;
	unsigned int numCanaisOcupados;

	bool inicializado;

	float volumeGlobal;
};

#endif

