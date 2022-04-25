#ifndef TESCORE_IO_H
#define TESCORE_IO_H

#include "../model/datasheet.h"

#define DEFAULTFILEADDRESS "../demo.txt"
#define MAXSTRLEN 255

void testing(char*);

void apIndex(INDEX);
void delIndex(INDEX);

void initDatasheet();
void accessDatasheet();

#endif
