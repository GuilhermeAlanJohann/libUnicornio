#ifndef UNI_GERENCIADORDERECURSOS_H
#define UNI_GERENCIADORDERECURSOS_H

#include <map>
#include "Fonte.h"

class SpriteSheet;
class Som;

class GerenciadorDeRecursos
{
public:
	GerenciadorDeRecursos();
	~GerenciadorDeRecursos();

	SpriteSheet*	carregarSpriteSheet(const std::string& nome, const std::string& caminho, int num_animacoes = 1, int num_max_frames = 1);
	Fonte*			carregarFonte(const std::string& nome, const std::string& caminho, int tamanho = 16, EstiloFonte estilo = FONTE_ESTILO_NORMAL);
	Som*			carregarSom(const std::string& nome, const std::string& caminho, int volume = 128, int distancia = 0, int angulo = 0);

	void			descarregarTudo();
	void			descarregarTodosSpriteSheets();
	void			descarregarTodasFotes();
	void			descarregarTodosSons();
	bool			descarregar(const std::string& nome);
	bool			descarregarSpriteSheet(const std::string& nome);
	bool			descarregarFonte(const std::string& nome);
	bool			descarregarSom(const std::string& nome);

	SpriteSheet*	getSpriteSheet(const std::string& nome);
	Fonte*			getFonte(const std::string& nome);
	Som*			getSom(const std::string& nome);

private:
	std::map<std::string, SpriteSheet*> mSpriteSheets;
	std::map<std::string, Fonte*> mFontes;
	std::map<std::string, Som*> mSons;
};

#endif