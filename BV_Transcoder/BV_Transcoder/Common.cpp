#include "FileGroup.h"

uint32_t GetFileSize(char* filename)  
{  
    FILE *fp=fopen(filename,"r");  
    if(!fp) return 0;  

    fseek(fp,0L,SEEK_END);  
    int size=ftell(fp);  
    fclose(fp);  
      
    return size;  
}
