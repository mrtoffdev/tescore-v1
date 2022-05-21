/*========================================
      INDEX MODEL
      Author: Christopher Abadillos Jr.
  ========================================*/
#ifndef TESCORE_INDEX_H
#define TESCORE_INDEX_H

// DATA MODEL PARAMETERS
#define MAXNAMECHARLIMIT 509 // Standard limit for char ANSI Compatibility

typedef struct Index {
    char    indexName[MAXNAMECHARLIMIT];
    short   value;
} Index;
#endif