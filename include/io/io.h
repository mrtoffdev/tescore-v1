/*========================================
                  FILE OPS
  ========================================*/

#ifndef TESCORE_IO_H
#define TESCORE_IO_H

#include "../model/datamodel.h"

#define DEFAULTFILEADDRESS "../demo.txt"
#define MAXSTRLEN 255

/*========================================
                  Testing
  ========================================*/
void testing(char*);
void fetchData(FILE*, char*, char*, int);
void closeFile(FILE*);

/*========================================
                    CRUD
  ========================================*/
void appendIndex(INDEX);
void delIndex(INDEX);

void initSheet();
void accessDatasheet();

/*========================================
                    SORT
  ========================================*/

SUBSHEET rankerModule();
SUBSHEET masterlistModule();
#endif
