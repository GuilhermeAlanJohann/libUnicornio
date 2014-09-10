#ifndef UNI_MUSICA_H
#define UNI_MUSICA_H

#include "SDL.h"
#include "SDL_mixer.h"
#include <string>

using namespace std;

class Musica
{  
public:
	Musica();
	Musica(const Musica &r);
	Musica& operator=(const Musica &r);
	bool operator==(const Musica &r);
	bool operator!=(const Musica &r);
	~Musica();
	bool carregar(std::string arquivo);
	void descarregar();
	bool estaCarregado();
	void tocar(bool repetir = true);
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
	Musica clonar();

private:
	std::string caminhoArquivo;

	_Mix_Music *smp;

	Sint16 angulo;
	Uint8 distancia;
	int volume;

	int canal;
};

#endif