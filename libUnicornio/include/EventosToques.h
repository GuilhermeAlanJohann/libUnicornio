#ifndef UNI_EVENTOSTELADETOQUE_H
#define UNI_EVENTOSTELADETOQUE_H

#include "uniAPI.h"
#include "Toque.h"
#include <vector>

class UNI_API EventosToques
{
public:
	EventosToques();
	~EventosToques();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	std::vector<Toque> pressionou;
	std::vector<Toque> segurando;
	std::vector<Toque> soltou;
	std::vector<Toque> moveu;

	std::vector<Toque> getTodosToques();

	bool estaLimitandoPosicao();
	void setLimitandoPosicao(bool limitar);

private:
	Toque gerarToque(const SDL_TouchFingerEvent& evento);
	void calcularPosicaoEmPixels(Toque& toque);
	//void corrigirPosicaoFullscreen(Toque& toque);

	void limitarPosicao(Toque& toque);
	bool limitandoPos;
};

#endif