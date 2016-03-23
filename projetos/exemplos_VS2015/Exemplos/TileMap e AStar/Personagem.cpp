#include "Personagem.h"


Personagem::Personagem()
{
	objeto = NULL;
	dest_x = dest_y = 0;
	calcular_caminho = false;
}

Personagem::~Personagem()
{
}

void Personagem::inicializar(string sheet, ObjetoTileMap* objeto, AStar* astar)
{
	//	setar spritesheet
	spr.setSpriteSheet(sheet);

	//	setar ancora para os pes do personagem
	spr.setAncora(0.5, 0.75);

	//	set vel anim (4 frames por segundo)
	spr.setVelocidadeAnimacao(4.0);

	//	guardar o ponteiro do objeto
	this->objeto = objeto;

	//	guarda o ponteiro do A*
	this->astar = astar;

	//	setar sprite para o objeto
		//	ao fazer isso, o sprite passa a ser desenhado automaticamente junto com o mapa,na posicao central do objeto, 
		//	entao nao precisamos chamar spr.desenhar(x, y)
	objeto->setSprite(&spr);

	//	setar a velocidade de travessia
	travessia.setVelocidade(2.0f);
	//	(Opcional) setar o deslocamento em tiles. O padrão já é (0.5f, 0.5f)
	travessia.setDeslocamento(0.5f, 0.5f);
}

void Personagem::processarCliqueMouse(float mx, float my)
{
	//	interrompe a travessia
	//	chamar esse método não causa interrupção imediata.
	//	O algoritmo tenta parar no proximo nodo
	travessia.interromper();

	//	seta o destino do proximo caminho
	dest_x = mx;
	dest_y = my;
	calcular_caminho = true;
}

void Personagem::atualizar()
{
	atualizarTravessia();
	atualizarAnimacao();
}

Vetor2D Personagem::getPos()
{
	return objeto->getPosCentro();
}

void Personagem::atualizarTravessia()
{
	//	avanca a travessia
	travessia.avancar();

	//	espera o travessia parar para calcular um novo caminho
	if (calcular_caminho && travessia.estaParado())
	{
		//	calcula o caminho que vai da posicao atual até o destino
		Vetor2D pos = objeto->getPosCentro();
		bool existe_caminho = astar->calcularCaminho(pos.x, pos.y, dest_x, dest_y);

		//	se existe caminho até o destino, seta ele para algoritmo de travessia, passando 'true' para reiniciar
		if (existe_caminho)
			travessia.setCaminho(astar->getCaminho(), true);

		//	já calculamos o caminho, então...
		calcular_caminho = false;
	}

	//	posiciona o ObjetoTileMap na posicao atual da travessia
	if(!travessia.caminhoEstaVazio())
		objeto->setPosCentro(travessia.getPos());
}

void Personagem::atualizarAnimacao()
{
	//	avançar anim
	spr.avancarAnimacao();

	//	pega a direcao do movimento
	Vetor2D dir = travessia.getDirecao();

	//	setar anim conforme a direcao
	if (dir.x > 0.0)
		spr.setAnimacao(ANIMACAO_DIR);
	else if (dir.x < 0.0)
		spr.setAnimacao(ANIMACAO_ESQ);
	else if (dir.y > 0.0)
		spr.setAnimacao(ANIMACAO_BAIXO);
	else if (dir.y < 0.0)
		spr.setAnimacao(ANIMACAO_CIMA);
	else
		spr.recomecarAnimacao();		//	para ficar parado
}