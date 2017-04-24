#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "RNC.h"
void Usage ( char * Msg )
{
   puts (Msg);
   puts ("Usage: RNC_ENC FileName");
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
   sprintf (FileOu, "%s.enc", argv[1]);

   fi = fopen(FileIn,"rb");
   if (!fi)
      Usage("Cannot open input file");
   fo = fopen(FileOu,"wb");
   if (!fo)
   {
      fclose(fi);
      Usage("Cannot open output file");
   }
   while (!feof(fi))
   {
      memset(DenCR,0,1024);
      BytesRead=fread(DenCR, 1, 200,fi);
      Enc256(DenCR,&OutCR);
      OutCR.prnum=Index;
      Index++;
      fwrite(&OutCR,sizeof(DCR256),1,fo);
   }
   fclose(fi);
   fclose(fo);
}
   
