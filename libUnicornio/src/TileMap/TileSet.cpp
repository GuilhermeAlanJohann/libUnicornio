#include "TileSet.h"
#include "libUnicornio.h"

TileSet::TileSet()
{
	tex = NULL;

	num_tiles_x = 0;
	num_tiles_y = 0;

	largura_tile = 0;
	altura_tile = 0;
}

TileSet::~TileSet()
{
	if(tex)
	{
		SDL_DestroyTexture(tex);
	}
}

bool TileSet::carregar(string arquivo, int largura_tiles, int altura_tiles)
{
	if(!uni_init)
	{
		uniDesenharTexto("sem uni_inicializar() antes de tentar carregar:" + arquivo, 10, 10);
		return false;
	}

	if(tex)
	{
		SDL_DestroyTexture(tex);
	}

	tex = IMG_LoadTexture(renderer, arquivo.c_str());
	
	if(!tex) 
	{
		string s_err = "Erro carreg. arq: " + arquivo;
		uniErro(s_err);
		uni_debug = true;
		tex = NULL;
		return false;
	}

	largura_tile = largura_tiles;
	altura_tile = altura_tiles;

	int largura_total;
	int altura_total;
	SDL_QueryTexture(tex, NULL, NULL, &largura_total, &altura_total);

	num_tiles_x = largura_total/largura_tiles;
	num_tiles_y = altura_total/altura_tiles;

	return true;
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

SDL_Texture* TileSet::getTextura()
{
	return tex;
}

void TileSet::setNome(string nome)
{
	this->nome = nome;
}

void TileSet::setPrimeiroIDGlobal(int primeiro_ID)
{
	primeiro_ID_Global = primeiro_ID;
}