#ifndef UNI_PREFERENCIAS_H
#define UNI_PREFERENCIAS_H

#include "uniAPI.h"
#include <string>
#include "json/json.h"
#include <fstream>
#include <vector>

using namespace std;

class UNI_API Preferencias
{
public:
	Preferencias();
	Preferencias(string arquivo);
	~Preferencias();

	void carregar(string caminho);
	void recarregar();
	void salvar();

	Json::Value getValue(const string& nome_da_preferencia, Json::Value valor_padrao);
	bool		getBool(const string& nome_da_preferencia, bool valor_padrao);
	int			getInt(const string& nome_da_preferencia, int valor_padrao);
	float		getFloat(const string& nome_da_preferencia, float valor_padrao);
	double		getDouble(const string& nome_da_preferencia, double valor_padrao);
	string		getString(const string& nome_da_preferencia, string valor_padrao);
	unsigned int getUInt(const string& nome_da_preferencia, unsigned int valor_padrao);

	vector<bool>	getVetorDeBool(const string& nome_da_preferencia, const vector<bool>& valores_padrao);
	vector<int>		getVetorDeInt(const string& nome_da_preferencia, const vector<int>& valores_padrao);
	vector<float>	getVetorDeFloat(const string& nome_da_preferencia, const vector<float>& valores_padrao);
	vector<double>	getVetorDeDouble(const string& nome_da_preferencia, const vector<double>& valores_padrao);
	vector<string>	getVetorDeString(const string& nome_da_preferencia, const vector<string>& valores_padrao);
	vector<unsigned int> getVetorDeUInt(const string& nome_da_preferencia, const vector<unsigned int>& valores_padrao);

	void setValue(const string& nome_da_preferencia, Json::Value valor);
	void setBool(const string& nome_da_preferencia, bool valor);
	void setInt(const string& nome_da_preferencia, int valor);
	void setfloat(const string& nome_da_preferencia, float valor);
	void setDouble(const string& nome_da_preferencia, double valor);
	void setString(const string& nome_da_preferencia, string valor);
	void setUInt(const string& nome_da_preferencia, unsigned int valor);

	void setVetorDeBool(const string& nome_da_preferencia, const vector<bool>& valores);
	void setVetorDeInt(const string& nome_da_preferencia, const vector<int>& valores);
	void setVetorDeFloat(const string& nome_da_preferencia, const vector<float>& valores);
	void setVetorDeDouble(const string& nome_da_preferencia, const vector<double>& valores);
	void setVetorDeString(const string& nome_da_preferencia, const vector<string>& valores);
	void setVetorDeUInt(const string& nome_da_preferencia, const vector<unsigned int>& valores);

	void setVetorDeBool(const string& nome_da_preferencia, bool valores[], unsigned int tamanho_array);
	void setVetorDeInt(const string& nome_da_preferencia, int valores[], unsigned int tamanho_array);
	void setVetorDeFloat(const string& nome_da_preferencia, float valores[], unsigned int tamanho_array);
	void setVetorDeDouble(const string& nome_da_preferencia, double valores[], unsigned int tamanho_array);
	void setVetorDeString(const string& nome_da_preferencia, string valores[], unsigned int tamanho_array);
	void setVetorDeUInt(const string& nome_da_preferencia, unsigned int valores[], unsigned int tamanho_array);

private:
	string removerSeparadores(const string& arquivo);

	Json::Value root;
	string nome_arquivo;
};

#endif