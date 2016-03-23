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

	//	O resto da inicialização vem aqui!
	//	...

	//	1)	Carregar os arquivos de strings.
	//	Primeiro, carregamos o arquivo com a lingua principal.
	//	Depois as traduções, passando um nome (string) único, para cada um deles.
	gStrings.carregar("assets/strings/strings.json");
	gStrings.carregarTraducao("pt_BR", "assets/strings/strings-pt_BR.json");
	gStrings.carregarTraducao("it_IT", "assets/strings/strings-it_IT.json");
	gStrings.carregarTraducao("fr_FR", "assets/strings/strings-fr_FR.json");
	gStrings.carregarTraducao("es_ES", "assets/strings/strings-es_ES.json");

	//	Atualiza as stirngs usadas no jogo
	atualizarStrings();
}

void Jogo::finalizar()
{
	//	4) Quando as strings não são mais necessárias.
	//	Descarregar todas elas.	As traduções são descarregadas junto.
	gStrings.descarregar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		atualizarInput();
		desenharInstrucoes();
		desenharStrings();

		uniTerminarFrame();
	}
}

void Jogo::atualizarInput()
{
	//	3)	Durante o jogo, trocar a lingua/tradução conforme a escolha do jogador
	//	Isso é feito chamando o método 'setTraducao' passando com parâmetro o nome da traducao.
	//	Para retornar a lingua padrão, basta passar uma string vazia.
	if (gTeclado.pressionou[TECLA_1])
	{
		gStrings.setTraducao("");
		atualizarStrings();
	}
	else if (gTeclado.pressionou[TECLA_2])
	{
		gStrings.setTraducao("pt_BR");
		atualizarStrings();
	}
	else if (gTeclado.pressionou[TECLA_3])
	{
		gStrings.setTraducao("it_IT");
		atualizarStrings();
	}
	else if (gTeclado.pressionou[TECLA_4])
	{
		gStrings.setTraducao("fr_FR");
		atualizarStrings();
	}
	else if (gTeclado.pressionou[TECLA_5])
	{
		gStrings.setTraducao("es_ES");
		atualizarStrings();
	}
}

void Jogo::atualizarStrings()
{
	//	2)	Logo após mudar a tradução (ou logo após carregar), pegar as strings passando o nome delas 
	//	para o método 'getString'.
	//	O método retorna a string associada ao nome na lingua/tradução atual.
	//	Se uma string com esse nome não é encontrada na tradução atual, ele é procurando na tradução padrão. 
	//	Se mesmo assim não é encontrada, uma string vazia é retornada.

	name = gStrings.getString("Name");
	charName = gStrings.getString("CharName");

	class_ = gStrings.getString("Class");
	charClass = gStrings.getString("CharClass");

	description = gStrings.getString("CharDescription");
	skills = gStrings.getString("Skills");

	skillNames = gStrings.getVetorDeString("SkillNames");
}

void Jogo::desenharInstrucoes()
{
	string texto = "Instruções:\n"
		"Pressione [1], [2], [3], [4], ou [5] para trocar a língua do jogo.";

	gGraficos.desenharTexto(texto, 25, 25, 255, 255, 255, 255, 0, 0);
}

void Jogo::desenharStrings()
{
	int y = 150;
	string texto;
	texto = description + ": ";
	gGraficos.desenharTexto(texto, 50, y, 255, 255, 255, 255, 0, 0);
	texto = "    " + name + ": " + charName;
	y += 20;
	gGraficos.desenharTexto(texto, 50, y, 255, 255, 255, 255, 0, 0);
	texto = "    " + class_ + ": " + charClass;
	y += 20;
	gGraficos.desenharTexto(texto, 50, y, 255, 255, 255, 255, 0, 0);
	y += 20;
	texto = "    " + skills + ": ";
	gGraficos.desenharTexto(texto, 50, y, 255, 255, 255, 255, 0, 0);
	y += 20;
	for (int i = 0; i < skillNames.size(); ++i)
	{
		texto = "        " + to_string(i+1) + ") " + skillNames[i];
		gGraficos.desenharTexto(texto, 50, y, 255, 255, 255, 255, 0, 0);
		y += 20;
	}
}