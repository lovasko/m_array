#include "m_array.h"

int
m_array_extremes(m_array* array,
                 size_t start,
                 size_t end,
                 int(*cmp_fn)(const void*, const void*),
                 void** out_min,
                 void** out_max)
{
	void* min;
	void* max;
	void* elem;
	size_t i;

	if (array == NULL || cmp_fn == NULL)
		return M_ARRAY_E_NULL;

	if (start > end)
		return M_ARRAY_E_ORDER;

	if (start >= array->used_length || end >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	if (start == end) {
		if (out_min != NULL)
			*out_min = &array->data[array->object_size * start];

		if (out_max != NULL)
			*out_max = &array->data[array->object_size * start];

		return M_ARRAY_OK;
	}

	min = &array->data[array->object_size * start];
	max = &array->data[array->object_size * start];

	for (i = start+1; i < end+1; i++) {
		elem = &array->data[array->object_size * i];

		if (cmp_fn(min, elem) > 0)
			min = elem;
		else if (cmp_fn(max, elem) < 0)
			max = elem;
	}

	if (out_min != NULL)
		*out_min = min;

	if (out_max != NULL)
		*out_max = max;

	return M_ARRAY_OK;
}

