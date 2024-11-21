#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

enum questionType {
    CHECKBOX=0, RADIOS, SELECT, TEXT, IMAGE, DOCUMENT, LONGTEXT, NUMERIC, PASSWORD, DATE
};

enum selectType {
    TEXT=0, NUMERIC, DATE
};

enum symbolType {
    QUESTION=0,STEP,SHOWIF
};

struct question {
    int index;
    char * stepId;
    questionType type;
    selectType selectType;
};


struct symbolEntry {
    char * id;
    symbolType type;
    question value;
};


#endif  // _SYMBOL_TABLE_H_