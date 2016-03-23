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

	//	1) Carrega o arquivo de preferencias (arquivo contendo as configurações e saves do usuário).
	//	Se o arquivo ainda não existe, nenhum erro acontece e as preferências ficam vazias. 
	//	Um novo arquivo com este nome será criado quando o método 'salvar' for chamado.
	prefs.carregar("assets/preferencias/prefs");


	//	2) Obtem os dados do jogador contidos no arquivo, 
	//	passando como parâmetro o nome do dado e o valor padrão para esse dado.
	//	Esses valores serão retornados caso o arquivo não contenha um dado com este nome.
	dados.nome = prefs.getString("nome", "Player1");
	dados.pontos = prefs.getInt("pontos", 0);
	for (int i = 0; i < NUM_ACHIVEMENTS; ++i)	//	prenche o vetor com valores padrões 
		dados.achievements.push_back(false);
	dados.achievements = prefs.getVetorDeBool("achievements", dados.achievements);
}

void Jogo::finalizar()
{
	//	4)	Quando for conveniente (Ex: quando o jogador está saindo do jogo),
	//	salva o arquivo de preferências para poder carregar as informações na 
	//	próxima vez que o jogo inicializar
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
	//	Se o dado com esse nome não existe, então ele é criado.
	//	Ao passar os dados para o arquivo, eles NÃO são salvos automaticamente.
	//	Para salvar é necesario chamar o método 'salvar'. 
	//	Mas não vamos fazer isso agora. Somente quando o jogodor sair do jogo.

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
		"Instruções: \n"
		"Pressione [1], [2], ou [3] para completar/descompletar os achievements. \n"
		"Pressione [+], [-] para almentar, diminuir a pontuação. \n"
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
