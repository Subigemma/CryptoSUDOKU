typedef struct dcr256 
{
   unsigned char crnum;
   unsigned char trnum;
   unsigned char prnum;
   unsigned char ofnum;
   unsigned char Msg[256];
   unsigned char Trail;
   struct dcr256 * Next;
   struct dcr256 * Prev;
}DCR256;

/*
** RNC_CR.c
*/
int Enc256 ( char * , DCR256 * );
int Den256 ( char * , DCR256 * );
