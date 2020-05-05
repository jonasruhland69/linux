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

		  char * readBytes(long offset, int length){
			char bytes[length];
			fseek(fp,512L+offset,SEEK_CUR);
			fread(bytes, length,1,fp);
			return bytes;
		  }



		  BOOL gpt_process()  {
			// fp
			puts("\nDEBUG::gpt_close\n");
			unsigned char buffer[92];
			int haveRead = 0;
			int gptPosition=0;

                        //Get buffer size
			fseek(fp,512L,SEEK_CUR);
			//read file into the buffer
			haveRead = fread(buffer,1, 8, fp);
			if (haveRead ==0){
				printf("Error in reading the file block.\n");
				return FALSE;
			}else{
				while(gptPosition<92){
					printf("%02x ", buffer[gptPosition++]);
					if(gptPosition%8==0)
						printf("\n");
				}

				gptPosition=0;
				//Output Signatur
				printf("\nSignatur:\n");
				printf("%s",readBytes(0,8));

				//Output Header-Größe
				printf("\nHeader-Größe\n");
				gptPosition=12;
				while(gptPosition<16){
					printf("%02x \n",buffer[gptPosition]);
					gptPosition++;
				}

				//Output Backup LBA
				printf("\nBackup LBA (location of the other header copy)\n");
				gptPosition=32;
				while(gptPosition<40){
					printf("%d \n",buffer[gptPosition]);
					gptPosition++;
				}

				//Output Anzahl Partitionseinträge
				printf("\nAnzahl der Partitionseinträge (Partitionen)\n");
				gptPosition=80;
				while(gptPosition<84){
					printf("%d \n",buffer[gptPosition]);
					gptPosition++;
				}

				//Output Größe Partitionseintrag
				printf("\nGröße eines Partitionseintrags\n");
				gptPosition=84;
				while(gptPosition<88){
					printf("%d \n",buffer[gptPosition]);
					gptPosition++;
				}
			}
		  }