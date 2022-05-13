/*========================================
      FILE OPERATIONS HEADER
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_IO_H
#define TESCORE_IO_H

// Models
#include "../model/datamodel.h"
#include "../model/renderctx.h"

// Interface Parameters
#define DEFAULTFILEADDRESS "../demo.txt"
#define MAXADDRLENGTH 509 // Standard string char limit for ANSI Compatibility

#define RANKERSHEETID 12247
#define MASTERSHEETID 12248

/*========================================
                  Testing
  ========================================*/
void testing();
void fetchData(FILE*, char* [], char* [], int);
void closeFile(FILE*);

/*========================================
                    CRUD
  ========================================*/
Renderctx render_init_ctx(DATASHEET sessionSheet);
void datasheet_init_demo();

void fetch_gradeTable(DATASHEET Datactx, int distributionTable[11][2]);
void fetch_studentDistTable(DATASHEET Datactx);

void sheet_fetch_ctx(FILE*);
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
