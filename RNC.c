#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "RNC.h"

int main (void)
{
   DCR256 OutCR;
   char   DenCR[1024];

   memset (DenCR,0,1024);

   // Enc256("Texto a encriptar tope de chungo y ademas la tira de largo, bueno, digamos que largo solo", &OutCR);
   Enc256("Ricard Navarro Clarassó", &OutCR);
   printf("crnum:%d\n", OutCR.crnum);
   printf("trnum:%d\n", OutCR.trnum);
   printf("prnum:%d\n", OutCR.prnum);
   printf("ofnum:%d\n", OutCR.ofnum);
   printf("data:[%s]\n", OutCR.Msg);
   Den256(DenCR, &OutCR);
   printf("denc:[%s]\n", DenCR);
}
   
