#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "RNC.h"

#define STR_CRSIZE           17
#define ARR_CRSIZE           18
#define FILL_STUFF "Neben SPSS Statistics und Modeler wird auch die kognitive Intelligenz Watson Analytics vorgestellt. Watson lernt standig und entwickelt sich stets weiter, um noch intelligenter zu werden. Wir stellen Ihnen vor, wie Sie mit Hilfe von Cognitive Computing Ihre Analysen ebenfalls zukünftig verbessern können.iZoeken in Ondersteuning w lijst van recentelijk bekeken producten delen"

unsigned char Sudoku[STR_CRSIZE][STR_CRSIZE]  = {
                                 "EFGHIJKLMNOPABCD",
                                 "IJKLMNOPABCDEFGH",
                                 "IJKLMNOPABCDEFGH",
                                 "MNOPABCDEFGHIJKL",

                                 "BCDEFGHIJKLMNOPA",
                                 "FGHIJKLMNOPABCDE",
                                 "JKLMNOPABCDEFGHI",
                                 "NOPABCDEFGHIJKLM",

                                 "CDEFGHIJKLMNOPAB",
                                 "GHIJKLMNOPABCDEF",
                                 "KLMNOPABCDEFGHIJ",
                                 "OPABCDEFGHIJKLMN",

                                 "DEFGHIJKLMNOPABC",
                                 "HIJKLMNOPABCDEFG",
                                 "LMNOPABCDEGFHIJK",
                                 "PABCDEFGHIJKLMNO"
                             };

int Enc256 ( char * ToCr , DCR256 * MyCr )
{
   unsigned long  lDummy=0;
   unsigned int   iDummy=0;
   unsigned int   LenToCopy=0;
   char *         p_Aux;
   char           c_Aux;
   unsigned char  MyCadCR[STR_CRSIZE];
   unsigned char  MyCadTR[STR_CRSIZE];
   unsigned char  MyBuff[ARR_CRSIZE][STR_CRSIZE];
   unsigned char  MyBuff2[ARR_CRSIZE][STR_CRSIZE];
   unsigned char  TmpArray[300];
   unsigned short LoopVar,Col,Row=0;
   
   time_t t;
   DCR256 MyMsg;
   
   memset ( &MyMsg , 0, sizeof(DCR256));   
   memset ( TmpArray , 0, 300);   
   memset ( MyCadCR, 0, STR_CRSIZE);   
   memset ( MyCadTR, 0, STR_CRSIZE);   
   for (LoopVar=0;LoopVar<ARR_CRSIZE;LoopVar++)
   {
      memset (MyBuff[LoopVar],0,STR_CRSIZE);
      memset (MyBuff2[LoopVar],0,STR_CRSIZE);
   }
   srand((unsigned) time(&t));
   lDummy=(unsigned long) rand()*16;
   iDummy=(unsigned int) (lDummy/RAND_MAX);
   MyMsg.crnum=iDummy;

   lDummy=(unsigned long) rand()*16;
   iDummy=(unsigned int) (lDummy/RAND_MAX);
   MyMsg.trnum=iDummy;

   if (strlen(ToCr) > 256)
      return(-1);
 
   sprintf( TmpArray, "%s%s%s", Sudoku[MyMsg.crnum], ToCr, Sudoku[MyMsg.trnum] );
   LenToCopy=strlen(TmpArray);
   strncat ( TmpArray, FILL_STUFF, 288 - LenToCopy);
   for (LoopVar=0;LoopVar<STR_CRSIZE;LoopVar++)
      memcpy(MyBuff[LoopVar], &TmpArray[LoopVar*(STR_CRSIZE-1)], STR_CRSIZE-1);

   for (Col=0;Col<16;Col++)
   {
      for(Row=0;Row<16;Row++)   
      {
         MyBuff2[Col][Row]=MyBuff[Row][Col];
      }
   }
   for (Col=0;Col<16;Col++)
   {
      for(Row=0;Row<16;Row++)   
      {
         if (MyBuff2[Row][0]>MyBuff2[Col][0])
         {
            memset ( TmpArray , 0, 300);   
            strcpy(TmpArray, MyBuff2[Col]);
            strcpy(MyBuff2[Col],MyBuff2[Row]);
            strcpy(MyBuff2[Row],TmpArray);
         }
      }
   }

   for (LoopVar=0;LoopVar<16;LoopVar++)
      strcat ( MyMsg.Msg, MyBuff2[LoopVar]);
   for (LoopVar=0;LoopVar<strlen(MyMsg.Msg);LoopVar++)
      MyMsg.Msg[LoopVar]+=32;
   
   memcpy ( MyCr, &MyMsg, sizeof(DCR256));
}
int Den256 ( char * ToCr, DCR256 * MyMsg )
{
   unsigned char  MyBuff[ARR_CRSIZE][STR_CRSIZE];
   unsigned char  MyBuff2[ARR_CRSIZE][STR_CRSIZE];
   unsigned char  TmpArray[1024];
   unsigned short Row,Col,LoopVar=0;
   char * p_Aux;

   if (strlen(MyMsg->Msg) != 256)
      return (-1);
   memset (TmpArray,0,1024);
   for (LoopVar=0;LoopVar<256;LoopVar++)
      MyMsg->Msg[LoopVar]-=32;
   for (LoopVar=0;LoopVar<16;LoopVar++)
   {
      memset (MyBuff2[LoopVar],0,STR_CRSIZE);
      memset (MyBuff[LoopVar],0,STR_CRSIZE);
      memcpy (MyBuff[LoopVar], &MyMsg->Msg[LoopVar*16], 16);
   }
   for (Row=0;Row<16;Row++)
   {
      for (Col=0;Col<16;Col++)
      {
         if (Sudoku[MyMsg->crnum][Row] == MyBuff[Col][0])
            memcpy(MyBuff2[Row],MyBuff[Col],16);
      }
   }
   for (LoopVar=0;LoopVar<16;LoopVar++)
      memset (MyBuff[LoopVar],0,STR_CRSIZE);
   for (Col=0;Col<16;Col++)
   {
      for(Row=0;Row<16;Row++)   
      {
         MyBuff[Col][Row]=MyBuff2[Row][Col];
      }
   }
   for (LoopVar=0;LoopVar<16;LoopVar++)
      strcat (TmpArray, MyBuff[LoopVar]);
   p_Aux = strstr ( &TmpArray[16], Sudoku[MyMsg->trnum]);  
   if (!p_Aux)
      return (-1);

   * p_Aux=(char)0;
  
   strcpy (ToCr, &TmpArray[16]); 
   
}
