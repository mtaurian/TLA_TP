#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include "../../shared/lib/hashmap.h"


int entrySymbolCompare(const void *a, const void *b, void *udata);

boolean entrySymbolIter(const void *item, void *udata);

uint64_t entrySymbolHash(const void *item, uint64_t seed0, uint64_t seed1);

#endif  // _SYMBOL_TABLE_H_