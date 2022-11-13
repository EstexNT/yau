#include "parser.h"

static int parser_readarg(char *lineBuffer, int letterSkip) {
    strcpy(sCurrentArgument, lineBuffer + letterSkip);
    char argInt = atoi(sCurrentArgument);
    if (argInt > 0b00001111) { // Binary format doesn't allow for arguments larger than 0b1111 (15)
        fprintf(stderr, "WARNING: The supplied argument is larger than 15 (Line: %lld)\n", sCurrentLine);
        argInt = 0;
    }
    if (sCurrentMC.opcode == OP_JE || sCurrentMC.opcode == OP_JNE) {
        if ((argInt >= 0b00001000 && sCurrentArgument[0] != '-') || (argInt < -8)) {
            fprintf(stderr, "WARNING: The supplied argument for JE/JNE should be in range of [-8; 7] (Line: %lld)\n", sCurrentLine);
            argInt = 0;
        } 
    }
    memset(sCurrentArgument, 0, sizeof(sCurrentArgument));
    return argInt;
}

void parser_init() {
    // TODO
}

static void parser_handle_ops(char *lineBuffer, FILE *outputFile) {
    if (strcmp(lineBuffer, "") == 0) {
        // Skip empty lines
        return;
    } 
    else if (lineBuffer[0] == '#') {
        // Skip comments
        return;
    }
    else if (strcmp(lineBuffer, "STOP") == 0) {
        sCurrentMC.opcode = OP_STOP;
        sCurrentMC.argument = 0;
    }
    else if (strncmp(lineBuffer, "MOVA", strlen("MOVA")) == 0) {
        sCurrentMC.opcode = OP_MOVA;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("MOVA"));
    }
    else if (strncmp(lineBuffer, "MOVB", strlen("MOVB")) == 0) {
        sCurrentMC.opcode = OP_MOVB;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("MOVB"));
    }
    else if (strcmp(lineBuffer, "PUSHA") == 0) {
        sCurrentMC.opcode = OP_PUSHA;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "PUSHB") == 0) {
        sCurrentMC.opcode = OP_PUSHB;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "POPA") == 0) {
        sCurrentMC.opcode = OP_POPA;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "POPB") == 0) {
        sCurrentMC.opcode = OP_POPB;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "INCA") == 0) {
        sCurrentMC.opcode = OP_INCA;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "INCB") == 0) {
        sCurrentMC.opcode = OP_INCB;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "CMPAB") == 0) {
        sCurrentMC.opcode = OP_INCB;
        sCurrentMC.argument = 0b1111; // Hack
    }
    else if (strncmp(lineBuffer, "CMPA", strlen("CMPA")) == 0) {
        sCurrentMC.opcode = OP_CMPA;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("CMPA"));
    }
    else if (strncmp(lineBuffer, "CMPB", strlen("CMPB")) == 0) {
        sCurrentMC.opcode = OP_CMPB;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("CMPB"));
    }
    else if (strncmp(lineBuffer, "JE", strlen("JE")) == 0) {
        sCurrentMC.opcode = OP_JE;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("JE"));
    }
    else if (strncmp(lineBuffer, "JNE", strlen("JNE")) == 0) {
        sCurrentMC.opcode = OP_JNE;
        sCurrentMC.argument = parser_readarg(lineBuffer, strlen("JNE"));
    }
    else if (strcmp(lineBuffer, "OUTA") == 0) {
        sCurrentMC.opcode = OP_OUTA;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "OUTB") == 0) {
        sCurrentMC.opcode = OP_OUTB;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "NOP") == 0) {
        sCurrentMC.opcode = OP_NOP;
        sCurrentMC.argument = 0;
    } 
    else if (strcmp(lineBuffer, "DMP") == 0) {
        sCurrentMC.opcode = OP_NOP;
        sCurrentMC.argument = 0b1111; // Hack
    } 

    else {
        fprintf(stderr, "WARNING: Unrecognized instruction at line %lld\n", sCurrentLine);
        return;
    }
    
    fwrite(&sCurrentMC, sizeof(struct MachineCodeFormat), sizeof(sCurrentMC), outputFile);
}

int parser_parse(FILE *inputFile, FILE *outputFile) {
    // Read the input file
    while (fgets(sInFileLineBuffer, sizeof(sInFileLineBuffer), inputFile) != NULL) {
        sCurrentLine++;

        // Remove the newline
        int lineBufLen = strlen(sInFileLineBuffer) - 1;
        if (sInFileLineBuffer[lineBufLen] == '\n') {
            sInFileLineBuffer[lineBufLen] = '\0'; 
        }
        parser_handle_ops(sInFileLineBuffer, outputFile);
    }
    return 0;
}