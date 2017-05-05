#include "TileMap.h"
#include "uniFuncoesPrincipais.h"
#include "uniSistemaDeArquivos.h"
#include "Global.h"
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

	finalRenderQueueAbaixo = -1;
	finalRenderQueueAoMeio = -1;

	carregou = false;
}

TileMap::~TileMap()
{
	if(estaCarregado())
	{
		descarregar();
	}
}

bool TileMap::carregar(const string& arquivo)
{
	if(!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if(estaCarregado())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois TileMap ja carregou algum arquivo.");
		return false;
	}

	//	Abrir o arquivo 
	SDL_RWops *ifs = SDL_RWFromFile(arquivo.c_str(), "rb");
	if(!ifs)
	{
		gDebug.erro("Erro ao abrir arquivo '" + arquivo + "'. Talvez o arquivo nao exista.");
		return false;
	}

	unsigned int tamanho_arquivo_em_bytes = ifs->size(ifs);
	char *bytes_do_arquivo = new char[tamanho_arquivo_em_bytes];
	ifs->read(ifs, bytes_do_arquivo, tamanho_arquivo_em_bytes, 1);
	ifs->close(ifs);

	//	Fazer o parse do arquivo
	Json::Value root;
	Json::Reader reader;
	if(!reader.parse(bytes_do_arquivo, bytes_do_arquivo + tamanho_arquivo_em_bytes, root, false))
	{
		gDebug.erro("Erro ao fazer o parse do arquivo '" + arquivo + "'.");
		delete[] bytes_do_arquivo;
		return false;
	}

	//	pegar informacoes basicas
	largura_em_tiles = root.get("width", 0).asInt();
	altura_em_tiles = root.get("height", 0).asInt();

	largura_tile= root.get("tilewidth", 0).asInt();
	altura_tile= root.get("tileheight", 0).asInt();

	// posicionar tile (0, 0) no canto superior esquerdo da tela e centralizar o mapa, caso ele caiba inteiro na tela
	if(largura_em_tiles*largura_tile < gJanela.getLargura())
		desloc_x = ((float)(gJanela.getLargura())/(float)(largura_tile) - (float)(largura_em_tiles))/2.0f;

	if(altura_em_tiles*altura_tile < gJanela.getAltura())
		desloc_y = ((float)(gJanela.getAltura())/(float)(altura_tile) - (float)(altura_em_tiles))/2.0f;

	x = 0.0f;
	y = 0.0f;

	//	carregar propriedades do mapa
	Json::Value props = root.get("properties", -1);
	if (!props.isInt())
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

		arq = acharCaminhoTileSet(arq, arquivo);

		if(!tilesets[i].carregar(arq, tlarg, talt))
		{
			tilesets.clear();
			delete[] bytes_do_arquivo;
			return false;
		}

		tilesets[i].setPrimeiroIDGlobal(tsets[i].get("firstgid", -1).asInt());
		tilesets[i].setNome(tsets[i].get("name", "").asString());

		//	guarda nome do arquivo de configuracao do tileset
		//	e ignora todas as outras propriedades
		Json::Value props = tsets[i].get("properties", -1);
		if(!props.isInt())
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
		if(!tilesets_config[i].empty())
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

		camadas_objetos[l] = new CamadaDeObjetosTileMap;

		camadas_objetos[l]->setTileMap(this);
		camadas_objetos[l]->setNome(jLayers[i].get("name", "").asString());
		camadas_objetos[l]->setVisivel(jLayers[i].get("visible", true).asBool());

		/*Json::Value props = jLayers[i].get("properties", -1);
		if(!props.isInt())
			for(unsigned int p = 0; p < props.getMemberNames().size(); ++p)
			{
				string nome = props.getMemberNames()[p];
				string valor = props.get(nome, "").toStyledString();//.asString();
			}
			*/
		objs = jLayers[i]["objects"];
		for(unsigned int j = 0; j < objs.size(); ++j)
		{
			ObjetoTileMap* o = camadas_objetos[l]->criarObjeto();
			o->setNome(objs[j].get("name", "").asString());
			o->setTipo(objs[j].get("type", "").asString());

			o->setPos(objs[j].get("x", 0).asFloat()/(float)largura_tile, objs[j].get("y", 0).asFloat()/(float)altura_tile);
			o->setTamanho(objs[j].get("width", 0).asFloat()/(float)largura_tile, objs[j].get("height", 0).asFloat()/(float)altura_tile);

			o->setVisivel(objs[j].get("visible", true).asBool());

			props = objs[j].get("properties", -1);
			if (!props.isInt())
				for(unsigned int i = 0; i < props.getMemberNames().size(); ++i)
				{
					string nome = props.getMemberNames()[i];
					string valor = props.get(nome, "").toStyledString();//.asString();

					if (nome == "nivel")
					{
						int nivel = atoi(valor.c_str());
						if (nivel < ABAIXO_DOS_OBJETOS || nivel > ACIMA_DOS_OBJETOS)
							nivel = NO_NIVEL_DOS_OBJETOS;
						o->setNivel((NivelTile)nivel);
					}
					else
						o->setPropriedade(nome, valor);
				}

		}

		++l;
	}

	delete[] bytes_do_arquivo;
	carregou = true;
	return true;
}

bool TileMap::carregarConfigTileSet(TileSet* tileset, const string& arquivo)
{
	SDL_RWops *file = SDL_RWFromFile(arquivo.c_str(), "r");
	if(!file)
	{
		gDebug.erro("Erro ao abrir arquivo '" + arquivo + "'. Talvez o arquivo nao exista.");
		return false;
	}

	unsigned int tamanho_arquivo_em_bytes = file->size(file);
	char *bytes_do_arquivo = new char[tamanho_arquivo_em_bytes];
	file->read(file, bytes_do_arquivo, tamanho_arquivo_em_bytes, 1);
	file->close(file);
	
	stringstream stream(bytes_do_arquivo);
	delete[] bytes_do_arquivo;

	string nome_arquivo;
	int larg_tile, alt_tile;

	stream >> nome_arquivo;
	stream >> larg_tile >> alt_tile;

	if(larg_tile != tileset->getLarguraTiles() || alt_tile != tileset->getAlturaTiles())
		return false;

	int tiles_x = tileset->getNumTilesX();
	int tiles_y = tileset->getNumTilesY();

	string marcador;
	int num;
	bool b;

	//	caminhavel
	do stream >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			stream >> b;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setCaminhavel(b);
		}

	//	profundidade
	do stream >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			stream >> num;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setNivel((NivelTile)num);
		}

	//	custo adicional
	do stream >> marcador;
	while(marcador != "*");

	for(int j = 0; j < tiles_y; ++j)
		for(int i = 0; i < tiles_x; ++i)
		{
			stream >> num;
			tiles[tileset->getPrimeiroIDGlobal()-1 + i + j*tiles_x].setCustoAdicional(num);
		}

	return true;
}

bool TileMap::carregarConfigTileSet(const string& nome_tileset, const string& arquivo)
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

	limparRenderQueue();
	objetosDesenhaveis.clear();

	carregou = false;
}

bool TileMap::estaCarregado()
{
	return carregou;
}

void TileMap::desenhar()
{
	float tiles_na_tela_x = (float)(gJanela.getLargura())/(float)largura_tile;
	float tiles_na_tela_y = (float)(gJanela.getAltura())/(float)altura_tile;

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
	prepararRenderQueue();

		//	objetos que estao abaixo dos outros
	for(int i = 0; i <= finalRenderQueueAbaixo; ++i)
	{
		float xo, yo;
		int pxo, pyo;
		renderQueueObjetos[i]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		renderQueueObjetos[i]->desenhar(pxo, pyo);
	}

		//	objetos que estao no meio e tiles que estao no nivel dos objetos
	int prox_obj = finalRenderQueueAbaixo + 1;
	int py = py0;
	for(int j = ity; j <= fty; ++j, py += altura_tile)
	{
		//	objetos nesta linha (ou antes dela)
		for(int o = prox_obj; o <= finalRenderQueueAoMeio; ++o)
		{
			float xo, yo;
			int pxo, pyo;
			renderQueueObjetos[o]->obterPosCentro(xo, yo);
			tileParaTela(xo, yo, pxo, pyo);

			if(pyo <= py+altura_tile)
			{
				renderQueueObjetos[o]->desenhar(pxo, pyo);
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
	for(int o = prox_obj; o <= finalRenderQueueAoMeio; ++o)
	{
		float xo, yo;
		int pxo, pyo;
		renderQueueObjetos[o]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		renderQueueObjetos[o]->desenhar(pxo, pyo);
	}

		//	objetos que estao acima dos outros
	for(unsigned int i = finalRenderQueueAoMeio + 1; i < renderQueueObjetos.size(); ++i)
	{
		float xo, yo;
		int pxo, pyo;
		renderQueueObjetos[i]->obterPosCentro(xo, yo);
		tileParaTela(xo, yo, pxo, pyo);
		renderQueueObjetos[i]->desenhar(pxo, pyo);
	}

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

	//	se todos tiles tem o mesmo tamanho, retorna verdadeiro
	if (maior_largura_tile == largura_tile && maior_altura_tile == altura_tile)	
		return true;

	//	calcula dif de tamanho entre os tiles
	int dx = maior_largura_tile/largura_tile;
	int dy = maior_altura_tile/altura_tile;

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

bool TileMap::retanguloECaminhavel(float tx, float ty, float larg, float alt)
{
	//	se esta fora da tela (retorna falso)
	if (tx + larg < 0 || tx >= largura_em_tiles || ty + alt < 0 || ty >= altura_em_tiles)
		return false;

	//	se o tamanho excede o mapa, remove o excesso
	if (tx + larg > largura_em_tiles)
		larg -= (tx + larg) - largura_em_tiles;
	else if (ty + alt > altura_em_tiles)
		alt -= (ty + alt) - altura_em_tiles;

	//	se a posicao (esqcima) esta excede o mapa, remove o excesso
	if (tx < 0)
	{
		larg -= fabsf(tx);
		tx = 0.0f;
	}
	if (ty < 0)
	{
		alt -= fabsf(ty);
		ty = 0.0f;
	}
		
	// calc tiles no retangulo
	int tx0 = tx;
	int ty0 = ty;
	int tx1 = tx + (larg - 0.01f);	//	hack (-0.01f) para não testar o próximo tile
	int ty1 = ty + (alt  - 0.01f);	//	hack (-0.01f) para não testar o próximo tile

	//	pra cada tile no retangulo
	for (int i = tx0; i <= tx1; ++i)
	{
		for (int j = ty0; j <= ty1; ++j)
		{
			// testa em cada uma das camadas de tiles
			for (unsigned int l = 0; l < camadas_tiles.size(); ++l)
			{
				int id = camadas_tiles[l].getIDdoTile(i, j);
				if (id < 1)
					continue;

				if (!tiles[id - 1].eCaminhavel())
					return false;
			}
		}
	}

	//	se todos tiles tem o mesmo tamanho, retorna verdadeiro
	if (maior_largura_tile == largura_tile && maior_altura_tile == altura_tile)
		return true;

	//	calcula dif de tamanho entre os tiles,
	//	para testar também os tiles de tamanho diferentes (maiores)
	int dx = maior_largura_tile / largura_tile;
	int dy = maior_altura_tile / altura_tile;
	
	//	testa tiles com tamanho diferente
	for (int i = 0; i <= dx; ++i)
		for (int j = 0; j <= dy; ++j)
		{
			if (i + j == 0)
				continue;

			// testa em cada uma das camadas de tiles
			for (unsigned int l = 0; l < camadas_tiles.size(); ++l)
			{
				//	testa na ultima linha
				for (int txx = tx0; txx <= tx1; ++txx)
				{
					if ((txx - i < 0) || (ty1 + j >= altura_em_tiles))
						continue;

					int id = camadas_tiles[l].getIDdoTile(txx - i, ty1 + j);
					if (id < 1)
						continue;

					TileSet* tileset = tiles[id - 1].getTileSet();
					if (tileset->getLarguraTiles() / largura_tile > i && tileset->getAlturaTiles() / altura_tile > j)
						if (!tiles[id - 1].eCaminhavel())
							return false;
				}

				// testa na primeira coluna
				for (int tyy = ty0; tyy <= ty1; ++tyy)
				{
					if ((tx0 - i < 0) || (tyy + j >= altura_em_tiles))
						continue;

					int id = camadas_tiles[l].getIDdoTile(tx0 - i, tyy + j);
					if (id < 1)
						continue;

					TileSet* tileset = tiles[id - 1].getTileSet();
					if (tileset->getLarguraTiles() / largura_tile > i && tileset->getAlturaTiles() / altura_tile > j)
						if (!tiles[id - 1].eCaminhavel())
							return false;
				}
			}		
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

void TileMap::adicionarObjetoNaRenderQueue(ObjetoTileMap* obj)
{
	objetosDesenhaveis.push_back(obj);
}

void TileMap::removerObjetoDaRenderQueue(ObjetoTileMap* obj)
{
	vector<ObjetoTileMap*>::iterator it;
	unsigned int size = objetosDesenhaveis.size();
	for(int i = 0; i < size; ++i)
		if (objetosDesenhaveis[i] == obj)
		{
			//	troca de lugar com o último
			objetosDesenhaveis[i] = objetosDesenhaveis[size - 1];
			//	remove o último
			objetosDesenhaveis.pop_back();
			return;
		}
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
	float tiles_na_tela_em_x = (float)(gJanela.getLargura())/(float)(largura_tile);

	if(tiles_na_tela_em_x > largura_em_tiles)
		tiles_na_tela_em_x = largura_em_tiles;

	return tiles_na_tela_em_x;
}

int TileMap::getNumTilesNaTelaEmY()
{
	float tiles_na_tela_em_y = (float)(gJanela.getAltura())/(float)(altura_tile);

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

CamadaDeObjetosTileMap *TileMap::criarCamadaDeObjetos(const string& nome)
{
	CamadaDeObjetosTileMap* camada = new CamadaDeObjetosTileMap();
	camada->setNome(nome);
	camada->setTileMap(this);
	camada->setVisivel(true);
	camadas_objetos.push_back(camada);
	return camada;
}

bool TileMap::destruirCamadaDeObjetos(int indice)
{
	if (indice < 0 || indice >= camadas_objetos.size())
		return false;

	camadas_objetos.erase(camadas_objetos.begin() + indice);
	return true;
}

bool TileMap::destruirCamadaDeObjetos(const string& nome)
{
	for (int i = 0; i < camadas_objetos.size(); ++i)
	{
		if (camadas_objetos[i]->getNome() == nome)
		{
			return destruirCamadaDeObjetos(i);
		}
	}
	return false;
}

CamadaDeObjetosTileMap *TileMap::getCamadaDeObjetos(int indice)
{
	return camadas_objetos[indice];
}

CamadaDeObjetosTileMap *TileMap::getCamadaDeObjetos(const string& nome)
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

CamadaDeTiles *TileMap::getCamadaDeTiles(const string& nome)
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

TileSet *TileMap::getTileSet(const string& nome)
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

Tile *TileMap::getTile(const Vetor2D& pos, int indice_camada)
{
	return getTile(pos.x, pos.y, indice_camada);
}

Tile *TileMap::getTile(const Vetor2D& pos, const string& nome_camada)
{
	return getTile(pos.x, pos.y, nome_camada);
}

Tile *TileMap::getTile(int tx, int ty, int indice_camada)
{
	return &tiles[camadas_tiles[indice_camada].getIDdoTile(tx, ty)];
}

Tile *TileMap::getTile(int tx, int ty, const string& nome_camada)
{
	return &tiles[getCamadaDeTiles(nome_camada)->getIDdoTile(tx, ty)];
}

bool TileMap::existeObjetoNaPos(const Vetor2D& pos)
{
	return existeObjetoNaPos(pos.x, pos.y);
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

bool TileMap::existeObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	return existeObjetoNoRetangulo(pos.x, pos.y, tamanho.x, tamanho.y);
}

bool TileMap::existeObjetoNoRetangulo(float tx, float ty, float larg, float alt)
{
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if (camadas_objetos[i]->existeObjetoNoRetangulo(tx, ty, larg, alt))
			return true;
	}

	return false;
}

bool TileMap::existeObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	return existeObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

bool TileMap::existeObjetoDoTipoNaPos(const string& tipo, float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if(camadas_objetos[i]->existeObjetoDoTipoNaPos(tipo, tx, ty))
			return true;
	}

	return false;
}

bool TileMap::existeObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	return existeObjetoDoTipoNoRetangulo(tipo, pos.x, pos.y, tamanho.x, tamanho.y);
}

bool TileMap::existeObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		if (camadas_objetos[i]->existeObjetoDoTipoNoRetangulo(tipo, tx, ty, larg, alt))
			return true;
	}

	return false;
}

ObjetoTileMap *TileMap::getObjeto(const string& nome)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTileMap *obj = camadas_objetos[i]->getObjeto(nome);
		if(obj)
			return obj;
	}

	return NULL;
}

ObjetoTileMap *TileMap::getObjetoNaPos(const Vetor2D& pos)
{
	return getObjetoNaPos(pos.x, pos.y);
}

ObjetoTileMap *TileMap::getObjetoNaPos(float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTileMap *obj = camadas_objetos[i]->getObjetoNaPos(tx, ty);
		if(obj)
			return obj;
	}

	return NULL;
}

ObjetoTileMap *TileMap::getObjetoNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	return getObjetoNoRetangulo(pos.x, pos.y, tamanho.x, tamanho.y);
}

ObjetoTileMap *TileMap::getObjetoNoRetangulo(float tx, float ty, float larg, float alt)
{
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTileMap *obj = camadas_objetos[i]->getObjetoNoRetangulo(tx, ty, larg, alt);
		if (obj)
			return obj;
	}

	return NULL;
}

ObjetoTileMap *TileMap::getObjetoDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	return getObjetoDoTipoNaPos(tipo, pos.x, pos.y);
}

ObjetoTileMap *TileMap::getObjetoDoTipoNaPos(const string& tipo, float tx, float ty)
{
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTileMap *obj = camadas_objetos[i]->getObjetoDoTipoNaPos(tipo, tx, ty);
		if(obj)
			return obj;
	}

	return NULL;
}

ObjetoTileMap *TileMap::getObjetoDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	return getObjetoDoTipoNoRetangulo(tipo, pos.x, pos.y, tamanho.x, tamanho.y);
}

ObjetoTileMap *TileMap::getObjetoDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		ObjetoTileMap *obj = camadas_objetos[i]->getObjetoDoTipoNoRetangulo(tipo, tx, ty, larg, alt);
		if (obj)
			return obj;
	}

	return NULL;
}

vector<ObjetoTileMap*> TileMap::getObjetosDoTipo(const string& tipo)
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosDoTipo(tipo);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosNaPos(const Vetor2D& pos)
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosNaPos(pos);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosNaPos(float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosNaPos(tx, ty);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosNoRetangulo(const Vetor2D& pos, const Vetor2D& tamanho)
{
	vector<ObjetoTileMap*> r;
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosNoRetangulo(pos, tamanho);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosNoRetangulo(float tx, float ty, float larg, float alt)
{
	vector<ObjetoTileMap*> r;
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosNoRetangulo(tx, ty, larg, alt);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosDoTipoNaPos(const string& tipo, const Vetor2D& pos)
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosDoTipoNaPos(tipo, pos);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosDoTipoNaPos(const string& tipo, float tx, float ty)
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosDoTipoNaPos(tipo, tx, ty);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosDoTipoNoRetangulo(const string& tipo, const Vetor2D& pos, const Vetor2D& tamanho)
{
	vector<ObjetoTileMap*> r;
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosDoTipoNoRetangulo(tipo, pos, tamanho);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getObjetosDoTipoNoRetangulo(const string& tipo, float tx, float ty, float larg, float alt)
{
	vector<ObjetoTileMap*> r;
	for (unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getObjetosDoTipoNoRetangulo(tipo, tx, ty, larg, alt);
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

vector<ObjetoTileMap*> TileMap::getTodosObjetos()
{
	vector<ObjetoTileMap*> r;
	for(unsigned int i = 0; i < camadas_objetos.size(); ++i)
	{
		vector<ObjetoTileMap*> v = camadas_objetos[i]->getTodosObjetos();
		r.insert(r.end(), v.begin(), v.end());
	}
	return r;
}

string TileMap::getPropriedade(const string& nome)
{
	map<string, string>::iterator it = propriedades.find(nome);
	if(it != propriedades.end())
		return it->second;

	return "";
}

int TileMap::getPropriedadeInt(const string& nome)
{
	stringstream ss(getPropriedade(nome));
	int r;
	ss >> r;
	return r;
}

float TileMap::getPropriedadeFloat(const string& nome)
{
	stringstream ss(getPropriedade(nome));
	float r;
	ss >> r;
	return r;
}

bool TileMap::getPropriedadeBool(const string& nome)
{
	string s = getPropriedade(nome);

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

void TileMap::setPropriedade(const string& nome, const string& valor)
{
	map<string, string>::iterator it = propriedades.find(nome);
	if(it != propriedades.end())
		it->second = valor;
	else
		propriedades.insert(pair<string, string>(nome, valor));
}

void TileMap::setPropriedadeInt(const string& nome, int valor)
{
	stringstream ss;
	ss << valor;
	setPropriedade(nome, ss.str());
}

void TileMap::setPropriedadeFloat(const string& nome, float valor)
{
	stringstream ss;
	ss << valor;
	setPropriedade(nome, ss.str());
}

void TileMap::setPropriedadeBool(const string& nome, bool valor)
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

	CamadaDeObjetosTileMap *camada1 = camadas_objetos[indice_camada1];
	CamadaDeObjetosTileMap *camada2 = camadas_objetos[indice_camada2];
	for(unsigned int i = 0; i < camada2->getNumObjetos(); ++i)
	{
		ObjetoTileMap *obj = camada1->criarObjeto();

		*obj = *camada2->getObjeto(i);
		obj->setCamada(camada1);
	}

	camada2->destruirTodosObjetos();
	delete camada2;
	camadas_objetos.erase(camadas_objetos.begin() + indice_camada2);

	return true;
}

bool TileMap::juntarCamadasDeObjetos(const string& nome_camada1, const string& nome_camada2)
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
		CamadaDeObjetosTileMap *camada2 = camadas_objetos[i];
		for(unsigned int j = 0; j < camada2->getNumObjetos(); ++j)
		{
			ObjetoTileMap *obj = camadas_objetos[0]->criarObjeto();

			*obj = *camada2->getObjeto(j);
			obj->setCamada(camadas_objetos[0]);
		}

		camada2->destruirTodosObjetos();
		delete camada2;
		camadas_objetos.erase(camadas_objetos.begin() + i);
	}
}

string TileMap::acharCaminhoTileSet(const string& caminhoOriginal, const string& caminhoTilemap)
{
	SDL_RWops *file = SDL_RWFromFile(caminhoOriginal.c_str(), "rb");
	if (file)
	{
		file->close(file);
		return caminhoOriginal;
	}

	string nome = uniGetNomeEExtencaoDoArquivo(caminhoTilemap);
	string pasta = caminhoTilemap.substr(0, caminhoTilemap.size() - nome.size());
	string caminho = pasta + caminhoOriginal;
	file = SDL_RWFromFile(caminho.c_str(), "rb");
	if (file)
	{
		file->close(file);
		return caminho;
	}

	return caminhoOriginal;
}

void TileMap::desenharTileNoPixel(int id, float px, float py)
{
	TileSet *tileset = tiles[id-1].getTileSet();

	Quad retan;
	retan.larg = tileset->getLarguraTiles();
	retan.alt = tileset->getAlturaTiles();
	retan.x = ((id - tileset->getPrimeiroIDGlobal()) % tileset->getNumTilesX())*retan.larg;
	retan.y = ((id - tileset->getPrimeiroIDGlobal()) / tileset->getNumTilesX())*retan.alt;

	Quad dest;
	dest.larg = retan.larg;
	dest.alt = retan.alt;

	SDL_Point pivot = { 0, dest.alt };	//	ancora igual ao Tiled Map editor (0, 1)

	dest.x = (px)-pivot.x;
	dest.y = (py + altura_tile) - pivot.y;	//	soma 1 tile na altura, pois altura 0 em deve ser no pixel 'altura_tile', para ficar igual a ancora do Tiled Map Editor

	gGraficos.desenharTextura(tileset->getTextura(), retan, dest, Cor(255, 255, 255, 255));
}

void TileMap::prepararRenderQueue()
{
	limparRenderQueue();
	unsigned int size = objetosDesenhaveis.size();
	int menor, maior;
	for (unsigned int j = 0; j < size; ++j)
	{
		ObjetoTileMap* obj = objetosDesenhaveis[j];
		CamadaDeObjetosTileMap* c = obj->getCamada();
		if (c->estaVisivel())
		{
			switch (obj->getNivel())
			{
			case ABAIXO_DOS_OBJETOS:
				menor = 0;
				maior = finalRenderQueueAbaixo + 1;
				finalRenderQueueAbaixo++;
				finalRenderQueueAoMeio++;
				break;

			case ACIMA_DOS_OBJETOS:
				menor = finalRenderQueueAoMeio + 1;
				maior = renderQueueObjetos.size();
				break;

			case NO_NIVEL_DOS_OBJETOS:
			default:
				menor = finalRenderQueueAbaixo + 1;
				maior = finalRenderQueueAoMeio + 1;
				finalRenderQueueAoMeio++;
			}
		}
		quicksortObjetosTileMap(obj, menor, maior);
	}

}

void TileMap::limparRenderQueue()
{
	renderQueueObjetos.clear();
	finalRenderQueueAbaixo = -1;
	finalRenderQueueAoMeio = -1;
}

void TileMap::quicksortObjetosTileMap(ObjetoTileMap *o, int menor, int maior)
{
	if (menor >= maior)
	{
		if (menor > maior)
			menor = maior;
		if (menor < 0)
			menor = 0;

		renderQueueObjetos.insert(renderQueueObjetos.begin() + menor, o);
		return;
	}
	else
	{
		unsigned int meio = menor + ((maior - menor) / 2);
		ObjetoTileMap *o_meio = renderQueueObjetos[meio];

		if (o->getYCentro() < o_meio->getYCentro())
		{
			quicksortObjetosTileMap(o, menor, meio);
		}
		else
		{
			quicksortObjetosTileMap(o, meio + 1, maior);
		}
	}
}