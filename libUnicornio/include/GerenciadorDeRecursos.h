#ifndef UNI_GERENCIADORDERECURSOS_H
#define UNI_GERENCIADORDERECURSOS_H

#include <map>
#include "Fonte.h"

class SpriteSheet;
class Audio;

class GerenciadorDeRecursos
{
public:
	GerenciadorDeRecursos();
	~GerenciadorDeRecursos();

	SpriteSheet*	carregarSpriteSheet(const std::string& nome, const std::string& caminho, int num_animacoes = 1, int num_max_frames = 1);
	Fonte*			carregarFonte(const std::string& nome, const std::string& caminho, int tamanho = 16, EstiloFonte estilo = FONTE_ESTILO_NORMAL);
	Audio*			carregarAudio(const std::string& nome, const std::string& caminho);

	void			descarregarTudo();
	void			descarregarTodosSpriteSheets();
	void			descarregarTodasFontes();
	void			descarregarTodosAudios();
	bool			descarregar(const std::string& nome);
	bool			descarregarSpriteSheet(const std::string& nome);
	bool			descarregarFonte(const std::string& nome);
	bool			descarregarAudio(const std::string& nome);

	SpriteSheet*	getSpriteSheet(const std::string& nome);
	Fonte*			getFonte(const std::string& nome);
	Audio*			getAudio(const std::string& nome);

	bool			carregouSpriteSheet(const std::string& nome);
	bool			carregouFonte(const std::string& nome);
	bool			carregouAudio(const std::string& nome);

private:
	std::map<std::string, SpriteSheet*> mSpriteSheets;
	std::map<std::string, Fonte*> mFontes;
	std::map<std::string, Audio*> mAudios;
};

#endif