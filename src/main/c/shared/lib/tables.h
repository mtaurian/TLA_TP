#ifndef TABLES_H
#define TABLES_H
#include <stddef.h>

#define CHUNK_SIZE 10
#define ROWS(table,row) ((struct row**)(table)->rows)

struct Table {
    void ** rows;
    size_t size;
    size_t capacity;
    size_t rowSize;
};

struct Table * initTable(size_t rowSize);
void * addRow(struct Table * table, void * new_row_data);
void freeTable(struct Table * table);

#endif
