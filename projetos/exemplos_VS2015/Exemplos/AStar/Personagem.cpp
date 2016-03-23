#include "Personagem.h"
#include "Mapa.h"


Personagem::Personagem()
{
}

Personagem::~Personagem()
{
}

void Personagem::inicializar(Mapa* mapa)
{
	//	seta spritesheet
	spr.setSpriteSheet("player");
	//	guarda ponteiro para o mapa
	this->mapa = mapa;
	//	não calcula o caminho no inicio
	calc_caminho = false;

	do
	{
		//	Sorteia posição aleatória
		pos.x = uniRandEntre(0, mapa->getTilesEmX() - 1) + 0.5;
		pos.y = uniRandEntre(0, mapa->getTilesEmY() - 1) + 0.5;
		
		//	Enquanto está em uma posição não caminhavel
	} while (!mapa->getAStar()->getNodo(pos.x, pos.y)->caminhavel);

	//	seta posição inicial da travessia
	travessia.setPos(pos);
}

void Personagem::atualizar()
{
	//	Se pressionou botão esquerdo do mouse
	if (gMouse.pressionou[BOTAO_MOUSE_ESQ])
	{
		//	interrompe a travessia e calcula a posição do destino
		travessia.interromper();
		mapa->telaParaTile(gMouse.x, gMouse.y, destino.x, destino.y);
		calc_caminho = true;
	}
	//	Se precisa parou a travessia e precisa recalcular
	else if (calc_caminho && travessia.estaParado())
	{
		//	Calcula caminho e passa ele para a travessia
		mapa->getAStar()->calcularCaminho(pos, destino);
		travessia.setCaminho(mapa->getAStar()->getCaminho());
		calc_caminho = false;
	}
	//	Se não,
	else
	{
		//	Avança atravessia e seta a posição
		travessia.avancar();
		pos = travessia.getPos();
	}
}

void Personagem::desenhar()
{
	//	Desenhar
	int x, y;
	mapa->tileParaTela(pos.x, pos.y, x, y);
	spr.desenhar(x, y);
}