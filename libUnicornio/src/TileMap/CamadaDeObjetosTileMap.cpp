#include "CamadaDeObjetosTileMap.h"

CamadaDeObjetosTileMap::CamadaDeObjetosTileMap()
{
	visivel = true;
	nivel = NO_NIVEL_DOS_OBJETOS;
}

CamadaDeObjetosTileMap::~CamadaDeObjetosTileMap()
{
	destruirTodosObjetos();
}

string CamadaDeObjetosTileMap::getNome()
{
	return nome;
}

bool CamadaDeObjetosTileMap::estaVisivel()
{
	return visivel;
}

NivelTile CamadaDeObjetosTileMap::getNivel()
{
	return nivel;
}

void CamadaDeObjetosTileMap::setNome(string nome)
{
	this->nome = nome;
}

void CamadaDeObjetosTileMap::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

void CamadaDeObjetosTileMap::setNivel(NivelTile nivel)
{
	this->nivel = nivel;
}

ObjetoTileMap *CamadaDeObjetosTileMap::criarObjeto()
{
	ObjetoTileMap *obj = new ObjetoTileMap;
	obj->setCamada(this);
	objetos.push_back(obj);
	return obj;
}

ObjetoTileMap *CamadaDeObjetosTileMap::criarObjeto(Vetor2D pos_centro)
{
	return criarObjeto(pos_centro.x, pos_centro.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::criarObjeto(float centro_x, float centro_y)
{
	ObjetoTileMap *obj = criarObjeto();
	obj->setPosCentro(centro_x, centro_y);
	return obj;
}

bool CamadaDeObjetosTileMap::destruirObjeto(string nome)
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
		{
			delete objetos[i];
			objetos.erase(objetos.begin() + i);
			return true;
		}

	return false;
}

bool CamadaDeObjetosTileMap::destruirObjeto(ObjetoTileMap *obj)
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(*objetos[i] == *obj)
		{
			delete objetos[i];
			objetos.erase(objetos.begin() + i);
			return true;
		}

	return false;
}

void CamadaDeObjetosTileMap::destruirTodosObjetos()
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		delete objetos[i];
	}
	objetos.clear();
}

bool CamadaDeObjetosTileMap::existeObjetoNaPos(Vetor2D pos)
{
	return existeObjetoNaPos(pos.x, pos.y);
}

bool CamadaDeObjetosTileMap::existeObjetoNaPos(float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox, oy);
		ox += ox0;
		oy += oy0;

		if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
			return true;
	}

	return false;
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	return existeObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		if(objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox, oy);
			ox += ox0;
			oy += oy0;

			if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
				return true;
		}
	}

	return false;
}

int CamadaDeObjetosTileMap::getNumObjetos()
{
	return (int)objetos.size();
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjeto(int indice)
{
	return objetos[indice];
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjeto(string nome)
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
			return objetos[i];

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoNaPos(Vetor2D pos)
{
	return getObjetoNaPos(pos.x, pos.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoNaPos(float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox, oy);
		ox += ox0;
		oy += oy0;

		if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
			return objetos[i];
	}

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	return getObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		if(objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox, oy);
			ox += ox0;
			oy += oy0;

			if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
				return objetos[i];
		}
	}

	return NULL;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipo(string tipo)
{
	vector<ObjetoTileMap*> r;

	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getTipo() == tipo)
			r.push_back(objetos[i]);

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNaPos(Vetor2D pos)
{
	vector<ObjetoTileMap*> r;
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox, oy);
		ox += ox0;
		oy += oy0;

		if(pos.x >= ox0 && pos.x <= ox && pos.y >= oy0 && pos.y <= oy)
			r.push_back(objetos[i]);
	}

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox, oy);
		ox += ox0;
		oy += oy0;

		if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
			r.push_back(objetos[i]);
	}

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNaPos(string tipo, Vetor2D pos)
{
	vector<ObjetoTileMap*> r;
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		if(objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox, oy);
			ox += ox0;
			oy += oy0;

			if(pos.x >= ox0 && pos.x <= ox && pos.y >= oy0 && pos.y <= oy)
				r.push_back(objetos[i]);
		}
	}

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNaPos(string tipo, float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	float ox0, oy0, ox, oy;
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		if(objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox, oy);
			ox += ox0;
			oy += oy0;

			if(tx >= ox0 && tx <= ox && ty >= oy0 && ty <= oy)
				r.push_back(objetos[i]);
		}
	}

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getTodosObjetos()
{
	return objetos;
}