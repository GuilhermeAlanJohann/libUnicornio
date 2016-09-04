#ifndef UNI_GRUPODESTRINGS_H
#define UNI_GRUPODESTRINGS_H

#include "uniAPI.h"
#include <string>
#include <vector>
#include "json/json.h"

using namespace std;

class UNI_API GrupoDeStrings
{
public:
	GrupoDeStrings();
	~GrupoDeStrings();

	bool carregar(const string& nome, const string& caminho_arquivo);
	bool descarregar();

	bool estaCarregado();

	string getCaminhoDoArquivo();
	string getNome();

	string getString(const string& nome);
	vector<string> getVetorDeString(const string& nome);

	bool obterString(const string& nome, string& s);
	bool obterVetorDeString(const string& nome, vector<string>& v);

	unsigned int getNumVetoresDeStrings();
	unsigned int getNumStrings();

private:
	map<string, string> strings;
	map<string, vector<string> > vetoresDeStrings;

	string caminho_arquivo;
	string nome;
	bool carregado;
};

#endif