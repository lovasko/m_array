#include "m_array.h"

int
m_array_map(m_array* array, void(*fn)(void*,void*), void* payload)
{
	size_t i;

	if (array == NULL || fn == NULL)
		return M_ARRAY_E_NULL;

	for (i = 0; i < array->used_length; i++)
		fn((void*)&array->data[i * array->object_size], payload);

	return M_ARRAY_OK;
}

