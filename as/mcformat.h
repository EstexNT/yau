#pragma once

#pragma pack(push,1)
struct MachineCodeFormat {
    char argument:4; // (note: sometimes arg is abused as a part of the opcode)
    unsigned char opcode:4;
};
#pragma pack(pop)
