/*========================================
                  FILE OPS
  ========================================*/

#ifndef TESCORE_IO_H
#define TESCORE_IO_H

#include "../model/datamodel.h"

#define DEFAULTFILEADDRESS "../demo.txt"
#define MAXSTRLEN 255

void testing(char*);
void fetchData(FILE*);
void closeFile(FILE*);

void appendIndex(INDEX);
void delIndex(INDEX);

void initSheet();
void accessDatasheet();

#endif
