#ifndef UNI_SOM_H
#define UNI_SOM_H

#include "uniAPI.h"
#include "Audio.h"
#include "MixadorDeAudios.h"

class UNI_API Som
{
public:
	Som();
	Som(const Som& r);
	~Som();

	Som& operator=(const Som &r);
	bool operator==(const Som &r);
	bool operator!=(const Som &r);

	void tocar(bool repetir = false);
	void parar(float tempo_fadeout = 0.0f);
	void pausar();
	void continuar();
	bool estaExecutandoFadeOut();
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

	void setGrupo(const string& grupo);
	string getNomeDoGrupo();

	//	Nao usar! Metodo de uso interno. Chamado pela biblioteca.
	void quandoTerminarDeTocar();

protected:
	Audio* audio;

	Sint16 angulo;
	Uint8 distancia;
	float volume;
	bool repetindo;
	bool terminouTocar;

	Sint8 indiceDoGrupo;
	int indiceDoCanalAtual;
};

#endif