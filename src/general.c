#include <string.h>
#include <errno.h>

#include "m_array.h"

/** Initialise the data structure.
  *
  * @param[in] arr  array
  * @param[in] ilen initial length
  * @param[in] obsz object size
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_MEMORY unable to allocate memory (consult errno)
  * @retval M_ARRAY_OK       success
**/
int
m_array_init(m_array* arr, uint64_t ilen, uint64_t obsz)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  errno = 0;
  arr->ar_data = malloc(ilen * obsz);
  if (arr->ar_data == NULL)
    return M_ARRAY_E_MEMORY;

  ar->ar_obsz = obsz;
  ar->ar_ulen = 0;
  ar->ar_alen = il;
  ar->ar_ilen = il;
  ar->ar_expg = 2.0;
  ar->ar_ling = 0;

  return M_ARRAY_OK;
}

/** Free all resources held by the array.
  *
  * @param[in] arr array
  *
  * @return status code
  * @retval M_ARRAY_E_NULL arr is NULL
  * @retval M_ARRAY_OK     success
**/
int
m_array_free(m_array* arr)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  free(arr->data);
  memset(arr, 0, sizeof(m_array));

  return M_ARRAY_OK;
}

/** Return the length of the array.
  *
  * @param[in]  arr array
  * @param[out] len length
  *
  * @return status code
  * @retval M_ARRAY_E_NULL arr and/or len is NULL
  * @retval M_ARRAY_OK     success
**/
int
m_array_length(m_array* arr, size_t* len)
{
  if (arr == NULL || len == NULL)
    return M_ARRAY_E_NULL;

  *len = arr->ar_ulen;
  return M_ARRAY_OK;
}
