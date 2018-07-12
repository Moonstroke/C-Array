#ifndef CODS_ARRAYMAP_H
#define CODS_ARRAYMAP_H


#include <stdbool.h>
#include <stddef.h> /* for size_t */
#include <stdlib.h> /* for NULL */

#include "cods.h" /* for func attrs, data_t */



typedef struct arraymap ArrayMap;

typedef data_t key_t;
typedef data_t value_t;


CODS_CTOR ArrayMap *am_new(size_t size, int (*cmp)(const key_t*, const key_t*))
CODS_NOTNULL(2);

CODS_MEMBER void am_free(ArrayMap *self);


CODS_MEMBER bool am_put(ArrayMap *self, key_t *key, value_t *value)
CODS_NOTNULL(2, 3);

CODS_MEMBER value_t *am_get(const ArrayMap *self, const key_t *key)
CODS_NOTNULL(2);
CODS_MEMBER CODS_INLINE CODS_NOTNULL(2, 3)
value_t *am_getd(const ArrayMap *const self, const key_t *const key,
                 value_t *const d_val) {
	value_t *const value = am_get(self, key);
	return value == NULL ? d_val : value;
}

CODS_MEMBER bool am_contains(const ArrayMap *self, const key_t *key);

CODS_MEMBER value_t *am_remove(ArrayMap *self, key_t *key);


#endif /* CODS_ARRAYMAP_H */
