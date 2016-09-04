#include "TileSet.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"

TileSet::TileSet()
{
	num_tiles_x = 0;
	num_tiles_y = 0;

	largura_tile = 0;
	altura_tile = 0;

	primeiro_ID_Global = -1;
}

TileSet::~TileSet()
{
	if(estaCarregado())
	{
		descarregar();
	}
}

bool TileSet::carregar(const string& arquivo, int largura_tiles, int altura_tiles)
{
	if(!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois TileSet '" + nome + "' ja carregou algum arquivo.");
		return false;
	}

	bool r = tex.criarDoArquivo(arquivo, QUALIDADE_ESCALA_BAIXA);
	
	if(!r) 
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "'.");
		return false;
	}

	largura_tile = largura_tiles;
	altura_tile = altura_tiles;

	int largura_total;
	int altura_total;
	tex.obterTamanho(largura_total, altura_total);

	num_tiles_x = largura_total/largura_tiles;
	num_tiles_y = altura_total/altura_tiles;

	return true;
}

void TileSet::descarregar()
{
	if (estaCarregado())
	{
		tex.destruir();
		nome = "";
		num_tiles_x = 0;
		num_tiles_y = 0;
		largura_tile = 0;
		altura_tile = 0;
		primeiro_ID_Global = -1;
	}
}

bool TileSet::estaCarregado()
{
	return tex.estaCriada();
}
	
string TileSet::getNome()
{
	return nome;
}

int TileSet::getAlturaTiles()
{
	return altura_tile;
}

int TileSet::getLarguraTiles()
{
	return largura_tile;
}

int TileSet::getNumTiles()
{
	return num_tiles_x*num_tiles_y;
}

int TileSet::getNumTilesX()
{
	return num_tiles_x;
}

int TileSet::getNumTilesY()
{
	return num_tiles_y;
}

int TileSet::getPrimeiroIDGlobal()
{
	return primeiro_ID_Global;
}

void TileSet::obterTamanhoTiles(int &w, int &h)
{
	w = largura_tile;
	h = altura_tile;
}

Textura* TileSet::getTextura()
{
	return &tex;
}

void TileSet::setNome(const string& nome)
{
	this->nome = nome;
}

void TileSet::setPrimeiroIDGlobal(int primeiro_ID)
{
	primeiro_ID_Global = primeiro_ID;
}