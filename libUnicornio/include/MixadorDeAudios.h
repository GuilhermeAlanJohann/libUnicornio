#ifndef UNI_MIXADORDEAUDIOS_H
#define UNI_MIXADORDEAUDIOS_H

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

class MixadorDeAudios
{
public:
	MixadorDeAudios();
	~MixadorDeAudios();

	bool inicializar();
	bool finalizar();

	void reservarCanalDeAudio(int indice_canal, Som *som);
	void liberarCanalDeAudio(int indice_canal);
	void liberarTodosCanaisDeAudio();
	void marcarSomComoDestruido(int indice_canal);

	void pararTodosCanais();

	int getNumMaxCanaisDeAudio();
	int getNumCanaisUsados();
	int getNumCanaisLivres();

private:
	#define NUM_MAX_CANAIS_DE_AUDIO 256

	CanalDeAudio* pool_de_canais;
	int num_canais_usados;

	bool inicializado;
};

#endif

