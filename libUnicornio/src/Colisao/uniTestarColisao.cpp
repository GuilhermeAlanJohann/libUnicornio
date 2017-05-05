#include "uniTestarColisao.h"
#include "SDL.h"
#include <algorithm>

using namespace std;

//	colisaor entre ponto e circulo
bool uniTestarColisaoPontoComCirculo(float ponto_x, float ponto_y, float circulo_x, float circulo_y, float raio)
{
	float dist_ao_quadrado = (ponto_x - circulo_x)*(ponto_x - circulo_x) + (ponto_y - circulo_y)*(ponto_y - circulo_y);

	return (dist_ao_quadrado < raio*raio);
}

//	colisao entre ponto e retangulo alinhado aos eixos
bool uniTestarColisaoPontoComRetangulo(float ponto_x, float ponto_y, const Quad& retangulo)
{
	return (ponto_x >= retangulo.x && ponto_x < retangulo.x + retangulo.larg &&
		ponto_y >= retangulo.y && ponto_y < retangulo.y + retangulo.alt);
}

//	colisao entre ponto e retangulo
bool uniTestarColisaoPontoComRetangulo(float ponto_x, float ponto_y, float x, float y, float rot, float largura, float altura, float ancora_x, float ancora_y)
{
	//	invez de rotacionar o retangulo, transladar, e calcular se o ponto est� dentro dele
	//	vamos transladar o retangulo, rotacionar o ponto e calcular se o ponto est� dentro do retangulo
	//	essa abordagem � muito mais simples e r�pida, pois o retangulo fica alinhado aos eixos, facilitando o calculo

	//	primeiro translada o retangulo para a origem
	SDL_Rect rect;
	rect.w = (int)largura;
	rect.h = (int)altura;
	rect.x = (int)(-ancora_x*rect.w);
	rect.y = (int)(-ancora_y*rect.h);

	//	depois, translada o ponto para a origem e rotaciona ao contrario
	Vetor2D vec;
	vec.x = ponto_x - x;
	vec.y = ponto_y - y;

	float rad = (-rot)*(float)(PI/180.0);	//	rota��o ao contrario
	float cs = cos(rad);
	float sn = sin(rad);

	ponto_x = vec.x * cs - vec.y * sn;
	ponto_y = vec.x * sn + vec.y * cs;

	//	por fim, calcula se o ponto est� dentro do retangulo
	return ( (ponto_x < rect.x + rect.w) && (ponto_x >= rect.x) && (ponto_y < rect.y + rect.h) && (ponto_y >= rect.y) );
}

//	colisao entre ponto e poligono
bool uniTestarColisaoPontoComPoligono(float ponto_x, float ponto_y, Vetor2D* pontos, int num_pontos, float x, float y, float rot)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	Vetor2D* poli = new Vetor2D[num_pontos];

	//	calcula rot(em radianos), seno e cosseno
	float rad = rot*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	//	rotaciona os pontos (em rela��o a origem)
	float xx = pontos[0].x * cs - pontos[0].y * sn;
	float yy = pontos[0].x * sn + pontos[0].y * cs;

	//	translada os pontos de volta
	poli[0].x = xx + x;
	poli[0].y = yy + y;

	Vetor2D menor, maior;
	maior = menor = poli[0];

	//	calcula os pontos
	for(int i = 1; i < num_pontos; ++i)
	{
		//	rotaciona os pontos (em rela��o a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		poli[i].x = xx + x;
		poli[i].y = yy + y;

		//	calcula AABB (para um primeiro teste)
		menor.x = min(menor.x, poli[i].x);
		menor.y = min(menor.y, poli[i].y);
		maior.x = max(maior.x, poli[i].x);
		maior.y = max(maior.y, poli[i].y);
	}

	//	testa AABB 
	if(ponto_x < menor.x || ponto_x > maior.x || ponto_y < menor.y || ponto_y > maior.y)
        return false;

	//	Usa algoritmo 'pnpoly' http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
    bool dentro = false;
	for(int i = 0, j = num_pontos-1 ; i < num_pontos; j = i++)
    {
        if((poli[i].y > ponto_y ) != (poli[j].y > ponto_y ) &&
			ponto_x < (poli[j].x - poli[i].x)*(ponto_y - poli[i].y)/(poli[j].y - poli[i].y) + poli[i].x)
			{
				dentro = !dentro;
			}
    }

	delete[] poli;
    return dentro;
}

bool uniTestarColisaoLinhaComLinha(float linhaA_x0, float linhaA_y0, float linhaA_x1, float linhaA_y1, float linhaB_x0, float linhaB_y0, float linhaB_x1, float linhaB_y1)
{
	float denominador = ((linhaB_y1 - linhaB_y0) * (linhaA_x1 - linhaA_x0)) - ((linhaB_x1 - linhaB_x0) * (linhaA_y1 - linhaA_y0));

	if (denominador == 0)
		return false;

	float ua = (((linhaB_x1 - linhaB_x0) * (linhaA_y0 - linhaB_y0)) - ((linhaB_y1 - linhaB_y0) * (linhaA_x0 - linhaB_x0))) / denominador;
	float ub = (((linhaA_x1 - linhaA_x0) * (linhaA_y0 - linhaB_y0)) - ((linhaA_y1 - linhaA_y0) * (linhaA_x0 - linhaB_x0))) / denominador;

	if ((ua < 0.0) || (ua > 1.0) || (ub < 0.0) || (ub > 1.0))
		return false;

	return true;
}

bool uniTestarColisaoLinhaComCirculo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float circulo_x, float circulo_y, float raio)
{
	//	translada pontos da linha para ficarem em relacao ao centro do circulo
	float p1_x = linha_x1 - circulo_x;
	float p1_y = linha_y1 - circulo_y;

	float p2_x = linha_x2 - circulo_x;
	float p2_y = linha_y2 - circulo_y;

	//	calcula a distancia entre esses pontos
	float dx = p2_x - p1_x;
	float dy = p2_y - p1_y;

	//	calcula 'a', 'b' e 'c' da equacao de baskara
	float a = (dx*dx) + (dy*dy);
	float b = 2 * ((p1_x*dx) + (p1_y*dy));
	float c = (p1_x*p1_x) + (p1_y*p1_y) - (raio*raio);

	//	calcula 'delta' da equacao de baskara
	float delta = (b*b) - (4*a*c);

	//	se delta < 0. Nao tem interseccao
	if(delta < 0)
		return false;

	//	se delta == 0. Tem uma interseccao
	if(delta == 0)
	{
		float u = -b/(2*a);

		return !(u < 0.0f || u > 1.0f);
	}

	//	se delta > 0. Tem duas interseccoes
	float raiz_quadrada_delta = sqrt(delta);

	float u1 = (-b + raiz_quadrada_delta)/(2*a);
	float u2 = (-b - raiz_quadrada_delta)/(2*a);

	return ((u1 >= 0.0f && u1 <= 1.0f) || (u2 >= 0.0f && u2 <= 1.0f));
}

//	colisao entre linha e retangulo
bool uniTestarColisaoLinhaComRetangulo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y)
{
	Vetor2D canto_retan;
	canto_retan.x = -retan_ancora_x*retan_largura;
	canto_retan.y = -retan_ancora_y*retan_altura;

	Vetor2D pontos[4];
	pontos[0].x = canto_retan.x;				 pontos[0].y = canto_retan.y;
	pontos[1].x = canto_retan.x + retan_largura; pontos[1].y = canto_retan.y;
	pontos[2].x = canto_retan.x + retan_largura; pontos[2].y = canto_retan.y + retan_altura;
	pontos[3].x = canto_retan.x;				 pontos[3].y = canto_retan.y + retan_altura;

	float rad = retan_rot*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em rela��o a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + retan_x;
		pontos[i].y = yy + retan_y;
	}

	for(int i = 0; i < 4; ++i)
	{
		int j = (i+1)%4;
		if(uniTestarColisaoLinhaComLinha(linha_x1, linha_y1, linha_x2, linha_y2,
								   (float)pontos[i].x, (float)pontos[i].y, (float)pontos[j].x, (float)pontos[j].y))
			return true;
	}

	return false;
}

//	colisao entre linha e poligono
bool uniTestarColisaoLinhaComPoligono(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad = poli_rot*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	float xx_ant;
	float yy_ant;
	float xx;
	float yy;

	xx = (pontos[0].x * cs - pontos[0].y * sn) + poli_x;
	yy = (pontos[0].x * sn + pontos[0].y * cs) + poli_y;

	for(int i = 0; i < num_pontos; ++i)
	{
		xx_ant = xx;
		yy_ant = yy;

		int j = (i+1)%num_pontos;

		xx = (pontos[j].x * cs - pontos[j].y * sn) + poli_x;
		yy = (pontos[j].x * sn + pontos[j].y * cs) + poli_y;

		if(uniTestarColisaoLinhaComLinha(linha_x1, linha_y1, linha_x2, linha_y2, xx_ant, yy_ant, xx, yy))
		{
			return true;
		}
	}

	return false;
}

//	colisao entre circulos
bool uniTestarColisaoCirculoComCirculo(float cx1, float cy1, float raio1, float cx2, float cy2, float raio2)
{
	float dist_ao_quadrado = (cx1 - cx2)*(cx1 - cx2) + (cy1 - cy2)*(cy1 - cy2);
	float soma_dos_raios = raio1+raio2;

	return (dist_ao_quadrado < soma_dos_raios*soma_dos_raios);
}

//	colisao entre circulo e retangulo
bool uniTestarColisaoCirculoComRetangulo(float circulo_x, float circulo_y, float raio, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, bool testar_dentro)
{
	Vetor2D canto_retan;
	canto_retan.x = -retan_ancora_x*retan_largura;
	canto_retan.y = -retan_ancora_y*retan_altura;

	Vetor2D pontos[4];
	pontos[0].x = canto_retan.x;				 pontos[0].y = canto_retan.y;
	pontos[1].x = canto_retan.x + retan_largura; pontos[1].y = canto_retan.y;
	pontos[2].x = canto_retan.x + retan_largura; pontos[2].y = canto_retan.y + retan_altura;
	pontos[3].x = canto_retan.x;				 pontos[3].y = canto_retan.y + retan_altura;

	float rad = retan_rot*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em rela��o a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + retan_x;
		pontos[i].y = yy + retan_y;
	}

	bool colidiu = false;
	for(int i = 0; i < 4 && !colidiu; ++i)
	{
		int j = (i+1)%4;
		colidiu = uniTestarColisaoLinhaComCirculo(pontos[i].x, pontos[i].y, pontos[j].x, pontos[j].y, circulo_x, circulo_y, raio);
	}

	if(!colidiu && testar_dentro)
	{
		colidiu = uniTestarColisaoPontoComCirculo(retan_x, retan_y, circulo_x, circulo_y, raio)
			|| uniTestarColisaoPontoComRetangulo(circulo_x, circulo_y, retan_x, retan_y, retan_rot, retan_largura, retan_altura, retan_ancora_x, retan_ancora_y);
	}

	return colidiu;
}

//	colisao entre circulo e poligono
bool uniTestarColisaoCirculoComPoligono(float circulo_x, float circulo_y, float raio, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad = poli_rot*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	float xx_ant;
	float yy_ant;
	float xx;
	float yy;

	xx = (pontos[0].x * cs - pontos[0].y * sn) + poli_x;
	yy = (pontos[0].x * sn + pontos[0].y * cs) + poli_y;

	bool colidiu = false;
	for(int i = 0; i < num_pontos && !colidiu; ++i)
	{
		xx_ant = xx;
		yy_ant = yy;

		int j = (i+1)%num_pontos;

		xx = (pontos[j].x * cs - pontos[j].y * sn) + poli_x;
		yy = (pontos[j].x * sn + pontos[j].y * cs) + poli_y;

		colidiu = uniTestarColisaoLinhaComCirculo(xx_ant, yy_ant, xx, yy, circulo_x, circulo_y, raio);
	}

	if(!colidiu && testar_dentro)
	{
		colidiu = uniTestarColisaoPontoComCirculo(poli_x, poli_y, circulo_x, circulo_y, raio)
			|| uniTestarColisaoPontoComPoligono(circulo_x, circulo_y, pontos, num_pontos, poli_x, poli_y, poli_rot);
	}

	return colidiu;
}

//	colisao entre retangulos alinhados aos eixos
bool uniTestarColisaoRetanguloComRetangulo(const Quad& retangulo1, const Quad& retangulo2)
{
	return (retangulo1.x + retangulo1.larg >= retangulo2.x && retangulo1.x < retangulo2.x + retangulo2.larg &&
		retangulo1.y + retangulo1.alt >= retangulo2.y && retangulo1.y < retangulo2.y + retangulo2.alt);
}

//	colisao entre retangulos
bool uniTestarColisaoRetanguloComRetangulo(float x1, float y1, float rot1, float largura1, float altura1, float ancora_x1, float ancora_y1, float x2, float y2, float rot2, float largura2, float altura2, float ancora_x2, float ancora_y2, bool testar_dentro)
{

	//	1) calcula linhas do retangulo 1
	//	coloca a ancora do retangulo na origem
	Vetor2D canto_retan;
	canto_retan.x = -ancora_x1*largura1;
	canto_retan.y = -ancora_y1*altura1;

	Vetor2D pontos[4];
	pontos[0].x = canto_retan.x;			pontos[0].y = canto_retan.y;
	pontos[1].x = canto_retan.x + largura1;	pontos[1].y = canto_retan.y;
	pontos[2].x = canto_retan.x + largura1; pontos[2].y = canto_retan.y + altura1;
	pontos[3].x = canto_retan.x;			pontos[3].y = canto_retan.y + altura1;

	float rad = rot1*(float)(PI/180.0);
	float cs = cos(rad);
	float sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em rela��o a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + x1;
		pontos[i].y = yy + y1;
	}

	//	calcula as 4 linhas do retangulo
	Vetor2D linhasA[4][2];	// 4 linhas, cada uma com 2 pontos
	linhasA[0][0] = pontos[0];
	linhasA[0][1] = pontos[1];
	linhasA[1][0] = pontos[1];
	linhasA[1][1] = pontos[2];
	linhasA[2][0] = pontos[2];
	linhasA[2][1] = pontos[3];
	linhasA[3][0] = pontos[3];
	linhasA[3][1] = pontos[0];

	//	2) calcula linhas do retangulo 2
	//	coloca a ancora do retangulo na origem
	canto_retan.x = -ancora_x2*largura2;
	canto_retan.y = -ancora_y2*altura2;

	pontos[0].x = canto_retan.x;			pontos[0].y = canto_retan.y;
	pontos[1].x = canto_retan.x + largura2;	pontos[1].y = canto_retan.y;
	pontos[2].x = canto_retan.x + largura2; pontos[2].y = canto_retan.y + altura2;
	pontos[3].x = canto_retan.x;			pontos[3].y = canto_retan.y + altura2;

	rad = rot2*(float)(PI/180.0);
	cs = cos(rad);
	sn = sin(rad);

	for(int i = 0; i < 4; ++i)
	{
		//	rotaciona os pontos (em rela��o a origem)
		float xx = pontos[i].x * cs - pontos[i].y * sn;
		float yy = pontos[i].x * sn + pontos[i].y * cs;

		//	translada os pontos de volta
		pontos[i].x = xx + x2;
		pontos[i].y = yy + y2;
	}

	//	calcula as 4 linhas do retangulo
	Vetor2D linhasB[4][2];	// 4 linhas, cada uma com 2 pontos
	linhasB[0][0] = pontos[0];
	linhasB[0][1] = pontos[1];
	linhasB[1][0] = pontos[1];
	linhasB[1][1] = pontos[2];
	linhasB[2][0] = pontos[2];
	linhasB[2][1] = pontos[3];
	linhasB[3][0] = pontos[3];
	linhasB[3][1] = pontos[0];

	//	testa intersec��o entre as linhas de um retangulo contra as linhas do outro
	bool colidiu = false;
	for(int i = 0; i < 4 && !colidiu; ++i)
	{
		for(int j = 0; j < 4 && !colidiu; ++j)
		{
			colidiu = uniTestarColisaoLinhaComLinha(linhasA[i][0].x, linhasA[i][0].y, linhasA[i][1].x, linhasA[i][1].y,
											  linhasB[j][0].x, linhasB[j][0].y, linhasB[j][1].x, linhasB[j][1].y);
		}
	}

	//	se n�o ouve nenhuma intersec��o
	//	pode ser que um retangulo esteja totalmente dentro do outro,
	//	ent�o testa este caso

	if(!colidiu && testar_dentro)
	{
		colidiu = uniTestarColisaoPontoComRetangulo(x1, y1, x2, y2, rot2, largura2, altura2, ancora_x2, ancora_y2)
			   || uniTestarColisaoPontoComRetangulo(x2, y2, x1, y1, rot1, largura1, altura1, ancora_x1, ancora_y1);
	}

	return colidiu;
}

//	colisao entre retangulo e poligono
bool uniTestarColisaoRetanguloComPoligono(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro)
{
	Vetor2D retan[4];
	retan[0].x = -retan_ancora_x*retan_largura;
	retan[0].y = -retan_ancora_y*retan_altura;
	retan[1].x = retan[0].x + retan_largura;
	retan[1].y = retan[0].y;
	retan[2].x = retan[1].x;
	retan[2].y = retan[0].y + retan_altura;
	retan[3].x = retan[0].x;
	retan[3].y = retan[2].y;

	return uniTestarColisaoPoligonoComPoligono(pontos, num_pontos, poli_x, poli_y, poli_rot, retan, 4, retan_x, retan_y, retan_rot, testar_dentro);
}

//	colisao entre poligonos
bool uniTestarColisaoPoligonoComPoligono(Vetor2D* pontos1, int num_pontos1, float x1, float y1, float rot1, Vetor2D* pontos2, int num_pontos2, float x2, float y2, float rot2, bool testar_dentro)
{
	//	se nao tiver pontos suficientes, nao testa
	if(num_pontos1 < 3 || num_pontos2 < 3)
		return false;

	//	calcula rot(em radianos), seno e cosseno
	float rad1 = rot1*(float)(PI/180.0);
	float cs1 = cos(rad1);
	float sn1 = sin(rad1);

	float rad2 = rot2*(float)(PI/180.0);
	float cs2 = cos(rad2);
	float sn2 = sin(rad2);

	//	testa cada uma das linhas
	bool colidiu = false;

	float poli1_xx = (pontos1[0].x * cs1 - pontos1[0].y * sn1) + x1;
	float poli1_yy = (pontos1[0].x * sn1 + pontos1[0].y * cs1) + y1;
	float poli1_xx_ant;
	float poli1_yy_ant;

	for(int i = 0; i < num_pontos1 && !colidiu; ++i)
	{
		poli1_xx_ant = poli1_xx;
		poli1_yy_ant = poli1_yy;

		int ii = (i+1)%num_pontos1;

		poli1_xx = (pontos1[ii].x * cs1 - pontos1[ii].y * sn1) + x1;
		poli1_yy = (pontos1[ii].x * sn1 + pontos1[ii].y * cs1) + y1;

		float poli2_xx = (pontos2[0].x * cs2 - pontos2[0].y * sn2) + x2;
		float poli2_yy = (pontos2[0].x * sn2 + pontos2[0].y * cs2) + y2;
		float poli2_xx_ant;
		float poli2_yy_ant;

		for(int j = 0; j < num_pontos2; ++j)
		{		
			poli2_xx_ant = poli2_xx;
			poli2_yy_ant = poli2_yy;

			int jj = (j+1)%num_pontos2;

			poli2_xx = (pontos2[jj].x * cs2 - pontos2[jj].y * sn2) + x2;
			poli2_yy = (pontos2[jj].x * sn2 + pontos2[jj].y * cs2) + y2;

			if(uniTestarColisaoLinhaComLinha(poli1_xx_ant, poli1_yy_ant, poli1_xx, poli1_yy,
									   poli2_xx_ant, poli2_yy_ant, poli2_xx, poli2_yy))
			{
				colidiu = true;
				break;
			}
		}
	}

	//	se n�o ouve nenhuma intersec��o
	//	pode ser que um poligono esteja totalmente dentro do outro,
	//	ent�o testa este caso

	if(!colidiu && testar_dentro)
	{
		colidiu = uniTestarColisaoPontoComPoligono(x1, y1, pontos2, num_pontos2, x2, y2, rot2)
			   || uniTestarColisaoPontoComPoligono(x2, y2, pontos1, num_pontos1, x1, y1, rot1);
	}

	return colidiu;
}