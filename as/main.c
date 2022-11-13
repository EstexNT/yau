#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parser.h"

void print_usage(char *programName) {
    printf("Usage: \n");
    printf("%s <inFile> [-o outFile]\n", programName);
}

int main(int argc, char *argv[]) {
    printf("YAU Assembler\n");
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }
    FILE *inFile = fopen(argv[1], "r"); // our input file (assembly)
    if (inFile == NULL) { // if it doesn't exist, screech
        fprintf(stderr, "ERROR: The input file was not found\n");
        return 1;
    }

    char *outFileName = "a.out";
    if (argv[2] == NULL || argv[3] == NULL) {
        goto SkipOutFileCheck; // skip output file stuff if the arguments were not supplied
    }
    if (strcmp(argv[2], "-o") == 0) {
        //printf("found output file argument\n");
        if (strcmp(argv[1], argv[3]) == 0) {
            fprintf(stderr, "WARNING: The output file is the same as the input file\n");
            goto SkipOutFileCheck;
        }
        outFileName = argv[3];
    }

    SkipOutFileCheck:
    if (argv[2] != NULL) {
        if (strcmp(argv[2], "-o") == 0) {
            if (argv[3] == NULL) {
               fprintf(stderr, "WARNING: Output file name not found\n");
            }
        }
    }

    // create the output file
    FILE *outFile = fopen(outFileName, "w+b");
    if (outFile == NULL) {
        fprintf(stderr, "ERROR: Could not create the output file");
    }
    /*
    // read the input file
    fseek(inFile, 0, SEEK_END);
    long inFileSize = ftell(inFile);
    rewind(inFile);
    //printf("input filesize = %ld\n", inFileSize);
    char *inFileBuffer = NULL;
    inFileBuffer = malloc(sizeof(char) * inFileSize);

    if (fread(inFileBuffer, 1, inFileSize, inFile) != inFileSize) {
        fprintf(stderr, "ERROR: Could not read the input file");
    }
    */

    parser_init();

    parser_parse(inFile, outFile);

    // in the end, cleanup everything
    fclose(inFile);
    fclose(outFile);
    //free(inFileBuffer);
    return 0;
}