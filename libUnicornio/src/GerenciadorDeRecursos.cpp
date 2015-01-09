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
	if(carregouSpriteSheet(nome))
	{
		uniErro("Recurso '" + nome + "' nao pode ser carregado, pois um SpriteSheet com esse nome ja existe.");
		return NULL;
	}

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

Fonte* GerenciadorDeRecursos::carregarFonte(const string& nome, const string& caminho, int tamanho, int estilo)
{
	if(carregouFonte(nome))
	{
		uniErro("Recurso '" + nome + "' nao pode ser carregado, pois uma Fonte com esse nome ja existe.");
		return NULL;
	}

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

Audio* GerenciadorDeRecursos::carregarAudio(const string& nome, const string& caminho)
{
	if(carregouAudio(nome))
	{
		uniErro("Recurso '" + nome + "' nao pode ser carregado, pois um Som com esse nome ja existe.");
		return NULL;
	}

	Audio* audio = new Audio;
	if(audio->carregar(caminho))
	{
		mAudios.insert(pair<string, Audio*>(nome, audio));
	}
	else
	{
		delete audio;
		audio = NULL;
	}

	return audio;
}

void GerenciadorDeRecursos::descarregarTudo()
{
	descarregarTodosSpriteSheets();
	descarregarTodasFontes();
	descarregarTodosAudios();
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

void GerenciadorDeRecursos::descarregarTodasFontes()
{
	for(std::map<std::string, Fonte*>::iterator it = mFontes.begin(); it != mFontes.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mFontes.clear();
}

void GerenciadorDeRecursos::descarregarTodosAudios()
{
	for(std::map<std::string, Audio*>::iterator it = mAudios.begin(); it != mAudios.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mAudios.clear();
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

	if(descarregarAudio(nome))
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

bool GerenciadorDeRecursos::descarregarAudio(const string& nome)
{
	std::map<std::string, Audio*>::iterator it = mAudios.find(nome);

	if(it != mAudios.end())
	{
		it->second->descarregar();
		delete it->second;
		mAudios.erase(it);
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

Audio* GerenciadorDeRecursos::getAudio(const string& nome)
{
	std::map<std::string, Audio*>::iterator it = mAudios.find(nome);

	if(it != mAudios.end())
	{
		return it->second;
	}

	return NULL;
}

bool GerenciadorDeRecursos::carregouSpriteSheet(const std::string& nome)
{
	return (mSpriteSheets.find(nome) != mSpriteSheets.end());
}

bool GerenciadorDeRecursos::carregouFonte(const std::string& nome)
{
	return (mFontes.find(nome) != mFontes.end());
}

bool GerenciadorDeRecursos::carregouAudio(const std::string& nome)
{
	return (mAudios.find(nome) != mAudios.end());
}