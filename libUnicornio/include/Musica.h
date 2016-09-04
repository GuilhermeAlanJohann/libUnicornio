#ifndef UNI_MUSICA_H
#define UNI_MUSICA_H

#include "uniAPI.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include <string>

using namespace std;

class UNI_API Musica
{  
public:
	Musica();
	Musica(const Musica &r);
	~Musica();

	Musica& operator=(const Musica &r);
	bool operator==(const Musica &r);
	bool operator!=(const Musica &r);
	
	bool carregar(std::string arquivo);
	void descarregar();
	bool estaCarregado();

	void setVolume(float vol);
	float getVolume();

	_Mix_Music* get_Mix_Music();
	string getCaminhoDoArquivo();
	Musica clonar();

protected:
	string caminhoArquivo;
	_Mix_Music *smp;
	float volume;
};

#endif