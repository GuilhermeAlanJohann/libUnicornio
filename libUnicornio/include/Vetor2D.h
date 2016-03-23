#ifndef UNI_VETOR2D_H
#define UNI_VETOR2D_H

#ifndef PI
	#define PI 3.14159265358979
#endif

class Vetor2D
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
	float getAnguloDoVetor(const Vetor2D& vet);
	float getAngulo();

	float x, y;
};

#endif
