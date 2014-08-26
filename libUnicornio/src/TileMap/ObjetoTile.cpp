#include "ObjetoTile.h"
#include "libUnicornio.h"

ObjetoTile::ObjetoTile()
{
	spr = NULL;

	x = 0.0f;
	y = 0.0f;
	rot = 0.0f;

	larg = 0.0f;
	alt = 0.0f;

	visivel = true;
}

ObjetoTile::~ObjetoTile()
{
}

bool ObjetoTile::operator==(const ObjetoTile& other)
{
	return (x == other.x && y == other.y && rot == other.rot && larg == other.larg && alt == other.alt && visivel == other.visivel && spr == other.spr && nome == other.nome && tipo == other.tipo);
}

bool ObjetoTile::operator!=(const ObjetoTile& other)
{
	return !(*this == other);
}

Sprite* ObjetoTile::getSprite()
{
	return spr;
}

bool ObjetoTile::estaVisivel()
{
	return visivel;
}

string ObjetoTile::getNome()
{
	return nome;
}

string ObjetoTile::getTipo()
{
	return tipo;
}

float ObjetoTile::getX()
{
	return x;
}

float ObjetoTile::getY()
{
	return y;
}

float ObjetoTile::getRot()
{
	return rot;
}

float ObjetoTile::getXCentro()
{
	return (x + larg/2.0f);
}

float ObjetoTile::getYCentro()
{
	return (y + alt/2.0f);
}

float ObjetoTile::getLargura()
{
	return larg;
}

float ObjetoTile::getAltura()
{
	return alt;
}

string ObjetoTile::getPropriedade(string nome)
{
	map<string, string>::iterator it = propriedades.find(nome);

	if(it != propriedades.end())
		return it->second;

	return "";
}

void ObjetoTile::obterPos(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void ObjetoTile::obterPosCentro(float& x, float& y)
{
	x = getXCentro();
	y = getYCentro();
}

void ObjetoTile::obterTamanho(float& larg, float& alt)
{
	larg = this->larg;
	alt = this->alt;
}

void ObjetoTile::setSprite(Sprite* spr)
{
	this->spr = spr;
}

void ObjetoTile::setVisivel(bool b)
{
	visivel = b;
}

void ObjetoTile::setNome(string nome)
{
	this->nome = nome;
}

void ObjetoTile::setTipo(string tipo)
{
	this->tipo = tipo;
}

void ObjetoTile::setX(float x)
{
	this->x = x;
}

void ObjetoTile::setY(float y)
{
	this->y = y;
}

void ObjetoTile::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void ObjetoTile::setRot(float rot)
{
	this->rot = rot;
}

void ObjetoTile::setXCentro(float x)
{
	this->x = x - larg/2.0f;
}

void ObjetoTile::setYCentro(float y)
{
	this->y = y - alt/2.0f;
}

void ObjetoTile::setPosCentro(float x, float y)
{
	this->x = x - larg/2.0f;
	this->y = y - alt/2.0f;
}

void ObjetoTile::setLargura(float larg)
{
	this->larg = larg;
}

void ObjetoTile::setAltura(float alt)
{
	this->alt = alt;
}

void ObjetoTile::setTamanho(float larg, float alt)
{
	this->larg = larg;
	this->alt = alt;
}

void ObjetoTile::setPropriedade(string nome, string valor)
{
	map<string, string>::iterator it = propriedades.find(nome);

	if(it == propriedades.end())
		propriedades.insert(pair<string, string>(nome, valor));
	else
		it->second = valor;
}

void ObjetoTile::desenhar(int px, int py)
{
	if(spr && visivel)
		spr->desenhar(px, py, rot);
}
