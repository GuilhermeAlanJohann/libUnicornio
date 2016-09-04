#ifndef UNI_GERENCIADORDESTRINGS_H
#define UNI_GERENCIADORDESTRINGS_H

#include "uniAPI.h"
#include "GrupoDeStrings.h"

using namespace std;

class UNI_API GerenciadorDeStrings
{
public:
	GerenciadorDeStrings();
	~GerenciadorDeStrings();

	bool carregar(const string& arquivo);
	bool descarregar();

	bool estaCarregado();

	bool carregarTraducao(const string& nome, const string& arquivo);
	bool descarregarTraducao(const string& nome, const string& arquivo);
	bool descarregarTotasTraducoes();
	bool carregouTraducao(const string& nome);

	unsigned int getNumTraducoes();

	string getString(const string& nome);
	vector<string> getVetorDeString(const string& nome);

	string getNomeDaTraducaoAtual();
	void setTraducao(const string& nome);

private:
	GrupoDeStrings grupoPadrao;
	vector<GrupoDeStrings*> traducoes;

	GrupoDeStrings* grupoAtual;
};

#endif