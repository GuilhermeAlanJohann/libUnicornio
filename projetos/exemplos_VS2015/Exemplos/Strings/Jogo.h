#pragma once
#include "libUnicornio.h"

class Jogo
{
public:
	Jogo();
	~Jogo();

	void inicializar();
	void finalizar();

	void executar();

private:
	string name;
	string class_;
	string charName;
	string charClass;
	string description;
	string skills;
	vector<string> skillNames;

	void atualizarInput();
	void atualizarStrings();
	void desenharInstrucoes();
	void desenharStrings();
};

