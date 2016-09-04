#ifndef UNI_EVENTOSMOUSE_H
#define UNI_EVENTOSMOUSE_H

#include "uniAPI.h"
#include "EnumsInputs.h"

class UNI_API EventosMouse
{
public:
	EventosMouse();
	~EventosMouse();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	int x;
	int y;
	int dx;
	int dy;
	float nx;
	float ny;
	float ndx;
	float ndy;
	int roda;

	bool pressionou[NUMERO_DE_BOTOES_MOUSE];
	bool segurando[NUMERO_DE_BOTOES_MOUSE];
	bool soltou[NUMERO_DE_BOTOES_MOUSE];

	void esconderCursor();
	void mostrarCursor();

	void posicionarEm(int x, int y);

	bool estaLimitandoPosicao();
	void setLimitandoPosicao(bool limitar);

private:
	//	corrige a posicao conforme letterboxing da janela
	void corrigirPosicao();
	void limitarPosicao();
	bool limitandoPos;
};

#endif