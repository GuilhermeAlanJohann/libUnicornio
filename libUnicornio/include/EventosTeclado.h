#ifndef UNI_EVENTOSTECLADO_H
#define UNI_EVENTOSTECLADO_H

#include "uniAPI.h"
#include "EnumsInputs.h"
#include "EventosInputTexto.h"

class UNI_API EventosTeclado
{
public:
	EventosTeclado();
	~EventosTeclado();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	Uint8 *pressionou;
	Uint8 *segurando;
	Uint8 *soltou;

	EventosInputTexto inputTexto;
};

#endif