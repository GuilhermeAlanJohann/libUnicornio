#pragma once

#include <string>
#include <vector>

using namespace std;

/*
Estrutura que guarda os dados do jogador.
Esses dados serão salvos quando o jogador sair do jogo  (ou em outro momento, dependendo do jogo)
e carregados quando ele entrar novamente.
*/

struct DadosDoJogador
{
	string nome;
	int pontos;
	vector<bool> achievements;
};
