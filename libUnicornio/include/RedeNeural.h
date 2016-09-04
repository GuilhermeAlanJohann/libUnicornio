#ifndef UNI_REDENEURAL_H
#define UNI_REDENEURAL_H

#include "uniAPI.h"
#include "Neuronio.h"

enum UNI_API EnumFuncaoDeAtivacaoRedeNeural
{
	FUNCAO_DE_ATIVACAO_RN_SIGMOID,
	FUNCAO_DE_ATIVACAO_RN_TANH
};

typedef UNI_API vector<Neuronio> CamadaDeNeuronios;

class UNI_API RedeNeural
{
public:
	RedeNeural();
	~RedeNeural();

	bool inicializar(const vector<unsigned int> &topologia);
	bool inicializar(const vector<unsigned int> &topologia, const vector<vector<double> > &pesos);
	void finalizar();

	bool alimentar(const vector<double> &entradas);
	bool retropropagar(const vector<double> &valores_desejados);
	void obterResultados(vector<double> &resultados) const;
	const vector<double> getResultados() const;

	//bool salvar(const string& arquivo);
	//bool carregar(const string& arquivo);
	bool salvarPesos(const string& arquivo);
	bool carregarPesos(const string& arquivo);
	vector<vector<double> > getPesos();
	void setPesos(const vector<vector<double> >& pesos);
	
	CamadaDeNeuronios& getCamada(unsigned int indice);
	Neuronio& getNeuronio(unsigned int indiceCamada, unsigned int indiceNeuronio);

	int getNumEntradas();
	int getNumSaidas();
	int getNumCamadas();
	int getNumCamadasOcultas();
	int getNumNeuroniosNaCamada(unsigned int indiceCamada);
	int getFuncaoDeAtivacao();
	double getBias();
	double getTaxaDeAprendizado();
	double getMomentum();

	double getErroMedio();
	double getErroMedioRecente();
	double getAtenuacaoErroMedioRecente();

	void setFuncaoDeActivacao(EnumFuncaoDeAtivacaoRedeNeural tipo_func);
	void setBias(double bias);
	void setTaxaDeAprendizado(double taxa);
	void setMomentum(double momentum);

	double funcaoDeAtivacao(double soma);
	double funcaoDeAtivacaoDerivada(double soma);
	inline double sigmoid(double valor);
	inline double sigmoidDerivada(double valor);
	inline double tangenteHiperbolica(double valor);
	inline double tangenteHiperbolicaDerivada(double valor);

protected:
	double (RedeNeural::*ptrFuncaoDeAtivacao)(double);
	double (RedeNeural::*ptrFuncaoDeAtivacaoDerivada)(double);

	void alimentarNeuronio(Neuronio *neuronio, unsigned int indice_neuronio, const CamadaDeNeuronios *camada_ant);
	void calcularDeltaDoNeuronioDeSaida(Neuronio *neuronio, double valor_desejado);
	void calcularDeltaDoNeuronioOculto(Neuronio *neuronio, const CamadaDeNeuronios *prox_camada);
	void atualizarPesosDeEntrada(Neuronio &neuronio, unsigned int indice_neuronio, CamadaDeNeuronios *camada_ant);

	vector<CamadaDeNeuronios> camadas;

	int numEntradas;
	int numSaidas;
	int tipoFuncAtivacao;
	double bias;
	double taxaDeAprendizado;	//	Também chamado de 'eta'
	double momentum;			//	Também chamado de 'alpha', multiplicador do último deltaPeso

	double erroMedio;
	double erroMedioRecente;
	double atenuacaoDeErroMedioRecente;
};

#endif