#include <string.h>

#include "m_array.h"

int
m_array_insert(m_array* array, size_t index, size_t object_count, void* data)
{
	size_t new_length;
	size_t need_length;

	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (index > array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	need_length = array->used_length + object_count;
	if (need_length > array->alloc_length) {
		new_length = (size_t)(array->alloc_length * array->growth_factor);
		if (new_length < need_length)
			return M_ARRAY_E_GROWTH;
		m_array_resize(array, new_length);
	}

	memmove(&array->data[(index+object_count) * array->object_size],
	        &array->data[index * array->object_size],
	        (array->used_length - index) * array->object_size);

	memcpy(&array->data[index * array->object_size],
	       data,
	       object_count * array->object_size);

	array->used_length += object_count;

	return M_ARRAY_OK;
}

int
m_array_append(m_array* array, size_t object_count, void* data)
{
	return m_array_insert(array, array->used_length, object_count, data);
}

int
m_array_prepend(m_array* array, size_t object_count, void* data)
{
	return m_array_insert(array, 0, object_count, data);
}

