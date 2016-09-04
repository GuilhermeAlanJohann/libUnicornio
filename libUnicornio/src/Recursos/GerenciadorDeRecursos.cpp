#include "GerenciadorDeRecursos.h"
#include "Global.h"

GerenciadorDeRecursos::GerenciadorDeRecursos()
{
}

GerenciadorDeRecursos::~GerenciadorDeRecursos()
{
	descarregarTudo();
}

SpriteSheet* GerenciadorDeRecursos::carregarSpriteSheet(const string& nome, const string& caminho, int num_animacoes, int num_max_frames, EnumQualidadeEscala qualidade_escala)
{
	if(carregouSpriteSheet(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois um SpriteSheet com esse nome já existe.");
		return NULL;
	}

	SpriteSheet* sheet = new SpriteSheet;
	if(sheet->carregar(caminho, num_animacoes, num_max_frames, qualidade_escala))
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

Fonte* GerenciadorDeRecursos::carregarFonte(const string& nome, const string& caminho, int tamanho, int estilo, Uint16 primeiro_glifo, Uint16 ultimo_glifo, EnumQualidadeEscala qualidade_escala)
{
	if(carregouFonte(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois uma Fonte com esse nome já existe.");
		return NULL;
	}

	Fonte* fonte = new Fonte;
	if(fonte->carregar(caminho, tamanho, estilo, primeiro_glifo, ultimo_glifo, qualidade_escala))
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

Fonte* GerenciadorDeRecursos::carregarFonte(const string& nome, const string& caminho, const wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala)
{
	if (carregouFonte(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois uma Fonte com esse nome já existe.");
		return NULL;
	}

	Fonte* fonte = new Fonte;
	if (fonte->carregar(caminho, caracteres, num_glifos_x, num_glifos_y, qualidade_escala))
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

Fonte* GerenciadorDeRecursos::carregarFonte(const string& nome, const string& caminho, const string& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala)
{
	wstring carac;
	unsigned int size = caracteres.size();
	carac.resize(size);
	for (unsigned int i = 0; i < size; ++i)
		carac[i] = (unsigned char)caracteres[i];

	return carregarFonte(nome, caminho, carac, num_glifos_x, num_glifos_y, qualidade_escala);
}

Audio* GerenciadorDeRecursos::carregarAudio(const string& nome, const string& caminho)
{
	if(carregouAudio(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois um Som com esse nome já existe.");
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

Musica* GerenciadorDeRecursos::carregarMusica(const std::string& nome, const std::string& caminho, float volume)
{
	if (carregouMusica(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois uma Musica com esse nome já existe.");
		return NULL;
	}

	Musica* musica = new Musica;
	if (musica->carregar(caminho))
	{
		musica->setVolume(volume);
		mMusicas.insert(pair<string, Musica*>(nome, musica));
	}
	else
	{
		delete musica;
		musica = NULL;
	}

	return musica;
}

Textura* GerenciadorDeRecursos::carregarTextura(const std::string& nome, const std::string& caminho, EnumQualidadeEscala qualidade_escala)
{
	if (carregouTextura(nome))
	{
		gDebug.erro("Recurso '" + nome + "' não pode ser carregado, pois uma Textura com esse nome já existe.");
		return NULL;
	}

	Textura* textura = new Textura;
	if (textura->criarDoArquivo(caminho, qualidade_escala))
	{
		mTexturas.insert(pair<string, Textura*>(nome, textura));
	}
	else
	{
		delete textura;
		textura = NULL;
	}

	return textura;
}

void GerenciadorDeRecursos::descarregarTudo()
{
	descarregarTodosSpriteSheets();
	descarregarTodasFontes();
	descarregarTodosAudios();
	descarregarTodasMusicas();
	descarregarTodasTexturas();
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

void GerenciadorDeRecursos::descarregarTodasMusicas()
{
	for (std::map<std::string, Musica*>::iterator it = mMusicas.begin(); it != mMusicas.end(); ++it)
	{
		it->second->descarregar();
		delete it->second;
	}

	mMusicas.clear();
}

void GerenciadorDeRecursos::descarregarTodasTexturas()
{
	for (std::map<std::string, Textura*>::iterator it = mTexturas.begin(); it != mTexturas.end(); ++it)
	{
		it->second->destruir();
		delete it->second;
	}

	mTexturas.clear();
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

	if (descarregarMusica(nome))
	{
		descarregou = true;
	}

	if (descarregarTextura(nome))
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
		return true;
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
		return true;
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
		return true;
	}

	return false;
}

bool GerenciadorDeRecursos::descarregarMusica(const string& nome)
{
	std::map<std::string, Musica*>::iterator it = mMusicas.find(nome);

	if (it != mMusicas.end())
	{
		it->second->descarregar();
		delete it->second;
		mMusicas.erase(it);
		return true;
	}

	return false;
}

bool GerenciadorDeRecursos::descarregarTextura(const string& nome)
{
	std::map<std::string, Textura*>::iterator it = mTexturas.find(nome);

	if (it != mTexturas.end())
	{
		it->second->destruir();
		delete it->second;
		mTexturas.erase(it);
		return true;
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

Musica* GerenciadorDeRecursos::getMusica(const string& nome)
{
	std::map<std::string, Musica*>::iterator it = mMusicas.find(nome);

	if (it != mMusicas.end())
	{
		return it->second;
	}

	return NULL;
}

Textura* GerenciadorDeRecursos::getTextura(const string& nome)
{
	std::map<std::string, Textura*>::iterator it = mTexturas.find(nome);

	if (it != mTexturas.end())
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

bool GerenciadorDeRecursos::carregouMusica(const std::string& nome)
{
	return (mMusicas.find(nome) != mMusicas.end());
}

bool GerenciadorDeRecursos::carregouTextura(const std::string& nome)
{
	return (mTexturas.find(nome) != mTexturas.end());
}