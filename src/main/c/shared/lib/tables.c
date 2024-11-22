#include "tables.h"
#include <stdlib.h>
#include <string.h>

struct Table* initTable(size_t rowSize) {
    struct Table* table = (struct Table*)malloc(sizeof(struct Table));
    if (table == NULL) {
        return NULL;
    }
    table->rows = (void**)malloc(CHUNK_SIZE * sizeof(void*));
    if (table->rows == NULL) {
        return NULL;
    }
    table->size = 0;
    table->capacity = CHUNK_SIZE;
    table->rowSize = rowSize;
    return table;
}


void *addRow(struct Table* table, void *new_row_data) {
    if (table->size == table->capacity) {
        table->capacity += CHUNK_SIZE;
        table->rows = (void**)realloc(table->rows, table->capacity * sizeof(void*));
        if (table->rows == NULL) {
            return NULL;
        }
    }
    table->rows[table->size] = malloc(table->rowSize);
    if (table->rows[table->size] == NULL) {
        return NULL;
    }
    memcpy(table->rows[table->size], new_row_data, table->rowSize);
    table->size++;
    return table->rows[table->size-1];
}


void freeTable(struct Table* table) {
    for (size_t i = 0; i < table->size; i++) {
        free(table->rows[i]);
    }
    free(table->rows);
    free(table);
}
