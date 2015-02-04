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
	for(unsigned int i = 0; i < tilesets_config.size(); ++i)
		carregarConfigTileSet(&tilesets[i], tilesets_config[i]);

	//	calcular num camadas de tiles e num camadas de objetos
	Json::Value jLayers = root["layers"];
	int num_tilelayers = 0;
	int num_objectlayers = 0;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() == "tilelayer")
			++num_tilelayers;
		else if(jLayers[i].get("type", "").asString() == "objectgroup")
			++num_objectlayers;
	}
	camadas_tiles.resize(num_tilelayers);
	camadas_objetos.resize(num_objectlayers);

	//	criar camadas de tiles
	int l = 0;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() != "tilelayer")
			continue;

		camadas_tiles[l].setNome(jLayers[i].get("name", "").asString());
		camadas_tiles[l].setVisivel(jLayers[i].get("visible", true).asBool());

		camadas_tiles[l].redimensionar(largura_em_tiles, altura_em_tiles);

		Json::Value tileArray = jLayers[i]["data"];
		int t = 0;
		for(unsigned int k = 0; k < altura_em_tiles; ++k)
			for(unsigned int j = 0; j < largura_em_tiles; ++j)
			{
				camadas_tiles[l].setIDdoTile(tileArray[t].asInt(), j, k);
				++t;
			}


		l++;
	}

	//	criar camadas de objetos
	Json::Value objs;
	l = 0;
	for(unsigned int i = 0; i < jLayers.size(); ++i)
	{
		if(jLayers[i].get("type", "").asString() != "objectgroup")
			continue;

		camadas_objetos[l] = new CamadaDeObjetos;

		camadas_objetos[l]->setNome(jLayers[i].get("name", "").asString());
		camadas_objetos[l]->setVisivel(jLayers[i].get("visible", true).asBool());

		Json::Value props = jLayers[i].get("properties", -1);
		if(!props.isInt())
		for(unsigned int p = 0; p < props.getMemberNames().size(); ++p)
		{
			string nome = props.getMemberNames()[p];
			if(nome == "nivel")
			{
				string valor = props.get(nome, NO_NIVEL_DOS_OBJETOS).asString();
				int nivel = atoi(valor.c_str());
				if(nivel < ABAIXO_DOS_OBJETOS || nivel > ACIMA_DOS_OBJETOS)
					nivel = NO_NIVEL_DOS_OBJETOS;
				camadas_objetos[l]->setNivel((NivelTile)nivel);
			}
		}

		objs = jLayers[i]["objects"];
		for(unsigned int j = 0; j < objs.size(); ++j)
		{
			ObjetoTile* o = camadas_objetos[l]->criarObjeto();
			o->setNome(objs[j].get("name", "").asString());
			o->setTipo(objs[j].get("type", "").asString());

			o->setPos(objs[j].get("x", 0).asFloat()/(float)largura_tile, objs[j].get("y", 0).asFloat()/(float)altura_tile);
			o->setTamanho(objs[j].get("width", 0).asFloat()/(float)largura_tile, objs[j].get("height", 0).asFloat()/(float)altura_tile);

			o->setVisivel(objs[j].get("visible", true).asBool());

			props = objs[j].get("properties", -1);
			for(unsigned int i = 0; i < props.getMemberNames().size(); ++i)
			{
				string nome = props.getMemberNames()[i];
				string valor = props.get(nome, "").asString();
				o->setPropriedade(nome, valor);
			}

		}

		++l;
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
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setNivel((NivelTile)num);
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
	for(unsigned int i = 0; i < tilesets.size(); ++i)
		if(tilesets[i].getNome() == nome_tileset)
			return carregarConfigTileSet(&tilesets[i], arquivo);
	
	return false;
}

void TileMap::descarregar()
{
	for(unsigned int i = 0; i < tilesets.size(); ++i)
		tilesets[i].descarregar();

	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
		delete camadas_objetos[i];

	tiles.clear();
	tilesets.clear();
	camadas_tiles.clear();
	camadas_objetos.clear();

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
	for(unsigned int camada = 0; camada < camadas_tiles.size(); ++camada)
	{
		if(!camadas_tiles[camada].estaVisivel())
			continue;

		int py = py0;
		for(int j = ity; j <= fty; ++j, py += altura_tile)
		{
			int px = px0;
			for(int i = itx; i <= ftx; ++i, px += largura_tile)
			{
				int id = camadas_tiles[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getNivel() == ABAIXO_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}

	//	desenhar objetos e tiles no nivel dos objetos
	prepararRenderQueues();

		//	objetos que estao abaixo dos outros
	for(unsigned int i = 0; i < render_queue_abaixo.size(); ++i)
	{
		float xo, yo;
		int pxo, pyo;
		render_queue_abaixo[i]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		render_queue_abaixo[i]->desenhar(pxo, pyo);
	}

		//	objetos que estao no meio e tiles que estao no nivel dos objetos
	int prox_obj = 0;
	int py = py0;
	for(int j = ity; j <= fty; ++j, py += altura_tile)
	{
		//	objetos nesta linha (ou antes dela)
		for(unsigned int o = prox_obj; o < render_queue_aomeio.size(); ++o)
		{
			float xo, yo;
			int pxo, pyo;
			render_queue_aomeio[o]->obterPosCentro(xo, yo);
			tileParaTela(xo, yo, pxo, pyo);

			if(pyo <= py+altura_tile)
			{
				render_queue_aomeio[o]->desenhar(pxo, pyo);
				prox_obj++;
			}
			else
				break;

		}

		//	tiles nesta linha
		int px = px0;
		for(int i = itx; i <= ftx; ++i, px += largura_tile)
		{
			for(unsigned int camada = 0; camada < camadas_tiles.size(); ++camada)
			{
				if(!camadas_tiles[camada].estaVisivel())
					continue;

				int id = camadas_tiles[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getNivel() == NO_NIVEL_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}

		//	objetos restantes (abaixo da tela) 
	for(unsigned int o = prox_obj; o < render_queue_aomeio.size(); ++o)
	{
		float xo, yo;
		int pxo, pyo;
		render_queue_aomeio[o]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		render_queue_aomeio[o]->desenhar(pxo, pyo);
	}

		//	objetos que estao acima dos outros
	for(unsigned int i = 0; i < render_queue_acima.size(); ++i)
	{
		float xo, yo;
		int pxo, pyo;
		render_queue_acima[i]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		render_queue_acima[i]->desenhar(pxo, pyo);
	}

	limparRenderQueues();

	//	desenhar tiles acima dos objetos
	for(unsigned int camada = 0; camada < camadas_tiles.size(); ++camada)
	{
		if(!camadas_tiles[camada].estaVisivel())
			continue;

		int py = py0;
		for(int j = ity; j <= fty; ++j, py += altura_tile)
		{
			int px = px0;
			for(int i = itx; i <= ftx; ++i, px += largura_tile)
			{
				int id = camadas_tiles[camada].getIDdoTile(i, j);
				if(id > 0)
					if(tiles[id-1].getNivel() == ACIMA_DOS_OBJETOS)
							desenharTileNoPixel(id, px, py);
			}
		}
	}
}

void TileMap::telaParaTile(int px, int py, float &tx, float &ty)
{
	tx = x - desloc_x + (float)(px)/(float)(largura_tile);
	ty = y - desloc_y + (float)(py)/(float)(altura_tile);
}

void TileMap::tileParaTela(float tx, float ty, int &px, int &py)
{
	px = (int)((tx - x + desloc_x)*largura_tile);
	py = (int)((ty - y + desloc_y)*altura_tile);
}

bool TileMap::tileECaminhavel(float tx, float ty)
{
	//	se esta fora da tela (retorna falso)
	if(tx < 0 || tx >= largura_em_tiles || ty < 0 || ty >= altura_em_tiles)
		return false;

	// testa em cada uma das camadas de tiles
	for(unsigned int l = 0; l < camadas_tiles.size(); ++l)
	{
		int id = camadas_tiles[l].getIDdoTile(tx, ty);
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
	for(unsigned int l = 0; l < camadas_tiles.size(); ++l)
		for(int i = 0; i < dx; ++i)
			for(int j = 0; j < dy; ++j)
			{
				if(i + j == 0)
					continue;

				if((tx - i < 0) || (ty + j >= altura_em_tiles))
					continue;

				int id = camadas_tiles[l].getIDdoTile(tx - i, ty + j);
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

	// testa em cada uma das camadas de tiles
	for(unsigned int l = 0; l < camadas_tiles.size(); ++l)
	{
		int id = camadas_tiles[l].getIDdoTile(tx, ty);
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
	for(unsigned int l = 0; l < camadas_tiles.size(); ++l)
		for(int i = 0; i < dx; ++i)
			for(int j = 0; j < dy; ++j)
			{
				if(i + j == 0)
					continue;

				if((tx - i < 0) || (ty + j >= altura_em_tiles))
					continue;

				int id = camadas_tiles[l].getIDdoTile(tx - i, ty + j);
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

int TileMap::getNumCamadasDeObjetos()
{
	return camadas_objetos.size();
}

int TileMap::getNumCamadasDeTiles()
{
	return camadas_tiles.size();
}

int TileMap::getNumTileSets()
{
	return tilesets.size();
}

int TileMap::getNumTiles()
{
	return tiles.size();
}

CamadaDeObjetos *TileMap::getCamadaDeObjetos(int indice)
{
	return camadas_objetos[indice];
}

CamadaDeObjetos *TileMap::getCamadaDeObjetos(string nome)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(nome == camadas_objetos[i]->getNome())
			return camadas_objetos[i];
	}
	return NULL;
}

CamadaDeTiles *TileMap::getCamadaDeTiles(int indice)
{
	return &camadas_tiles[indice];
}

CamadaDeTiles *TileMap::getCamadaDeTiles(string nome)
{
	for(unsigned int i = 0; i < camadas_tiles.size(); ++i)
	{
		if(nome == camadas_tiles[i].getNome())
			return &camadas_tiles[i];
	}
	return NULL;
}

TileSet *TileMap::getTileSet(int indice)
{
	return &tilesets[indice];
}

TileSet *TileMap::getTileSet(string nome)
{
	for(unsigned int i = 0; i < tilesets.size(); ++i)
	{
		if(nome == tilesets[i].getNome())
			return &tilesets[i];
	}
	return NULL;
}

Tile *TileMap::getTile(int idGlobal)
{
	return &tiles[idGlobal-1];
}

Tile *TileMap::getTile(Vetor2D pos, int indice_camada)
{
	return getTile(pos.x, pos.y, indice_camada);
}

Tile *TileMap::getTile(Vetor2D pos, string nome_camada)
{
	return getTile(pos.x, pos.y, nome_camada);
}

Tile *TileMap::getTile(int tx, int ty, int indice_camada)
{
	return &tiles[camadas_tiles[indice_camada].getIDdoTile(tx, ty)];
}

Tile *TileMap::getTile(int tx, int ty, string nome_camada)
{
	return &tiles[getCamadaDeTiles(nome_camada)->getIDdoTile(tx, ty)];
}

bool TileMap::existeObjetoNaPos(Vetor2D pos)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(camadas_objetos[i]->existeObjetoNaPos(pos))
			return true;
	}

	return false;
}

bool TileMap::existeObjetoNaPos(float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(camadas_objetos[i]->existeObjetoNaPos(tx, ty))
			return true;
	}

	return false;
}

bool TileMap::existeObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(camadas_objetos[i]->existeObjetoDoTipoNaPos(tipo, pos))
			return true;
	}

	return false;
}

bool TileMap::existeObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(camadas_objetos[i]->existeObjetoDoTipoNaPos(tipo, tx, ty))
			return true;
	}

	return false;
}

ObjetoTile *TileMap::getObjeto(string nome)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTile *obj = camadas_objetos[i]->getObjeto(nome);
		if(obj)
			return obj;
	}

	return NULL;
}

ObjetoTile *TileMap::getObjetoNaPos(Vetor2D pos)
{
	return getObjetoNaPos(pos.x, pos.y);
}

ObjetoTile *TileMap::getObjetoNaPos(float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTile *obj = camadas_objetos[i]->getObjetoNaPos(tx, ty);
		if(obj)
			return obj;
	}

	return NULL;
}

ObjetoTile *TileMap::getObjetoDoTipoNaPos(string tipo, Vetor2D pos)
{
	return getObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

ObjetoTile *TileMap::getObjetoDoTipoNaPos(string tipo, float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTile *obj = camadas_objetos[i]->getObjetoDoTipoNaPos(tipo, tx, ty);
		if(obj)
			return obj;
	}

	return NULL;
}

vector<ObjetoTile*> TileMap::getObjetosDoTipo(string tipo)
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getObjetosDoTipo(tipo);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTile*> TileMap::getObjetosNaPos(Vetor2D pos)
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getObjetosNaPos(pos);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTile*> TileMap::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getObjetosNaPos(tx, ty);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTile*> TileMap::getObjetosDoTipoNaPos(string tipo, Vetor2D pos)
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getObjetosDoTipoNaPos(tipo, pos);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTile*> TileMap::getObjetosDoTipoNaPos(string tipo, float tx, float ty)
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getObjetosDoTipoNaPos(tipo, tx, ty);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTile*> TileMap::getTodosObjetos()
{
	vector<ObjetoTile*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTile*> v = camadas_objetos[i]->getTodosObjetos();
		r.insert(r.end(), v.begin(), v.end());
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

bool TileMap::juntarCamadasDeObjetos(int indice_camada1, int indice_camada2)
{
	if(indice_camada1 == indice_camada2)
		return false;

	CamadaDeObjetos *camada1 = camadas_objetos[indice_camada1];
	CamadaDeObjetos *camada2 = camadas_objetos[indice_camada2];
	for(unsigned int i = 0; i < camada2->getNumObjetos(); ++i)
	{
		ObjetoTile *obj = camada1->criarObjeto();

		*obj = *camada2->getObjeto(i);
		obj->setCamada(camada1);
	}

	camada2->destruirTodosObjetos();
	delete camada2;
	camadas_objetos.erase(camadas_objetos.begin() + indice_camada2);

	return true;
}

bool TileMap::juntarCamadasDeObjetos(string nome_camada1, string nome_camada2)
{
	if(nome_camada1 == nome_camada2)
		return false;

	int i1, i2;
	i1 = i2 = -1;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
		if(nome_camada1 == camadas_objetos[i]->getNome())
			i1 = i;

	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
		if(nome_camada2 == camadas_objetos[i]->getNome())
			i2 = i;

	if(i1 == -1 || i2 == -1)
		return false;

	return juntarCamadasDeObjetos(i1, i2);
}

void TileMap::juntarTodasCamadasDeObjetos()
{
	for(unsigned int i = camadas_objetos.size()-1; i > 0; --i)
	{
		CamadaDeObjetos *camada2 = camadas_objetos[i];
		for(unsigned int j = 0; j < camada2->getNumObjetos(); ++j)
		{
			ObjetoTile *obj = camadas_objetos[0]->criarObjeto();

			*obj = *camada2->getObjeto(j);
			obj->setCamada(camadas_objetos[0]);
		}

		camada2->destruirTodosObjetos();
		delete camada2;
		camadas_objetos.erase(camadas_objetos.begin() + i);
	}
}

void TileMap::desenharTileNoPixel(int id, float px, float py)
{
	TileSet *tileset = tiles[id-1].getTileSet();

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

	SDL_Texture *tex = tileset->getTextura();

    //	Draw the texture
	SDL_RenderCopyEx(sdl_renderer, tex, &clip, &rect, 0, &pivot, SDL_FLIP_NONE);
}

void TileMap::prepararRenderQueues()
{
	vector<ObjetoTile*> *render_queue;

	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(!camadas_objetos[i]->estaVisivel())
			continue;

		vector<ObjetoTile*> objs = camadas_objetos[i]->getTodosObjetos();
		unsigned int size = objs.size();
		unsigned int menor;

		switch(camadas_objetos[i]->getNivel())
		{
		case ABAIXO_DOS_OBJETOS:
			render_queue = &render_queue_abaixo;
			menor = render_queue->size();
			break;

		case ACIMA_DOS_OBJETOS:
			render_queue = &render_queue_acima;
			menor = render_queue->size();
			break;

		case NO_NIVEL_DOS_OBJETOS:
		default:
			render_queue = &render_queue_aomeio;
			menor = 0;
		}

		for(unsigned int j = 0; j < size; ++j)
		{
			if(objs[j]->estaVisivel() && objs[j]->getSprite())
				quicksortObjetosTile(render_queue, objs[j], menor, render_queue->size());
		}
	}
}

void TileMap::limparRenderQueues()
{
	render_queue_abaixo.clear();
	render_queue_aomeio.clear();
	render_queue_acima.clear();
}

void TileMap::quicksortObjetosTile(vector<ObjetoTile*> *queue, ObjetoTile *o, unsigned int menor, unsigned int maior)
{
	if(menor == maior)
	{
		queue->insert(queue->begin() + menor, o);
		return;
	}
	else
	{
		unsigned int meio = menor + ((maior-menor)/2);
		ObjetoTile *o_meio = (*queue)[meio];

		if(o->getYCentro() < o_meio->getYCentro())
		{
			quicksortObjetosTile(queue, o, menor, meio);
		}
		else
		{
			quicksortObjetosTile(queue, o, meio+1, maior);
		}
	}
}