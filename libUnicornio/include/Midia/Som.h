#ifndef UNI_SOM_H
#define UNI_SOM_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>

// SDL_Mixer
#define SAMPLE Mix_Chunk

using namespace std;

class Som
{
public:
	Som();
	Som(const Som &r);
	Som& operator=(const Som &r);
	bool operator==(const Som &r);
	bool operator!=(const Som &r);
	~Som();
	bool carregar(std::string arquivo);
	void descarregar();
	bool estaCarregado();
	void tocar(bool repetir = false);
	void parar();
	void pausar();
	void continuar();
	void ajustar(int vol, int dist = 0, int ang = 0);
	bool estaTocando();
	void setVolume(int vol);
	void setDistancia(int dist);
	void setAngulo(int ang);
	int	 getVolume();
	int  getDistancia();
	int  getAngulo();
	string getCaminhoDoArquivo();
	Som clonar();

private:
	string caminhoArquivo;

	SAMPLE *smp;

	Sint16 angulo;
	Uint8 distancia;
	int volume;

	int canal;

	bool loop;
};

#endif