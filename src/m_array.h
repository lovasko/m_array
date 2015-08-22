#ifndef M_ARRAY_H
#define M_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#define M_ARRAY_OK              0
#define M_ARRAY_E_NULL          1
#define M_ARRAY_E_OUT_OF_BOUNDS 2
#define M_ARRAY_E_GROWTH        3

#define M_ARRAY_GROWTH_CONSERVATIVE 1.5
#define M_ARRAY_GROWTH_EXPONENTIAL  2.0

struct m_array {
	uint8_t* data;
	size_t used_length;
	size_t alloc_length;
	size_t object_size;
	size_t end_index;
	double growth_factor;
};

int m_array_init(struct m_array* array, size_t object_size);
int m_array_length(struct m_array* array, size_t* out_length);
int m_array_growth_factor(struct m_array* array, double new_growth_factor);
int m_array_resize(struct m_array* array, size_t new_length);
int m_array_get(struct m_array* array, size_t index, void** out_data);
int m_array_set(struct m_array* array,
                size_t index,
                size_t object_count,
                void* data);
int m_array_append(struct m_array* array, size_t object_count, void* data);
int m_array_map(struct m_array* array, void(*fn)(void*,void*), void* payload);
int m_array_sort(struct m_array* array, int(*cmp_fn)(const void*, const void*));

#endif

