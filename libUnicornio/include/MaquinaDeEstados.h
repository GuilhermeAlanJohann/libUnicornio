#ifndef UNI_MAQUINADEESTADOS_H
#define UNI_MAQUINADEESTADOS_H

class Estado;

class MaquinaDeEstados
{
public:
	MaquinaDeEstados();
	virtual ~MaquinaDeEstados();

	//	Métodos virtuais
	virtual bool inicializar(Estado* estado);
	virtual bool finalizar();
	virtual void aoInicializar();
	virtual void aoFinalizar();

	virtual void atualizar(float dt);

	virtual void trocarEstado(Estado* proxEstado);

	//	Métodos normais
	void atualizar();
	bool estaInicializada();

protected:
	Estado* proxEstado;
	Estado* estadoAtual;
	bool trocandoEstado;
	bool inicializada;
};

#endif