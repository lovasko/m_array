#ifndef M_ARRAY_H
#define M_ARRAY_H

#include <stdlib.h>
#include <stdint.h>

#define M_ARRAY_OK              0
#define M_ARRAY_E_NULL          1
#define M_ARRAY_E_OUT_OF_BOUNDS 2
#define M_ARRAY_E_GROWTH        3
#define M_ARRAY_E_ORDER         4
#define M_ARRAY_NOT_FOUND       5

#define M_ARRAY_GROWTH_CONSERVATIVE 1.5
#define M_ARRAY_GROWTH_EXPONENTIAL  2.0

#define M_ARRAY_NOT_SORTED 0
#define M_ARRAY_SORTED     1

typedef struct m_array {
	uint8_t* data;
	size_t used_length;
	size_t alloc_length;
	size_t object_size;
	size_t init_length;
	double growth_factor;
} m_array;

int m_array_init(m_array* array, size_t initial_length, size_t object_size);
int m_array_free(m_array* array);
int m_array_resize(m_array* array, size_t new_length);
int m_array_trim(m_array* array);
int m_array_length(m_array* array, size_t* out_length);
int m_array_growth_factor(m_array* array, double new_growth_factor);
int m_array_get(m_array* array, size_t index, void** out_data);
int m_array_set(m_array* array, size_t index, size_t object_count, void* data);
int m_array_swap(m_array* array, size_t i, size_t j, size_t object_count);
int m_array_append(m_array* array, size_t object_count, void* data);
int m_array_prepend(m_array* array, size_t object_count, void* data);
int m_array_insert(m_array* array, size_t index, size_t object_count, void* data);
int m_array_remove(m_array* array, size_t index, size_t object_count);
int m_array_remove_last(m_array* array, size_t object_count);
int m_array_remove_all(m_array* array);
int m_array_map(m_array* array, void(*fn)(void*,void*), void* payload);
int m_array_sort(m_array* array, int(*cmp_fn)(const void*,const void*));
int m_array_search(m_array* array, void* key, int(*cmp_fn)(const void*,const void*), int is_sorted, size_t* out_index);
int m_array_extremes(m_array* array, size_t start, size_t end, int(*cmp_fn)(const void*, const void*), size_t* out_min, size_t* out_max);

#endif

