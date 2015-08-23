#include <stdlib.h>

#include "m_array.h"

int
m_array_search(struct m_array* array,
               void* key,
               int(*cmp_fn)(const void*, const void*),
               int is_sorted,
               size_t* out_index)
{
	void* match;
	size_t i;

	if (array == NULL || key == NULL || cmp_fn == NULL || out_index == NULL)
		return M_ARRAY_E_NULL;

	if (is_sorted) {
		match = bsearch(key,
		                array->data,
		                array->used_length,
		                array->object_size,
		                cmp_fn);

		if (match == NULL)
			return M_ARRAY_E_NOT_FOUND;
		else {
			*out_index = (size_t)((uint8_t*)match - array->data);	
			return M_ARRAY_OK;
		}
	} else {
		for (i = 0; i < array->used_length; i++) {
			if (cmp_fn(key, &array->data[i * array->object_size]) == 0) {
				*out_index = i;
				return M_ARRAY_OK;
			}
		}
		return M_ARRAY_E_NOT_FOUND;
	}
}

