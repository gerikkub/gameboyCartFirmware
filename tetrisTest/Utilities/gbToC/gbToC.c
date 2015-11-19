#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char* outFileHeader = "#include <stdint.h>\n\nuint8_t gameData[] = {";
static char* outFileFooter = "};\n";

void writeFile(FILE* inFile, FILE* outFile)
{
   char outTxt[] = "0x00";
   char data;
   int currIdx = 0;
   int inFileLen;

   fseek(inFile, 0, SEEK_END);
   inFileLen = ftell(inFile);
   fseek(inFile, 0, SEEK_SET);

   printf("File Length %d\n", inFileLen);

   fprintf(outFile, outFileHeader);
   
   for (currIdx = 0; currIdx < inFileLen; currIdx++)
   {
      if (currIdx % 16 == 0)
      {
         fprintf(outFile, "\n");
      }

      fread(&data, sizeof(char), 1, inFile);

      sprintf(&outTxt[2], "%.2hhX", data);

      fprintf(outFile, "%s, ", outTxt);


   }

   fseek(inFile, -2, SEEK_CUR);

   fprintf(outFile, outFileFooter);
}


int main(int argc, char** argv)
{

   if (argc < 2)
   {
      printf("Usage: %s gameboyFilename\n", argv[0]);
   }

   FILE* gbFile = fopen(argv[1], "rb");

   if (gbFile == NULL)
   {
      printf("Unable to open %s\n", argv[1]);
      exit(1);
   }

   char* outFilename = calloc(strlen(argv[1]) + strlen(".c"), sizeof(char));

   outFilename = strcat(argv[1], ".c");

   FILE* outFile = fopen(outFilename, "w");

   if (outFile == NULL)
   {
      printf("Unable to open %s for writing\n", outFilename);
      fclose(gbFile);
      exit(1);
   }

   writeFile(gbFile, outFile);

   fclose(gbFile);
   fclose(outFile);
   //free(outFilename);

   return 0;
}
