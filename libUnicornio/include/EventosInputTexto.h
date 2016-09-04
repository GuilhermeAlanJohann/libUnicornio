#ifndef UNI_EVENTOSINPUTTEXTO_H
#define UNI_EVENTOSINPUTTEXTO_H

#include "uniAPI.h"
#include "SDL_events.h"
#include <string>

class UNI_API EventosInputTexto
{
public:
	EventosInputTexto();
	~EventosInputTexto();

	void habilitar();
	void desabilitar();
	bool estaHabilitado();

	std::string getString();
	void setString(std::string s);
	void inserir(std::string s);
	void inserir(char c);
	void apagar();
	void apagarTudo();

	std::string getStringSelecao();
	void apagarStringSelecao();

	int getPosCursor();
	void setPosCursor(int pos);

	int getTamanhoSelecao();
	void setTamanhoSelecao(int tam);

	void selecionar(int pos_inicio, int pos_fim);
	void selecionarTudo();

	void moverPosCursorParaDir();
	void moverPosCursorParaEsq();
	void moverPosCursorParaInicio();
	void moverPosCursorParaFim();
	void moverSelecaoParaDir();
	void moverSelecaoParaEsq();
	void moverSelecaoParaInicio();
	void moverSelecaoParaFim();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

private:
	std::string str;
	int pos_cursor;
	int tamanho_selecao;
	bool habilitado;
};

#endif