#include "CamadaDeObjetos.h"

CamadaDeObjetos::CamadaDeObjetos()
{
	visivel = true;
	nivel = NO_NIVEL_DOS_OBJETOS;
}

CamadaDeObjetos::~CamadaDeObjetos()
{
	destruirTodosObjetos();
}

string CamadaDeObjetos::getNome()
{
	return nome;
}

bool CamadaDeObjetos::estaVisivel()
{
	return visivel;
}

NivelTile CamadaDeObjetos::getNivel()
{
	return nivel;
}

void CamadaDeObjetos::setNome(string nome)
{
	this->nome = nome;
}

void CamadaDeObjetos::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

void CamadaDeObjetos::setNivel(NivelTile nivel)
{
	this->nivel = nivel;
}

ObjetoTile *CamadaDeObjetos::criarObjeto()
{
	ObjetoTile *obj = new ObjetoTile;
	obj->setCamada(this);
	objetos.push_back(obj);
	return obj;
}

ObjetoTile *CamadaDeObjetos::criarObjeto(Vetor2D pos_centro)
{
	return criarObjeto(pos_centro.x, pos_centro.y);
}

ObjetoTile *CamadaDeObjetos::criarObjeto(float centro_x, float centro_y)
{
	ObjetoTile *obj = criarObjeto();
	obj->setPosCentro(centro_x, centro_y);
	return obj;
}

bool CamadaDeObjetos::destruirObjeto(string nome)
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

bool CamadaDeObjetos::destruirObjeto(ObjetoTile *obj)
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

void CamadaDeObjetos::destruirTodosObjetos()
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
	{
		delete objetos[i];
	}
	objetos.clear();
}

bool CamadaDeObjetos::existeObjetoNaPos(Vetor2D pos)
{
	return existeObjetoNaPos(pos.x, pos.y);
}

bool CamadaDeObjetos::existeObjetoNaPos(float tx, float ty)
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

bool CamadaDeObjetos::existeObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	return existeObjetoDoTipoNaPos(tipo, pos);
}

bool CamadaDeObjetos::existeObjetoDoTipoNaPos(string tipo, float tx, float ty)
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

int CamadaDeObjetos::getNumObjetos()
{
	return (int)objetos.size();
}

ObjetoTile *CamadaDeObjetos::getObjeto(int indice)
{
	return objetos[indice];
}

ObjetoTile *CamadaDeObjetos::getObjeto(string nome)
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
			return objetos[i];

	return NULL;
}

ObjetoTile *CamadaDeObjetos::getObjetoNaPos(Vetor2D pos)
{
	return getObjetoNaPos(pos.x, pos.y);
}

ObjetoTile *CamadaDeObjetos::getObjetoNaPos(float tx, float ty)
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

ObjetoTile *CamadaDeObjetos::getObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	return getObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

ObjetoTile *CamadaDeObjetos::getObjetoDoTipoNaPos(string tipo, float tx, float ty)
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

vector<ObjetoTile*> CamadaDeObjetos::getObjetosDoTipo(string tipo)
{
	vector<ObjetoTile*> r;

	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getTipo() == tipo)
			r.push_back(objetos[i]);

	return r;
}

vector<ObjetoTile*> CamadaDeObjetos::getObjetosNaPos(Vetor2D pos)
{
	vector<ObjetoTile*> r;
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

vector<ObjetoTile*> CamadaDeObjetos::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTile*> r;
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

vector<ObjetoTile*> CamadaDeObjetos::getObjetosDoTipoNaPos(string tipo, Vetor2D pos)
{
	vector<ObjetoTile*> r;
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

vector<ObjetoTile*> CamadaDeObjetos::getObjetosDoTipoNaPos(string tipo, float tx, float ty)
{
	vector<ObjetoTile*> r;
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

vector<ObjetoTile*> CamadaDeObjetos::getTodosObjetos()
{
	return objetos;
}