#ifndef UNI_CAMADADEOBJETOS_H
#define UNI_CAMADADEOBJETOS_H

#include <vector>
#include <string>
#include "ObjetoTile.h"
#include "Tile.h"

using namespace std;

class CamadaDeObjetos
{
public:
	CamadaDeObjetos();
	~CamadaDeObjetos();

	string getNome();
	bool estaVisivel();
	NivelTile getNivel();

	void setNome(string nome);
	void setVisivel(bool visivel);
	void setNivel(NivelTile nivel);

	ObjetoTile *criarObjeto();
	ObjetoTile *criarObjeto(Vetor2D pos_centro);
	ObjetoTile *criarObjeto(float centro_x, float centro_y);
	bool destruirObjeto(string nome);
	bool destruirObjeto(ObjetoTile *obj);
	void destruirTodosObjetos();
	bool existeObjetoNaPos(Vetor2D pos);
	bool existeObjetoNaPos(float tx, float ty);
	bool existeObjetoDoTipoNaPos(string tipo, Vetor2D pos);
	bool existeObjetoDoTipoNaPos(string tipo, float tx, float ty);

	int getNumObjetos();
	ObjetoTile *getObjeto(int indice);
	ObjetoTile *getObjeto(string nome);
	ObjetoTile *getObjetoNaPos(Vetor2D pos);
	ObjetoTile *getObjetoNaPos(float tx, float ty);
	ObjetoTile *getObjetoDoTipoNaPos(string tipo, Vetor2D pos);
	ObjetoTile *getObjetoDoTipoNaPos(string tipo, float tx, float ty);
	vector<ObjetoTile*> getObjetosDoTipo(string tipo);
	vector<ObjetoTile*> getObjetosNaPos(Vetor2D pos);
	vector<ObjetoTile*> getObjetosNaPos(float tx, float ty);
	vector<ObjetoTile*> getObjetosDoTipoNaPos(string tipo, Vetor2D pos);
	vector<ObjetoTile*> getObjetosDoTipoNaPos(string tipo, float tx, float ty);
	vector<ObjetoTile*> getTodosObjetos();

private:
	string nome;
	bool visivel;
	NivelTile nivel;
	vector<ObjetoTile*> objetos;
};

#endif