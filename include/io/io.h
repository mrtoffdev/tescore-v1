/*========================================
      FILE OPERATIONS HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_IO_H
#define TESCORE_IO_H

// Models
#include "../model/datamodel.h"

// Interface Parameters
#define DEFAULTFILEADDRESS "../demo.txt"
#define MAXADDRLENGTH 509 // Standard string char limit for ANSI Compatibility

#define RANKERSHEETID 12247
#define MASTERSHEETID 12248

/*========================================
                  Testing
  ========================================*/
void testing();
void fetchData(FILE*, char*, char*, int);
void closeFile(FILE*);

/*========================================
                    CRUD
  ========================================*/
void openSheet(FILE*);
void appendIndex(INDEX);
void delIndex(INDEX);
void accessDatasheet();

DATASHEET initSheetDemo();
/*========================================
                    SORT
  ========================================*/
SUBSHEET rankerModule();
SUBSHEET masterlistModule();
#endif
