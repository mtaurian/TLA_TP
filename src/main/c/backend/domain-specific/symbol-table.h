#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "../extern-utils/hashmap.h"

enum questionType {
    CHECKBOX=0, RADIOS, SELECT, TEXT, IMAGE, DOCUMENT, LONGTEXT, NUMERIC, PASSWORD, DATE
}questionType;

enum selectType {
    TEXT=0, NUMERIC, DATE
}selectType;

enum symbolType {
    QUESTION=0,STEP,SHOWIF
}symbolType;

struct question {
    int index;
    char * stepId;
    questionType type;
    selectType selectType;
} question;



struct symbolEntry {
    char * id;
    symbolType type;
    question value;
}symbolEntry;

int formFg_compare(const void *a, const void *b, void *udata);

bool formFg_iter(const void *item, void *udata);

uint64_t formFg_hash(const void *item, uint64_t seed0, uint64_t seed1);

#endif  // _SYMBOL_TABLE_H_