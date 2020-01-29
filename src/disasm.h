/*
disasm.h
provides dissasembly
*/

#pragma once

#include "asm.h"
#include "instr.h"

typedef struct {
    char *buf;
    size_t size;
    size_t pos;
} DecoderState;

typedef struct {
    bool valid_magic;
    uint16_t entry;
    uint16_t code_size;
    size_t decode_offset;
} RGHeader;

ARG take_arg(DecoderState *st) { return st->buf[st->pos++]; }

RGHeader decode_header(char *buf, size_t buf_sz) {
    RGHeader hd;
    hd.valid_magic = (buf[0] == 'r') && (buf[1] == 'g');
    if (hd.valid_magic) {
        hd.entry = buf[2] | (buf[3] << 8);
        hd.code_size = buf[4] | (buf[5] << 8);
        hd.decode_offset = 6; // start after header
    } else {
        printf("WARN: magic header not matched. reading as bare binary.\n");
        // set default values
        hd.entry = 0;
        hd.code_size = buf_sz;
    }
    return hd;
}

void dump_header(RGHeader hd) {
    printf("entry:     $%04x\n", hd.entry);
    printf("code size: $%04x\n", hd.code_size);
}

Program decode_program(char *buf, size_t buf_sz) {
    // read header
    RGHeader hd = decode_header(buf, buf_sz);
    DecoderState st = {.buf = buf, .size = hd.code_size, .pos = hd.decode_offset};
    int statement_buf_size = 128;
    Statement *statements = malloc(statement_buf_size * sizeof(statements));
    int statement_count = 0;
    Program prg = {.statements = statements, .status = 0, .entry = hd.entry};
    // check size multiple
    if ((hd.code_size % INSTR_SIZE) != 0) {
        // invalid size for program
        printf("invalid size %d for program.\n", (int)hd.code_size);
        prg.status = 1;
        return prg;
    }

    while (st.pos < hd.code_size) {

        ARG op = take_arg(&st);
        ARG a1 = take_arg(&st);
        ARG a2 = take_arg(&st);
        ARG a3 = take_arg(&st);

        // interpret instruction
        Statement stmt = {.opcode = op, .a1 = a1, .a2 = a2, .a3 = a3};
        populate_statement(&stmt);

        // save statement
        statements[statement_count++] = stmt;
    }

    prg.statement_count = statement_count;
    return prg;
}
