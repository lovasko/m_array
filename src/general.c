#include "m_array.h"

int
m_array_init(struct m_array* array, size_t initial_length, size_t object_size)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	array->data = malloc(initial_length * object_size);
	array->object_size = object_size;
	array->used_length = 0;
	array->alloc_length = initial_length;
	array->init_length = initial_length;
	array->growth_factor = M_ARRAY_GROWTH_EXPONENTIAL;

	return M_ARRAY_OK;
}

int
m_array_length(struct m_array* array, size_t* out_length)
{
	if (array == NULL || out_length == NULL)
		return M_ARRAY_E_NULL;

	*out_length = array->used_length;
	return M_ARRAY_OK;
}

int
m_array_growth_factor(struct m_array* array, double new_growth_factor)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	if (new_growth_factor <= 1.0)
		return M_ARRAY_E_GROWTH;

	array->growth_factor = new_growth_factor;
	return M_ARRAY_OK;
}

static size_t
min(size_t a, size_t b)
{
	return (a < b) ? a : b;
}

int
m_array_resize(struct m_array* array, size_t new_length)
{
	if (array == NULL)
		return M_ARRAY_E_NULL;

	array->alloc_length = new_length;
	array->used_length = min(new_length, array->used_length);
	array->data = realloc(array->data, new_length * array->object_size);

	return M_ARRAY_OK;
}

