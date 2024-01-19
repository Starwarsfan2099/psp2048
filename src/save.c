//based off VitaShell code by  TheFloW
#include "save.h"
#include <stdio.h>
#include <string.h>

int ReadFile(char *file, void *buf, int size) {
	SceUID fd = sceIoOpen(file, PSP_O_RDONLY, 0);
	if (fd < 0)
	return fd;

	int read = sceIoRead(fd, buf, size);

	sceIoClose(fd);
	return read;
}

int WriteFile(char *file, void *buf, int size) {
	SceUID fd = sceIoOpen(file, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	if (fd < 0)
	return fd;

	int written = sceIoWrite(fd, buf, size);

	sceIoClose(fd);
	return written;
}
void saveScore(int score) {
	char buf[20];
	sprintf(buf, "%d", score);
	int size = strlen(buf); 
	int ret = WriteFile("ms0:/2048_highscore.txt", buf, size); 

	if(ret<0) {
		//sceIoMkdir("ux0:/data/psp2048/", 0777);
		int ret = WriteFile("ms0:/2048_highscore.txt", buf, size); 
	}
	
}
int loadScore() {
    char buf[20];
    int output;
    int ret = ReadFile("ms0:/2048_highscore.txt", buf, sizeof(buf) - 1); // Read the entire content

    if(ret < 0) {
        output = 0; 
    } else  {
        buf[ret] = '\0'; // Null-terminate the string
        sscanf(buf, "%d", &output);
    }
    return output;
}