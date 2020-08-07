# include <glut.h>

unsigned int StringLength(void* font, const char* str) {
  int stringSize = 0;
  const char* c;

  for (c=str; *c != '\0'; c++)
    stringSize += glutBitmapWidth(font, *c);
  
  return stringSize;
}



void DisplayString(int x, int y, void* font, const char* str,int & length_string) {
  const char* c;

  // Position the cursor for font drawing
  glRasterPos2i(x, y);

  // Draw the font letter-by-letter
  for (c=str; length_string-->0; c++)
    glutBitmapCharacter(font, *c);
}