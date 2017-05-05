#include "EventosInputTexto.h"
#include <algorithm>
#include "uniPlataformas.h"

using namespace std;

#if !UNI_PLATAFORMA_ANDROID
#include <locale>
#include <codecvt>
#endif

EventosInputTexto::EventosInputTexto()
{
	pos_cursor = 0;
	tamanho_selecao = 0;
	habilitado = false;
}

EventosInputTexto::~EventosInputTexto()
{}

void EventosInputTexto::habilitar()
{
	SDL_StartTextInput();
	habilitado = true;

	pos_cursor = 0;
	tamanho_selecao = 0;
	str.clear();
}

void EventosInputTexto::desabilitar()
{
	habilitado = false;
	SDL_StopTextInput();

	pos_cursor = 0;
	tamanho_selecao = 0;
	str.clear();
}

bool EventosInputTexto::estaHabilitado()
{
	return habilitado;
}

std::string EventosInputTexto::getString()
{
	return str;
}

void EventosInputTexto::setString(std::string s)
{
	str = s;
	if(pos_cursor > (int)str.size())
		pos_cursor = (int)str.size();

	tamanho_selecao = 0;
}

void EventosInputTexto::inserir(std::string s)
{
	int pos = min(pos_cursor, pos_cursor + tamanho_selecao);
	int tam = max(tamanho_selecao, -tamanho_selecao);
	str.replace(pos, tam, s);
	pos_cursor = pos + (int)s.size();
	tamanho_selecao = 0;
}

void EventosInputTexto::inserir(char c)
{
	int pos = min(pos_cursor, pos_cursor + tamanho_selecao);
	int tam = max(tamanho_selecao, -tamanho_selecao);
	str.replace(pos, tam, 1, c);
	pos_cursor = pos + 1;
	tamanho_selecao = 0;
}

void EventosInputTexto::apagar()
{
	if(str.length() == 0)
		return;

	if(tamanho_selecao)
	{
		int pos = min(pos_cursor, pos_cursor + tamanho_selecao);
		int tam = max(tamanho_selecao, -tamanho_selecao);
		str.erase(str.begin() + pos, str.begin() + pos + tam);
		pos_cursor = pos;
	}
	else
	{
		str.erase(str.begin() + pos_cursor -1);
		pos_cursor -= 1;
	}

	tamanho_selecao = 0;
	if(pos_cursor < 0)
		pos_cursor = 0;
	if (pos_cursor > str.size())
		pos_cursor = str.size();
}

void EventosInputTexto::apagarTudo()
{
	str.clear();
	pos_cursor = 0;
	tamanho_selecao = 0;
}

std::string EventosInputTexto::getStringSelecao()
{
	std::string s;
	if(tamanho_selecao)
	{
		int pos = min(pos_cursor, pos_cursor + tamanho_selecao);
		int tam = max(tamanho_selecao, -tamanho_selecao);
		s = std::string(str.begin() + pos, str.begin() + pos + tam);
	}
	
	return s;
}

void EventosInputTexto::apagarStringSelecao()
{
	if(tamanho_selecao)
	{
		int pos = min(pos_cursor, pos_cursor + tamanho_selecao);
		int tam = max(tamanho_selecao, -tamanho_selecao);
		str.erase(str.begin() + pos, str.begin() + pos + tam);
		pos_cursor = pos;

		tamanho_selecao = 0;
		if(pos_cursor < 0)
			pos_cursor = 0;
		if (pos_cursor > str.size())
			pos_cursor = str.size();
	}
}

int EventosInputTexto::getPosCursor()
{
	return pos_cursor;
}

void EventosInputTexto::setPosCursor(int pos)
{
	if(pos < 0)
		pos = 0;
	else if(pos > (int)str.size())
		pos = (int)str.size();

	pos_cursor = pos;
}

int EventosInputTexto::getTamanhoSelecao()
{
	return tamanho_selecao;
}

void EventosInputTexto::setTamanhoSelecao(int tam)
{
	if(tam + pos_cursor < 0)
		tam = -pos_cursor;
	else if(tam + pos_cursor > (int)str.size())
		tam = (int)str.size() - pos_cursor;

	tamanho_selecao = tam;
}

void EventosInputTexto::selecionar(int pos_inicio, int pos_fim)
{
	if(pos_inicio < 0)
		pos_inicio = 0;
	else if(pos_inicio > (int)str.size())
		pos_inicio = (int)str.size();

	if(pos_fim < 0)
		pos_fim = 0;
	else if(pos_fim > (int)str.size())
		pos_fim = (int)str.size();

	pos_cursor = pos_fim;
	tamanho_selecao = pos_inicio - pos_fim;
}

void EventosInputTexto::selecionarTudo()
{
	pos_cursor = (int)str.size();
	tamanho_selecao = -(int)str.size();
}

void EventosInputTexto::moverPosCursorParaDir()
{
	pos_cursor += 1;
	if(pos_cursor > (int)str.size())
		pos_cursor = (int)str.size();

	tamanho_selecao = 0;
}

void EventosInputTexto::moverPosCursorParaEsq()
{
	pos_cursor -= 1;
	if(pos_cursor < 0)
		pos_cursor = 0;

	tamanho_selecao = 0;
}

void EventosInputTexto::moverPosCursorParaInicio()
{
	pos_cursor = 0;
	tamanho_selecao = 0;
}

void EventosInputTexto::moverPosCursorParaFim()
{
	pos_cursor = (int)str.size();
	tamanho_selecao = 0;
}

void EventosInputTexto::moverSelecaoParaDir()
{
	pos_cursor += 1;
	if(pos_cursor > (int)str.size())
	{
		pos_cursor = (int)str.size();
	}
	else
	{
		tamanho_selecao -= 1;
		if(tamanho_selecao + pos_cursor < 0)
			tamanho_selecao += 1;
	}
}

void EventosInputTexto::moverSelecaoParaEsq()
{
	pos_cursor -= 1;
	if(pos_cursor < 0)
	{
		pos_cursor = 0;
	}
	else
	{
		tamanho_selecao += 1;
		if(tamanho_selecao + pos_cursor > (int)str.size())
			tamanho_selecao -= 1;
	}
}

void EventosInputTexto::moverSelecaoParaInicio()
{
	if(tamanho_selecao > 0)
	{
		tamanho_selecao = pos_cursor + tamanho_selecao;
	}
	else
	{
		tamanho_selecao = pos_cursor;
	}
	
	pos_cursor = 0;
}

void EventosInputTexto::moverSelecaoParaFim()
{
	tamanho_selecao = (pos_cursor + tamanho_selecao) - (int)str.size();
	pos_cursor = (int)str.size();
}

void EventosInputTexto::atualizar()
{
}

void EventosInputTexto::processarEvento(const SDL_Event& evento)
{
	switch(evento.type)
	{
	case SDL_TEXTINPUT:
		{
		#if UNI_PLATAFORMA_ANDROID
		    inserir(evento.text.text);
		#else
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			std::wstring ws = converter.from_bytes(evento.text.text);

			std::string s;
			for(unsigned int i = 0; i < ws.size(); ++i)
				s.push_back((char)ws[i]);

			inserir(s);
		#endif
		}
		break;

	case SDL_TEXTEDITING:
		// Faz nada. Estou tratando edicao de texto de outra maneira.
		break;
	}
}