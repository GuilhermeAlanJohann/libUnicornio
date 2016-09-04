#include "Texto.h"
//#include "uniFuncoesPrincipais.h"
#include "Global.h"

Texto::Texto()
{
	fonte = NULL;
	largura = 0;
	altura = 0;
	ancora.set(0.5f, 0.5f);
	escala.set(1.0f, 1.0f);
	cor.r = 255;
	cor.g = 255;
	cor.b = 255;
	cor.a = 255;

	largura_max = 0;

	num_linhas = 0;
	espacamento_linhas = 1.0f;
	alinhamento = TEXTO_ALINHADO_A_ESQUERDA;
}

Texto::~Texto()
{
	apagar();
}

Vetor2D Texto::getAncora()
{
	return ancora;
}

float Texto::getAncoraX()
{
	return ancora.x;
}

float Texto::getAncoraY()
{
	return ancora.y;
}

Vetor2D Texto::getEscala()
{
	return escala;
}

float Texto::getEscalaX()
{
	return escala.x;
}

float Texto::getEscalaY()
{
	return escala.y;
}

int	Texto::getLargura()
{
	return largura*escala.x;
}

int Texto::getAltura()
{
	return altura*escala.y;
}

int	Texto::getLarguraOriginal()
{
	return largura;
}

int Texto::getAlturaOriginal()
{
	return altura;
}

int Texto::getLarguraMaxima()
{
	return largura_max;
}

Cor Texto::getCor()
{
	return cor;
}

int Texto::getCorVermelho()
{
	return cor.r;
}

int Texto::getCorVerde()
{
	return cor.g;
}

int Texto::getCorAzul()
{
	return cor.b;
}

int Texto::getCorAlpha()
{
	return cor.a;
}

int Texto::getNumLinhas()
{
	return num_linhas;
}

float Texto::getEspacamentoLinhas()
{
	return espacamento_linhas;
}

EnumAlinhamentoTexto Texto::getAlinhamento()
{
	return alinhamento;
}

Fonte* Texto::getFonte()
{
	return fonte;
}

string Texto::getString()
{
	string s;
	int size = wstr.size();
	s.resize(size);
	for (int i = 0; i < size; ++i)
		s[i] = wstr[i];

	return s;
}

wstring Texto::getWstring()
{
	return wstr;
}

Letra* Texto::getLetra(unsigned int indice)
{
	if (indice >= letras.size())
		return NULL;

	return &letras[indice];
}

Cor Texto::getCorLetra(unsigned int indice)
{
	if (indice >= letras.size())
		return cor;

	return letras[indice].cor;
}

void Texto::obterAncora(float &x, float &y)
{
	x = ancora.x;
	y = ancora.y;
}

void Texto::obterEscala(float &sx, float& sy)
{
	sx = escala.x;
	sy = escala.y;
}

void Texto::obterTamanho(int &larg, int &alt)
{
	larg = getLargura();
	alt = getAltura();
}

void Texto::obterTamanhoOriginal(int &larg, int &alt)
{
	larg = getLarguraOriginal();
	alt = getAlturaOriginal();
}

void Texto::obterCor(int &r, int &g, int &b)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
}

void Texto::obterCor(int &r, int &g, int &b, int &a)
{
	r = cor.r;
	g = cor.g;
	b = cor.b;
	a = cor.a;
}

void Texto::setAncora(Vetor2D anc)
{
	ancora = anc;
}

void Texto::setAncora(float x, float y)
{
	ancora.x = x;
	ancora.y = y;
}

void Texto::setEscala(Vetor2D esc)
{
	escala = esc;

	if (largura_max > 0)
		calcularDimensoes();
}

void Texto::setEscala(float sx, float sy)
{
	escala.x = sx;
	escala.y = sy;

	if (largura_max > 0)
		calcularDimensoes();
}

void Texto::setEscalaX(float x)
{
	escala.x = x;

	if (largura_max > 0)
		calcularDimensoes();
}

void Texto::setEscalaY(float y)
{
	escala.y = y;
}

void Texto::setLarguraMaxima(int larg_max)
{
	largura_max = larg_max;
	calcularDimensoes();
}

void Texto::setCor(Cor cor, bool aplicarEmTodasAsLetras)
{
	if (aplicarEmTodasAsLetras)
		for (unsigned int i = 0; i < letras.size(); ++i)
			letras[i].cor = cor;
	else
		for (unsigned int i = 0; i < letras.size(); ++i)
			if(letras[i].cor == this->cor)
				letras[i].cor = cor;

	this->cor = cor;
}

void Texto::setCor(int r, int g, int b, bool aplicarEmTodasAsLetras)
{
	setCor(Cor(r, g, b, cor.a), aplicarEmTodasAsLetras);
}

void Texto::setCor(int r, int g, int b, int a, bool aplicarEmTodasAsLetras)
{
	setCor(Cor(r, g, b, a), aplicarEmTodasAsLetras);
}

void Texto::setCorVermelho(int vermelho, bool aplicarEmTodasAsLetras)
{
	if (aplicarEmTodasAsLetras)
		for (unsigned int i = 0; i < letras.size(); ++i)
			letras[i].cor = cor;
	else
		for (unsigned int i = 0; i < letras.size(); ++i)
			if(letras[i].cor == cor)
				letras[i].cor.r = vermelho;

	cor.r = vermelho;
}

void Texto::setCorVerde(int verde, bool aplicarEmTodasAsLetras)
{
	if (aplicarEmTodasAsLetras)
		for (unsigned int i = 0; i < letras.size(); ++i)
			letras[i].cor = cor;
	else
		for (unsigned int i = 0; i < letras.size(); ++i)
			if (letras[i].cor == cor)
				letras[i].cor.g = verde;

	cor.g = verde;
}

void Texto::setCorAzul(int azul, bool aplicarEmTodasAsLetras)
{
	if (aplicarEmTodasAsLetras)
		for (unsigned int i = 0; i < letras.size(); ++i)
			letras[i].cor = cor;
	else
		for (unsigned int i = 0; i < letras.size(); ++i)
			if (letras[i].cor == cor)
				letras[i].cor.b = azul;

	cor.b = azul;
}

void Texto::setCorAlpha(int alpha, bool aplicarEmTodasAsLetras)
{
	if (aplicarEmTodasAsLetras)
		for (unsigned int i = 0; i < letras.size(); ++i)
			letras[i].cor = cor;
	else
		for (unsigned int i = 0; i < letras.size(); ++i)
			if (letras[i].cor == cor)
				letras[i].cor.a = alpha;

	cor.a = alpha;
}

void Texto::setEspacamentoLinhas(float espacamento)
{
	espacamento_linhas = espacamento;

	if (fonte)
	{
		altura = fonte->getAlturaGlifos()*num_linhas*espacamento_linhas;
	}
}

void Texto::setAlinhamento(EnumAlinhamentoTexto alinhamento)
{
	this->alinhamento = alinhamento;
}

void Texto::setFonte(string nome)
{
	setFonte(gRecursos.getFonte(nome));
}

void Texto::setFonte(Fonte* fnt)
{
	if (!fnt)
	{
		return;
	}

	fonte = fnt;

	criarVetorDeLetras();
	calcularDimensoes();
}

void Texto::setString(string str)
{
	wstr.resize(str.size());
	for (unsigned int i = 0; i < wstr.size(); ++i)
		wstr[i] = (unsigned char)str[i];

	criarVetorDeLetras();
	calcularDimensoes();
}

void Texto::setWstring(wstring wstr_)
{
	wstr = wstr_;
	criarVetorDeLetras();
	calcularDimensoes();
}

void Texto::setCorLetra(unsigned int i, Cor cor)
{
	if (i >= letras.size())
		return;

	letras[i].cor = cor;
}

void Texto::setCorLetra(unsigned int i, int r, int g, int b, int a)
{
	if (i >= letras.size())
		return;

	letras[i].cor.set(r, g, b, a);
}

void Texto::setCorPalavra(const string& palavra, Cor cor)
{
	unsigned int pos = wstr.find(converterParaWstring(palavra));

	if (pos == std::string::npos)
		return;

	unsigned int fim = pos + palavra.size();
	for (unsigned int i = pos; i < fim; ++i)
		setCorLetra(i, cor);
}

void Texto::setCorPalavra(const string& palavra, int r, int g, int b, int a)
{
	setCorPalavra(palavra, Cor(r, g, b, a));
}

void Texto::adicionarString(string str, bool noInicio)
{
	wstr.append(converterParaWstring(str));

	adicionarAoVetorDeLetras(str, noInicio);
	calcularDimensoes();
}

void Texto::adicionarWstring(wstring wstr_, bool noInicio)
{
	wstr += wstr_;
	adicionarAoVetorDeLetras(wstr_, noInicio);
	calcularDimensoes();
}

void Texto::removerString(string str)
{
	removerWstring(converterParaWstring(str));
}

void Texto::removerWstring(wstring wstr_)
{
	unsigned int pos = wstr.find(wstr_);
	wstr.erase(wstr.begin() + pos, wstr.begin() + pos + wstr_.size());
	letras.erase(letras.begin() + pos, letras.begin() + pos + wstr_.size());

	calcularDimensoes();
}

void Texto::apagar()
{
	wstr.clear();
	letras.clear();

	num_linhas = 0;

	largura = 0;
	altura = 0;
}

bool Texto::quebrarStringParaLargura(int larg)
{
	if (largura <= larg)
		return false;

	wstr = getWstringParaLarguraMaxima(larg, largura, altura, num_linhas);
	calcularDimensoes();
	return true;
}

void Texto::desenhar(int x, int y, float rot)
{
	//if (!uniEstaInicializada())
		//return;

	if (!fonte)
	{
		gDebug.erro("Nao pode desenhar Texto antes de setar Fonte.", this);
		return;
	}

	int x_canto, y_canto;
	int x_canto_linha, y_canto_linha;
	float x_glifo, y_glifo;
	int altLinha = fonte->getAlturaGlifos()*espacamento_linhas*escala.y;
	x_canto = x - (largura*escala.x*ancora.x);
	y_canto = y - (altura*escala.y*ancora.y);

	unsigned int inicio = 0;
	unsigned int fim = -1;
	unsigned int largLinha = 0;
	unsigned int linha = 0;
	unsigned int tamStr = wstr.size();

	while (inicio < tamStr)
	{
		largLinha = 0;
		inicio = fim + 1;
		fim = tamStr - 1;
		if (inicio > fim)
			break;

		for (unsigned int i = inicio; i < tamStr; ++i)
		{
			largLinha += letras[i].glifo->avanco;
			if (letras[i].fimDeLinha)
			{
				if (letras[i].glifo->caractere == L' ' ||
					letras[i].glifo->caractere == L'\n')
					largLinha -= letras[i].glifo->avanco;

				fim = i;
				break;
			}
		}

		switch (alinhamento)
		{
		case TEXTO_ALINHADO_A_ESQUERDA:
		default:
			x_canto_linha = x_canto;
			break;

		case TEXTO_ALINHADO_A_DIREITA:
			x_canto_linha = x_canto + (largura - largLinha)*escala.x;
			break;

		case TEXTO_CENTRALIZADO:
			x_canto_linha = x_canto + (largura - largLinha)*escala.x / 2.0f;
			break;
		}

		y_canto_linha = y_canto + (linha*altLinha);
		x_glifo = x_canto_linha;
		y_glifo = y_canto_linha;

		unsigned int numLetrasNaLinha;
		if(letras[fim].glifo->caractere == L'\n')
			numLetrasNaLinha = fim - inicio;
		else
			numLetrasNaLinha = fim - inicio + 1;

		Glifo* g;
		for (unsigned int j = 0; j < numLetrasNaLinha; ++j)
		{
			g = letras[inicio + j].glifo;
			fonte->desenharGlifo(g, x_glifo, y_glifo, x, y, rot, escala, letras[inicio + j].cor, NAO_INVERTER);
			x_glifo += g->avanco*escala.x;
		}

		++linha;
	}
}

wstring Texto::converterParaWstring(const string& s)
{
	wstring r;
	r.resize(s.size());
	for (unsigned int i = 0; i < r.size(); ++i)
		r[i] = (unsigned char)s[i];
	return r;
}

/*
void Texto::obterInicioEFimDaLinha(int linha, int& inicio, int& fim)
{
	inicio = fim = -1;
	unsigned int l = 0;

	int larg_linha = 0;
	int larg_palavra = 0;
	int ultimo_espaco = 0;

	for (unsigned int i = 0; i < wstr.size(); ++i)
	{
		if (wstr[i] != u'\n')
			larg_palavra += fonte->getGlifo(wstr[i])->avanco;

		if (wstr[i] == u' ')
		{
			ultimo_espaco = i;
			larg_linha += larg_palavra;
			larg_palavra = 0;
		}

		if (wstr[i] == u'\n')
		{
			ultimo_espaco = i;
			larg_linha = 0;
			larg_palavra = 0;
			++l;
			if (l == linha)
			{
				inicio = i+1;
			}
			else if (l == linha + 1)
			{
				fim = i;
				break;
			}
			else
				continue;
		}
		else if ((larg_linha + larg_palavra)*escala.x > largura_max)
		{
			++l;

			if (larg_linha == 0)	//	quebra no meio de uma palavra
			{
				if (larg_palavra == fonte->getGlifo(wstr[i])->avanco)
				{
					++i;
					larg_palavra = 0;
				}
				else
				{
					larg_palavra = fonte->getGlifo(wstr[i])->avanco;
				}

				if (l == linha)
				{
					inicio = i;
				}
				else if (l == linha+1)
				{
					fim = i-1;
					break;
				}

				ultimo_espaco = i;
			}
			else	//	quebra em algum espaco em branco
			{
				if (l == linha)
				{
					inicio = ultimo_espaco + 1;
				}
				else if (l == linha + 1)
				{
					fim = ultimo_espaco;
					break;
				}

				++ultimo_espaco;
				larg_linha = 0;
			}
		}
	}

	if (fim == -1 && inicio != -1)
		fim = wstr.size()-1;
	else if (fim != -1 && inicio == -1)
		inicio = 0;
}
*/
wstring Texto::getWstringParaLarguraMaxima(int larg_max, int& r_larg, int& r_alt, int& r_num_linhas)
{
	wstring _str = wstr;
	r_larg = 0;
	r_alt = 0;
	r_num_linhas = 0;

	unsigned int linha = 0;
	int larg_linha = 0;
	int larg_palavra = 0;
	int ultimo_espaco = 0;
	Glifo* g;
	Glifo* g_ue = fonte->getGlifo(_str[0]);
	for (unsigned int i = 0; i < _str.size(); ++i)
	{
		g = fonte->getGlifo(_str[i]);
		if (_str[i] != L'\n')
			larg_palavra += g->avanco;

		if (_str[i] == L' ')
		{
			g_ue = g;
			ultimo_espaco = i;
			larg_linha += larg_palavra;
			larg_palavra = 0;
		}
		else if (_str[i] == L'\n')
		{
			if (r_larg < larg_linha + larg_palavra)
				r_larg = larg_linha + larg_palavra;

			g_ue = g;
			ultimo_espaco = i;
			larg_linha = 0;
			larg_palavra = 0;
			++linha;
			continue;
		}

		if (larg_max > 0 && (larg_linha + larg_palavra)*escala.x > larg_max)
		{
			++linha;

			if (larg_linha == 0)	//	quebra no meio de uma palavra
			{
				if (larg_palavra == g->avanco)	//	se tem apenas uma letra na linha, quebra depois da letra
				{
					if (r_larg < larg_palavra)
						r_larg = larg_palavra;

					++i;				
				}
				else	//	se tem mais de uma, quebra antes
				{
					if (r_larg < larg_palavra - g->avanco)
						r_larg = larg_palavra - g->avanco;
				}

				_str.replace(i, 0, L"\n");
				larg_palavra = 0;
			}
			else	//	quebra em algum espaco em branco
			{
				
				if (r_larg < larg_linha - g_ue->avanco)
					r_larg = larg_linha - g_ue->avanco;

				_str.replace(ultimo_espaco, 1, L" \n");
				++i;
				larg_linha = 0;
			}
		}
	}

	if (r_larg < larg_linha + larg_palavra)
		r_larg = larg_linha + larg_palavra;

	++linha;
	r_alt = linha * fonte->getAlturaGlifos() * espacamento_linhas;
	r_num_linhas = linha;

	return _str;
}

void Texto::criarVetorDeLetras()
{
	if (!fonte)
		return;

	unsigned int size = wstr.size();
	letras.resize(size);
	for (unsigned int i = 0; i < size; ++i)
	{
		letras[i].cor = cor;
		letras[i].fimDeLinha = false;
		letras[i].glifo = fonte->getGlifo(wstr[i]);
	}
}

void Texto::adicionarAoVetorDeLetras(string str, bool noInicio)
{
	if (!fonte)
		return;

	vector<Letra> l;
	unsigned int numLetras = str.size();
	l.resize(numLetras);
	for (unsigned int i = 0; i < numLetras; ++i)
	{
		l[i].cor = cor;
		l[i].fimDeLinha = false;
		l[i].glifo = fonte->getGlifo((unsigned char)str[i]);
	}

	if (noInicio)
		letras.insert(letras.begin(), l.begin(), l.end());
	else
		letras.insert(letras.end(), l.begin(), l.end());
}

void Texto::adicionarAoVetorDeLetras(wstring wstr_, bool noInicio)
{
	if (!fonte)
		return;

	vector<Letra> l;
	unsigned int numLetras = wstr_.size();
	l.resize(numLetras);
	for (unsigned int i = 0; i < numLetras; ++i)
	{
		l[i].cor = cor;
		l[i].fimDeLinha = false;
		l[i].glifo = fonte->getGlifo(wstr_[i]);
	}

	if (noInicio)
		letras.insert(letras.begin(), l.begin(), l.end());
	else
		letras.insert(letras.end(), l.begin(), l.end());
}

void Texto::removerDoVetorDeLetras(unsigned int inicio, unsigned int fim)
{
	letras.erase(letras.begin() + inicio, letras.begin() + fim);
}

void Texto::calcularDimensoes()
{
	largura = 0;
	altura = 0;
	num_linhas = 0;

	if (!fonte || wstr.empty())
		return;

	unsigned int linha = 0;
	int larg_linha = 0;
	int larg_palavra = 0;
	int ultimo_espaco = 0;
	Glifo* g;
	Glifo* g_ue = fonte->getGlifo(wstr[0]);
	for (unsigned int i = 0; i < wstr.size(); ++i)
	{
		g = fonte->getGlifo(wstr[i]);
		letras[i].glifo = g;
		if (wstr[i] != L'\n')
		{
			larg_palavra += g->avanco;
			letras[i].fimDeLinha = false;
		}

		if (wstr[i] == L' ')
		{
			g_ue = g;
			ultimo_espaco = i;
			larg_linha += larg_palavra;
			larg_palavra = 0;
		}
		else if (wstr[i] == L'\n')
		{
			if (largura < larg_linha + larg_palavra)
				largura = larg_linha + larg_palavra;

			letras[i].fimDeLinha = true;
			g_ue = g;
			ultimo_espaco = i;
			larg_linha = 0;
			larg_palavra = 0;
			++linha;
			continue;
		}

		if (largura_max > 0 && (larg_linha + larg_palavra)*escala.x > largura_max)
		{
			++linha;

			if (larg_linha == 0)	//	quebra no meio de uma palavra
			{
				if (larg_palavra == g->avanco)	//	se tem apenas uma letra na linha, quebra depois da letra
				{
					if (largura < larg_palavra)
						largura = larg_palavra;

					letras[i].fimDeLinha = true;
					larg_palavra = 0;
					g_ue = g;
					ultimo_espaco = i;
				}
				else	//	se tem mais de uma, quebra antes
				{
					if (largura < larg_palavra - g->avanco)
						largura = larg_palavra - g->avanco;

					larg_palavra = g->avanco;
					letras[i-1].fimDeLinha = true;
					g_ue = letras[i-1].glifo;
					ultimo_espaco = i-1;
				}
			}
			else	//	quebra em algum espaco em branco
			{

				if (largura < larg_linha - g_ue->avanco)
					largura = larg_linha - g_ue->avanco;

				letras[ultimo_espaco].fimDeLinha = true;
				larg_linha = 0;
				g_ue = g;
				ultimo_espaco = i;
			}
		}
	}

	if (largura < larg_linha + larg_palavra)
		largura = larg_linha + larg_palavra;

	++linha;
	altura = linha * fonte->getAlturaGlifos() * espacamento_linhas;
	num_linhas = linha;
}