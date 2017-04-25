#include <stdlib.h>

#include "m_array.h"


/** Force the array to preallocate necessary space.
  *
  * @param[in] arr  array
  * @param[in] ncnt new object count
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_MEMORY unable to allocate memory (consult errno)
  * @retval M_ARRAY_OK       success
**/
int
m_array_resize(m_array* arr, uint64_t ncnt)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  arr->ar_alen = ncnt;
  arr->ar_ulen = cnt < arr->ar_ulen ? cnt : arr->ar_ulen;

  arr->ar_data = realloc(arr->ar_data, arr->ar_ulen * arr->ar_obsz);
  if (arr->ar_data == NULL)
    return M_ARRAY_E_MEMORY;


  return M_ARRAY_OK;
}

/** Free all unused memory by the array data.
  *
  * @param[in] arr array
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_MEMORY unable to allocate memory (consult errno)
  * @retval M_ARRAY_OK       success
**/
int
m_array_trim(m_array* arr)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  arr->ar_alen = arr->ar_ulen;

  arr->ar_data = realloc(arr->ar_data, arr->ar_ulen * arr->ar_obsz);
  if (arr->ar_data == NULL)
    return M_ARRAY_E_MEMORY;

  return M_ARRAY_OK;
}

/** Change the array growth to be linear.
  *
  * @param[in] arr  array
  * @param[in] ling linear step size
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_GROWTH ling is zero
  * @retval M_ARRAY_OK       success
**/
int
m_array_grow_lin(m_array* arr, uint64_t ling)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  if (ling == 0)
    return M_ARRAY_E_GROWTH;

  arr->ar_expg = 0.0;
  arr->ar_ling = ling;

  return M_ARRAY_OK;
}

/** Change the array growth to be exponential.
  *
  * @param[in] arr array
  * @param[in] expg exponent of growth
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_GROWTH expg is less than 1.0
  * @retval M_ARRAY_OK       success
**/
int
m_array_grow_exp(m_array* arr, double expg)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  if (expg <= 1.0)
    return M_ARRAY_E_GROWTH;

  arr->ar_expg = expg;
  arr->ar_ling = 0;

  return M_ARRAY_OK;
}
