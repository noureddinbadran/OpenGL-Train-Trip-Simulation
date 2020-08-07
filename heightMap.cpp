
#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include "texture.h"
#include <iostream>

GLubyte* LoadHeightMap(char *filename) 
{
    int i, j=0;
    FILE *textureFile;
	GLubyte* textureData;

    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;

	if( (textureFile = fopen(filename, "rb"))==NULL) return textureData;
    
	fread(&fileheader, sizeof(fileheader), 1, textureFile);
	
    fseek(textureFile, sizeof(fileheader), SEEK_SET);

    fread(&infoheader, sizeof(infoheader), 1, textureFile);

	textureData = new GLubyte[infoheader.biWidth * infoheader.biHeight];

	fread(textureData, sizeof(GLubyte), infoheader.biWidth*infoheader.biHeight, textureFile); 

    fclose(textureFile);
     
	return textureData;
}

