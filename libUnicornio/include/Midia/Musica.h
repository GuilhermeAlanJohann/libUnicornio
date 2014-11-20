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
	bool estaTocando();
	void setVolume(int vol);
	int	 getVolume();
	string getCaminhoDoArquivo();
	Musica clonar();

private:
	std::string caminhoArquivo;

	_Mix_Music *smp;

	int volume;

	int canal;
};

#endif