#ifndef UNI_GERENCIADORDERECURSOS_H
#define UNI_GERENCIADORDERECURSOS_H

#include "uniAPI.h"
#include <map>
#include "SpriteSheet.h"
#include "Fonte.h"
#include "Audio.h"
#include "Musica.h"
#include "Textura.h"

class UNI_API GerenciadorDeRecursos
{
public:
	GerenciadorDeRecursos();
	~GerenciadorDeRecursos();

	SpriteSheet*	carregarSpriteSheet(const std::string& nome, const std::string& caminho, int num_animacoes = 1, int num_max_frames = 1, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	Fonte*			carregarFonte(const std::string& nome, const std::string& caminho, int tamanho = 16, int estilo = FONTE_ESTILO_NORMAL, Uint16 primeiro_glifo = 0, Uint16 ultimo_glifo = 255, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	Fonte*			carregarFonte(const std::string& nome, const std::string& arquivo, const std::wstring& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	Fonte*			carregarFonte(const std::string& nome, const std::string& arquivo, const std::string& caracteres, int num_glifos_x, int num_glifos_y, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);
	Audio*			carregarAudio(const std::string& nome, const std::string& caminho);
	Musica*			carregarMusica(const std::string& nome, const std::string& caminho, float volume = 100.0f);
	Textura*		carregarTextura(const std::string& nome, const std::string& caminho, EnumQualidadeEscala qualidade_escala = QUALIDADE_ESCALA_BAIXA);

	void			descarregarTudo();
	void			descarregarTodosSpriteSheets();
	void			descarregarTodasFontes();
	void			descarregarTodosAudios();
	void			descarregarTodasMusicas();
	void			descarregarTodasTexturas();

	bool			descarregar(const std::string& nome);
	bool			descarregarSpriteSheet(const std::string& nome);
	bool			descarregarFonte(const std::string& nome);
	bool			descarregarAudio(const std::string& nome);
	bool			descarregarMusica(const std::string& nome);
	bool			descarregarTextura(const std::string& nome);

	SpriteSheet*	getSpriteSheet(const std::string& nome);
	Fonte*			getFonte(const std::string& nome);
	Audio*			getAudio(const std::string& nome);
	Musica*			getMusica(const std::string& nome);
	Textura*		getTextura(const std::string& nome);

	bool			carregouSpriteSheet(const std::string& nome);
	bool			carregouFonte(const std::string& nome);
	bool			carregouAudio(const std::string& nome);
	bool			carregouMusica(const std::string& nome);
	bool			carregouTextura(const std::string& nome);

private:
	std::map<std::string, SpriteSheet*> mSpriteSheets;
	std::map<std::string, Fonte*> mFontes;
	std::map<std::string, Audio*> mAudios;
	std::map<std::string, Musica*> mMusicas;
	std::map<std::string, Textura*> mTexturas;
};

#endif