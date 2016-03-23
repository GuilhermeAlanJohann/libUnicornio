#pragma once
#include "libUnicornio.h"

//	Classe base para todos as telas
//		Essa classe contem a lógica base de todas as telas
//		Ela implementa os métodos virtuais da classe Estado que são:
//			void entrar();
//			void sair();
//			void atualizar(float dt);
//
//		e cria outros métodos virtuais para as suas classes filhas. São eles:
//			void aoEntrar();
//			void aoSair();
//			void aoAtualizar(float dt);
//			void aoDesenhar();
class Tela : public Estado
{
public:
	Tela();
	~Tela();

	//	Métodos virtuais criados da classe pai
	//		Esses métodos são implementado por essa classe e 
	//		fazem uso do outros métodos virtuais que devem ser 
	//		implementados pelas classes filhas
	void entrar();
	void sair();
	void atualizar(float dt);


	//	Métodos virtuais para as classes filhas
	//		Esses métodos, quando necessarios,
	//		devem ser implementados pelas classes filhas
	virtual void aoEntrar() {};
	virtual void aoSair() {};
	virtual void aoAtualizar(float dt) {};
	virtual void aoDesenhar() {};
};



