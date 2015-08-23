#include <string.h>

#include "m_array.h"

int
m_array_get(struct m_array* array, size_t index, void** out_data)
{
	if (array == NULL || out_data == NULL)
		return M_ARRAY_E_NULL;

	if (index >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	*out_data = &array->data[array->object_size * index];
	return M_ARRAY_OK;
}

static void
set(struct m_array* array, size_t index, size_t count, void* data)
{
	memcpy(&array->data[index * array->object_size],
	       data,
				 count * array->object_size);
}

int
m_array_set(struct m_array* array,
            size_t index,
            size_t object_count,
            void* data)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (index + object_count >= array->used_length)
		return M_ARRAY_E_OUT_OF_BOUNDS;

	set(array, index, object_count, data);
	return M_ARRAY_OK;
}

int
m_array_append(struct m_array* array, size_t object_count, void* data)
{
	size_t new_length;

	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (array->used_length == array->alloc_length-1) {
		new_length = (size_t)(array->alloc_length * array->growth_factor);
		if (new_length <= array->alloc_length)
			return M_ARRAY_E_GROWTH;
		m_array_resize(array, new_length);
	}

	set(array, array->used_length, object_count, data);
	array->used_length++;

	return M_ARRAY_OK;
}

