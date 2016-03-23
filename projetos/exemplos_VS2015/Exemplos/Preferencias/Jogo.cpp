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

	//	1) Carrega o arquivo de preferencias (arquivo contendo as configura��es e saves do usu�rio).
	//	Se o arquivo ainda n�o existe, nenhum erro acontece e as prefer�ncias ficam vazias. 
	//	Um novo arquivo com este nome ser� criado quando o m�todo 'salvar' for chamado.
	prefs.carregar("assets/preferencias/prefs");


	//	2) Obtem os dados do jogador contidos no arquivo, 
	//	passando como par�metro o nome do dado e o valor padr�o para esse dado.
	//	Esses valores ser�o retornados caso o arquivo n�o contenha um dado com este nome.
	dados.nome = prefs.getString("nome", "Player1");
	dados.pontos = prefs.getInt("pontos", 0);
	for (int i = 0; i < NUM_ACHIVEMENTS; ++i)	//	prenche o vetor com valores padr�es 
		dados.achievements.push_back(false);
	dados.achievements = prefs.getVetorDeBool("achievements", dados.achievements);
}

void Jogo::finalizar()
{
	//	4)	Quando for conveniente (Ex: quando o jogador est� saindo do jogo),
	//	salva o arquivo de prefer�ncias para poder carregar as informa��es na 
	//	pr�xima vez que o jogo inicializar
	prefs.salvar();

	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();

		atualizar();
		desenharInstrucoes();
		desenhar();

		uniTerminarFrame();
	}
}

void Jogo::atualizar()
{
	//	3) Usa os dados ao logo do jogo e passa eles para o arquivo de preferencias informando o nome do dado.
	//	Se o dado com esse nome n�o existe, ent�o ele � criado.
	//	Ao passar os dados para o arquivo, eles N�O s�o salvos automaticamente.
	//	Para salvar � necesario chamar o m�todo 'salvar'. 
	//	Mas n�o vamos fazer isso agora. Somente quando o jogodor sair do jogo.

	if (gTeclado.pressionou[TECLA_1])
	{
		dados.achievements[0] = !dados.achievements[0];
		prefs.setVetorDeBool("achievements", dados.achievements);
	}
	if (gTeclado.pressionou[TECLA_2])
	{
		dados.achievements[1] = !dados.achievements[1];
		prefs.setVetorDeBool("achievements", dados.achievements);
	}
	if (gTeclado.pressionou[TECLA_3])
	{
		dados.achievements[2] = !dados.achievements[2];
		prefs.setVetorDeBool("achievements", dados.achievements);
	}

	if (gTeclado.pressionou[TECLA_ENTER])
	{
		dados.nome = "Meu Nome";
		prefs.setString("nome", dados.nome);
	}
	if (gTeclado.pressionou[TECLA_KP_MAIS])
	{
		dados.pontos += 10;
		prefs.setInt("pontos", dados.pontos);
	}
	if (gTeclado.pressionou[TECLA_KP_MENOS])
	{
		dados.pontos -= 10;
		prefs.setInt("pontos", dados.pontos);
	}
}

void Jogo::desenharInstrucoes()
{
	string texto =
		"Instru��es: \n"
		"Pressione [1], [2], ou [3] para completar/descompletar os achievements. \n"
		"Pressione [+], [-] para almentar, diminuir a pontua��o. \n"
		"Pressione [ENTER] para mudar o nome do jogador para 'Meu Nome'. \n";

	gGraficos.desenharTexto(texto, 25, 25, 255, 255, 255, 255, 0, 0);
}

void Jogo::desenhar()
{
	int y = 150;
	gGraficos.desenharTexto("nome: ", 150, y, 255, 255, 255, 255, 0, 0);
	gGraficos.desenharTexto(dados.nome, 160, y + 20, 255, 255, 255, 255, 0, 0);

	y += 50;
	gGraficos.desenharTexto("pontos: ", 150, y, 255, 255, 255, 255, 0, 0);
	gGraficos.desenharTexto(to_string(dados.pontos), 160, y + 20, 255, 255, 255, 255, 0, 0);

	y += 50;
	for (int i = 0; i < NUM_ACHIVEMENTS; ++i)
	{
		gGraficos.desenharTexto("achivement_" + to_string(i) + ": ", 150, y, 255, 255, 255, 255, 0, 0);
		gGraficos.desenharTexto(to_string((int)dados.achievements[i]), 160, y + 20, 255, 255, 255, 255, 0, 0);
		y += 50;
	}
}
