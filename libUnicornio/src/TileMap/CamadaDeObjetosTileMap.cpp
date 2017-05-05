#include "CamadaDeObjetosTileMap.h"
#include "TileMap.h"

CamadaDeObjetosTileMap::CamadaDeObjetosTileMap()
{
	visivel = true;
	tilemap = NULL;
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

void CamadaDeObjetosTileMap::setNome(string nome)
{
	this->nome = nome;
}

void CamadaDeObjetosTileMap::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

ObjetoTileMap *CamadaDeObjetosTileMap::criarObjeto()
{
	ObjetoTileMap *obj = new ObjetoTileMap;
	obj->setCamada(this);
	obj->_indiceNaCamada = objetos.size();
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

void CamadaDeObjetosTileMap::adicionarObjeto(ObjetoTileMap* obj)
{
	obj->setCamada(this);
	obj->_indiceNaCamada = objetos.size();
	objetos.push_back(obj);
	if (obj->getSprite())
		getTileMap()->adicionarObjetoNaRenderQueue(obj);
}

bool CamadaDeObjetosTileMap::destruirObjeto(string nome)
{
	for (unsigned int i = 0; i < objetos.size(); ++i)
		if (objetos[i]->getNome() == nome)
			return destruirObjeto(i);

	return false;
}

bool CamadaDeObjetosTileMap::destruirObjeto(ObjetoTileMap *obj)
{
	int i = obj->_indiceNaCamada;
	if (objetos[i] == obj)
		return destruirObjeto(i);

	return false;
}

bool CamadaDeObjetosTileMap::destruirObjeto(int indice)
{
	if (indice < objetos.size() && indice >= 0)
	{
		(*objetos.rbegin())->_indiceNaCamada = indice;
		delete objetos[indice];
		objetos[indice] = *objetos.rbegin();
		objetos.pop_back();
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

bool CamadaDeObjetosTileMap::existeObjetoNaPos(const Vetor2D& pos)
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

		if(tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
			return true;
	}

	return false;
}

bool CamadaDeObjetosTileMap::existeObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	return existeObjetoNoRetangulo(pos.x, pos.y, tamanho.x, tamanho.y);
}

bool CamadaDeObjetosTileMap::existeObjetoNoRetangulo(float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox1, oy1);
		ox1 += ox0;
		oy1 += oy0;

		if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y0)
			return true;
	}

	return false;
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	return existeObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNaPos(const string& tipo, float tx, float ty)
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

			if(tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
				return true;
		}
	}

	return false;
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	return existeObjetoDoTipoNoRetangulo(tipo, pos.x, pos.y, tamanho.x, tamanho.y);
}

bool CamadaDeObjetosTileMap::existeObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		if (objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox1, oy1);
			ox1 += ox0;
			oy1 += oy0;

			if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y0)
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
	if(indice < objetos.size() && indice >= 0)
		return objetos[indice];

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjeto(const string& nome)
{
	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
			return objetos[i];

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoNaPos(const Vetor2D& pos)
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

		if(tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
			return objetos[i];
	}

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	return getObjetoNoRetangulo(pos.x, pos.y, tamanho.x, tamanho.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoNoRetangulo(float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox1, oy1);
		ox1 += ox0;
		oy1 += oy0;

		if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y1)
			return objetos[i];
	}

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	return getObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNaPos(const string& tipo, float tx, float ty)
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

			if(tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
				return objetos[i];
		}
	}

	return NULL;
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	return getObjetoDoTipoNoRetangulo(tipo, pos.x, pos.y, tamanho.x, tamanho.y);
}

ObjetoTileMap *CamadaDeObjetosTileMap::getObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		if (objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox1, oy1);
			ox1 += ox0;
			oy1 += oy0;

			if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y1)
				return objetos[i];
		}
	}

	return NULL;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipo(const string& tipo)
{
	vector<ObjetoTileMap*> r;

	for(unsigned int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getTipo() == tipo)
			r.push_back(objetos[i]);

	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNaPos(const Vetor2D& pos)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosNaPos(&r, pos.x, pos.y);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosNaPos(&r, tx, ty);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosNoRetangulo(&r, pos.x, pos.y, tamanho.x, tamanho.y);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosNoRetangulo(float tx, float ty, float larg, float alt)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosNoRetangulo(&r, tx, ty, larg, alt);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosDoTipoNaPos(&r, tipo, pos.x, pos.y);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNaPos(const string& tipo, float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosDoTipoNaPos(&r, tipo, tx, ty);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosDoTipoNoRetangulo(&r, tipo, pos.x, pos.y, tamanho.x, tamanho.y);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getObjetosDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	vector<ObjetoTileMap*> r;
	_obterObjetosDoTipoNoRetangulo(&r, tipo, tx, ty, larg, alt);
	return r;
}

vector<ObjetoTileMap*> CamadaDeObjetosTileMap::getTodosObjetos()
{
	return objetos;
}

void CamadaDeObjetosTileMap::setTileMap(TileMap* tilemap)
{
	this->tilemap = tilemap;
}

TileMap* CamadaDeObjetosTileMap::getTileMap()
{
	return tilemap;
}

void CamadaDeObjetosTileMap::_obterObjetosNaPos(vector<ObjetoTileMap*>* v, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox, oy);
		ox += ox0;
		oy += oy0;

		if (tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
			v->push_back(objetos[i]);
	}
}

void CamadaDeObjetosTileMap::_obterObjetosNoRetangulo(vector<ObjetoTileMap*>* v, float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		objetos[i]->obterPos(ox0, oy0);
		objetos[i]->obterTamanho(ox1, oy1);
		ox1 += ox0;
		oy1 += oy0;

		if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y0)
			v->push_back(objetos[i]);
	}
}

void CamadaDeObjetosTileMap::_obterObjetosDoTipoNaPos(vector<ObjetoTileMap*>* v, const string& tipo, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		if (objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox, oy);
			ox += ox0;
			oy += oy0;

			if (tx >= ox0 && tx < ox && ty >= oy0 && ty < oy)
				v->push_back(objetos[i]);
		}
	}
}

void CamadaDeObjetosTileMap::_obterObjetosDoTipoNoRetangulo(vector<ObjetoTileMap*>* v, const string& tipo, float tx, float ty, float larg, float alt)
{
	//	limites do retangulo
	float x0 = tx;
	float y0 = ty;
	float x1 = tx + larg;
	float y1 = ty + alt;

	//	limites do objeto
	float ox0, oy0, ox1, oy1;
	for (unsigned int i = 0; i < objetos.size(); ++i)
	{
		if (objetos[i]->getTipo() == tipo)
		{
			objetos[i]->obterPos(ox0, oy0);
			objetos[i]->obterTamanho(ox1, oy1);
			ox1 += ox0;
			oy1 += oy0;

			if (ox0 < x1 && oy0 < y1 && ox1 >= x0 && oy1 >= y0)
				v->push_back(objetos[i]);
		}
	}
}