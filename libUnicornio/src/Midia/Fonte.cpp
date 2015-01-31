#include "Fonte.h"
#include "libUnicornio.h"

Fonte::Fonte()
{
	carregada = false;
	carregada_da_memoria = false;
	font = NULL;
	estilo = FONTE_ESTILO_NORMAL;
	largura_max_glifo = 0;
	altura_max_glifo = 0;
	altura_max_acima_da_base = 0;
	altura_max_abaixo_da_base = 0;
	monoespacada = false;
}

Fonte::~Fonte()
{
}

bool Fonte::carregar(string arquivo, int tamanho, int estilo)
{
	if(!uni_init) 
	{
		uniErro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}
	
	if(estaCarregada())
	{
		uniErro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Fonte ja carregou o arquivo " + caminho_arquivo + ".");
		return false;
	}
	
	font = TTF_OpenFont(arquivo.c_str(), tamanho);
	if(!font) 
	{
		uniErro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	caminho_arquivo = arquivo;

	this->estilo = estilo;
	TTF_SetFontStyle(font, estilo);

	monoespacada = TTF_FontFaceIsFixedWidth(font) > 0;

	largura_max_glifo = tamanho;
	altura_max_glifo = TTF_FontHeight(font);
	altura_max_acima_da_base = TTF_FontAscent(font);
	altura_max_abaixo_da_base = -TTF_FontDescent(font);

	carregada = criarGlifoNulo();

	carregada_da_memoria = false;
	return carregada;
}

bool Fonte::carregarMem(unsigned char mem[], int tamanho_mem, int tamanho, int estilo)
{
	if(!uni_init) return false;

	SDL_RWops* rwops = SDL_RWFromMem((void*)mem,tamanho_mem);
	//SDL_RWops* rwops = SDL_RWFromConstMem((const void*)mem,memsize);
	if(!rwops)
	{
		uniErro("Erro ao carregar fonte da memoria.");
		return false;
	}

	font = TTF_OpenFontIndexRW(rwops,1,tamanho,0);
	if(!estaCarregada()) 
	{
		uniErro("Erro ao carregar fonte da memoria.");
		return false;
	}

	caminho_arquivo = "";

	this->estilo = estilo;
	TTF_SetFontStyle(font, estilo);

	monoespacada = TTF_FontFaceIsFixedWidth(font) > 0;

	largura_max_glifo = tamanho;
	altura_max_glifo = TTF_FontHeight(font);
	altura_max_acima_da_base = TTF_FontAscent(font);
	altura_max_abaixo_da_base = -TTF_FontDescent(font);

	carregada = criarGlifoNulo();

	carregada_da_memoria = carregada;
	return carregada;
}

void Fonte::descarregar()
{
	if(carregada)
	{
		map<Uint16, Glifo*>::iterator it;
		for(it = mapa_glifos.begin(); it != mapa_glifos.end(); ++it)
		{
			SDL_DestroyTexture(it->second->sdl_tex);
		}
		mapa_glifos.clear();

		TTF_CloseFont(font);
		font = NULL;
	}

	caminho_arquivo = "";
	estilo = FONTE_ESTILO_NORMAL;

	monoespacada = false;
	largura_max_glifo = 0;
	altura_max_glifo = 0;
	altura_max_acima_da_base = 0;
	altura_max_abaixo_da_base = 0;
}

bool Fonte::estaCarregada()
{
	return carregada;
}

void Fonte::preCarregarGlifos(string caracteres)
{
	map<Uint16, Glifo *>::iterator it;
	for(unsigned int i = 0; i < caracteres.size(); ++i)
	{
		it = mapa_glifos.find(caracteres[i]);

		if(it == mapa_glifos.end())
		{
			Glifo *glifo;
			criarGlifo((unsigned char)caracteres[i], glifo);
		}
	}
}

void Fonte::preCarregarGlifos(wstring caracteres)
{
	map<Uint16, Glifo *>::iterator it;
	for(unsigned int i = 0; i < caracteres.size(); ++i)
	{
		it = mapa_glifos.find(caracteres[i]);

		if(it == mapa_glifos.end())
		{
			Glifo *glifo;
			criarGlifo(caracteres[i], glifo);
		}
	}
}

void Fonte::preCarregarGlifos(Uint16 inicio, Uint16 fim)
{
	if(fim < inicio)
		return;

	map<Uint16, Glifo *>::iterator it;
	for(unsigned int i = inicio; i <= fim; ++i)
	{
		it = mapa_glifos.find(i);

		if(it == mapa_glifos.end())
		{
			Glifo *glifo;
			criarGlifo(i, glifo);
		}
	}
}

void Fonte::preCarregarGlifo(Uint16 caractere)
{
	map<Uint16, Glifo *>::iterator it = mapa_glifos.find(caractere);
	if(it == mapa_glifos.end())
	{
		Glifo *glifo;
		criarGlifo(caractere, glifo);
	}
}

bool Fonte::eMonoespacada()
{
	return monoespacada;
}

Glifo *Fonte::getGlifo(Uint16 ch)
{
	map<Uint16, Glifo *>::iterator it = mapa_glifos.find(ch);

	if(it == mapa_glifos.end())
	{
		if(TTF_GlyphIsProvided(font, ch))
		{
			Glifo *glifo;
			if(criarGlifo(ch, glifo))
			{
				return glifo;
			}
			else
			{
				it = mapa_glifos.find(0); 
			}
		}
		else
		{
			it = mapa_glifos.find(0);
		}
	}

	return it->second;
}

int Fonte::getNumGlifosUsados()
{
	return mapa_glifos.size();
}
	
int Fonte::getLarguraMaxDosGlifos()
{
	return largura_max_glifo;
}

int Fonte::getAlturaMaxDosGlifos()
{
	return altura_max_glifo;
}

int Fonte::getAlturaMaxDosGlifosAcimaDaBase()
{
	return altura_max_acima_da_base;
}

int Fonte::getAlturaMaxDosGlifosAbaixoDaBase()
{
	return altura_max_abaixo_da_base;
}

int Fonte::getTamanho()
{
	return largura_max_glifo;
}

int Fonte::getEstilo()
{
	return estilo;
}

TTF_Font *Fonte::getTTF_Font()
{
	return font;
}

string Fonte::getCaminhoDoArquivo()
{
	return caminho_arquivo;
}

Fonte Fonte::clonar()
{
	Fonte r(*this);
	if(!carregada_da_memoria)
	{
		r.carregar(caminho_arquivo, largura_max_glifo, estilo);
	}
	return r;
}

bool Fonte::criarGlifo(Uint16 ch, Glifo *&glifo)
{
	glifo = new Glifo;
	bool b = criarTexturaParaGlifo(ch, glifo->sdl_tex);

	if(!b)
	{
		delete glifo;
		return false;
	}

	int minx, miny, maxx, maxy;
	TTF_GlyphMetrics(font, ch, &minx, &maxx, &miny, &maxy, &glifo->avanco);
	glifo->larg = maxx - minx;
	glifo->alt = maxy - miny;
	glifo->alt_abaixo_da_base = -minx;
	glifo->alt_acima_da_base = maxy;
	glifo->caractere = ch;

	mapa_glifos.insert(std::pair<Uint16, Glifo *>(ch, glifo));

	return b;
}

bool Fonte::criarGlifoNulo()
{
	Glifo *nulo = new Glifo;

	nulo->sdl_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, largura_max_glifo, altura_max_glifo);
	SDL_SetTextureBlendMode(nulo->sdl_tex, SDL_BLENDMODE_BLEND);
	
	if(!nulo->sdl_tex)
	{
		delete nulo;
		return false;
	}

	TTF_GlyphMetrics(font, 0, NULL, NULL, NULL, NULL, &nulo->avanco);
	nulo->larg = largura_max_glifo;
	nulo->alt = altura_max_glifo;
	nulo->alt_abaixo_da_base = 0;
	nulo->alt_acima_da_base = altura_max_glifo;
	nulo->caractere = 0;

	mapa_glifos.insert(std::pair<Uint16, Glifo *>(0, nulo));

	return true;
}

bool Fonte::criarTexturaParaGlifo(int ch, SDL_Texture *&tex)
{
	uint32_t rmask, gmask, bmask, amask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	SDL_Color cor_glifo = {255, 255, 255, 255};
	SDL_Surface *surface = TTF_RenderGlyph_Blended(font, ch, cor_glifo);

	if(!surface)
	{
		uniErro("Erro ao criar glifo do arquivo: '" + caminho_arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");
	tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	SDL_FreeSurface(surface);

	return true;
}
