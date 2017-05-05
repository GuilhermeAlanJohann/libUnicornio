#include "Preferencias.h"
#include <algorithm>
#include "Global.h"
#include "uniSistemaDeArquivos.h"
#include <SDL.h>

Preferencias::Preferencias()
{
}

Preferencias::Preferencias(string arquivo)
{
	carregar(arquivo);
}

Preferencias::~Preferencias()
{
}

void Preferencias::carregar(string arquivo)
{
	root.clear();

#if UNI_PLATAFORMA_MOVEL
	arquivo = removerSeparadores(arquivo);
#endif

	string caminho = uniGetCaminhoPreferencias() + arquivo;

	ifstream ifs;
	ifs.open(caminho.c_str());
	nome_arquivo = arquivo;

	if (!ifs.is_open())
	{
		//uniErro("Erro ao abrir arquivo de preferencias '" + arquivo + "'.");
		return;
	}

	if (!ifs.eof())
	{
		Json::Reader reader;
		if (!reader.parse(ifs, root, false))
		{
			nome_arquivo.clear();
			gDebug.erro("Erro ao fazer o parse do arquivo de preferencias '" + arquivo + "'.");
		}
	}
	ifs.close();
}

void Preferencias::recarregar()
{
	carregar(nome_arquivo);
}

void Preferencias::salvar()
{
	Json::StyledWriter writer;
	string str = writer.write(root);

	ofstream ofs(nome_arquivo.c_str());
	ofs << str;
	ofs.close();
}

Json::Value Preferencias::getValue(const string& nome_da_preferencia, Json::Value valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao);
}

bool Preferencias::getBool(const string& nome_da_preferencia, bool valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asBool();
}

int Preferencias::getInt(const string& nome_da_preferencia, int valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asInt();
}

float Preferencias::getFloat(const string& nome_da_preferencia, float valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asFloat();
}

double Preferencias::getDouble(const string& nome_da_preferencia, double valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asDouble();
}

string Preferencias::getString(const string& nome_da_preferencia, string valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asString();
}

unsigned int Preferencias::getUInt(const string& nome_da_preferencia, unsigned int valor_padrao)
{
	return root.get(nome_da_preferencia, valor_padrao).asUInt();
}

vector<bool> Preferencias::getVetorDeBool(const string& nome_da_preferencia, const vector<bool>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<bool> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asBool();
	
	return v;
}

vector<int>	Preferencias::getVetorDeInt(const string& nome_da_preferencia, const vector<int>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<int> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asInt();

	return v;
}

vector<float> Preferencias::getVetorDeFloat(const string& nome_da_preferencia, const vector<float>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<float> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asFloat();

	return v;
}

vector<double> Preferencias::getVetorDeDouble(const string& nome_da_preferencia, const vector<double>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<double> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asDouble();

	return v;
}

vector<string> Preferencias::getVetorDeString(const string& nome_da_preferencia, const vector<string>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<string> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asString();

	return v;
}

vector<unsigned int> Preferencias::getVetorDeUInt(const string& nome_da_preferencia, const vector<unsigned int>& valores_padrao)
{
	Json::Value arr = root.get(nome_da_preferencia, -1);
	if (!arr.isArray())
		return valores_padrao;

	vector<unsigned int> v;
	v.resize(arr.size());
	for (unsigned int i = 0; i < arr.size(); ++i)
		v[i] = arr[i].asUInt();

	return v;
}

void Preferencias::setValue(const string& nome_da_preferencia, Json::Value valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setBool(const string& nome_da_preferencia, bool valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setInt(const string& nome_da_preferencia, int valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setfloat(const string& nome_da_preferencia, float valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setDouble(const string& nome_da_preferencia, double valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setString(const string& nome_da_preferencia, string valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setUInt(const string& nome_da_preferencia, unsigned int valor)
{
	root[nome_da_preferencia] = valor;
}

void Preferencias::setVetorDeBool(const string& nome_da_preferencia, const vector<bool>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (bool)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeInt(const string& nome_da_preferencia, const vector<int>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (int)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeFloat(const string& nome_da_preferencia, const vector<float>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (float)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeDouble(const string& nome_da_preferencia, const vector<double>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (double)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeString(const string& nome_da_preferencia, const vector<string>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (string)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeUInt(const string& nome_da_preferencia, const vector<unsigned int>& valores)
{
	Json::Value arr;
	for (unsigned int i = 0; i < valores.size(); ++i)
		arr[i] = (unsigned int)valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeBool(const string& nome_da_preferencia, bool valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeInt(const string& nome_da_preferencia, int valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeFloat(const string& nome_da_preferencia, float valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeDouble(const string& nome_da_preferencia, double valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeString(const string& nome_da_preferencia, string valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

void Preferencias::setVetorDeUInt(const string& nome_da_preferencia, unsigned int valores[], unsigned int tamanho_array)
{
	Json::Value arr;
	for (unsigned int i = 0; i < tamanho_array; ++i)
		arr[i] = valores[i];
	root[nome_da_preferencia] = arr;
}

string Preferencias::removerSeparadores(const string& caminho)
{
	string r = caminho;
	std::replace(r.begin(), r.end(), '/', '.');
	std::replace(r.begin(), r.end(), '\\', '.');
	return r;
}
