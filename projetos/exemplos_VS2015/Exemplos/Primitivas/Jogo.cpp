#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);
}

void Jogo::finalizar()
{
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		//	1)	Desenha as primitivas usando o 'gGraficos'
		desenharPixel();
		desenharLinha();
		desenharArco();
		desenharSemiCirculo();
		desenharCirculo();
		desenharElipse();
		desenharRetangulo();
		desenharRetanguloRotacionado();
		desenharRetanguloArredondado();
		desenharTriangulo();
		desenharPoligono();

		uniTerminarFrame();
	}
}

void Jogo::desenharPixel()
{
	Cor cor(255, 255, 255, 255);
	int x = 50;
	int y = 60;

	//	Desenhar o pixel
	gGraficos.desenharPixel(x, y, cor.r, cor.g, cor.b, cor.a);

	//	Desenha um texto
	gGraficos.desenharTexto("Pixel", x, y - 30);
}

void Jogo::desenharLinha()
{
	Cor cor(255, 255, 255, 255);
	int x1 = 120;
	int y1 = 60;
	int x2 = 170;
	int y2 = 90;

	//	Desenhar a linha
	gGraficos.desenharLinha(x1, y1, x2, y2, cor.r, cor.g, cor.b, cor.a);

	//	Desenha um texto
	int x = (x2 + x1)/2;
	int y = 30;
	gGraficos.desenharTexto("Linha", x, y);
}

void Jogo::desenharArco()
{
	Cor cor(255, 255, 255, 255);
	int x = 250;
	int y = 60;
	int raio = 10;
	int anguloMin = 0;
	int anguloMax = 270;

	//	Desenhar o arco
	gGraficos.desenharArco(x, y, raio, anguloMin, anguloMax, cor.r, cor.g, cor.b, cor.a);

	//	Desenha um texto
	gGraficos.desenharTexto("Arco", x, y - 30);
}

void Jogo::desenharSemiCirculo()
{
	Cor cor(255, 255, 255, 255);
	int x = 350;
	int y = 60;
	int raio = 10;
	int anguloMin = 0;
	int anguloMax = 270;

	//	Desenhar o semi-circulo (aberto)
	gGraficos.desenharSemiCirculo(x, y, raio, anguloMin, anguloMax, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o semi-circulo (fechado)
	y += 50;
	gGraficos.desenharSemiCirculo(x, y, raio, anguloMin, anguloMax, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Semi-círculo", x, y - 80);
}

void Jogo::desenharCirculo()
{
	Cor cor(255, 255, 255, 255);
	int x = 450;
	int y = 60;
	int raio = 10;

	//	Desenhar o circulo (aberto)
	gGraficos.desenharCirculo(x, y, raio, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o circulo (fechado)
	y += 50;
	gGraficos.desenharCirculo(x, y, raio, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Círculo", x, y - 80);
}

void Jogo::desenharElipse()
{
	Cor cor(255, 255, 255, 255);
	int x = 550;
	int y = 60;
	int raioX = 20;
	int raioY = 10;

	//	Desenhar a elipse (aberto)
	gGraficos.desenharElipse(x, y, raioX, raioY, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar a elipse (fechado)
	y += 50;
	gGraficos.desenharElipse(x, y, raioX, raioY, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Elipse", x, y - 80);
}

void Jogo::desenharRetangulo()
{
	Cor cor(255, 255, 255, 255);
	int x = 50;
	int y = 200;
	int larg = 35;
	int alt  = 20;
	Quad retan(x - larg/2, y - alt/2, larg, alt);

	//	Desenhar o retângulo (aberto)
	gGraficos.desenharRetangulo(retan, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o retângulo (fechado)
	retan.y += 50;
	gGraficos.desenharRetangulo(retan, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Retângulo", x, y - 30);
}

void Jogo::desenharRetanguloRotacionado()
{
	Cor cor(255, 255, 255, 255);
	int x = 150;
	int y = 200;
	int larg = 35;
	int alt = 20;
	float rot = 20.0f;
	float ancoraX = 0.5;
	float ancoraY = 0.5;

	//	Desenhar o retângulo (aberto)
	gGraficos.desenharRetangulo(x, y, rot, larg, alt, ancoraX, ancoraY, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o retângulo (fechado)
	y += 50;
	gGraficos.desenharRetangulo(x, y, rot, larg, alt, ancoraX, ancoraY, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Retângulo\nRotacionado", x, y - 80);
}

void Jogo::desenharRetanguloArredondado()
{
	Cor cor(255, 255, 255, 255);
	int x = 250;
	int y = 200;
	int larg = 40;
	int alt = 20;
	float ancoraX = 0.5;
	float ancoraY = 0.5;
	float raio = 5.0f;

	//	Desenhar o retângulo arredondado (aberto)
	gGraficos.desenharRetanguloArredondado(x, y, larg, alt, ancoraX, ancoraY, raio, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o retângulo arredondado (fechado)
	y += 50;
	gGraficos.desenharRetanguloArredondado(x, y, larg, alt, ancoraX, ancoraY, raio, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Retângulo\nArredondado", x, y - 80);
}

void Jogo::desenharTriangulo()
{
	Cor cor(255, 255, 255, 255);
	int x = 350;
	int y = 200;
	float rot = 30;
	Vetor2D pontos[3];
	pontos[0].set(+20, -20);
	pontos[1].set(-20, -10);
	pontos[2].set(+5,  +30);


	//	Desenhar o triângulo (aberto) - Um triângulo é um polígono de 3 vértices!
	gGraficos.desenharPoligono(x, y, rot, pontos, 3, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o triângulo (fechado) - Um triângulo é um polígono de 3 vértices!
	y += 50;
	gGraficos.desenharPoligono(x, y, rot, pontos, 3, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Triângulo", x, y - 80);
}

void Jogo::desenharPoligono()
{
	Cor cor(255, 255, 255, 255);
	int x = 450;
	int y = 200;
	float rot = 30;
	Vetor2D pontos[5];
	pontos[0].set(+20, -20);
	pontos[1].set(-20, -10);
	pontos[2].set(-15, +20);
	pontos[3].set(+5,  +30);
	pontos[4].set(+15, +10);


	//	Desenhar o polígono de 5 vértices (aberto)
	gGraficos.desenharPoligono(x, y, rot, pontos, 5, cor.r, cor.g, cor.b, cor.a);

	//	Desenhar o polígono de 5 vértices (fechado)
	y += 50;
	gGraficos.desenharPoligono(x, y, rot, pontos, 5, cor.r, cor.g, cor.b, cor.a, true);

	//	Desenha um texto
	gGraficos.desenharTexto("Polígono", x, y - 80);
}

