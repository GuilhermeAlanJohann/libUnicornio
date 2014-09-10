#include "GerenciadorDeRecursos.h"
#include "libUnicornio.h"

GerenciadorDeRecursos::GerenciadorDeRecursos()
{
}

GerenciadorDeRecursos::~GerenciadorDeRecursos()
{
	descarregarTudo();
}

SpriteSheet* GerenciadorDeRecursos::carregarSpriteSheet(const string& nome, const string& caminho, int num_animacoes, int num_max_frames)
{
	SpriteSheet* sheet = new SpriteSheet;
	if(sheet->carregar(caminho, num_animacoes, num_max_frames))
	{
		mSpriteSheets.insert(pair<string, SpriteSheet*>(nome, sheet));
	}
	else
	{
		delete sheet;
		sheet = NULL;
	}

	return sheet;
}

Fonte* GerenciadorDeRecursos::carregarFonte(const string& nome, const string& caminho, int tamanho, EstiloFonte estilo)
{
	Fonte* fonte = new Fonte;
	if(fonte->carregar(caminho, tamanho, estilo))
	{
		mFontes.insert(pair<string, Fonte*>(nome, fonte));
	}
	else
	{
		delete fonte;
		fonte = NULL;
	}

	return fonte;
}

Som* GerenciadorDeRecursos::carregarSom(const string& nome, const string& caminho, int volume, int distancia, int angulo)
{
	Som* som = new Som;
	if(som->carregar(caminho))
	{
		mSons.insert(pair<string, Som*>(nome, som));
		som->ajustar(volume, distancia, angulo);
	}
	else
	{
		delete som;
		som = NULL;
	}

	return som;
}

void GerenciadorDeRecursos::descarregarTudo()
{
	descarregarTodosSpriteSheets();
	descarregarTodasFotes();
	descarregarTodosSons();
}

void GerenciadorDeRecursos::descarregarTodosSpriteSheets()
{
	for(std::map<std::string, SpriteSheet*>::iterator it = mSpriteSheets.begin(); it != mSpriteSheets.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mSpriteSheets.clear();
}

void GerenciadorDeRecursos::descarregarTodasFotes()
{
	for(std::map<std::string, Fonte*>::iterator it = mFontes.begin(); it != mFontes.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mFontes.clear();
}

void GerenciadorDeRecursos::descarregarTodosSons()
{
	for(std::map<std::string, Som*>::iterator it = mSons.begin(); it != mSons.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mSons.clear();
}

bool GerenciadorDeRecursos::descarregar(const string& nome)
{
	bool descarregou = false;

	if(descarregarSpriteSheet(nome))
	{
		descarregou = true;
	}

	if(descarregarFonte(nome))
	{
		descarregou = true;
	}

	if(descarregarSom(nome))
	{
		descarregou = true;
	}

	return descarregou;
}

bool GerenciadorDeRecursos::descarregarSpriteSheet(const string& nome)
{
	std::map<std::string, SpriteSheet*>::iterator it = mSpriteSheets.find(nome);

	if(it != mSpriteSheets.end())
	{
		it->second->descarregar();
		delete it->second;
		mSpriteSheets.erase(it);
	}

	return false;
}

bool GerenciadorDeRecursos::descarregarFonte(const string& nome)
{
	std::map<std::string, Fonte*>::iterator it = mFontes.find(nome);

	if(it != mFontes.end())
	{
		it->second->descarregar();
		delete it->second;
		mFontes.erase(it);
	}

	return false;
}

bool GerenciadorDeRecursos::descarregarSom(const string& nome)
{
	std::map<std::string, Som*>::iterator it = mSons.find(nome);

	if(it != mSons.end())
	{
		it->second->descarregar();
		delete it->second;
		mSons.erase(it);
	}

	return false;
}

SpriteSheet* GerenciadorDeRecursos::getSpriteSheet(const string& nome)
{
	std::map<std::string, SpriteSheet*>::iterator it = mSpriteSheets.find(nome);

	if(it != mSpriteSheets.end())
	{
		return it->second;
	}

	return NULL;
}

Fonte* GerenciadorDeRecursos::getFonte(const string& nome)
{
	std::map<std::string, Fonte*>::iterator it = mFontes.find(nome);

	if(it != mFontes.end())
	{
		return it->second;
	}

	return NULL;
}

Som* GerenciadorDeRecursos::getSom(const string& nome)
{
	std::map<std::string, Som*>::iterator it = mSons.find(nome);

	if(it != mSons.end())
	{
		return it->second;
	}

	return NULL;
}