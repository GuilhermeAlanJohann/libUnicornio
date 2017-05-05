#include "GrupoDeStrings.h"
#include "Global.h"
#include <SDL_rwops.h>

GrupoDeStrings::GrupoDeStrings()
{
	carregado = false;
}

GrupoDeStrings::~GrupoDeStrings()
{
}

bool GrupoDeStrings::carregar(const string& nome, const string& caminho_arquivo)
{
	if (estaCarregado())
	{
		gDebug.erro("Erro ao carregar arquivo '" + caminho_arquivo + "'. GrupoDeStrings já está carregado.");
		return false;
	}

	//	Abrir o arquivo 
	SDL_RWops *ifs = SDL_RWFromFile(caminho_arquivo.c_str(), "rb");
	if (!ifs)
	{
		gDebug.erro("Erro ao abrir arquivo '" + caminho_arquivo + "'. Talvez o arquivo nao exista.");
		return false;
	}

	unsigned int tamanho_arquivo_em_bytes = ifs->size(ifs);
	char *bytes_do_arquivo = new char[tamanho_arquivo_em_bytes];
	ifs->read(ifs, bytes_do_arquivo, tamanho_arquivo_em_bytes, 1);
	ifs->close(ifs);

	//	Fazer o parse do arquivo
	Json::Value root;
	Json::Reader reader;
	if (!reader.parse(bytes_do_arquivo, bytes_do_arquivo + tamanho_arquivo_em_bytes, root, false))
	{
		gDebug.erro("Erro ao fazer o parse do arquivo '" + caminho_arquivo + "'.");
		delete[] bytes_do_arquivo;
		return false;
	}

	//	não precisamos mais do bite do arquivo depois do parser
	delete[] bytes_do_arquivo;

	//	ler o nome de todos os membros filhos de root
	vector<string> nomes_strings = root.getMemberNames();

	//	para cada filho
	for (unsigned int i = 0; i < root.size(); ++i)
	{
		Json::Value filho;
		filho = root[nomes_strings[i]];

		//	se é um array, lê as strings e coloca em um vetor, passando para 'vetoresDeStrigs'
		if (filho.isArray())
		{
			vector<string> vet;
			for (unsigned int j = 0; j < filho.size(); ++j)
			{
				Json::Value membro = filho[j];
				if (membro.isString() || membro.isConvertibleTo(Json::stringValue))
				{
					vet.push_back(membro.asString());
				}
			}
			pair<string, vector<string> > par;
			par.first = nomes_strings[i];
			par.second = vet;
			vetoresDeStrings.insert(par);
		}
		//	se é uma string, ou pode ser convertido para string, lê nome e valor e coloca dentro de 'strings'
		else if (filho.isString() || filho.isConvertibleTo(Json::stringValue))
		{
			pair<string, string> par;
			par.first = nomes_strings[i];
			par.second = filho.asString();
			strings.insert(par);	
		}
	}

	//	preenche as informacoes do arquivo
	this->nome = nome;
	this->caminho_arquivo = caminho_arquivo;

	carregado = true;
	return true;
}

bool GrupoDeStrings::descarregar()
{
	strings.clear();
	vetoresDeStrings.clear();

	nome.clear();
	caminho_arquivo.clear();

	carregado = false;
	return true;
}

bool GrupoDeStrings::estaCarregado()
{
	return carregado;
}

string GrupoDeStrings::getCaminhoDoArquivo()
{
	return caminho_arquivo;
}

string GrupoDeStrings::getNome()
{
	return nome;
}

string GrupoDeStrings::getString(const string& nome)
{
	map<string, string>::iterator it = strings.find(nome);
	if (it == strings.end())
		return "";

	return it->second;
}

vector<string> GrupoDeStrings::getVetorDeString(const string& nome)
{
	map<string, vector<string> >::iterator it = vetoresDeStrings.find(nome);
	if (it == vetoresDeStrings.end())
		return vector<string>();

	return it->second;
}

bool GrupoDeStrings::obterString(const string& nome, string& s)
{
	map<string, string>::iterator it = strings.find(nome);
	if (it == strings.end())
	{
		s.clear();
		return false;
	}

	s = it->second;
	return true;
}

bool GrupoDeStrings::obterVetorDeString(const string& nome, vector<string>& v)
{
	map<string, vector<string> >::iterator it = vetoresDeStrings.find(nome);
	if (it == vetoresDeStrings.end())
	{
		v.clear();
		return false;
	}

	v = it->second;
	return true;
}

unsigned int GrupoDeStrings::getNumVetoresDeStrings()
{
	return vetoresDeStrings.size();
}

unsigned int GrupoDeStrings::getNumStrings()
{
	return strings.size();
}