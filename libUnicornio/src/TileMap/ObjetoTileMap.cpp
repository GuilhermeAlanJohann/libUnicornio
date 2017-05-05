#include "ObjetoTileMap.h"
#include "CamadaDeObjetosTileMap.h"
#include "TileMap.h"

ObjetoTileMap::ObjetoTileMap()
{
	_indiceNaCamada = -1;

	spr = NULL;
	nivel = NO_NIVEL_DOS_OBJETOS;

	x = 0.0f;
	y = 0.0f;
	rot = 0.0f;

	larg = 0.0f;
	alt = 0.0f;

	voidPtr = NULL;
	camada = NULL;

	visivel = true;

	propriedades = NULL;
}

ObjetoTileMap::~ObjetoTileMap()
{
	if (propriedades)
		delete propriedades;

	if (camada && spr)
	{
		camada->getTileMap()->removerObjetoDaRenderQueue(this);
	}
}

bool ObjetoTileMap::operator==(const ObjetoTileMap &outro)
{
	return (x == outro.x && y == outro.y && rot == outro.rot && larg == outro.larg && alt == outro.alt && visivel == outro.visivel && spr == outro.spr && nome == outro.nome && tipo == outro.tipo && camada == outro.camada);
}

bool ObjetoTileMap::operator!=(const ObjetoTileMap &outro)
{
	return !(*this == outro);
}

Sprite *ObjetoTileMap::getSprite()
{
	return spr;
}

bool ObjetoTileMap::estaVisivel()
{
	return visivel;
}

string ObjetoTileMap::getNome()
{
	return nome;
}

string ObjetoTileMap::getTipo()
{
	return tipo;
}

NivelTile ObjetoTileMap::getNivel()
{
	return nivel;
}

float ObjetoTileMap::getX()
{
	return x;
}

float ObjetoTileMap::getY()
{
	return y;
}

float ObjetoTileMap::getRot()
{
	return rot;
}

Vetor2D ObjetoTileMap::getPos()
{
	return Vetor2D(x, y);
}

float ObjetoTileMap::getXCentro()
{
	return (x + larg/2.0f);
}

float ObjetoTileMap::getYCentro()
{
	return (y + alt/2.0f);
}

Vetor2D ObjetoTileMap::getPosCentro()
{
	return Vetor2D(getXCentro(), getYCentro());
}

float ObjetoTileMap::getLargura()
{
	return larg;
}

float ObjetoTileMap::getAltura()
{
	return alt;
}

void* ObjetoTileMap::getPtr()
{
	return voidPtr;
}

CamadaDeObjetosTileMap *ObjetoTileMap::getCamada()
{
	return camada;
}

TileMap *ObjetoTileMap::getTileMap()
{
	if(camada)
		return camada->getTileMap();

	return NULL;
}

string ObjetoTileMap::getPropriedade(string nome)
{
	if (!propriedades)
		return "";

	map<string, string>::iterator it = propriedades->find(nome);

	if(it != propriedades->end())
		return it->second;

	return "";
}

void ObjetoTileMap::obterPos(float &x, float &y)
{
	x = this->x;
	y = this->y;
}

void ObjetoTileMap::obterPosCentro(float &x, float &y)
{
	x = getXCentro();
	y = getYCentro();
}

void ObjetoTileMap::obterTamanho(float &larg, float &alt)
{
	larg = this->larg;
	alt = this->alt;
}

void ObjetoTileMap::setSprite(Sprite *spr)
{
	//	Se já tem um Sprite, já está na render queue;
	//	Então não adiciona novamente.
	if (this->spr)
	{
		this->spr = spr;

		//	Se se o novo Sprite não for válido, remove da render queue.
		if (!spr && getTileMap())
			getTileMap()->removerObjetoDaRenderQueue(this);

		return;
	}

	//	Se não estava na render queue, 
	//	adiciona se sprite for válido
	this->spr = spr;
	if (spr && getTileMap())
		getTileMap()->adicionarObjetoNaRenderQueue(this);
}

void ObjetoTileMap::setVisivel(bool b)
{
	visivel = b;
}

void ObjetoTileMap::setNome(string nome)
{
	this->nome = nome;
}

void ObjetoTileMap::setTipo(string tipo)
{
	this->tipo = tipo;
}

void ObjetoTileMap::setNivel(NivelTile nivel)
{
	this->nivel = nivel;
}

void ObjetoTileMap::setX(float x)
{
	this->x = x;
}

void ObjetoTileMap::setY(float y)
{
	this->y = y;
}

void ObjetoTileMap::setPos(Vetor2D pos)
{
	x = pos.x;
	y = pos.y;
}

void ObjetoTileMap::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void ObjetoTileMap::setRot(float rot)
{
	this->rot = rot;
}

void ObjetoTileMap::setXCentro(float x)
{
	this->x = x - larg/2.0f;
}

void ObjetoTileMap::setYCentro(float y)
{
	this->y = y - alt/2.0f;
}

void ObjetoTileMap::setPosCentro(const Vetor2D& pos)
{
	x = pos.x - larg/2.0f;
	y = pos.y - alt/2.0f;
}

void ObjetoTileMap::setPosCentro(float x, float y)
{
	this->x = x - larg/2.0f;
	this->y = y - alt/2.0f;
}

void ObjetoTileMap::setLargura(float larg)
{
	this->larg = larg;
}

void ObjetoTileMap::setAltura(float alt)
{
	this->alt = alt;
}

void ObjetoTileMap::setTamanho(const Vetor2D& tam)
{
	larg = tam.x;
	alt = tam.y;
}

void ObjetoTileMap::setTamanho(float larg, float alt)
{
	this->larg = larg;
	this->alt = alt;
}

void ObjetoTileMap::setPtr(void* ptr)
{
	voidPtr = ptr;
}

void ObjetoTileMap::setCamada(CamadaDeObjetosTileMap *camada)
{
	this->camada = camada;
}

void ObjetoTileMap::setPropriedade(string nome, string valor)
{
	if (!propriedades)
	{
		propriedades = new map<string, string>();
	}

	map<string, string>::iterator it = propriedades->find(nome);

	if(it == propriedades->end())
		propriedades->insert(pair<string, string>(nome, valor));
	else
		it->second = valor;
}

void ObjetoTileMap::desenhar(int px, int py)
{
	if(visivel)
		spr->desenhar(px, py, rot);
}
