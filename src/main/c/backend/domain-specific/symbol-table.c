#include "symbol-table.h"

#include <stdio.h>
#include <string.h>

#include "../../shared/CompilerState.h"

int entrySymbolCompare(const void *a, const void *b, void *udata) {
    const struct EntrySymbols *ua = a;
    const struct EntrySymbols *ub = b;
    return strcmp(ua->id, ub->id);
}

boolean entrySymbolIter(const void *item, void *udata) {
    const struct EntrySymbols *entry = item;
    printf(" Entry: %s\n", entry->id);
    return true;
}

uint64_t entrySymbolHash(const void *item, uint64_t seed0, uint64_t seed1){
    const struct EntrySymbols *entry = item;
    return hashmap_sip(entry->id, strlen(entry->id), seed0, seed1);
}