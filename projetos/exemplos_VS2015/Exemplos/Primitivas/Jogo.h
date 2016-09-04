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
	void desenharPixel();
	void desenharLinha();
	void desenharArco();
	void desenharSemiCirculo();
	void desenharCirculo();
	void desenharElipse();
	void desenharRetangulo();
	void desenharRetanguloRotacionado();
	void desenharRetanguloArredondado();
	void desenharTriangulo();
	void desenharPoligono();
};

