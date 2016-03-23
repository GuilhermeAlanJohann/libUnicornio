#pragma once
#include "libUnicornio.h"

//	Classe base para todos as telas
//		Essa classe contem a l�gica base de todas as telas
//		Ela implementa os m�todos virtuais da classe Estado que s�o:
//			void entrar();
//			void sair();
//			void atualizar(float dt);
//
//		e cria outros m�todos virtuais para as suas classes filhas. S�o eles:
//			void aoEntrar();
//			void aoSair();
//			void aoAtualizar(float dt);
//			void aoDesenhar();
class Tela : public Estado
{
public:
	Tela();
	~Tela();

	//	M�todos virtuais criados da classe pai
	//		Esses m�todos s�o implementado por essa classe e 
	//		fazem uso do outros m�todos virtuais que devem ser 
	//		implementados pelas classes filhas
	void entrar();
	void sair();
	void atualizar(float dt);


	//	M�todos virtuais para as classes filhas
	//		Esses m�todos, quando necessarios,
	//		devem ser implementados pelas classes filhas
	virtual void aoEntrar() {};
	virtual void aoSair() {};
	virtual void aoAtualizar(float dt) {};
	virtual void aoDesenhar() {};
};



