#ifndef UNI_UNITESTARCOLISAO_H
#define UNI_UNITESTARCOLISAO_H

#include "uniAPI.h"
#include <cmath>
#include "Vetor2D.h"
#include "Quad.h"
#include "uniPlataformas.h"

#ifndef PI
	#define PI 3.14159265358979
#endif

bool UNI_API uniTestarColisaoPontoComCirculo(float ponto_x, float ponto_y, float circulo_x, float circulo_y, float raio);	
bool UNI_API uniTestarColisaoPontoComRetangulo(float ponto_x, float ponto_y, const Quad& retangulo);
bool UNI_API uniTestarColisaoPontoComRetangulo(float ponto_x, float ponto_y, float x, float y, float rot, float largura, float altura, float ancora_x, float ancora_y);
bool UNI_API uniTestarColisaoPontoComPoligono(float ponto_x, float ponto_y, Vetor2D* pontos, int num_pontos, float x, float y, float rot);
	 
bool UNI_API uniTestarColisaoLinhaComLinha(float linhaA_x0, float linhaA_y0, float linhaA_x1, float linhaA_y1, float linhaB_x0, float linhaB_y0, float linhaB_x1, float linhaB_y1);
bool UNI_API uniTestarColisaoLinhaComCirculo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float circulo_x, float circulo_y, float raio);	
bool UNI_API uniTestarColisaoLinhaComRetangulo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y);
bool UNI_API uniTestarColisaoLinhaComPoligono(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot);
	
bool UNI_API uniTestarColisaoCirculoComCirculo(float circulo_x1, float circulo_y1, float raio1, float circulo_x2, float circulo_y2, float raio2);
bool UNI_API uniTestarColisaoCirculoComRetangulo(float circulo_x, float circulo_y, float raio, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, bool testar_dentro = true);
bool UNI_API uniTestarColisaoCirculoComPoligono(float circulo_x, float circulo_y, float raio, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro = true);
	
bool UNI_API uniTestarColisaoRetanguloComRetangulo(const Quad& retangulo1, const Quad& retangulo2);
bool UNI_API uniTestarColisaoRetanguloComRetangulo(float x1, float y1, float rot1, float largura1, float altura1, float ancora_x1, float ancora_y1, float x2, float y2, float rot2, float largura2, float altura2, float ancora_x2, float ancora_y2, bool testar_dentro = true);
bool UNI_API uniTestarColisaoRetanguloComPoligono(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro = true);
	
bool UNI_API uniTestarColisaoPoligonoComPoligono(Vetor2D* pontos1, int num_pontos1, float x1, float y1, float rot1, Vetor2D* pontos2, int num_pontos2, float x2, float y2, float rot2, bool testar_dentro = true);

#endif