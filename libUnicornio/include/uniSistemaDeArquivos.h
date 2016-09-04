#ifndef UNI_UNISISTEMADEARQUIVOS_H
#define UNI_UNISISTEMADEARQUIVOS_H

#include "uniAPI.h"
#include <string>

using namespace std;

string UNI_API uniGetCaminhoPreferencias();
//string uniGetCaminhoDocumentos();
string UNI_API uniGetNomeEExtencaoDoArquivo(const string& caminho);
string UNI_API uniGetExtencaoDoArquivo(const string& caminho);

#endif


