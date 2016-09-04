#ifndef UNI_UNITESTARCOLISAOSPRITE_H
#define UNI_UNITESTARCOLISAOSPRITE_H

#include "uniTestarColisao.h"
#include "Sprite.h"

bool UNI_API uniTestarColisaoPontoComSprite(float ponto_x, float ponto_y, Sprite &spr, float x, float y, float rot);
bool UNI_API uniTestarColisaoLinhaComSprite(float linha_x1, float linha_y1, float linha_x2, float linha_y2, Sprite &spr, float x, float y, float rot);
bool UNI_API uniTestarColisaoCirculoComSprite(float circulo_x, float circulo_y, float raio, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_API uniTestarColisaoRetanguloComSprite(float retan_x, float retan_y, float retan_rot, float retan_largura, float retan_altura, float retan_ancora_x, float retan_ancora_y, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_API uniTestarColisaoPoligonoComSprite(Vetor2D* pontos, int num_pontos, float poli_x, float poli_y, float poli_rot, Sprite &spr, float x, float y, float rot, bool testar_dentro = true);
bool UNI_API uniTestarColisaoSpriteComSprite(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2, bool testar_dentro = true);

//	funcoes mais usadas, com nome mais curto (para facilitar)
bool UNI_API uniTestarColisao(float px, float py, Sprite &spr, float spr_x, float spr_y, float spr_rot);
bool UNI_API uniTestarColisao(Sprite &spr1, float x1, float y1, float rot1, Sprite &spr2, float x2, float y2, float rot2);

#endif