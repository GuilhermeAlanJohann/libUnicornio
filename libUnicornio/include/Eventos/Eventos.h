#ifndef UNI_EVENTOS_H
#define UNI_EVENTOS_H

#include "SDL_events.h"
#include "SDL_joystick.h"
#include "InputEnums.h"
#include <vector>
#include <queue>

class EventosMouse
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

private:
	void corrigirPosicaoFullscreen();
};

class EventosInputTexto
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

class EventosTeclado
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

struct Joystick
{
public:
	Joystick(): id(-1), deadZone(0.2f), x(0), y(0), xDir(0), yDir(0), js(NULL)
	{
		for(int i = 0; i < NUMERO_DE_BOTOES_JOYSTICK; ++i)
		{
			pressionou[i] = false;
			segurando[i] = false;
			soltou[i] = false;
		}
	};
	~Joystick()
	{};

	int id;

	float deadZone;

	float x;
	float y;

	float xDir;
	float yDir;

	bool pressionou[NUMERO_DE_BOTOES_JOYSTICK];
	bool segurando[NUMERO_DE_BOTOES_JOYSTICK];
	bool soltou[NUMERO_DE_BOTOES_JOYSTICK];

	SDL_Joystick *js;
};

class EventosJoysticks
{
public:
	EventosJoysticks();
	~EventosJoysticks();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	Joystick player1;
	Joystick player2;
	Joystick player3;
	Joystick player4;

private:
	Joystick *identificarJoystick(const int id);
	Joystick *getPrimeiroJoystickLivre();
	void filtrarInput(float& f, Joystick* joy);

	static int nextId;
};

struct Toque
{
public:
	TipoToque tipo;

	int x;
	int y;
	int dx;
	int dy;

	float nx;
	float ny;
	float ndx;
	float ndy;

	float pressao;

	int64_t idDedo;
};

class EventosTelaDeToque
{
public:
	EventosTelaDeToque();
	~EventosTelaDeToque();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	std::vector<Toque> pressionou;
	std::vector<Toque> segurando;
	std::vector<Toque> soltou;
	std::vector<Toque> moveu;

	std::vector<Toque> getTodosToques();

private:
	Toque gerarToque(const SDL_TouchFingerEvent& evento);
	void calcularPosicaoEmPixels(Toque& toque);
	void corrigirPosicaoFullscreen(Toque& toque);
};

class EventosiOS
{
public:
	EventosiOS();
	~EventosiOS();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	bool appEstaTerminando;
	bool appTemPoucaMemoria;
	bool appVaiEntrarEmPlanoDeFundo;
	bool appEntrouEmPlanoDeFundo;
	bool appVaiEntrarEmPrimeiroPlano;
	bool appEntrouEmPrimeiroPlano;
};

class EventosAplicacao
{
public:
	EventosAplicacao();
	~EventosAplicacao();

	void atualizar();
	void processarEvento(const SDL_Event& evento);

	bool sair;
	EventosiOS iOS;
};

class Eventos
{
public: 
	Eventos();
	~Eventos();

	void atualizar();

	void setUsarFila(bool b);
	bool estaUsandoFila();
	void limparFila();
	bool temEventoNaFila();
	SDL_Event tirarEventoDaFila();

	int registrarEventoDeUsuario();
	void adicionarEventoDeUsuario(int tipo, int codigo = 0, void *dado1 = NULL, void *dado2 = NULL);

	EventosAplicacao *aplicacao;
	EventosMouse *mouse;
	EventosTeclado *teclado;
	EventosJoysticks *joysticks;
	EventosTelaDeToque *telaDeToque;

private:
	std::queue<SDL_Event> fila_eventos;
	bool usandoFila;
};

#endif