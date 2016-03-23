#include "ObjetoTileMap.h"


ObjetoTileMap::ObjetoTileMap()
{
	spr = NULL;

	x = 0.0f;
	y = 0.0f;
	rot = 0.0f;

	larg = 0.0f;
	alt = 0.0f;

	dadoDeUsuario = NULL;

	visivel = true;
}

ObjetoTileMap::~ObjetoTileMap()
{
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

void* ObjetoTileMap::getDadoDeUsuario()
{
	return dadoDeUsuario;
}

CamadaDeObjetosTileMap *ObjetoTileMap::getCamada()
{
	return camada;
}

string ObjetoTileMap::getPropriedade(string nome)
{
	map<string, string>::iterator it = propriedades.find(nome);

	if(it != propriedades.end())
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
	this->spr = spr;
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

void ObjetoTileMap::setPosCentro(Vetor2D pos)
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

void ObjetoTileMap::setTamanho(float larg, float alt)
{
	this->larg = larg;
	this->alt = alt;
}

void ObjetoTileMap::setDadoDeUsuario(void* dado)
{
	dadoDeUsuario = dado;
}

void ObjetoTileMap::setCamada(CamadaDeObjetosTileMap *camada)
{
	this->camada = camada;
}

void ObjetoTileMap::setPropriedade(string nome, string valor)
{
	map<string, string>::iterator it = propriedades.find(nome);

	if(it == propriedades.end())
		propriedades.insert(pair<string, string>(nome, valor));
	else
		it->second = valor;
}

void ObjetoTileMap::desenhar(int px, int py)
{
	spr->desenhar(px, py, rot);
}
