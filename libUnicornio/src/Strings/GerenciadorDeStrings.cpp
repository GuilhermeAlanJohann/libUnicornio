#include "GerenciadorDeStrings.h"
#include "Global.h"


GerenciadorDeStrings::GerenciadorDeStrings()
{
	grupoAtual = NULL;
}

GerenciadorDeStrings::~GerenciadorDeStrings()
{
}

bool GerenciadorDeStrings::carregar(const string& arquivo)
{
	if (grupoPadrao.carregar("", arquivo))
	{
		grupoAtual = &grupoPadrao;
		return true;
	}
	return false;
}

bool GerenciadorDeStrings::descarregar()
{
	grupoPadrao.descarregar();

	for (unsigned int i = 0; i < traducoes.size(); ++i)
	{
		traducoes[i]->descarregar();
	}
	traducoes.clear();

	return true;
}

bool GerenciadorDeStrings::estaCarregado()
{
	return grupoPadrao.estaCarregado();
}

bool GerenciadorDeStrings::carregarTraducao(const string& nome, const string& arquivo)
{
	if (!estaCarregado())
		return false;

	if (carregouTraducao(nome))
	{
		gDebug.erro("Tradução '" + nome + "'. Uma tradução com este none já está carregada!");
		return false;
	}

	GrupoDeStrings* grupo = new GrupoDeStrings;
	if (grupo->carregar(nome, arquivo))
	{
		traducoes.push_back(grupo);
		return true;
	}
	delete grupo;
	return false;
}

bool GerenciadorDeStrings::descarregarTraducao(const string& nome, const string& arquivo)
{
	for (unsigned int i = 0; i < traducoes.size(); ++i)
	{
		if (traducoes[i]->getNome() == nome)
		{
			traducoes[i]->descarregar();
			traducoes.erase(traducoes.begin() + i);
			return true;
		}
	}

	gDebug.erro("Tradução '" + nome + "' não pode ser descarregada, pois não está carregada!");
	return false;
}

bool GerenciadorDeStrings::descarregarTotasTraducoes()
{
	for (unsigned int i = 0; i < traducoes.size(); ++i)
	{
		traducoes[i]->descarregar();
		traducoes.erase(traducoes.begin() + i);
	}
	return true;
}

bool GerenciadorDeStrings::carregouTraducao(const string& sufixo)
{
	for (unsigned int i = 0; i < traducoes.size(); ++i)
	{
		if (traducoes[i]->getNome() == sufixo)
			return true;
	}
	return false;
}

string GerenciadorDeStrings::getString(const string& nome)
{
	string s;
	if (!grupoAtual->obterString(nome, s))
	{
		if (grupoAtual != &grupoPadrao)
		{
			grupoPadrao.obterString(nome, s);
		}
	}
	return s;
}

vector<string> GerenciadorDeStrings::getVetorDeString(const string& nome)
{
	vector<string> v;
	if (!grupoAtual->obterVetorDeString(nome, v))
	{
		if (grupoAtual != &grupoPadrao)
		{
			grupoPadrao.obterVetorDeString(nome, v);
		}
	}
	return v;
}

unsigned int GerenciadorDeStrings::getNumTraducoes()
{
	return traducoes.size();
}

string GerenciadorDeStrings::getNomeDaTraducaoAtual()
{
	return grupoAtual->getNome();
}

void GerenciadorDeStrings::setTraducao(const string& nome)
{
	if (nome.empty())
	{
		grupoAtual = &grupoPadrao;
		return;
	}

	for (unsigned int i = 0; i < traducoes.size(); ++i)
	{
		if (traducoes[i]->getNome() == nome)
			grupoAtual = traducoes[i];
	}
}