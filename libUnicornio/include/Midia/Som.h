#ifndef UNI_SOM_H
#define UNI_SOM_H

#include "Audio.h"
#include "MixadorDeAudios.h"

class Som
{
public:
	Som();
	Som(const Som& r);
	~Som();

	Som& operator=(const Som &r);
	bool operator==(const Som &r);
	bool operator!=(const Som &r);

	void tocar(bool repetir = false);
	void parar();
	void pausar();
	void continuar();
	bool estaTocando();
	bool estaRepetindo();
	bool terminouDeTocar();

	Audio* getAudio();

	int	 getVolume();
	int  getDistancia();
	int  getAngulo();

	void setAudio(Audio* audio);
	void setAudio(string nome);

	void setVolume(float vol);
	void setDistancia(Uint8 dist);
	void setAngulo(Sint16 ang);

	//	Nao usar! Metodo de uso interno. Chamado pela biblioteca.
	void setTerminouDeTocar(bool b);
	//	Nao usar! Metodo de uso interno. Chamado pela biblioteca.
	void indefinirCanal();

private:
	Audio* audio;

	Sint16 angulo;
	Uint8 distancia;
	float volume;
	bool repetindo;
	bool terminou_de_tocar;

	int indice_canal_atual;
};

#endif