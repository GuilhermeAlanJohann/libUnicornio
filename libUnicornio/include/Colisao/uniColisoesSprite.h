#ifndef UNI_UNICOLISOESSPRITE_H
#define UNI_UNICOLISOESSPRITE_H

#include "uniColisoes.h"
#include "Sprite.h"

bool UNI_CALL_CONV uniColisaoPontoComSprite(float ponto_x, float ponto_y, Sprite &spr, float x, float y, float rot);
bool UNI_CALL_CONV uniColisaoLinhaComSprite(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Sprite &spr, float x, float y, float rot);
bool UNI_CALL_CONV uniColisaoCirculoComSprite(float circulo_x, float circulo_y, float raio, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoRetanguloComSprite(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoPoligonoComSprite(Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_CALL_CONV uniColisaoSpriteComSprite(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2, bool testar_dentro = true);

//	funcoes mais usadas, com nome mais curto (para facilitar)
bool UNI_CALL_CONV uniColisao(float px, float py, Sprite &spr, float spr_x, float spr_y, float spr_rot);
bool UNI_CALL_CONV uniColisao(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2);

#endif