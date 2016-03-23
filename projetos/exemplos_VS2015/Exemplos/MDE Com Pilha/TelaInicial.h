#pragma once
#include "Tela.h"

//	Classe para tela inicial
//		Essa classe mostra o logo a unicornio por dois segundos e
//		depois inicia o fade out.
//		Quando o fade out termina, ela troca para a proxima tela (TelaMenu)
class TelaInicial : public Tela
{
public:
	TelaInicial();
	~TelaInicial();

	//	Métodos virtuais criados pela classe Tela
	void aoEntrar();
	void aoSair();
	void aoAtualizar(float dt);
	void aoDesenhar();

private:
	float tempo;
	float duracao;
	Sprite spr;
};
