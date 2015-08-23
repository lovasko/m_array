#include <string.h>

#include "m_array.h"

int
m_array_remove(struct m_array* array, size_t index, size_t object_count)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (index + object_count >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	memmove(array->data + (index * array->object_size),
	        array->data + ((index + object_count) * array->object_size),
	        (array->used_length - index - object_count) * array->object_size);
	array->used_length -= object_count;

	return M_ARRAY_OK;
}

int
m_array_remove_all(struct m_array* array)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	m_array_remove(array, 0, array->used_length);
	m_array_resize(array, 8);

	return M_ARRAY_OK;
}

