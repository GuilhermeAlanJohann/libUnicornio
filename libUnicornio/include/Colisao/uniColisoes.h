#ifndef UNI_UNICOLISOES_H
#define UNI_UNICOLISOES_H

#include <math.h>
#include "Vetor2D.h"

#ifndef UNI_CALL_CONV
	#define UNI_CALL_CONV _cdecl
#endif

#ifndef PI
	#define PI 3.14159265358979
#endif

bool UNI_CALL_CONV uniColisaoPontoComCirculo(float ponto_x, float ponto_y, float circulo_x, float circulo_y, float raio);	
bool UNI_CALL_CONV uniColisaoPontoComRetangulo(float ponto_x, float ponto_y, float x, float y, float rot, float largura, float altura, float ancora_x, float ancora_y);
bool UNI_CALL_CONV uniColisaoPontoComPoligono(float ponto_x, float ponto_y, Vetor2D* pontos, int num_pontos, float x, float y, float rot);

bool UNI_CALL_CONV uniColisaoLinhaComLinha(float linhaA_x0, float linhaA_y0, float linhaA_x1, float linhaA_y1, float linhaB_x0, float linhaB_y0, float linhaB_x1, float linhaB_y1);
bool UNI_CALL_CONV uniColisaoLinhaComCirculo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float circulo_x, float circulo_y, float raio);	
bool UNI_CALL_CONV uniColisaoLinhaComRetangulo(float linha_x1, float linha_y1, float linha_x2, float linha_y2, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y);
bool UNI_CALL_CONV uniColisaoLinhaComPoligono(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot);

bool UNI_CALL_CONV uniColisaoCirculoComCirculo(float circulo_x1, float circulo_y1, float raio1, float circulo_x2, float circulo_y2, float raio2);
bool UNI_CALL_CONV uniColisaoCirculoComRetangulo(float circulo_x, float circulo_y, float raio, float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoCirculoComPoligono(float circulo_x, float circulo_y, float raio, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro = true);

bool UNI_CALL_CONV uniColisaoRetanguloComRetangulo(float x1, float y1, float rot1, float largura1, float altura1, float ancora_x1, float ancora_y1, float x2, float y2, float rot2, float largura2, float altura2, float ancora_x2, float ancora_y2, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoRetanguloComPoligono(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, bool testar_dentro = true);

bool UNI_CALL_CONV uniColisaoPoligonoComPoligono(Vetor2D* pontos1, int num_pontos1, float x1, float y1, float rot1, Vetor2D* pontos2, int num_pontos2, float x2, float y2, float rot2, bool testar_dentro = true);

#endif