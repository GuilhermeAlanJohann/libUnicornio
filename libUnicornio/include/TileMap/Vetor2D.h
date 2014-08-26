#ifndef UNI_VETOR2D_H
#define UNI_VETOR2D_H

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

	void operator*=(float a);
	void operator/=(float a);

	Vetor2D operator+(const Vetor2D& v);
	Vetor2D operator-(const Vetor2D& v);

	void set(float x_, float y_);
	void zerar();
	float comprimento() const;
	float comprimentoAoQuadrado() const;
	float normalizar();

	float x, y;
};

#endif
