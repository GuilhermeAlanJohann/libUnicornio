#include "PainelDeDebug.h"
#include <sstream>
#include <algorithm>
#include "uniFuncoesPrincipais.h"
#include "Global.h"
#include "Texto.h"
#include "uniTestarColisao.h"

PainelDeDebug::PainelDeDebug()
{
}

PainelDeDebug::~PainelDeDebug()
{
}

void PainelDeDebug::inicializar()
{
	x = y = 0;
	maiorLargura = 0;
	escalaGlobal.set(1.0f, 1.0f);
	retanTitulo.set(0, 0, 0, 0);
	retanFechar.set(0, 0, 0, 0);
	retanMinimizar.set(0, 0, 0, 0);

	corFundo.set(0, 0, 0, 128);
	corTitulo.set(255, 255, 255, 255);
	corErro.set(255, 0, 0, 255);
	corDepuracao.set(255, 255, 255, 255);

	corContorno.r = 255 - corFundo.r;
	corContorno.g = 255 - corFundo.g;
	corContorno.b = 255 - corFundo.b;
	corContorno.a = 255 - corFundo.a;

	ativo = true;
	visivel = true;
	minimizado = false;
	movendo = false;
}

void PainelDeDebug::finalizar()
{
	itensErro.clear();
	itensDepurar.clear();
}

void PainelDeDebug::atualizar()
{
	if (!ativo)
		return;

	if (itensErro.empty() && itensDepurar.empty())
		return;

	Fonte* fonte = gGraficos.getFontePadrao();
	if (!fonte)
		return;

	//	guarda a escala global usada para render
	SDL_RenderGetScale(gGraficos.sdl_renderer, &escalaGlobal.x, &escalaGlobal.y);

	//	calcula tamanho titulo (largura, altura)
	atualizarTamanhoTitulo();
	atualizarMoverPainel();
	retanTitulo.x = x*escalaGlobal.x;
	retanTitulo.y = y*escalaGlobal.y;
	atualizarTamanhoBotaoFechar();
	atualizarTamanhoBotaoMinimizar();
	atualizarCliqueBotaoFechar();
	atualizarCliqueBotaoMinimizar();
}

void PainelDeDebug::desenhar()
{
	if (!visivel)
		return;

	if (itensErro.empty() && itensDepurar.empty()) 
		return;

	Fonte* fonte = gGraficos.getFontePadrao();
	if (!fonte)
		return;

	//	guarda a escala global usada para render
	SDL_RenderGetScale(gGraficos.sdl_renderer, &escalaGlobal.x, &escalaGlobal.y);

	//	muda a escala do render para 1.0f, 1.0f
	//	pois nao queremos deformar a fonte usada nos textos
	SDL_RenderSetScale(gGraficos.sdl_renderer, 1.0f, 1.0f);

	int proxY;
	desenharTitulo(proxY);
	desenharBotaoFechar();
	desenharBotaoMinimizar();
	int yItens = proxY;

	if (!minimizado)
	{
		vector<ItemDebug> itens = itensErro;
		itens.insert(itens.end(), itensDepurar.begin(), itensDepurar.end());

		for (unsigned int i = 0; i < itens.size(); i++)
		{
			desenharItem(itens[i], retanTitulo.x, proxY, retanTitulo.larg, proxY);
		}
		
		gGraficos.desenharRetangulo(retanTitulo.x, yItens - 1, 0, retanTitulo.larg, proxY - yItens + 1, 0, 0, corContorno.r, corContorno.g, corContorno.b);
	}

	//	volta para a escala anterior
	SDL_RenderSetScale(gGraficos.sdl_renderer, escalaGlobal.x, escalaGlobal.y);
}

void PainelDeDebug::erro(const string& mensagem, void* ptr)
{
	if(ptr != 0)
		for (unsigned int i = 0; i < itensErro.size(); ++i)
		{
			if (itensErro[i].ptr == ptr)
			{
				itensErro[i].valor = mensagem;
				return;
			}
		}

	ItemDebug item;
	item.chave = "Erro";
	item.valor = mensagem;
	item.ptr = ptr;
	item.cor.set(255, 0, 0, 255);

	itensErro.push_back(item);
}

void PainelDeDebug::depurar(const string& chave, const string& valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, const string& valor, const Cor& cor)
{
	if (!ativo)
		return;

	for (unsigned int i = 0; i < itensDepurar.size(); i++)
	{
		if (itensDepurar[i].chave == chave)
		{
			itensDepurar[i].valor = valor;
			return;
		}
	}

	ItemDebug deb;
	deb.ptr = 0;
	deb.chave = chave;
	deb.valor = valor;
	deb.cor = cor;
	itensDepurar.push_back(deb);
}

void PainelDeDebug::depurar(const string& chave, int valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, int valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, unsigned int valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, unsigned int valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, double valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, double valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, float valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, float valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, char valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, char valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, unsigned char valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, unsigned char valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << valor;
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, const Vetor2D& valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, const Vetor2D& valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << "{ "; 
	sstream << valor.x;
	sstream << " , ";
	sstream << valor.y;
	sstream << " }";
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, const Quad& valor)
{
	depurar(chave, valor, corDepuracao);
}

void PainelDeDebug::depurar(const string& chave, const Quad& valor, const Cor& cor)
{
	std::ostringstream sstream;
	sstream << "{ ";
	sstream << valor.x;
	sstream << " , ";
	sstream << valor.y;
	sstream << " , ";
	sstream << valor.larg;
	sstream << " , ";
	sstream << valor.alt;
	sstream << " }";
	depurar(chave, sstream.str(), corDepuracao);
}

void PainelDeDebug::removerErro(int indice)
{
	itensErro.erase(itensErro.begin() + indice);
	maiorLargura = 0;
}

void PainelDeDebug::removerDepuracao(int indice)
{
	itensDepurar.erase(itensDepurar.begin() + indice);
	maiorLargura = 0;
}

void PainelDeDebug::removerDepuracao(const string& chave)
{
	for (unsigned int i = 0; i < itensDepurar.size(); ++i)
		if (chave == itensDepurar[i].chave)
			itensDepurar.erase(itensDepurar.begin() + i);
	maiorLargura = 0;
}

void PainelDeDebug::limpar()
{
	itensErro.clear();
	itensDepurar.clear();
	maiorLargura = 0;
}

void PainelDeDebug::limparErros()
{
	itensErro.clear();
	maiorLargura = 0;
}

void PainelDeDebug::limparDepuracoes()
{
	itensDepurar.clear();
	maiorLargura = 0;
}

void PainelDeDebug::ativar()
{
	setAtivo(true);
}

void PainelDeDebug::desativar()
{
	setAtivo(false);
}

void PainelDeDebug::mostrar()
{
	setVisivel(true);
}

void PainelDeDebug::esconder()
{
	setVisivel(false);
}

void PainelDeDebug::minimizar()
{
	minimizado = true;
}

void PainelDeDebug::restaurar()
{
	minimizado = false;
	visivel = true;
}

int PainelDeDebug::getX()
{
	return x;
}

int PainelDeDebug::getY()
{
	return y;
}

Cor PainelDeDebug::getCorFundo()
{
	return corFundo;
}

Cor PainelDeDebug::getCorContorno()
{
	return corContorno;
}

Cor PainelDeDebug::getCorTitulo()
{
	return corTitulo;
}

Cor PainelDeDebug::getCorErro()
{
	return corErro;
}

Cor PainelDeDebug::getCorDepuracao()
{
	return corDepuracao;
}

bool PainelDeDebug::estaAtivo()
{
	return ativo;
}

bool PainelDeDebug::estaVisivel()
{
	return visivel;
}

bool PainelDeDebug::estaMinimizado()
{
	return minimizado;
}

void PainelDeDebug::setAtivo(bool ativo)
{
	this->ativo = ativo;
}

void PainelDeDebug::setVisivel(bool visivel)
{
	this->visivel = visivel;
}

void PainelDeDebug::setX(int x)
{
	this->x = x;
}

void PainelDeDebug::setY(int y)
{
	this->y = y;
}

void PainelDeDebug::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void PainelDeDebug::setCorFundo(Cor cor)
{
	corFundo = cor;
}

void PainelDeDebug::setCorContorno(Cor cor)
{
	corContorno = cor;
}

void PainelDeDebug::setCorTitulo(Cor cor)
{
	corTitulo = cor;
}

void PainelDeDebug::setCorErro(Cor cor, bool mudarTodos)
{
	corErro = cor;

	if(mudarTodos)
		for (unsigned int i = 0; i < itensErro.size(); ++i)
			itensErro[i].cor = cor;
}

void PainelDeDebug::setCorDepuracao(Cor cor, bool mudarTodos)
{
	corDepuracao = cor;

	if (mudarTodos)
		for (unsigned int i = 0; i < itensDepurar.size(); ++i)
			itensDepurar[i].cor = cor;
}

void PainelDeDebug::atualizarTamanhoTitulo()
{
	unsigned int tam_maior_chave = 0;
	unsigned int tam_maior_valor = 0;

	for (unsigned int i = 0; i < itensErro.size(); i++)
	{
		tam_maior_chave = max(tam_maior_chave, (unsigned int)itensErro[i].chave.size());
		tam_maior_valor = max(tam_maior_valor, (unsigned int)itensErro[i].valor.size());
	}
	for (unsigned int i = 0; i < itensDepurar.size(); i++)
	{
		tam_maior_chave = max(tam_maior_chave, (unsigned int)itensDepurar[i].chave.size());
		tam_maior_valor = max(tam_maior_valor, (unsigned int)itensDepurar[i].valor.size());
	}

	Fonte* fonte = gGraficos.getFontePadrao();
	int larg = ((tam_maior_chave + tam_maior_valor + 1) * fonte->getLarguraGlifos()) + 15;

	int largMaiorChave = tam_maior_chave * fonte->getLarguraGlifos();
	meio = largMaiorChave + 5;

	if (larg < 256)
		larg = 256;

	if (larg > gJanela.getLargura()*escalaGlobal.x)
		larg = gJanela.getLargura()*escalaGlobal.x;

	if (larg > maiorLargura)
		maiorLargura = larg;
	else if (larg < maiorLargura)
		larg = maiorLargura;

	retanTitulo.larg = larg;
	retanTitulo.alt = fonte->getAlturaGlifos() + 10;
}

void PainelDeDebug::atualizarTamanhoBotaoFechar()
{
	//	 calcular tamanho
	int margem = (retanTitulo.alt - (retanTitulo.alt*0.8));
	retanFechar.larg = retanTitulo.alt - (margem * 2);
	retanFechar.alt = retanFechar.larg;
	retanFechar.x = (retanTitulo.x) + retanTitulo.larg - retanFechar.larg - margem;
	retanFechar.y = (retanTitulo.y) + margem;
}

void PainelDeDebug::atualizarCliqueBotaoFechar()
{
	//	verificar clique mouse
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		int mx = gMouse.x * escalaGlobal.x;
		int my = gMouse.y * escalaGlobal.y;
		if (uniTestarColisaoPontoComRetangulo(mx, my, retanFechar))
			visivel = false;
	}
}

void PainelDeDebug::atualizarTamanhoBotaoMinimizar()
{
	//	 calcular tamanho
	int margem = (retanTitulo.alt - (retanTitulo.alt*0.8));
	retanMinimizar.larg = retanTitulo.alt - margem * 2;
	retanMinimizar.alt = retanMinimizar.larg;
	retanMinimizar.x = (retanTitulo.x) + retanTitulo.larg - retanMinimizar.larg - retanFechar.larg - margem*2;
	retanMinimizar.y = (retanTitulo.y) + margem;
}

void PainelDeDebug::atualizarCliqueBotaoMinimizar()
{
	//	verificar clique mouse
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		int mx = gMouse.x * escalaGlobal.x;
		int my = gMouse.y * escalaGlobal.y;
		if (uniTestarColisaoPontoComRetangulo(mx, my, retanMinimizar))
			minimizado = !minimizado;
	}
}

void PainelDeDebug::atualizarMoverPainel()
{
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		int mx = gMouse.x * escalaGlobal.x;
		int my = gMouse.y * escalaGlobal.y;
		if (uniTestarColisaoPontoComRetangulo( mx, my, retanTitulo) &&
			!uniTestarColisaoPontoComRetangulo(mx, my, retanFechar) &&
			!uniTestarColisaoPontoComRetangulo(mx, my, retanMinimizar))
			movendo = true;
	}

	if (gMouse.soltou[BOTAO_MOUSE_ESQ])
		movendo = false;

	if (!movendo)
		return;

	x += gMouse.dx;
	y += gMouse.dy;
}

void PainelDeDebug::desenharTitulo(int &proxY)
{
	Texto t;
	t.setFonte(gGraficos.getFontePadrao());
	t.setString("Painel de DEBUG");
	t.setAncora(0.5f, 0.5f);
	t.setCor(corTitulo);

	//SDL_Rect dest = retanTitulo.getSDL_Rect();
	//SDL_Texture* tex = gGraficos.getSDL_TextureBranco();
	//SDL_SetTextureColorMod(tex, corFundo.r, corFundo.g, corFundo.b);
	//SDL_SetTextureAlphaMod(tex, corFundo.a);
	//SDL_RenderCopy(gGraficos.sdl_renderer, tex, NULL, &dest);
	Quad dest = retanTitulo;
	gGraficos.desenharRetangulo(dest, corFundo.r, corFundo.g, corFundo.b, corFundo.a, true);

	//gGraficos.desenharRetangulo(dest.x, dest.y, 0, dest.w, dest.h, 0, 0, corContorno.r, corContorno.g, corContorno.b);
	gGraficos.desenharRetangulo(dest, corContorno.r, corContorno.g, corContorno.b);

	t.desenhar(dest.x + (dest.larg / 2), dest.y + (dest.alt/2));

	proxY = dest.y + dest.alt;
}

void PainelDeDebug::desenharBotaoFechar()
{
	int margem = (retanTitulo.alt - (retanTitulo.alt*0.8));

	gGraficos.desenharRetangulo(retanFechar.x, retanFechar.y, 0, retanFechar.larg, retanFechar.alt, 0, 0, corContorno.r, corContorno.g, corContorno.b);
	gGraficos.desenharLinha(retanFechar.x + margem -1, retanFechar.y + margem -1, retanFechar.x + retanFechar.larg - margem, retanFechar.y + retanFechar.alt - margem, corContorno.r, corContorno.g, corContorno.b);
	gGraficos.desenharLinha(retanFechar.x + retanFechar.larg - margem, retanFechar.y + margem - 1, retanFechar.x + margem -1, retanFechar.y + retanFechar.alt - margem, corContorno.r, corContorno.g, corContorno.b);
}

void PainelDeDebug::desenharBotaoMinimizar()
{
	int margem = (retanTitulo.alt - (retanTitulo.alt*0.8));

	gGraficos.desenharRetangulo(retanMinimizar.x, retanMinimizar.y, 0, retanMinimizar.larg, retanMinimizar.alt, 0, 0, corContorno.r, corContorno.g, corContorno.b);
	gGraficos.desenharLinha(retanMinimizar.x + margem - 1, retanMinimizar.y + retanMinimizar.alt - margem, retanMinimizar.x + retanMinimizar.larg - margem, retanMinimizar.y + retanMinimizar.alt - margem, corContorno.r, corContorno.g, corContorno.b);
}

void PainelDeDebug::desenharItem(ItemDebug item, int x, int y, int larg, int &proxY)
{
	Texto txtChave;
	txtChave.setFonte(gGraficos.getFontePadrao());
	txtChave.setString(item.chave);
	txtChave.setLarguraMaxima(meio);
	txtChave.setAncora(0.0f, 0.5f);
	txtChave.setCor(item.cor, true);
	Texto txtValor;
	txtValor.setFonte(gGraficos.getFontePadrao());
	txtValor.setString(item.valor);
	txtValor.setLarguraMaxima(larg - meio);
	txtValor.setAncora(1.0f, 0.5f);
	txtValor.setCor(item.cor, true);

	int alt = max(txtChave.getAltura(), txtValor.getAltura());

	//SDL_Rect dest = { x, y, larg, alt};
	//SDL_Texture* tex = gGraficos.getSDL_TextureBranco();
	//SDL_SetTextureColorMod(tex, corFundo.r, corFundo.g, corFundo.b);
	//SDL_SetTextureAlphaMod(tex, corFundo.a);
	//SDL_RenderCopy(gGraficos.sdl_renderer, tex, NULL, &dest);
	gGraficos.desenharRetangulo(Quad(x, y, larg, alt), corFundo.r, corFundo.g, corFundo.b, corFundo.a, true);

	txtChave.desenhar(x + 5, y+(alt/2));
	txtValor.desenhar(x + larg -5, y + (alt / 2));

	proxY = y + alt;
}