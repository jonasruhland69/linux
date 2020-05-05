#define _GPT_ANALYSE_C

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "gptAnalyse.h"

#define DEBUG 1


static FILE *fp=NULL;
/*  **************** IMPLEMENTING MMODULE       *****/


		  BOOL gpt_open(char *gptTable) {
			        #ifdef DEBUG
				printf("\nDEBUG::get_open file: (%s)\n",gptTable);

				fp = fopen(gptTable,"rb");
				if (!fp) {
						  printf("Cannot open file <%s> due to error: %s\n",gptTable,strerror(errno));
						  return FALSE;
				}
                                #endif
				return TRUE;
		  }

		  void gpt_close() {
				puts("\nDEBUG::gpt_close\n");
				if (fp)
						  fclose(fp);
		  }

		  char * readBytes(int offset, int length){
			unsigned char bytes[length];
			fseek(fp,offset,SEEK_CUR);
			fread(bytes, 1,length,fp);
			return bytes;
		  }



		  BOOL gpt_process() {
              // fp
              int haveRead = 0;
              int length=0;

              puts("\nDEBUG::gpt_process\n");
              fseek(fp,512,SEEK_CUR);

              //Output Signatur
              printf("\nSignatur:\n");
              length=8;
              char *signatur = readBytes(0, length);
              printf("Dezimal:\n");
              for(int i = 0; i<length;i++)
                printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for(int i = 0; i<length;i++)
                  printf("0x%02x ", signatur[i]);

              //Output Header-Größe
              printf("\n\nHeader-Größe:\n");
              length=4;
              signatur = readBytes(4, length);
              printf("Dezimal:\n");
              for(int i = 0; i<length;i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for(int i = 0; i<length;i++)
                  printf("0x%02x ", signatur[i]);

              //Output Backup LBA
              printf("\n\nBackup LBA:\n");
              length=8;
              signatur = readBytes(16, length);
              printf("Dezimal:\n");
              for(int i = 0; i<length;i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for(int i = 0; i<length;i++)
                  printf("0x%02x ", signatur[i]);

              //Output Anzahl der Partitionseinträge
              printf("\n\nAnzahl der Partitionseintraege:\n");
              length=4;
              signatur = readBytes(40, length);
              printf("Dezimal:\n");
              for(int i = 0; i<length;i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for(int i = 0; i<length;i++)
                  printf("0x%02x ", signatur[i]);

              //Output Groesse eines Partitionseintrags
              printf("\n\nGröße eines Partitionseintrags:\n");
              length=4;
              signatur = readBytes(0, length);
              printf("Dezimal:\n");
              for(int i = 0; i<length;i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for(int i = 0; i<length;i++)
                  printf("0x%02x ", signatur[i]);
          }