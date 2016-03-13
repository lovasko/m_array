#include <string.h>

#include "m_array.h"

int
m_array_get(m_array* array, size_t index, void** out_data)
{
	if (array == NULL || out_data == NULL)
		return M_ARRAY_E_NULL;

	if (index >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	*out_data = &array->data[array->object_size * index];
	return M_ARRAY_OK;
}

int
m_array_set(m_array* array, size_t index, size_t object_count, void* data)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (index + object_count >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	memcpy(&array->data[index * array->object_size],
	       data,
				 object_count * array->object_size);
	return M_ARRAY_OK;
}

