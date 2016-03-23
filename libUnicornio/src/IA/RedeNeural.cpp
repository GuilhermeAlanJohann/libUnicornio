#include "RedeNeural.h"
#include "Global.h"
#include <sstream>

RedeNeural::RedeNeural(void)
{
	numEntradas = 0;
	numSaidas = 0;
	bias = 1.0;
	taxaDeAprendizado = 0.2;
	momentum = 0.5;
	atenuacaoDeErroMedioRecente = 0.5;
	setFuncaoDeActivacao(FUNCAO_DE_ATIVACAO_RN_SIGMOID);
}

RedeNeural::~RedeNeural(void)
{
}

bool RedeNeural::inicializar(const vector<unsigned int> &topologia)
{
	if (topologia.empty())
	{
		gDebug.erro("RedeNeural não pode ser inicializada com topologia vazia.", this);
		return false;
	}

	int numCamadas = topologia.size();

	numEntradas = topologia[0];
	numSaidas = topologia[numCamadas-1];

	camadas.resize(numCamadas);
	for(int i = 0; i < numCamadas -1; ++i)
	{
		unsigned int numNeuronios = topologia[i] + 1;
		camadas[i].resize(numNeuronios);
		for (unsigned int j = 0; j < numNeuronios; ++j)
			camadas[i][j] = Neuronio(topologia[i + 1]);
		camadas[i][numNeuronios - 1].valorDeSaida = bias;
	}

	//	última camada
	unsigned int numNeuronios = topologia.back() + 1;
	camadas.back().resize(numNeuronios);
	for (unsigned int j = 0; j < numNeuronios; ++j)
		camadas.back()[j] = Neuronio(0);

	//	último neurônio
	camadas.back().back().valorDeSaida = bias;

	return true;
}

bool RedeNeural::inicializar(const vector<unsigned int> &topologia, const vector<vector<double>> &pesos)
{
	if (topologia.empty())
	{
		gDebug.erro("RedeNeural não pode ser inicializada com topologia vazia.", this);
		return false;
	}

	int numCamadas = topologia.size();

	int numPesos = 0;
	int numConex = 0;
	for (int i = 0; i < numCamadas - 1; ++i)
		numConex += (topologia[i] + 1) * topologia[i + 1];
	
	for (int i = 0; i < pesos.size(); ++i)
		numPesos += pesos[i].size();

	if (numPesos != numConex)
	{
		gDebug.erro("RedeNeural não pode ser inicializada com número de pesos que não se encaixa na topologia.", this);
		return false;
	}


	numEntradas = topologia[0];
	numSaidas = topologia[numCamadas - 1];

	int contPesos = 0;
	camadas.resize(numCamadas);
	for (int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = topologia[i] + 1;
		unsigned int numConexoes = topologia[i + 1];
		camadas[i].resize(numNeuronios);
		vector<double> pesosNeuronio;
		pesosNeuronio.resize(numConexoes);
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				pesosNeuronio[k] = pesos[i][contPesos];
				++contPesos;
			}

			camadas[i][j] = Neuronio(pesosNeuronio);
		}
		contPesos = 0;
		camadas[i][numNeuronios - 1].valorDeSaida = bias;
	}

	//	última camada
	unsigned int numNeuronios = topologia.back() + 1;
	camadas.back().resize(numNeuronios);
	for (unsigned int j = 0; j < numNeuronios; ++j)
		camadas.back()[j] = Neuronio(0);

	//	último neurônio
	camadas.back().back().valorDeSaida = bias;

	return true;
}

void RedeNeural::finalizar()
{
	camadas.clear();
}

bool RedeNeural::alimentar(const vector<double> &entradas)
{
	if (camadas.empty())
	{
		gDebug.erro("RedeNeural não pode ser alimentada, pois está vazia.", this);
		return false;
	}

	//	Verifica o numero correto de entradas
	if(entradas.size() != camadas[0].size() - 1)	//	'-1' para descontar o neuronio bias
	{
		gDebug.erro("RedeNeural não pode ser alimentada com um numero diferente de entradas.", this);
		return false;
	}

	//	Coloca os valores de entrada nos neuronios de entrada
	for(int i = 0; i < entradas.size(); ++i)
	{
		camadas[0][i].valorDeSaida = entradas[i];
	}

	//	propagar valores (alimentar cada neuronio de cada camada)
	for(int i = 1; i < camadas.size(); ++i)
	{
		for(int j = 0; j < camadas[i].size()-1; ++j)
		{
			alimentarNeuronio(&camadas[i][j], j, &camadas[i-1]);
		}
	}

	return true;
}

bool RedeNeural::retropropagar(const vector<double> &valores_desejados)
{
	if (camadas.empty())
	{
		gDebug.erro("RedeNeural não pode retropropagar, pois está vazia.", this);
		return false;
	}

	//	Verifica o numero correto de saidas
	if (valores_desejados.size() != camadas.back().size() - 1)	//	'-1' para descontar o neuronio bias
	{
		gDebug.erro("RedeNeural não pode retropropagar, pois o número de valores desenjados não coresponde ao número de nerônios de saida.", this);
		return false;
	}

	//	Calcula o erro medio da rede (RMS)
	CamadaDeNeuronios &camadaDeSaida = camadas.back();

	erroMedio = 0.0;

	for(unsigned int i = 0; i < camadaDeSaida.size() -1; ++i)
	{
		double delta = valores_desejados[i] - camadaDeSaida[i].valorDeSaida;
		erroMedio += delta * delta;
	}
	erroMedio /= (camadaDeSaida.size() -1);	//	erro medio ao quadrado
	erroMedio = sqrt(erroMedio);	//	RMS

	//	media recente
	erroMedioRecente = (erroMedioRecente * atenuacaoDeErroMedioRecente + erroMedio)
		/ (atenuacaoDeErroMedioRecente + 1.0);

	//	Calcula gradientes da camada de saida
	for(unsigned int i = 0; i < camadaDeSaida.size() -1; ++i)
	{
		calcularDeltaDoNeuronioDeSaida(&camadaDeSaida[i], valores_desejados[i]);
	}

	//	Calcula gradientes das camadas ocultas
	for(unsigned int i = camadas.size() -2; i > 0; --i)
	{
		CamadaDeNeuronios *camadaOculta = &camadas[i];
		CamadaDeNeuronios *proxCamada = &camadas[i + 1];
		for(unsigned int j = 0; j < camadaOculta->size(); ++j)
		{
			calcularDeltaDoNeuronioOculto(&(*camadaOculta)[j], proxCamada);
		}
	}

	//	Para todas as camadas, comecando da camada de saida ate a primeira camada oculta
	//	atualiza os pesos das conexoes
	for(unsigned int i = camadas.size() -1; i > 0; --i)
	//for (unsigned int i = 1; i < camadas.size(); ++i)
	{
		CamadaDeNeuronios *camada = &camadas[i];
		CamadaDeNeuronios *camadaAnt = &camadas[i -1];

		for(unsigned int j = 0; j < camada->size()-1; ++j)
		{
			atualizarPesosDeEntrada((*camada)[j], j, camadaAnt);
		}
	}

	return true;
}

void RedeNeural::obterResultados(vector<double> &resultados) const
{
	resultados.clear();

	if (camadas.empty())
		return;

	//	Ignora neuronio bias na camada de saida
	for(unsigned int i = 0; i < camadas.back().size() -1; ++i)
	{
		resultados.push_back(camadas.back()[i].valorDeSaida);
	}
}

const vector<double> RedeNeural::getResultados() const
{
	vector<double> resultados;

	if (camadas.empty())
		return resultados;

	//	Ignora neuronio bias na camada de saida
	for (unsigned int i = 0; i < camadas.back().size() - 1; ++i)
	{
		resultados.push_back(camadas.back()[i].valorDeSaida);
	}
	return resultados;
}
/*
bool RedeNeural::salvar(const string& arquivo)
{
	//	Abrir o arquivo 
	SDL_RWops *ofs = SDL_RWFromFile(arquivo.c_str(), "wt");
	if (!ofs)
	{
		gDebug.erro("Erro ao tentar salvar RedeNeural no arquivo '" + arquivo + "'.", this);
		return false;
	}

	//	topologia
	stringstream ss;
	unsigned int numCamadas = camadas.size();
	ss << numCamadas << " \n";
	for (unsigned int i = 0; i < numCamadas; ++i)
	{
		unsigned int numNeuronios = camadas[i].size()-1;
		ss << numNeuronios << " ";
	}
	ss << " \n \n";

	//	parametros
	ss << tipoFuncAtivacao << " ";
	ss << bias << " ";
	ss << taxaDeAprendizado << " ";
	ss << momentum << " \n \n";

	//	pesos
	for (unsigned int i = 0; i < numCamadas-1; ++i)
	{
		unsigned int numNeuronios = camadas[i].size();
		unsigned int numConexoes = camadas[i + 1].size() - 1;
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				double peso = camadas[i][j].conexoes[k].peso;
				ss << peso << " ";
			}
			ss << "\n";
		}
		ss << "\n";
	}
	ofs->write(ofs, ss.str().c_str(), sizeof(char)*ss.str().size(), 1);
	ofs->close(ofs);
	return true;
}

bool RedeNeural::carregar(const string& arquivo)
{
	//	Testar inicializada
	if (!camadas.empty())
	{
		gDebug.erro("RedeNeural não pode carregar o arquivo '" + arquivo + "', pois já possui neurônios. Finalize a rede antes de carregar.", this);
		return false;
	}

	//	Abrir o arquivo 
	SDL_RWops *ifs = SDL_RWFromFile(arquivo.c_str(), "r");
	if (!ifs)
	{
		gDebug.erro("Erro ao abrir arquivo '" + arquivo + "'. Talvez o arquivo não exista.", this);
		return false;
	}

	unsigned int tamanho_arquivo_em_bytes = ifs->size(ifs);
	char *bytes_do_arquivo = new char[tamanho_arquivo_em_bytes];
	ifs->read(ifs, bytes_do_arquivo, tamanho_arquivo_em_bytes, 1);
	ifs->close(ifs);
	stringstream ss;
	ss << bytes_do_arquivo;
	delete[] bytes_do_arquivo;
	
	vector<unsigned int> topologia;
	unsigned int numCamadas;
	ss >> numCamadas;
	topologia.resize(numCamadas);
	for (unsigned int i = 0; i < numCamadas; ++i)
	{
		unsigned int numNeuronios;
		ss >> numNeuronios;
		topologia[i] = numNeuronios;
	}

	ss >> tipoFuncAtivacao;
	ss >> bias;
	ss >> taxaDeAprendizado;
	ss >> momentum;

	vector<vector<double>> pesos;
	pesos.resize(numCamadas - 1);
	for (unsigned int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = topologia[i]+1;
		unsigned int numConexoes = topologia[i+1];
		pesos[i].resize(numNeuronios*numConexoes);
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				double peso;
				ss >> peso;
				pesos[i][k + j*numConexoes] = peso;
			}
		}
	}

	setFuncaoDeActivacao((EnumFuncaoDeAtivacaoRedeNeural)tipoFuncAtivacao);
	inicializar(topologia, pesos);
	return true;
}
*/
bool RedeNeural::salvarPesos(const string& arquivo)
{
	//	Abrir o arquivo 
	SDL_RWops *ofs = SDL_RWFromFile(arquivo.c_str(), "wt");
	if (!ofs)
	{
		gDebug.erro("Erro ao tentar salvar RedeNeural no arquivo '" + arquivo + "'.", this);
		return false;
	}

	stringstream ss;
	unsigned int numCamadas = camadas.size();
	//	pesos
	for (unsigned int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = camadas[i].size();
		unsigned int numConexoes = camadas[i + 1].size() - 1;
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				double peso = camadas[i][j].conexoes[k].peso;
				ss << peso << " ";
			}
			ss << "\n";
		}
		ss << "\n";
	}
	ofs->write(ofs, ss.str().c_str(), sizeof(char)*ss.str().size(), 1);
	ofs->close(ofs);

	return true;
}

bool RedeNeural::carregarPesos(const string& arquivo)
{
	//	Abrir o arquivo 
	SDL_RWops *ifs = SDL_RWFromFile(arquivo.c_str(), "r");
	if (!ifs)
	{
		gDebug.erro("Erro ao abrir arquivo '" + arquivo + "'. Talvez o arquivo nao exista.", this);
		return false;
	}

	unsigned int tamanho_arquivo_em_bytes = ifs->size(ifs);
	char *bytes_do_arquivo = new char[tamanho_arquivo_em_bytes];
	ifs->read(ifs, bytes_do_arquivo, tamanho_arquivo_em_bytes, 1);
	ifs->close(ifs);
	stringstream ss;
	ss << bytes_do_arquivo;
	delete[] bytes_do_arquivo;

	unsigned int numCamadas = camadas.size();
	vector<vector<double>> pesos;
	pesos.resize(numCamadas - 1);
	for (unsigned int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = camadas[i].size();
		unsigned int numConexoes = camadas[i + 1].size() -1;
		pesos[i].resize(numNeuronios*numConexoes);
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				double peso;
				ss >> peso;
				pesos[i][k + j*numConexoes] = peso;
			}
		}
	}

	setPesos(pesos);

	return true;
}

vector<vector<double>> RedeNeural::getPesos()
{
	vector<vector<double>> pesos;
	unsigned int contConex = 0;

	unsigned int numCamadas = camadas.size();
	for (unsigned int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = camadas[i].size();
		unsigned int numConexoes = camadas[i + 1].size() - 1;
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				pesos[i][contConex] = camadas[i][j].conexoes[k].peso;
				++contConex;
			}
		}
		contConex = 0;
	}

	return pesos;
}

void RedeNeural::setPesos(const vector<vector<double>>& pesos)
{
	int numCamadas = camadas.size();

	unsigned int numPesos = 0;
	unsigned int numConex = 0;
	for (int i = 0; i < numCamadas - 1; ++i)
		numConex += camadas[i].size() * (camadas[i + 1].size() -1);

	for (int i = 0; i < pesos.size(); ++i)
		numPesos += pesos[i].size();

	if (numPesos != numConex)
	{
		gDebug.erro("RedeNeural não pode setar pesos, pois número de pesos que não se encaixa na topologia.", this);
		return;
	}

	unsigned int contConex = 0;
	for (unsigned int i = 0; i < numCamadas - 1; ++i)
	{
		unsigned int numNeuronios = camadas[i].size();
		unsigned int numConexoes = camadas[i + 1].size() - 1;
		for (unsigned int j = 0; j < numNeuronios; ++j)
		{
			for (unsigned int k = 0; k < numConexoes; ++k)
			{
				camadas[i][j].conexoes[k].peso = pesos[i][contConex];
				++contConex;
			}
		}
		contConex = 0;
	}
}

CamadaDeNeuronios& RedeNeural::getCamada(unsigned int indice)
{
	if (indice > camadas.size() - 1)
    {
        CamadaDeNeuronios c;
        return c;
		//return CamadaDeNeuronios();
    }

	return camadas[indice];
}

Neuronio& RedeNeural::getNeuronio(unsigned int indiceCamada, unsigned int indiceNeuronio)
{
	if (indiceCamada > camadas.size() - 1)
    {
        Neuronio n;
        return n;
		//return Neuronio();
    }
	else if (indiceNeuronio > camadas[indiceCamada].size()-1)
    {
        Neuronio n;
        return n;
        //return Neuronio();
    }

	return camadas[indiceCamada][indiceNeuronio];
}

int RedeNeural::getNumEntradas()
{
	return numEntradas;
}

int RedeNeural::getNumSaidas()
{
	return numSaidas;
}

int RedeNeural::getNumCamadas()
{
	return camadas.size();
}

int RedeNeural::getNumCamadasOcultas()
{
	if (camadas.empty())
		return 0;

	return camadas.size() - 2;
}

int RedeNeural::getNumNeuroniosNaCamada(unsigned int indiceCamada)
{
	if (indiceCamada > camadas.size()-1)
		return 0;

	return camadas[indiceCamada].size();
}

int RedeNeural::getFuncaoDeAtivacao()
{
	return tipoFuncAtivacao;
}

double RedeNeural::getBias()
{
	return bias;
}

double RedeNeural::getTaxaDeAprendizado()
{
	return taxaDeAprendizado;
}

double RedeNeural::getMomentum()
{
	return momentum;
}

double RedeNeural::getErroMedio()
{
	return erroMedio;
}

double RedeNeural::getErroMedioRecente()
{
	return erroMedioRecente;
}

double RedeNeural::getAtenuacaoErroMedioRecente()
{
	return atenuacaoDeErroMedioRecente;
}

void RedeNeural::setFuncaoDeActivacao(EnumFuncaoDeAtivacaoRedeNeural tipo_func)
{
	switch(tipo_func)
	{
	case FUNCAO_DE_ATIVACAO_RN_TANH:
		ptrFuncaoDeAtivacao = &RedeNeural::tangenteHiperbolica;
		ptrFuncaoDeAtivacaoDerivada = &RedeNeural::tangenteHiperbolicaDerivada;
		break;

	case FUNCAO_DE_ATIVACAO_RN_SIGMOID:
	default:
		ptrFuncaoDeAtivacao = &RedeNeural::sigmoid;
		ptrFuncaoDeAtivacaoDerivada = &RedeNeural::sigmoidDerivada;
		break;
	}

	tipoFuncAtivacao = tipo_func;
}

void RedeNeural::setBias(double bias)
{
	this->bias = bias;
}

void RedeNeural::setTaxaDeAprendizado(double taxa)
{
	taxaDeAprendizado = taxa;
}

void RedeNeural::setMomentum(double momentum)
{
	this->momentum = momentum;
}

double RedeNeural::funcaoDeAtivacao(double soma)
{
	return (this->*ptrFuncaoDeAtivacao)(soma);
}

double RedeNeural::funcaoDeAtivacaoDerivada(double soma)
{
	return (this->*ptrFuncaoDeAtivacaoDerivada)(soma);
}

inline double RedeNeural::sigmoid(double valor)
{
	return 1.0 / (1.0 + exp(-valor));
}

inline double RedeNeural::sigmoidDerivada(double valor)
{
	//	 Não é a real derivada da função sigmod, mas funciona.
	return (1.0 - valor) * valor;
	
	//	Aqui, a real derivada da sigmoid. 
	//	Que por algum motivo bizarro, não deixa a rede aprender.
	/*double sig = sigmoid(valor);
	return sig * (1.0 - sig);*/
}

inline double RedeNeural::tangenteHiperbolica(double valor)
{
	return tanh(valor);
}

inline double RedeNeural::tangenteHiperbolicaDerivada(double valor)
{
	double t = tanh(valor);
	return 1.0 - (t * t);
}

void RedeNeural::alimentarNeuronio(Neuronio *neuronio, unsigned int indice_neuronio, const CamadaDeNeuronios *camada_ant)
{
	//	Soma as saidas da camada anterior, que sao as entradas para este neuronio
	//	Inclui o neuronio bias (da camada anterior)

	double soma = 0.0;
	for(unsigned int i = 0; i < camada_ant->size(); ++i)
	{
		soma += (*camada_ant)[i].valorDeSaida *
				(*camada_ant)[i].conexoes[indice_neuronio].peso;
	}

	//	Funcao de ativacao
	neuronio->valorDeSaida = funcaoDeAtivacao(soma);
}

void RedeNeural::calcularDeltaDoNeuronioDeSaida(Neuronio *neuronio, double valor_desejado)
{
	double delta = valor_desejado - neuronio->valorDeSaida;
	neuronio->delta = delta * funcaoDeAtivacaoDerivada(neuronio->valorDeSaida);
}

void RedeNeural::calcularDeltaDoNeuronioOculto(Neuronio *neuronio, const CamadaDeNeuronios *prox_camada)
{
	double soma = 0.0;

	//	Soma a contribuicao deste neuronio para os erros dos neuronios que ele alimenta
	//	Nao inclui o neuronio bias
	for (unsigned int i = 0; i < prox_camada->size() - 1; ++i)
		soma += neuronio->conexoes[i].peso * (*prox_camada)[i].delta;

	neuronio->delta = soma * funcaoDeAtivacaoDerivada(neuronio->valorDeSaida);
}

void RedeNeural::atualizarPesosDeEntrada(Neuronio &neuronio, unsigned int indice_neuronio, CamadaDeNeuronios *camada_ant)
{
	//	Atualiza os pesos de entreada para este neuronio
	//	(localizados nas conexoes de saida da com este neuronio na camada anterior)
	//	Inclui o neuronio bias

	for(unsigned int i = 0; i < camada_ant->size(); ++i)
	{
		Neuronio *neuronio_ant = &((*camada_ant)[i]);
		double velhoDeltaPeso = neuronio_ant->conexoes[indice_neuronio].deltaPeso;

		double novoDeltaPeso = 
			//	Entrada individial, modificada pelo gradiente (delta*valorDeSaida) e taxa de aprendizagem
			(taxaDeAprendizado
			* neuronio_ant->valorDeSaida
			* neuronio.delta)
			//	Adiciona momentum (uma fracao do delta peso anterior)
			+ (momentum
			* velhoDeltaPeso);

		neuronio_ant->conexoes[indice_neuronio].deltaPeso = novoDeltaPeso;
		neuronio_ant->conexoes[indice_neuronio].peso += novoDeltaPeso;
	}
}