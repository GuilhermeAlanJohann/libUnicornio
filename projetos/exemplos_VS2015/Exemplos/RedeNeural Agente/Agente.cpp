#include "Agente.h"
#include "Ambiente.h"

RedeNeural Agente::rede = RedeNeural();

Agente::Agente()
{
}

Agente::~Agente()
{
}

void Agente::inicializar(Ambiente* ambiente)
{
	//	Guarda o ponteiro para o ambiente
	this->ambiente = ambiente;

	//	Seta SprteSheet, posi��o aleat�ria, rota��o 0
	spr.setSpriteSheet("branco");
	pos = uniRandEntre(Vetor2D(0, 0), Vetor2D(gJanela.getLargura(), gJanela.getAltura()));
	rot = 0;	

	dir.set(1, 0);				//	Dire��o atual
	dirIdeal.set(1, 0);			//	Dire��o ideal

	vel = 40.0f;				//	Velocidade de movimento
	velRot = 180.0f;			//	Velocidade de rota��o
	treinando = true;			//	booleana que diz se est� treinando a rede
	_desenharSensores = true;	//	booleana que diz se est� desenhando os sensores

	//	O n�mero de sensores � igual ao n�mero de comidas no ambiente
	numSensores = NUM_COMIDAS;

	//	vector que descreve a topologia da rede neural
	//		Neste caso, queremos uma rede com:
	//		2 Neur�nios na camada de entrada
	//		3 Neur�nios na primeira camada oculta
	//		3 Neur�nios na segunda  camada oculta
	//		1 Neur�nio  na camada de saida
	vector<unsigned int> topologia;
	topologia.push_back(2);
	topologia.push_back(3);
	topologia.push_back(3);
	topologia.push_back(1);

	//	1) Inicializar a rede passando a topologia como par�metro
	rede.inicializar(topologia);

	//	2)	Muda a fun��o de ativa��o da rede.
	//		Isse par�metro depende do tipo de problema que a rede vai resolver.
	//		A fun��o de ativa��o define como os valores da rede ser�o transmitidos de um neur�nio para o outro.
	//		Ela aplica uma suaviza��o nesses valores, transformando-os em valores entre um n�mero e outro.
	//		Por padr�o, a rede usa a fun��o de ativa��o sigmoid (FUNCAO_DE_ATIVACAO_RN_SIGMOID), que retorna 
	//		valores entre 0.0 e 1.0.
	//		Mas para pra este problema, vamos usar a funcao de ativacao tanagente hiporbolica, que retorna 
	//		valores entre -1.0 e 1.0;
	rede.setFuncaoDeActivacao(FUNCAO_DE_ATIVACAO_RN_TANH);
}

void Agente::atualizar()
{
	atualizarSensores();

	vector<double> entradas;
	vector<double> saidas;
	float rotIdeal;		//	Sa�da desejada;

	//	Se os sensores n�o est�o vazios, 
	//		Muda a dire��o ideal (dire��o desejada).
	//	Se os sensores est�o vazios, n�o muda, continua na mesma dire��o
	if (!sensores.empty())
	{
		dirIdeal = sensores.begin()->dist;
		dirIdeal.normalizar();
	}

	//	3) Calcula os valores de entrada e a rota��o ideal (sa�da desejada)
	//		As entradas para este exemplo s�o os angulos dos vetores de dire��o atual
	//		e da dire��o ideal (dire��o desejada)
	double angulo = dir.getAnguloAteVetor(dirIdeal);	//	�ngulo entre os dois vetores;
	double ang0 = dir.getAngulo();						//	�ngulo em rela��o ao eixo x+;
	double ang1 = dirIdeal.getAngulo();					//	�ngulo em rela��o ao eixo x+;

	rotIdeal = angulo / 180.f;							//	Divide por 180 para ter valores entre -1 e +1;
	entradas.push_back(ang0 / 180.0f);					//	Divide por 180 para ter valores entre -1 e +1;
	entradas.push_back(ang1 / 180.0f);					//	Divide por 180 para ter valores entre -1 e +1;

	//	4)	Alimenta a rede
	rede.alimentar(entradas);

	//	5) Pega os resultados
	saidas = rede.getResultados();

	
	//	6) Aplica os resultados
	//		Rota��o
	double r = saidas[0];
	r *= velRot * gTempo.getDeltaTempo();
	rot += r;
	//		Mantem a rota��o entre -360 e +360
	if (rot > 360.0f)
		rot -= 360.0f;
	else if (rot < -360.0f)
		rot += 360.0f;

	//		Transla��o
	dir.normalizar();
	dir.rotacionar(r);
	pos += dir * vel * gTempo.getDeltaTempo();

	//	7) Se est� treinando, faz a retropropaga��o
	if (treinando)
	{
		vector<double> saidasIdeais;
		saidasIdeais.push_back(rotIdeal);
		rede.retropropagar(saidasIdeais);
	}

	//	Se saiu da tela, coloca de volta do outro lado
	if (pos.x > gJanela.getLargura())
		pos.x = 0;
	else if (pos.x < 0)
		pos.x = gJanela.getLargura();

	if (pos.y > gJanela.getAltura())
		pos.y = 0;
	else if (pos.y < 0)
		pos.y = gJanela.getAltura();
}

void Agente::desenhar()
{
	spr.desenhar(pos.x, pos.y, rot);

	if (_desenharSensores)
		desenharSensores();
}

void Agente::atualizarSensores()
{
	//	Atualiza os sensores.
	//	Basicamente o que esse c�digo faz � criar um lista de sensores
	//	ordenados pela distancia. Os mais pr�ximos primeiro.
	//	Por�m n�o inclui os sensores que est�o atr�s do agente.
	sensores.clear();
	float compMaior = 0;
	list<Sensor>::iterator it;

	for (unsigned int i = 0; i < NUM_COMIDAS; ++i)
	{
		Sensor s;
		s.comida = &ambiente->getComida(i);
		s.dist = s.comida->pos - pos;
		s.comprimento = s.dist.comprimento();

		//	Exclui os sensores que est�o atras do agente
		double angulo = dir.getAnguloAteVetor(s.dist);
		if (angulo < -90.0 || angulo > 90.0)
			continue;

		//	Se n�o tem nenhum sensor ainda, insere o primeiro
		if (sensores.empty())
		{
			sensores.push_back(s);
			continue;
		}

		//	Faz a inser��o ordenada os sensores
		for (it = sensores.begin(); it != sensores.end(); ++it)
		{
			if (s.comprimento < it->comprimento)
			{
				sensores.insert(it, s);
				break;
			}
			else if (sensores.size() < numSensores)
				sensores.push_back(s);
		}
	}
}

void Agente::desenharSensores()
{
	list<Sensor>::iterator it;
	for (it = sensores.begin(); it != sensores.end(); ++it)
	{
		Vetor2D dir = this->dir;
		Vetor2D dirC = it->dist;
		dirC.normalizar();

		gGraficos.desenharLinha(pos.x, pos.y, it->comida->pos.x, it->comida->pos.y, 255, 0, 255);
	}

	gGraficos.desenharLinha(pos.x, pos.y, pos.x + dirIdeal.x * 40, pos.y + dirIdeal.y * 40, 0, 255, 0);
	gGraficos.desenharLinha(pos.x, pos.y, pos.x + dir.x * 40, pos.y + dir.y * 40, 255, 255, 255);
}

Vetor2D Agente::getPos()
{
	return pos;
}

float Agente::getRot()
{
	return rot;
}

Sprite& Agente::getSprite()
{
	return spr;
}

RedeNeural* Agente::getRede()
{
	return &rede;
}

void Agente::setTreinando(bool b)
{
	treinando = b;
}

bool Agente::getTreinando()
{
	return treinando;
}

void Agente::setDesenharSensores(bool b)
{
	_desenharSensores = b;
}

bool Agente::getDesenharSensores()
{
	return _desenharSensores;
}