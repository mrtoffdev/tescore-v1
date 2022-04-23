#ifndef TESCORE_RENDER_H
#define TESCORE_RENDER_H

// rendering interfaces
void renderFrame();
void renderAuth();
void renderSeparatorH();

// typeface modifications
char* typefaceBold(int, char*);
char* typefaceItalic(int, char*);
char* typefaceUnderline(int, char*);

char* typefaceReset(char*);
char* typefaceColor(int, char*);

#endif
