#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mcformat.h"


// opcodes commented out are the ones that abuse the no-arguments instructions
enum AsmOpcodes {
    OP_STOP = 0, // STOP
    OP_MOVA,     // MOVA X
    OP_MOVB,     // MOVB X
    OP_PUSHA,    // PUSHA
    OP_PUSHB,    // PUSHB
    OP_POPA,     // POPA
    OP_POPB,     // POPB
    OP_INCA,     // INCA
    OP_INCB,     // INCB
    //OP_CMPAB,    // CMPAB
    OP_CMPA,     // CMPA X
    OP_CMPB,     // CMPB X
    OP_JE,       // JE X
    OP_JNE,      // JNE X
    OP_OUTA,     // OUTA
    OP_OUTB,     // OUTB
    OP_NOP,      // NOP
    //OP_DMP,      // DMP
};

extern void parser_init();
extern int parser_parse(FILE *parsedFile, FILE *outputFile);

static char sInFileLineBuffer[1000 + 1] = {0};
static char sCurrentArgument[100 + 1] = {0};
static long long sCurrentLine = 0;

struct MachineCodeFormat sCurrentMC;