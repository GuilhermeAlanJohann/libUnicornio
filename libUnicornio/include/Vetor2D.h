#ifndef UNI_VETOR2D_H
#define UNI_VETOR2D_H

#include "uniAPI.h"

#ifndef PI
	#define PI 3.14159265358979
#endif

class UNI_API Vetor2D
{
public:
	Vetor2D();
	Vetor2D(float x, float y);
	~Vetor2D();

	Vetor2D operator-() const;

	float operator()(int i) const;
	float& operator()(int i);

	bool operator==(const Vetor2D& v);
	bool operator!=(const Vetor2D& v);

	void operator+=(const Vetor2D& v);
	void operator-=(const Vetor2D& v);
	void operator*=(const Vetor2D& v);
	void operator/=(const Vetor2D& v);

	void operator+=(float a);
	void operator-=(float a);
	void operator*=(float a);
	void operator/=(float a);

	void operator+=(double a);
	void operator-=(double a);
	void operator*=(double a);
	void operator/=(double a);

	void operator+=(int a);
	void operator-=(int a);
	void operator*=(int a);
	void operator/=(int a);

	Vetor2D operator+(const Vetor2D& v);
	Vetor2D operator-(const Vetor2D& v);
	Vetor2D operator*(const Vetor2D& v);
	Vetor2D operator/(const Vetor2D& v);

	Vetor2D operator+(float a);
	Vetor2D operator-(float a);
	Vetor2D operator*(float a);
	Vetor2D operator/(float a);

	Vetor2D operator+(double a);
	Vetor2D operator-(double a);
	Vetor2D operator*(double a);
	Vetor2D operator/(double a);

	Vetor2D operator+(int a);
	Vetor2D operator-(int a);
	Vetor2D operator*(int a);
	Vetor2D operator/(int a);

	void set(float x_, float y_);
	void zerar();
	float comprimento() const;
	float comprimentoAoQuadrado() const;
	float normalizar();
	void rotacionar(float angulo);

	float getAnguloAteVetor(const Vetor2D& vet);
	float getAnguloAPartirDoVetor(const Vetor2D& vet);
	float getAngulo();
	Vetor2D getNormal();
	Vetor2D getRotacionado(float angulo);

	float x, y;
};

//	DEFINES
#define ANCORA_CENTRO	 Vetor2D(0.5f, 0.5f)
#define ANCORA_ESQ		 Vetor2D(0.0f, 0.5f)
#define ANCORA_DIR		 Vetor2D(1.0f, 0.5f)
#define ANCORA_CIMA		 Vetor2D(0.5f, 0.0f)
#define ANCORA_BAIXO	 Vetor2D(0.5f, 1.0f)
#define ANCORA_ESQ_CIMA	 Vetor2D(0.0f, 0.0f)
#define ANCORA_ESQ_BAIXO Vetor2D(0.0f, 1.0f)
#define ANCORA_DIR_CIMA  Vetor2D(1.0f, 0.0f)
#define ANCORA_DIR_BAIXO Vetor2D(1.0f, 1.0f)

#define VETOR2D_UNIT_X	 Vetor2D(1.0f, 0.0f)
#define VETOR2D_UNIT_Y	 Vetor2D(0.0f, 1.0f)

#endif
