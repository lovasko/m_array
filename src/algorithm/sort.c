#include <stdlib.h>

#include "m_array.h"

int
m_array_sort(m_array* array, int(*cmp_fn)(const void*,const void*))
{
	if (array == NULL || cmp_fn == NULL)
		return M_ARRAY_E_NULL;

	qsort(array->data, array->used_length, array->object_size, cmp_fn);
	return M_ARRAY_OK;
}

