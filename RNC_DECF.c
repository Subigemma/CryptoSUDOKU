#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "RNC.h"
void Usage ( char * Msg )
{
   puts (Msg);
   puts ("Usage: RNC_DECF FileName");
   exit(1);
}
int main (int argc, char * argv[])
{
   DCR256 OutCR;
   unsigned short Index=0;
   char           DenCR[1024];
   size_t         BytesRead;
   char           FileIn[1024];
   char           FileOu[1024];
   FILE *         fi=NULL;
   FILE *         fo=NULL;

   if (argc<2)
      Usage("");  
 
   sprintf (FileIn, "%s", argv[1]);

   fi = fopen(FileIn,"rb");
   if (!fi)
      Usage("Cannot open input file");
   while (!feof(fi))
   {
      memset(DenCR,0,1024);
      memset(&OutCR,0,sizeof(DCR256));
      BytesRead=fread(&OutCR, 1, sizeof(DCR256),fi);
      Den256(DenCR,&OutCR);
      printf("%s",DenCR);
   }
   fclose(fi);
}
   
