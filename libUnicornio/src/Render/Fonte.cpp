#include "Fonte.h"
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "SDL_ttf.h"

Fonte::Fonte()
{
	ttf = false;
	estilo = FONTE_ESTILO_NORMAL;
	larguraGlifos = 0;
	alturaGlifos = 0;
	ascent = 0;
	monoespacada = false;
}

Fonte::~Fonte()
{
}

bool Fonte::carregar(const string& arquivo, int tamanho, int estilo, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala)
{
	return carregarTrueType(arquivo, tamanho, estilo, primeiro_glifo, ultimo_glifo, qualidade_escala);
}

bool Fonte::carregar(const string& arquivo, const wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala)
{
	return carregarBitmap(arquivo, caracteres, num_glifos_x, num_glifos_y, qualidade_escala);
}

bool Fonte::carregar(const string& arquivo, const string& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala)
{
	wstring carac;
	unsigned int size = caracteres.size();
	carac.resize(size);
	for (unsigned int i = 0; i < size; ++i)
		carac[i] = (unsigned char)caracteres[i];

	return carregar(arquivo, carac, num_glifos_x, num_glifos_y, qualidade_escala);
}

bool Fonte::descarregar()
{
	if (tex.destruir())
	{
		glifos.clear();
		ttf = false;
		estilo = FONTE_ESTILO_NORMAL;
		larguraGlifos = 0;
		ascent = 0;
		alturaGlifos = 0;
		glifoNulo = Glifo();
		monoespacada = false;
		return true;
	}
	return false;
}

bool Fonte::estaCarregada()
{
	return tex.estaCriada();
}

bool Fonte::eMonoespacada()
{
	return monoespacada;
}

bool Fonte::eTrueType()
{
	return estaCarregada() && ttf;
}

bool Fonte::eBitmap()
{
	return estaCarregada() && !ttf;
}

Glifo* Fonte::getGlifo(Uint16 caractere)
{
	if (ttf)
	{ 
		if (caractere < glifos[0].caractere)
			return &glifoNulo;

		return &glifos[caractere - glifos[0].caractere];
	}

	//	quick search 
	unsigned int maior = glifos.size()-1;
	unsigned int menor = 0;
	bool terminou = false;
	while (!terminou)
	{
		unsigned int meio = menor + ((maior - menor) / 2);
		if(glifos[meio].caractere == caractere)
			return &glifos[meio];

		if (menor == maior)
			terminou = true;

		if (caractere < glifos[meio].caractere)
		{
			maior = meio;
		}
		else
		{
			menor = meio + 1;
		}
	}

	return &glifoNulo;
}

Glifo* Fonte::getGlifoPeloIndice(Uint16 indice)
{
	return &glifos[indice];
}

Glifo* Fonte::getGlifoNulo()
{
	return &glifoNulo;
}

int Fonte::getNumGlifosX()
{
	return numGlifosX;
}

int Fonte::getNumGlifosY()
{
	return numGlifosY;
}

int Fonte::getNumGlifos()
{
	return glifos.size();
}

int Fonte::getLarguraGlifos()
{
	return larguraGlifos;
}

int Fonte::getAlturaGlifos()
{
	return alturaGlifos;
}

int Fonte::getTamanho()
{
	return larguraGlifos;	//	o tamanho da fonte ttf eh igual a largura
}

int Fonte::getAscent()
{
	return ascent;
}

int Fonte::getEstilo()
{
	return estilo;
}

int Fonte::getQualidadeEscala()
{
	return tex.getQualidadeDeEscala();
}

Textura* Fonte::getTextura()
{
	return &tex;
}

SDL_Texture* Fonte::getSDL_Texture()
{
	return tex.getSDL_Texture();
}

string Fonte::getCaminhoDoArquivo()
{
	return tex.getCaminhoDoArquivo();
}

Fonte Fonte::clonar()
{
	Fonte r;
	r.tex.clonar();
	r.glifos = glifos;
	r.glifoNulo = glifoNulo;
	r.estilo = estilo;
	r.numGlifosX = numGlifosX;
	r.numGlifosY = numGlifosY;
	r.larguraGlifos = larguraGlifos;
	r.alturaGlifos = alturaGlifos;
	r.ascent = ascent;
	r.monoespacada = monoespacada;
	return r;
}

void Fonte::setCaracteres(const string& caracteres, bool unsigned_char)
{
	if(unsigned_char)
		for (unsigned int i = 0; i < glifos.size() && caracteres.size(); ++i)
			glifos[i].caractere = (unsigned char)caracteres[i];
	else
		for (unsigned int i = 0; i < glifos.size() && caracteres.size(); ++i)
			glifos[i].caractere = caracteres[i];
}

void Fonte::setCaracteres(const wstring& caracteres)
{
	for (unsigned int i = 0; i < glifos.size() && caracteres.size(); ++i)
	{
		glifos[i].caractere = caracteres[i];
	}
}

void Fonte::desenharGlifo(Uint16 caractere, Quad& destino, const Cor& cor)
{
	Glifo* g = getGlifo(caractere);
	destino.x += g->dx;
	float escala_y = destino.alt/(float)g->quad.alt;
	destino.y += (ascent - g->alturaAcimaDaBase)*escala_y;
	gGraficos.desenharTextura(&tex, g->quad, destino, cor);
}

void Fonte::desenharGlifo(Uint16 caractere, int x_esq, int y_cima, int x_texto, int y_texto, float rot_texto, const Vetor2D& escala_texto, const Cor& cor, EnumInverterDesenho inverter)
{
	Glifo* g = getGlifo(caractere);
	desenharGlifo(getGlifo(caractere), x_esq, y_cima, x_texto, y_texto, rot_texto, escala_texto, cor, inverter);
}

void Fonte::desenharGlifo(Glifo* glifo, int x_esq, int y_cima, int x_texto, int y_texto, float rot_texto, const Vetor2D& escala_texto, const Cor& cor, EnumInverterDesenho inverter)
{
	Quad destino;
	destino.larg = glifo->quad.larg*escala_texto.x;
	destino.alt = glifo->quad.alt*escala_texto.y;
	destino.x = x_esq + glifo->dx;
	destino.y = y_cima;
	destino.y += (ascent - glifo->alturaAcimaDaBase)*escala_texto.y;
	SDL_Point center = { x_texto - destino.x, y_texto - destino.y };
	gGraficos.desenharTextura(&tex, glifo->quad, destino, rot_texto, center.x, center.y, cor, inverter);
}

bool Fonte::carregarTrueType(const string& arquivo, int tamanho, int estilo, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala)
{
	if (!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if (estaCarregada())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Fonte ja carregou o arquivo " + tex.getCaminhoDoArquivo() + ".");
		return false;
	}

	TTF_Font* ttf_font = TTF_OpenFont(arquivo.c_str(), tamanho);
	if (!ttf_font)
	{
		gDebug.erro("Erro ao carregar arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	TTF_SetFontStyle(ttf_font, estilo);

	if (!criarTexturaTrueType(ttf_font, tamanho, primeiro_glifo, ultimo_glifo, qualidade_escala))
	{
		glifos.clear();
		gDebug.erro("Erro ao criar textura para fonte ttf, usando arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}
	glifoNulo.quad.x = 0;
	glifoNulo.quad.y = 0;
	glifoNulo.quad.larg = 0;
	glifoNulo.quad.alt = 0;
	glifoNulo.alturaAcimaDaBase = 0;
	glifoNulo.avanco = tamanho;
	glifoNulo.caractere = 0;

	this->estilo = estilo;
	monoespacada = TTF_FontFaceIsFixedWidth(ttf_font) > 0;

	larguraGlifos = tamanho;
	alturaGlifos = TTF_FontHeight(ttf_font);

	ttf = true;
	return true;
}

bool Fonte::carregarBitmap(const string& arquivo, const wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala)
{
	if (!uniEstaInicializada())
	{
		gDebug.erro("Sem uniInicializar() antes de tentar carregar: '" + arquivo + "'.");
		return false;
	}

	if (estaCarregada())
	{
		gDebug.erro("Arquivo '" + arquivo + "' nao pode ser carregado, pois Fonte ja carregou o arquivo " + tex.getCaminhoDoArquivo() + ".");
		return false;
	}

	if (caracteres.empty())
	{
		gDebug.erro("Fonte bitmap '" + arquivo + "' não pode ser carregada sem informar os caracteres usados.");
		return false;
	}

	if (!criarTexturaBitmap(arquivo, qualidade_escala))
	{
		glifos.clear();
		gDebug.erro("Erro ao criar textura para fonte bitmap, usando arquivo: '" + arquivo + "' - " + SDL_GetError() + ".");
		return false;
	}

	int larg, alt;
	tex.obterTamanho(larg, alt);
	larg /= num_glifos_x;
	alt /= num_glifos_y;
	ascent = alt;
	unsigned int size = num_glifos_x*num_glifos_y;
	if (caracteres.size() < size)
		size = caracteres.size();
	glifos.resize(size);
	for (unsigned int i = 0; i < size; ++i)
	{
		Glifo* g = &glifos[i];
		g->caractere = (Uint16)caracteres[i];
		g->quad.alt = alt;
		g->quad.larg = larg;
		g->avanco = larg;
		g->quad.x = (i % num_glifos_x)*larg;
		g->quad.y = (i / num_glifos_x)*alt;
		g->dx = 0;
		g->alturaAcimaDaBase = alt;
	}
	//	ordena caracteres para poder acessa-los mais facilmente
	for (unsigned int i = 0; i < size; ++i)
		for (unsigned int j = i + 1; j < size; ++j)
		{
			if (glifos[j].caractere < glifos[i].caractere)
			{
				Glifo temp = glifos[i];
				glifos[i] = glifos[j];
				glifos[j] = temp;
			}
		}
	glifoNulo.quad.x = 0;
	glifoNulo.quad.y = 0;
	glifoNulo.quad.larg = 0;
	glifoNulo.quad.alt = 0;
	glifoNulo.dx = 0;
	glifoNulo.alturaAcimaDaBase = 0;
	glifoNulo.avanco = larg;
	glifoNulo.caractere = 0;

	estilo = FONTE_ESTILO_NORMAL;
	monoespacada = true;
	numGlifosX = num_glifos_x;
	numGlifosY = num_glifos_y;
	larguraGlifos = glifos[0].quad.larg;
	alturaGlifos = glifos[0].quad.alt;

	ttf = false;
	return true;
}

bool Fonte::criarTexturaTrueType(TTF_Font* ttf_font, int tamanho, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala)
{
	ascent = TTF_FontAscent(ttf_font);

	int larg_glifo = tamanho;
	int alt_glifo = TTF_FontHeight(ttf_font);
	if (ultimo_glifo < primeiro_glifo)
		ultimo_glifo = primeiro_glifo;

	Uint16 num_glifos = ultimo_glifo - primeiro_glifo + 1;
	Uint16 glifos_por_linha = sqrt(num_glifos);
	if (glifos_por_linha*glifos_por_linha != num_glifos)
		glifos_por_linha++;
	Uint16 glifos_por_coluna = ceilf((float)num_glifos / (float)glifos_por_linha);
	int larg = glifos_por_linha*larg_glifo;
	int alt = glifos_por_coluna*alt_glifo;

	glifos.resize(num_glifos);

	Uint32 rmask, gmask, bmask, amask;
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

	SDL_Surface* surface = SDL_CreateRGBSurface(0, larg, alt, 32, rmask, gmask, bmask, amask);
	if (!surface)
	{
		return false;
	}
	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 0, 0, 0, 0));
	SDL_Color cor_glifo = { 255, 255, 255, 255 };
	SDL_Rect rect;

	Uint16 i_glifo = 0;
	Uint16 lin = 0, col = 0;
	Glifo* g;
	for (Uint16 i = primeiro_glifo; i <= ultimo_glifo; ++i)
	{
		g = &glifos[i_glifo];
		g->caractere = i;
		SDL_Surface* surface_glifo = TTF_RenderGlyph_Blended(ttf_font, g->caractere, cor_glifo);
		if (surface_glifo)
		{
			SDL_SetSurfaceBlendMode(surface_glifo, SDL_BLENDMODE_BLEND);
			rect.x = col*larg_glifo;
			rect.y = lin*alt_glifo;
			rect.w = surface_glifo->w;
			rect.h = surface_glifo->h;
			SDL_BlitSurface(surface_glifo, NULL, surface, &rect);
			SDL_FreeSurface(surface_glifo);

			int minx, miny, maxx, maxy, av;
			TTF_GlyphMetrics(ttf_font, g->caractere, &minx, &maxx, &miny, &maxy, &av);
			g->avanco = av;
			g->quad.x = (col*larg_glifo);
			g->quad.y = (lin*alt_glifo) + ascent - maxy;
			g->quad.larg = rect.w;
			g->quad.alt = maxy - miny;
			g->dx = minx;
			g->alturaAcimaDaBase = maxy;
		}
		else
		{
			g->avanco = tamanho;
			g->quad.x = 0;
			g->quad.y = 0;
			g->quad.larg = 0;
			g->quad.alt = 0;
			g->dx = 0;
			g->alturaAcimaDaBase = 0;
		}

		++i_glifo;
		++col;
		if (col == glifos_por_linha)
		{
			col = 0;
			++lin;
		}
	}

	bool r = tex.criarDaSDL_Surface(surface, qualidade_escala);
	SDL_FreeSurface(surface);

	if (r)
	{
		numGlifosX = glifos_por_linha;
		numGlifosY = glifos_por_coluna;
	}

	return r;
}

bool Fonte::criarTexturaBitmap(const string& arquivo, EnumQualidadeEscala qualidade_escala)
{
	return tex.criarDoArquivo(arquivo, qualidade_escala);
}