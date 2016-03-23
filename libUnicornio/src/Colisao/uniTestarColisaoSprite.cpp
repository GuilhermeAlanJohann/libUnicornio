#include "uniTestarColisaoSprite.h"

//	colisao entre ponto e sprite 
bool uniTestarColisaoPontoComSprite(float ponto_x, float ponto_y, Sprite &spr, float x, float y, float rot)
{
	float ax, ay;
	int larg, alt;

	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);

	return uniTestarColisaoPontoComRetangulo(ponto_x, ponto_y, x, y, rot, (float)larg, (float)alt, ax, ay);
}

//	colisao entre linha e sprite
bool uniTestarColisaoLinhaComSprite(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Sprite &spr, float x, float y, float rot)
{
	float ax, ay;
	int larg, alt;

	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);

	return uniTestarColisaoLinhaComRetangulo(linha_x1, linha_y1, linha_x2, linha_y2, x, y, rot, (float)larg, (float)alt, ax, ay);
}

//	colisao entre circulo e sprite
bool uniTestarColisaoCirculoComSprite(float circulo_x, float circulo_y, float raio, Sprite &spr, float x, float y, float rot, bool testar_dentro)
{
	float ax, ay;
	int larg, alt;

	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);

	return uniTestarColisaoCirculoComRetangulo(circulo_x, circulo_y, raio, x, y, rot, (float)larg, (float)alt, ax, ay, testar_dentro);
}

//	colisao entre retangulo e sprite
bool uniTestarColisaoRetanguloComSprite(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Sprite &spr, float x, float y, float rot, bool testar_dentro)
{
	float ax, ay;
	int larg, alt;

	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);

	return uniTestarColisaoRetanguloComRetangulo(retan_x, retan_y, retan_rot, retan_largura, retan_altura, retan_ancora_x, retan_ancora_y, x, y, rot, (float)larg, (float)alt, ax, ay, testar_dentro);
}

//	colisao entre poligono e sprite
bool uniTestarColisaoPoligonoComSprite(Vetor2D *pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, Sprite &spr, float x, float y, float rot, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	float ax, ay;
	int larg, alt;

	spr.obterAncora(ax, ay);
	spr.obterTamanho(larg, alt);

	Vetor2D retan[4];
	retan[0].x = -ax*larg;
	retan[0].y = -ay*alt;
	retan[1].x = retan[0].x + larg;
	retan[1].y = retan[0].y;
	retan[2].x = retan[1].x;
	retan[2].y = retan[0].y + alt;
	retan[3].x = retan[0].x;
	retan[3].y = retan[2].y;

	return uniTestarColisaoPoligonoComPoligono(pontos, num_pontos, poli_x, poli_y, poli_rot, retan, 4, x, y, rot, testar_dentro);
}

//	colisao entre sprites
bool uniTestarColisaoSpriteComSprite(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2, bool testar_dentro)
{
	float ax1, ay1, ax2, ay2;
	int larg1, alt1, larg2, alt2;

	spr1.obterAncora(ax1, ay1);
	spr1.obterTamanho(larg1, alt1);
	spr2.obterAncora(ax2, ay2);
	spr2.obterTamanho(larg2, alt2);

	return uniTestarColisaoRetanguloComRetangulo(x1, y1, rot1, (float)larg1, (float)alt1, ax1, ay1, x2, y2, rot2, (float)larg2, (float)alt2, ax2, ay2, testar_dentro);
}

//	func de colisao entre ponto e sprite (nome mais curto)
bool uniTestarColisao(float px, float py, Sprite &spr, float spr_x, float spr_y, float spr_rot)
{
	return uniTestarColisaoPontoComSprite(px, py, spr, spr_x, spr_y, spr_rot);
}

//	func de colisao entre sprites (nome mais curto)
bool uniTestarColisao(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2)
{
	return uniTestarColisaoSpriteComSprite(spr1, x1, y1, rot1, spr2, x2, y2, rot2, true);
}