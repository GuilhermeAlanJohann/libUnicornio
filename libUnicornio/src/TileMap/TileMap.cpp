#include "TileMap.h"
#include "libUnicornio.h"
#include <fstream>
#include <sstream>
#include <algorithm>

TileMap::TileMap()
{
	x = 0.0f;
	y = 0.0f;

	desloc_x = 0.0f;
	desloc_y = 0.0f;

	maior_largura_tile = 0;
	maior_altura_tile = 0;

	largura_em_tiles = 0;
	altura_em_tiles = 0;

	largura_tile = 0;
	altura_tile = 0;

	carregou = false;
}

TileMap::~TileMap()
{
	if(estaCarregado())
	{
		descarregar();
	}
}

bool TileMap::carregar(string arquivo)
{
	if(!uni_init)
	{
		uniErro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		uniErro("Arquivo '" + arquivo + "' nao pode ser carregado, pois TileMap ja carregou algum arquivo.");
		return false;
	}

	//	abrir o arquivo (e fazer o parse)
	Json::Value root;
	Json::Reader reader;
	ifstream ifs(arquivo);
	if(!reader.parse(ifs, root))
	{
		uniErro("Erro ao carregar arquivo '" + arquivo + "'.");
		ifs.close();
		return false;
	}
	ifs.close();

	//	pegar informacoes basicas
	largura_em_tiles = root.get("width", 0).asInt();
	altura_em_tiles = root.get("height", 0).asInt();

	largura_tile= root.get("tilewidth", 0).asInt();
	altura_tile= root.get("tileheight", 0).asInt();

	// posicionar tile (0, 0) no canto superior esquerdo da tela e centralizar o mapa, caso ele caiba inteiro na tela
	if(largura_em_tiles*largura_tile < res_x)
		desloc_x = ((float)(res_x)/(float)(largura_tile) - (float)(largura_em_tiles))/2.0f;

	if(altura_em_tiles*altura_tile < res_y)
		desloc_y = ((float)(res_y)/(float)(altura_tile) - (float)(altura_em_tiles))/2.0f;

	x = 0.0f;
	y = 0.0f;

	//	carregar propriedades do mapa
	Json::Value props = root.get("properties", -1);
	for(unsigned int i = 0; i < props.getMemberNames().size(); ++i)
	{
		string nome = props.getMemberNames()[i];
		string valor = props.get(nome, "").asString();
		setPropriedade(nome, valor);
	}

	//	carregar tilesets
	vector<string> tilesets_config;
	maior_largura_tile = 0;
	maior_altura_tile = 0;
	Json::Value tsets = root["tilesets"];
	tilesets.resize(tsets.size());
	tilesets_config.resize(tsets.size());
	for(unsigned int i = 0; i < tsets.size(); ++i)
	{
		int tlarg = tsets[i].get("tilewidth", 0).asInt();
		int talt = tsets[i].get("tileheight", 0).asInt();
		string arq = tsets[i].get("image", "").asString();

		if(!tilesets[i].carregar(arq, tlarg, talt))
		{
			tilesets.clear();
			return false;
		}

		tilesets[i].setPrimeiroIDGlobal(tsets[i].get("firstgid", -1).asInt());
		tilesets[i].setNome(tsets[i].get("name", "").asString());

		//	guarda nome do arquivo de configuracao do tileset
		//	e ignora todas as outras propriedades
		Json::Value props = tsets[i].get("properties", -1);
		for(unsigned int p = 0; p < props.getMemberNames().size(); ++p)
		{
			string nome = props.getMemberNames()[p];
			if(nome == "config")
			{
				string valor = props.get(nome, "").asString();
				tilesets_config[i] = valor;
			}
		}

		if(maior_largura_tile < tlarg)
			maior_largura_tile = tlarg;

		if(maior_altura_tile < talt)
			maior_altura_tile = talt;

	}

	//	criar tiles
	int total_tiles = tilesets[tilesets.size()-1].getPrimeiroIDGlobal() + tilesets[tilesets.size()-1].getNumTiles() -1;
	tiles.resize(total_tiles);
	int indiceTileset = 0;
	for(unsigned int i = 0; i < tiles.size(); ++i)
	{
		if(i == tilesets[indiceTileset].getPrimeiroIDGlobal() + tilesets[indiceTileset].getNumTiles() -1)
			++indiceTileset;
			
		tiles[i].setTileset(&tilesets[indiceTileset]);
	}

	//	configurar tiles/tilesets
	for(int i = 0; i < tilesets_config.size(); ++i)
		carregarConfigTileSet(&tilesets[i], tilesets_config[i]);

	//	criar layers
	Json::Value jLayers = root["layers"];
	int num_tilelayers = 0;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() == "tilelayer")
			++num_tilelayers;
	}
	layers.resize(num_tilelayers);

	int l = 0;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() != "tilelayer")
			continue;

		layers[l].setNome(jLayers[i].get("name", "").asString());
		layers[l].setVisivel(jLayers[i].get("visible", true).asBool());

		layers[l].redimensionar(largura_em_tiles, altura_em_tiles);

		Json::Value tileArray = jLayers[i]["data"];
		int t = 0;
		for(int k = 0; k < altura_em_tiles; ++k)
			for(int j = 0; j < largura_em_tiles; ++j)
			{
				layers[l].setIDdoTile(tileArray[t].asInt(), j, k);
				++t;
			}


		l++;
	}

	//	criar objetos
	Json::Value objs;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() != "objectgroup")
			continue;

		objs = jLayers[i]["objects"];
		for(int j = 0; j < objs.size(); ++j)
		{
			ObjetoTile* o = new ObjetoTile();
			o->setNome(objs[j].get("name", "").asString());
			o->setTipo(objs[j].get("type", "").asString());

			o->setPos(objs[j].get("x", 0).asFloat()/(float)largura_tile, objs[j].get("y", 0).asFloat()/(float)altura_tile);
			o->setTamanho(objs[j].get("width", 0).asFloat()/(float)largura_tile, objs[j].get("height", 0).asFloat()/(float)altura_tile);

			o->setVisivel(objs[j].get("visible", true).asBool());

			Json::Value props = objs[j].get("properties", -1);
			for(unsigned int i = 0; i < props.getMemberNames().size(); ++i)
			{
				string nome = props.getMemberNames()[i];
				string valor = props.get(nome, "").asString();
				o->setPropriedade(nome, valor);
			}

			objetos.push_back(o);

		}
	}

	carregou = true;
	return true;
}

bool TileMap::carregarConfigTileSet(TileSet* tileset, string arquivo)
{
	ifstream ifs(arquivo);
	if(!ifs.is_open())
		return false;

	string nome_arquivo;
	int larg_tile, alt_tile;

	ifs >> nome_arquivo;
	ifs >> larg_tile >> alt_tile;

	if(larg_tile != tileset->getLarguraTiles() || alt_tile != tileset->getAlturaTiles())
		return false;

	int tiles_x = tileset->getNumTilesX();
	int tiles_y = tileset->getNumTilesY();

	string marcador;
	int num;
	bool b;

	//	caminhavel
	do ifs >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			ifs >> b;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setCaminhavel(b);
		}

	//	profundidade
	do ifs >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			ifs >> num;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setProfundidade((ProfundidadeTile)num);
		}

	//	custo adicional
	do ifs >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			ifs >> num;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setCustoAdicional(num);
		}

	ifs.close();
	return true;
}

bool TileMap::carregarConfigTileSet(string nome_tileset, string arquivo)
{
	for(int i = 0; i < tilesets.size(); ++i)
		if(tilesets[i].getNome() == nome_tileset)
			return carregarConfigTileSet(&tilesets[i], arquivo);
	
	return false;
}

void TileMap::descarregar()
{
	for(int i = 0; i < tilesets.size(); ++i)
		tilesets[i].descarregar();

	for(int i = 0; i < objetos.size(); ++i)
		delete objetos[i];

	tiles.clear();
	tilesets.clear();
	layers.clear();
	objetos.clear();

	carregou = false;
}

bool TileMap::estaCarregado()
{
	return carregou;
}

void TileMap::desenhar()
{
	float tiles_na_tela_x = (float)(res_x)/(float)largura_tile;
	float tiles_na_tela_y = (float)(res_y)/(float)altura_tile;

	if(tiles_na_tela_x > largura_em_tiles)
		tiles_na_tela_x = largura_em_tiles;

	if(tiles_na_tela_y > altura_em_tiles)
		tiles_na_tela_y = altura_em_tiles;

	int itx = (int)(x - (maior_largura_tile/largura_tile -1) - desloc_x);
	int ity = (int)(y - desloc_y);

	if(itx < 0)
		itx = 0;

	if(ity < 0)
		ity = 0;

	int ftx = (int)(itx + tiles_na_tela_x) + 1;
	int fty = (int)(ity + (maior_altura_tile/altura_tile -1) + tiles_na_tela_y) + 1;

	if(ftx > largura_em_tiles-1)
		ftx = largura_em_tiles-1;

	if(fty > altura_em_tiles-1)
		fty = altura_em_tiles-1;

	int px0 = (int)(((float)itx - x + desloc_x)*largura_tile);
	int py0 = (int)(((float)ity - y + desloc_y)*altura_tile);

	//	desenhar tiles abaixo dos objetos
	for(unsigned int camada = 0; camada < layers.size(); ++camada)
	{
		if(!layers[camada].estaVisivel())
			continue;

		int py = py0;
		for(int j = ity; j <= fty; ++j, py += altura_tile)
		{
			int px = px0;
			for(int i = itx; i <= ftx; ++i, px += largura_tile)
			{
				int id = layers[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getProfundidade() == ABAIXO_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}

	//	desenhar objetos e tiles no nivel dos objetos
	ordenarObjetosPorYCentral();
	int prox_obj = 0;

		//	objetos que estao acima da tela;
	for(int o = prox_obj; o < objetos.size(); ++o)
	{
		float pxo, pyo;
		objetos[o]->obterPosCentro(pxo, pyo);
		pxo += -x + desloc_x;
		pyo += -y + desloc_y;
		pxo *= largura_tile;
		pyo *= altura_tile;

		if(pyo < px0)
		{
			objetos[o]->desenhar(pxo, pyo);
			prox_obj++;
		}
		else
			break;
	}

	int py = py0;
	for(int j = ity; j <= fty; ++j, py += altura_tile)
	{
		//	objetos nesta linha
		for(int o = prox_obj; o < objetos.size(); ++o)
		{
			float pxo, pyo;
			objetos[o]->obterPosCentro(pxo, pyo);
			pxo += -x + desloc_x;
			pyo += -y + desloc_y;
			pxo *= largura_tile;
			pyo *= altura_tile;

			if(pyo >= py && pyo <= py+altura_tile)
			{
				objetos[o]->desenhar(pxo, pyo);
				prox_obj++;
			}
			else
				break;

		}

		//	tiles nesta linha
		int px = px0;
		for(int i = itx; i <= ftx; ++i, px += largura_tile)
		{
			for(unsigned int camada = 0; camada < layers.size(); ++camada)
			{
				if(!layers[camada].estaVisivel())
					continue;

				int id = layers[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getProfundidade() == NO_NIVEL_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}

		//	objetos restantes (abaixo da tela) 
	for(int o = prox_obj; o < objetos.size(); ++o)
	{
		float px, py;
		objetos[o]->obterPosCentro(px, py);
		px += -x + desloc_x;
		py += -y + desloc_y;
		px *= largura_tile;
		py *= altura_tile;

		objetos[o]->desenhar(px, py);
	}

	//	desenhar tiles acima dos objetos
	for(unsigned int camada = 0; camada < layers.size(); ++camada)
	{
		if(!layers[camada].estaVisivel())
			continue;

		int py = py0;
		for(int j = ity; j <= fty; ++j, py += altura_tile)
		{
			int px = px0;
			for(int i = itx; i <= ftx; ++i, px += largura_tile)
			{
				int id = layers[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getProfundidade() == ACIMA_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}
}


ObjetoTile* TileMap::criarObjeto()
{
	objetos.push_back(new ObjetoTile());
	return objetos[objetos.size()-1];
}

bool TileMap::destruirObjeto(string nome)
{
	for(int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
		{
			delete objetos[i];
			objetos.erase(objetos.begin() + i);
			return true;
		}

	return false;
}

bool TileMap::destruirObjeto(ObjetoTile* obj)
{
	for(int i = 0; i < objetos.size(); ++i)
		if(*objetos[i] == *obj)
		{
			delete objetos[i];
			objetos.erase(objetos.begin() + i);
			return true;
		}

	return false;
}

bool TileMap::existeObjetoNaPos(float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

bool TileMap::existeObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

void TileMap::telaParaTile(int px, int py, float& tx, float& ty)
{
	tx = x - desloc_x + (float)(px)/(float)(largura_tile);
	ty = y - desloc_y + (float)(py)/(float)(altura_tile);
}

void TileMap::tileParaTela(float tx, float ty, int& px, int& py)
{
	px = (int)((tx - x + desloc_x)*largura_tile);
	py = (int)((ty - y + desloc_y)*altura_tile);
}

bool TileMap::tileECaminhavel(float tx, float ty)
{
	//	se esta fora da tela (retorna falso)
	if(tx < 0 || tx >= largura_em_tiles || ty < 0 || ty >= altura_em_tiles)
		return false;

	// testa em cada uma das layers
	for(int l = 0; l < layers.size(); ++l)
	{
		int id = layers[l].getIDdoTile(tx, ty);
			if(id < 1)
				continue;

		if(!tiles[id-1].eCaminhavel())
			return false;
	}

	//	calcula dif de tamanho entre os tiles
	int dx = maior_largura_tile/largura_tile;
	int dy = maior_altura_tile/altura_tile;

	if(dx + dy == 0)	//	se todos tiles tem o mesmo tamanho, retorna verdadeiro
		return true;

	//	se nao, testa em tiles com tamanhos diferentes
	for(int l = 0; l < layers.size(); ++l)
		for(int i = 0; i < dx; ++i)
			for(int j = 0; j < dy; ++j)
			{
				if(i + j == 0)
					continue;

				if((tx - i < 0) || (ty + j >= altura_em_tiles))
					continue;

				int id = layers[l].getIDdoTile(tx - i, ty + j);
				if(id < 1)
					continue;

				TileSet* tileset = tiles[id-1].getTileSet();
				if(tileset->getLarguraTiles()/largura_tile > i && tileset->getAlturaTiles()/altura_tile > j)
					if(!tiles[id-1].eCaminhavel())
						return false;
			}

	return true;
}

int TileMap::getCustoAdicionalNoTile(float tx, float ty)
{
	//	se esta fora da tela (retorna falso)
	if(tx < 0 || tx >= largura_em_tiles || ty < 0 || ty >= altura_em_tiles)
		return 0;

	int custo = 0;

	// testa em cada uma das layers
	for(int l = 0; l < layers.size(); ++l)
	{
		int id = layers[l].getIDdoTile(tx, ty);
			if(id < 1)
				continue;

		custo += tiles[id-1].getCustoAdicional();
	}

	//	calcula dif de tamanho entre os tiles
	int dx = maior_largura_tile/largura_tile;
	int dy = maior_altura_tile/altura_tile;

	if(dx + dy == 0)	//	se todos tiles tem o mesmo tamanho, retorna custo
		return custo;

	//	se nao, testa em tiles com tamanhos diferentes
	for(int l = 0; l < layers.size(); ++l)
		for(int i = 0; i < dx; ++i)
			for(int j = 0; j < dy; ++j)
			{
				if(i + j == 0)
					continue;

				if((tx - i < 0) || (ty + j >= altura_em_tiles))
					continue;

				int id = layers[l].getIDdoTile(tx - i, ty + j);
				if(id < 1)
					continue;

				TileSet* tileset = tiles[id-1].getTileSet();
				if(tileset->getLarguraTiles()/largura_tile > i && tileset->getAlturaTiles()/altura_tile > j)
					custo += tiles[id-1].getCustoAdicional();
			}

	return custo;
}

float TileMap::getX()
{
	return x;
}

float TileMap::getY()
{
	return y;
}

float TileMap::getXCentro()
{
	return x + (getNumTilesNaTelaEmX()/2.0f);
}

float TileMap::getYCentro()
{
	return y + (getNumTilesNaTelaEmY()/2.0f);
}

int TileMap::getLarguraEmTiles()
{
	return largura_em_tiles;
}

int TileMap::getAlturaEmTiles()
{
	return altura_em_tiles;
}

int TileMap::getLarguraTile()
{
	return largura_tile;
}

int TileMap::getAlturaTile()
{
	return altura_tile;
}

int TileMap::getNumTilesNaTelaEmX()
{
	float tiles_na_tela_em_x = (float)(res_x)/(float)(largura_tile);

	if(tiles_na_tela_em_x > largura_em_tiles)
		tiles_na_tela_em_x = largura_em_tiles;

	return tiles_na_tela_em_x;
}

int TileMap::getNumTilesNaTelaEmY()
{
	float tiles_na_tela_em_y = (float)(res_y)/(float)(altura_tile);

	if(tiles_na_tela_em_y > altura_em_tiles)
		tiles_na_tela_em_y = altura_em_tiles;

	return tiles_na_tela_em_y;
}

int TileMap::getNumLayers()
{
	return layers.size();
}

int TileMap::getNumTileSets()
{
	return tilesets.size();
}

int TileMap::getNumTiles()
{
	return tiles.size();
}

int TileMap::getNumObjetos()
{
	return objetos.size();
}

TileLayer* TileMap::getTileLayer(int indice)
{
	return &layers[indice];
}

TileLayer* TileMap::getTileLayer(string nome)
{
	for(unsigned int i = 0; i < layers.size(); ++i)
	{
		if(nome == layers[i].getNome())
			return &layers[i];
	}
	return NULL;
}

TileSet* TileMap::getTileSet(int indice)
{
	return &tilesets[indice];
}

TileSet* TileMap::getTileSet(string nome)
{
	for(unsigned int i = 0; i < tilesets.size(); ++i)
	{
		if(nome == tilesets[i].getNome())
			return &tilesets[i];
	}
	return NULL;
}

Tile* TileMap::getTile(int idGlobal)
{
	return &tiles[idGlobal-1];
}

Tile* TileMap::getTile(int tx, int ty, int indiceLayer)
{
	return &tiles[layers[indiceLayer].getIDdoTile(tx, ty)];
}

Tile* TileMap::getTile(int tx, int ty, string nomeLayer)
{
	return &tiles[getTileLayer(nomeLayer)->getIDdoTile(tx, ty)];
}

ObjetoTile* TileMap::getObjeto(int indice)
{
	return objetos[indice];
}

ObjetoTile* TileMap::getObjeto(string nome)
{
	for(int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getNome() == nome)
			return objetos[i];

	return NULL;
}

ObjetoTile* TileMap::getObjetoNaPos(float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

ObjetoTile* TileMap::getObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

vector<ObjetoTile*> TileMap::getObjetosDoTipo(string tipo)
{
	vector<ObjetoTile*> r;

	for(int i = 0; i < objetos.size(); ++i)
		if(objetos[i]->getTipo() == tipo)
			r.push_back(objetos[i]);

	return r;
}

vector<ObjetoTile*> TileMap::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTile*> r;
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

vector<ObjetoTile*> TileMap::getObjetosDoTipoNaPos(string tipo, float tx, float ty)
{
	vector<ObjetoTile*> r;
	float ox0, oy0, ox, oy;
	for(int i = 0; i < objetos.size(); ++i)
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

string TileMap::getPropriedade(string nome)
{
	map<string, string>::iterator it = propriedades.find(nome);
	if(it != propriedades.end())
		return it->second;

	return "";
}

int TileMap::getPropriedadeInt(string nome)
{
	stringstream ss(getPropriedade(nome));
	int r;
	ss >> r;
	return r;
}

float TileMap::getPropriedadeFloat(string nome)
{
	stringstream ss(getPropriedade(nome));
	float r;
	ss >> r;
	return r;
}

bool TileMap::getPropriedadeBool(string nome)
{
	string s = getPropriedade(nome);
	std::transform(s.begin(), s.end(), s.begin(), ::tolower);
	
	if(s == "true")
		return true;
	else if(getPropriedadeInt(nome) == 1)
		return true;
	else
		return false;
}

void TileMap::obterPos(float& x, float& y)
{
	x = this->x;
	y = this->y;
}

void TileMap::obterPosCentro(float& x, float& y)
{
	x = getXCentro();
	y = getYCentro();
}

void TileMap::obterTamanhoEmTiles(int& larg, int& alt)
{
	larg = largura_em_tiles;
	alt = altura_em_tiles;
}

void TileMap::obterTamanhoTile(int& larg, int& alt)
{
	larg = largura_tile;
	alt = altura_tile;
}

void TileMap::setX(float x)
{
	this->x = x;
}

void TileMap::setY(float y)
{
	this->y = y;
}

void TileMap::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

void TileMap::setXCentro(float x)
{
	this->x = x - (getNumTilesNaTelaEmX()/2.0f);
}

void TileMap::setYCentro(float y)
{
	this->y = y - (getNumTilesNaTelaEmY()/2.0f);
}

void TileMap::setPosCentro(float x, float y)
{
	setXCentro(x);
	setYCentro(y);
}

void TileMap::setPropriedade(string nome, string valor)
{
	map<string, string>::iterator it = propriedades.find(nome);
	if(it != propriedades.end())
		it->second = valor;
	else
		propriedades.insert(pair<string, string>(nome, valor));
}

void TileMap::setPropriedadeInt(string nome, int valor)
{
	stringstream ss;
	ss << valor;
	setPropriedade(nome, ss.str());
}

void TileMap::setPropriedadeFloat(string nome, float valor)
{
	stringstream ss;
	ss << valor;
	setPropriedade(nome, ss.str());
}

void TileMap::setPropriedadeBool(string nome, bool valor)
{
	if(valor)
		setPropriedade(nome, "true");
	else
		setPropriedade(nome, "false");
}

void TileMap::desenharTileNoPixel(int id, float px, float py)
{
	TileSet* tileset = tiles[id-1].getTileSet();

	SDL_Rect clip;
	clip.w = tileset->getLarguraTiles();
	clip.h = tileset->getAlturaTiles();
	clip.x = ((id - tileset->getPrimeiroIDGlobal())%tileset->getNumTilesX())*clip.w;
	clip.y = ((id - tileset->getPrimeiroIDGlobal())/tileset->getNumTilesX())*clip.h;

	SDL_Rect rect;
	rect.w = clip.w;
	rect.h = clip.h;

	SDL_Point pivot = {0, rect.h};	//	ancora igual ao Tiled Map editor (0, 1)

	rect.x = (px) - pivot.x;
	rect.y = (py+altura_tile) - pivot.y;	//	soma 1 tile na altura, pois altura 0 em deve ser no pixel 'altura_tile', para ficar igual a ancora do Tiled Map Editor

	SDL_Texture* tex = tileset->getTextura();

    //	Draw the texture
	SDL_RenderCopyEx(renderer, tex, &clip, &rect, 0, &pivot, SDL_FLIP_NONE);
}

void TileMap::ordenarObjetosPorYCentral()
{
	bool ordenados = true;
	for(int i = 1; i < objetos.size(); ++i)
	{
		if(objetos[i]->getYCentro() < objetos[i-1]->getYCentro())
		{
			ordenados = false;
			break;
		}
	}

	if(ordenados)
		return;

	for(int i = 0; i < objetos.size(); ++i)
	{
		for(int j = i+1; j < objetos.size(); ++j)
		{
			if(objetos[j]->getYCentro() < objetos[i]->getYCentro())
			{
				ObjetoTile* temp = objetos[j];
				objetos[j]= objetos[i];
				objetos[i] = temp;
			}
		}
	}
}