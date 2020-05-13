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

		  char *readBytes(int offset, int length){
			char *bytes;
			fseek(fp,offset,SEEK_CUR);
			fread(bytes, 1,length,fp);
			return bytes;
		  }



		  BOOL gpt_process() {
              // fp
              int length = 0;

              puts("\nDEBUG::gpt_process\n");
              fseek(fp, 512, SEEK_CUR);

              //Output Signatur
              printf("\nSignatur:\n");
              length = 8;
              char *signatur = readBytes(0, length);
              printf("Dezimal:\n");
              for (int i = 0; i < length; i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for (int i = 0; i < length; i++)
                  printf("0x%02x ", signatur[i]);

              //Output Header-Größe
              printf("\n\nHeader-Größe:\n");
              length = 4;
              strcpy(signatur, readBytes(4, length));
              printf("Dezimal:\n");
              for (int i = 0; i < length; i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for (int i = 0; i < length; i++)
                  printf("0x%02x ", signatur[i]);

              //Output Backup LBA
              printf("\n\nBackup LBA:\n");
              length = 8;
              strcpy(signatur, readBytes(16, length));
              printf("Dezimal:\n");
              for (int i = 0; i < length; i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for (int i = 0; i < length; i++)
                  printf("0x%02x ", signatur[i]);

              //Output Anzahl der Partitionseinträge
              printf("\n\nAnzahl der Partitionseintraege:\n");
              length = 4;
              strcpy(signatur, readBytes(40, length));
              printf("Dezimal:\n");
              for (int i = 0; i < length; i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for (int i = 0; i < length; i++)
                  printf("0x%02x ", signatur[i]);

              //Output Groesse eines Partitionseintrags
              printf("\n\nGröße eines Partitionseintrags:\n");
              length = 4;
              strcpy(signatur, readBytes(0, length));
              printf("Dezimal:\n");
              for (int i = 0; i < length; i++)
                  printf("%d ", signatur[i]);
              printf("\nHex:\n");
              for (int i = 0; i < length; i++)
                  printf("0x%02x ", signatur[i]);


              //Sprung zum 513. Byte
              fseek(fp, 1025, SEEK_SET);
              for (int i = 0; i < 32; i++) {
                  printf("\n\nLBA %d", i);

                  printf("\nPartition type GUID:");
                  length = 16;
                  strcpy(signatur, readBytes(0, length));
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);

                  printf("\nUnique partition GUID:");
                  length = 16;
                  strcpy(signatur, readBytes(0, length));
                  printf("Dezimal:\n");
                  for (int i = 0; i < length; i++)
                      printf("%d ", signatur[i]);
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);

                  printf("\nFirst LBA:");
                  length = 8;
                  strcpy(signatur, readBytes(0, length));
                  printf("Dezimal:\n");
                  for (int i = 0; i < length; i++)
                      printf("%d ", signatur[i]);
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);

                  printf("\nLast LBA:");
                  length = 8;
                  strcpy(signatur, readBytes(0, length));
                  printf("Dezimal:\n");
                  for (int i = 0; i < length; i++)
                      printf("%d ", signatur[i]);
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);

                  printf("\nAttribute Flags:");
                  length = 8;
                  strcpy(signatur, readBytes(0, length));
                  printf("Dezimal:\n");
                  for (int i = 0; i < length; i++)
                      printf("%d ", signatur[i]);
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);

                  printf("\nPartition name:");
                  length = 72;
                  strcpy(signatur, readBytes(0, length));
                  printf("Dezimal:\n");
                  for (int i = 0; i < length; i++)
                      printf("%d ", signatur[i]);
                  printf("\nHex:\n");
                  for (int i = 0; i < length; i++)
                      printf("0x%02x \n", signatur[i]);
              }
          }