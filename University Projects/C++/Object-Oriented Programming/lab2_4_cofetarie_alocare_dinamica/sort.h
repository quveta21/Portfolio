#ifndef SORT_H
#define SORT_H
#include "controller.h"

typedef int (*CompareFunction)(materie mat1, materie mat2);

int compara_nume(materie mat1, materie mat2);

int compara_cantitate(materie mat1, materie mat2);

materie* sorteaza(repo_materii* repo, CompareFunction comparare, int ascending);


#endif