#include "Texto.h"
#include "libUnicornio.h"
#include <string>         // std::string, std::u32string
#include <locale>         // std::wstring_convert
#include <codecvt>        // std::codecvt_utf8
#include <cstdint>        // std::uint_least32_t

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

int Texto::getLarguraLinha(int linha)
{
	int larg = 0;
	return getLarguraOriginalLinha(linha)*escala.x;
}

int Texto::getAlturaLinha(int linha)
{
	int alt;
	return getAlturaOriginalLinha(linha)*escala.y;
}

int Texto::getLarguraOriginalLinha(int linha)
{
	if(!fonte)
		return 0;

	int larg = 0;
	wstring s = getWstringLinha(linha);
	for(unsigned int i = 0; i < s.size(); ++i)
		larg += fonte->getGlifo(s[i])->avanco;

	return larg;
}

int Texto::getAlturaOriginalLinha(int linha)
{	
	if(!fonte)
		return 0;

	int alt = 0;
	fonte->getAlturaMaxDosGlifos();

	return alt;
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

TipoAlinhamentoTexto Texto::getAlinhamento()
{
	return alinhamento;
}

Fonte* Texto::getFonte()
{
	return fonte;
}

string Texto::getString()
{
	return converterParaString(wstr);
}

string Texto::getStringLinha(int linha)
{
	return converterParaString(getWstringLinha(linha));
}

wstring Texto::getWstring()
{
	return wstr;
}

wstring Texto::getWstringLinha(int linha)
{
	if(linha < num_linhas)
	{
		int l = 0;
		unsigned int inicio = 0, tam = 0;

		if(l == linha)
			inicio = 0;

		for(unsigned int i = 0; i < wstr.size(); ++i)
		{
			if(wstr[i] == '\n')
			{
				l++;

				if(l == linha)
					inicio = i;
				else if(l == linha+1)
					tam = i - inicio -1;

			}
		}

		l++;
		if(l == linha+1)
			tam = wstr.size() - inicio -1;

		return wstring(wstr.begin() + inicio, wstr.begin() + inicio + tam);
	}

	return wstring();
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

void Texto::obterTamanhoLinha(int linha, int &larg, int &alt)
{
	obterTamanhoOriginalLinha(linha, larg, alt);

	larg *= escala.x;
	alt *= escala.y;
}

void Texto::obterTamanhoOriginalLinha(int linha, int &larg, int &alt)
{
	larg = 0;
	alt = 0;

	if(!fonte)
		return;

	wstring s = getWstringLinha(linha);
	for(unsigned int i = 0; i < s.size(); ++i)
	{
		larg += fonte->getGlifo(s[i])->avanco;
	}
	alt = fonte->getAlturaMaxDosGlifos();
}

void Texto::obterCor(int &vermelho, int &verde, int &azul)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
}

void Texto::obterCor(int &vermelho, int &verde, int &azul, int &alpha)
{
	vermelho = cor.r;
	verde = cor.g;
	azul = cor.b;
	alpha = cor.a;
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
}

void Texto::setEscala(float sx, float sy)
{
	escala.x = sx;
	escala.y = sy;
}

void Texto::setCor(int vermelho, int verde, int azul, int alpha)
{
	cor.r = vermelho;
	cor.g = verde;
	cor.b = azul;
	cor.a = alpha;
}

void Texto::setCorVermelho(int vermelho)
{
	cor.r = vermelho;
}

void Texto::setCorVerde(int verde)
{
	cor.g = verde;
}

void Texto::setCorAzul(int azul)
{
	cor.b = azul;
}

void Texto::setCorAlpha(int alpha)
{
	cor.a = alpha;
}

void Texto::setEspacamentoLinhas(float espacamento)
{
	espacamento_linhas = espacamento;

	if(fonte)
	{
		altura = fonte->getAlturaMaxDosGlifos()*num_linhas*espacamento_linhas;
	}
}

void Texto::setAlinhamento(TipoAlinhamentoTexto alinhamento)
{
	this->alinhamento = alinhamento;
}

void Texto::setFonte(string nome)
{
	setFonte(recursos.getFonte(nome));
}

void Texto::setFonte(Fonte* fnt)
{
	if(!fnt)
	{
		return;
	}

	fonte = fnt;

	calcularTamanho();
}

void Texto::setString(string str)
{
	wstr = converterParaWstring(str);
	calcularTamanho();
}

void Texto::setStringLinha(string str, int linha)
{
	setWstringLinha(converterParaWstring(str), linha);
}

void Texto::setWstring(wstring wstr_)
{
	wstr = wstr_;
	calcularTamanho();
}

void Texto::setWstringLinha(wstring wstr_, int linha)
{
	if(num_linhas-1 < linha)
	{
		int dif = linha - (num_linhas-1);
		for(int i = 0; i < dif; ++i)
		{
			wstr.append(L"\n");
		}
		wstr.append(wstr_);
	}
	else
	{
		unsigned int inicio = 0, tam = 0;
		unsigned int l = 0;
		for(unsigned int i = 0; i < wstr.size(); ++i)
		{
			if(wstr[i] == '\n')
			{
				++l;

				if(l == linha)
					inicio = i+1;
				else if(l == linha +1)
					tam = i - inicio;
			}
		}
		++l;
		if(l == linha +1)
			tam = wstr.size() - inicio;

		wstr.replace(inicio, tam, wstr_);
	}

	calcularTamanho();
}

void Texto::adicionarString(string str)
{
	wstr.append(converterParaWstring(str));
	calcularTamanho();
}

void Texto::adicionarStringNaLinha(string str, int linha)
{
	adicionarWstringNaLinha(converterParaWstring(str), linha);
}

void Texto::adicionarWstring(wstring wstr_)
{
	wstr = wstr_;
	calcularTamanho();
}

void Texto::adicionarWstringNaLinha(wstring wstr_, int linha)
{
	if(num_linhas-1 < linha)
	{
		int dif = linha - (num_linhas-1);
		for(int i = 0; i < dif; ++i)
		{
			wstr.append(L"\n");
		}
		wstr.append(wstr_);
	}
	else if(linha == num_linhas-1)
	{
		wstr.append(wstr_);
	}
	else
	{
		unsigned int pos = 0;
		unsigned int l = 0;
		for(unsigned int i = 0; i < wstr.size(); ++i)
		{
			if(this->wstr[i] == '\n')
			{
				if(l == linha)
				{
					pos = i;
					break;
				}

				++l;
			}
		}
		if(l == linha)
			wstr.replace(pos, 0, wstr_);
		else
			wstr.append(wstr_);
	}

	calcularTamanho();
}

void Texto::removerString(string str)
{
	removerWstring(converterParaWstring(str));
}

void Texto::removerStringNaLinha(string str, int linha)
{
	removerWstringNaLinha(converterParaWstring(str), linha);
}

void Texto::removerWstring(wstring wstr_)
{
	unsigned int pos = wstr.find(wstr_);
	wstr.erase(wstr.begin() + pos, wstr.begin() + pos + wstr_.size());

	calcularTamanho();
}

void Texto::removerWstringNaLinha(wstring wstr_, int linha)
{
	if(num_linhas < linha)
		return;

	unsigned int l = 0;
	unsigned int inicio = 0, tam = 0;
	wstring sub;

	for(unsigned int i = 0; i < wstr.size(); ++i)
	{
		if(wstr[i] == '\n')
		{
			++l;

			if(l == linha)
			{
				inicio = i+1;
			}
			else if(l == linha +1)
			{
				tam = i - inicio +1;
				break;
			}
		}
	}
	++l;
	if(l == linha +1)
		tam = wstr.size() - inicio;

	sub = wstr.substr(inicio, inicio + tam);
	unsigned int pos = sub.find(wstr_);
	wstr.erase(wstr.begin() + inicio + pos, wstr.begin() + inicio + pos + wstr_.size());

	calcularTamanho();
}

void Texto::removerLinha(int linha)
{
	if(num_linhas < linha)
		return;

	unsigned int l = 0;
	unsigned int inicio = 0, tam = 0;

	for(unsigned int i = 0; i < wstr.size(); ++i)
	{
		if(wstr[i] == '\n')
		{
			++l;

			if(l == linha)
			{
				inicio = i+1;
			}
			else if(l == linha +1)
			{
				tam = i - inicio + 1;
				break;
			}
		}
	}
	++l;
	if(l == linha +1)
		tam = wstr.size() - inicio;

	wstr.erase(wstr.begin() + inicio, wstr.begin() + inicio + tam);

	calcularTamanho();
}

void Texto::apagar()
{
	wstr.clear();

	num_linhas = 0;

	largura = 0;
	altura = 0;
}

void Texto::desenhar(int x, int y)
{
	if(!uni_init) 
		return;

	if(!fonte) 
	{
		uniDesenharTexto("Nao pode desenhar Texto antes de setar Fonte.", x, y, 255, 0, 0, 0.0f);
		return;
	}

	int x_canto, y_canto;
	int x_canto_linha, y_canto_linha;
	float x_glifo, y_glifo;
	float avanco = 1.0f;
	int alt_linha = fonte->getAlturaMaxDosGlifos()*espacamento_linhas*escala.y;

	x_canto = x - (largura*escala.x*ancora.x);
	y_canto = y - (altura*escala.y*ancora.y);

	unsigned int inicio = 0, fim = 0;	//	inicio e fim da linha
	unsigned int linha = 0;
	for(unsigned int i = 0; i < wstr.size(); ++i)
	{
		bool fim_da_linha = false;
		if(wstr[i] == '\n')
		{
			fim = i-1;
			fim_da_linha = true;
		}
		else if(i == wstr.size()-1)
		{
			fim = i;
			fim_da_linha = true;
		}

		if(fim_da_linha)
		{
			unsigned int dx = 0;
			for(unsigned int j = inicio; j <= fim; ++j)
			{
				switch(alinhamento)
				{
				case TEXTO_ALINHADO_A_ESQUERDA:
				default:
					x_canto_linha = x_canto;
					break;

				case TEXTO_ALINHADO_A_DIREITA:
					x_canto_linha = x_canto + (largura - getSomaDosAvancos(inicio, fim))*escala.x;
					break;

				case TEXTO_CENTRALIZADO:
					x_canto_linha = x_canto + (largura - getSomaDosAvancos(inicio, fim))*escala.x/2.0f;
					break;
				}

				y_canto_linha = y_canto + (linha*alt_linha);
				x_glifo = x_canto_linha + (dx*escala.x);
				y_glifo = y_canto_linha;

				desenharCaractere(wstr[j], x_glifo, y_glifo, x, y);
				dx += fonte->getGlifo(wstr[j])->avanco;
			}

			inicio = i+1;
			fim = i+1;
			++linha;
		}
	}
}

void Texto::desenhar(int x, int y, float rot)
{
	if(!uni_init) 
		return;

	if(!fonte) 
	{
		uniDesenharTexto("Nao pode desenhar Texto antes de setar Fonte.", x, y, 255, 0, 0, 0.0f);
		return;
	}

	int x_canto, y_canto;
	int x_canto_linha, y_canto_linha;
	float x_glifo, y_glifo;
	float avanco = 1.0f;
	int alt_linha = fonte->getAlturaMaxDosGlifos()*espacamento_linhas*escala.y;

	x_canto = x - (largura*escala.x*ancora.x);
	y_canto = y - (altura*escala.y*ancora.y);

	unsigned int inicio = 0, fim = 0;	//	inicio e fim da linha
	unsigned int linha = 0;
	for(unsigned int i = 0; i < wstr.size(); ++i)
	{
		bool fim_da_linha = false;
		if(wstr[i] == '\n')
		{
			fim = i-1;
			fim_da_linha = true;
		}
		else if(i == wstr.size()-1)
		{
			fim = i;
			fim_da_linha = true;
		}

		if(fim_da_linha)
		{
			unsigned int dx = 0;
			for(unsigned int j = inicio; j <= fim; ++j)
			{
				switch(alinhamento)
				{
				case TEXTO_ALINHADO_A_ESQUERDA:
				default:
					x_canto_linha = x_canto;
					break;

				case TEXTO_ALINHADO_A_DIREITA:
					x_canto_linha = x_canto + (largura - getSomaDosAvancos(inicio, fim))*escala.x;
					break;

				case TEXTO_CENTRALIZADO:
					x_canto_linha = x_canto + (largura - getSomaDosAvancos(inicio, fim))*escala.x/2.0f;
					break;
				}

				y_canto_linha = y_canto + (linha*alt_linha);
				x_glifo = x_canto_linha + (dx*escala.x);
				y_glifo = y_canto_linha;

				desenharCaractere(wstr[j], x_glifo, y_glifo, x, y, rot);
				dx += fonte->getGlifo(wstr[j])->avanco;
			}

			inicio = i+1;
			fim = i+1;
			++linha;
		}
	}
}

string Texto::converterParaString(wstring& s)
{
	string r(s.begin(), s.end());
	return r;
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//return converter.to_bytes(s);
}

wstring Texto::converterParaWstring(string& s)
{
	wstring r;
	r.resize(s.size());
	for(unsigned int i = 0; i < s.size(); ++i)
		r[i] = (unsigned char)s[i];

	return r;

	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	//return converter.from_bytes(s.data());
}

unsigned int Texto::getSomaDosAvancos(unsigned int inicio, unsigned int fim)
{
	unsigned int soma = 0;
	for(unsigned int i = inicio; i <= fim; ++i)
	{
		soma += fonte->getGlifo(wstr[i])->avanco;
	}

	return soma;
}

void Texto::desenharCaractere(wchar_t caractere, int x_canto_glifo, int y_canto_glifo, int x_texto, int y_texto)
{
	SDL_Rect retan;

	Glifo *glifo = fonte->getGlifo(caractere);
	SDL_Texture* tex = glifo->sdl_tex;

	SDL_QueryTexture(tex, NULL, NULL, &retan.w, &retan.h);

	retan.x = x_canto_glifo;
	retan.y = y_canto_glifo;
	retan.w *= escala.x;
	retan.h *= escala.y;

	SDL_SetTextureColorMod(tex, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(tex, cor.a);

	SDL_RenderCopy(renderer, tex, NULL, &retan);
}

void Texto::desenharCaractere(wchar_t caractere, int x_canto_glifo, int y_canto_glifo, int x_texto, int y_texto, float rot_texto)
{
	SDL_Rect retan;
	SDL_Point pivot;

	Glifo *glifo = fonte->getGlifo(caractere);
	SDL_Texture* tex = glifo->sdl_tex;

	SDL_QueryTexture(tex, NULL, NULL, &retan.w, &retan.h);

	retan.x = x_canto_glifo;
	retan.y = y_canto_glifo;
	retan.w *= escala.x;
	retan.h *= escala.y;

	pivot.x = x_texto - retan.x;
	pivot.y = y_texto - retan.y;

	SDL_SetTextureColorMod(tex, cor.r, cor.g, cor.b);
	SDL_SetTextureAlphaMod(tex, cor.a);

	SDL_RenderCopyEx(renderer, tex, NULL, &retan, rot_texto, &pivot, SDL_FLIP_NONE);
}

void Texto::calcularTamanho()
{
	if(!fonte)
	{
		largura = 0;
		altura = 0;
		return;
	}

	unsigned int linha = 0;
	unsigned int inicio = 0, fim = 0;

	int larg = 0;
	largura = 0;

	for(unsigned int i = 0; i < wstr.size(); ++i)
	{
		if(wstr[i] != '\n')
		{
			larg += fonte->getGlifo(wstr[i])->avanco;
		}
		if(wstr[i] == '\n' || i == wstr.size()-1)
		{
			if(largura < larg)
				largura = larg;

			++linha;
			larg = 0;
		}
		
	}

	altura = linha * fonte->getAlturaMaxDosGlifos() * espacamento_linhas;
	num_linhas = linha;
}