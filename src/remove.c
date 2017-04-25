#include <string.h>

#include "m_array.h"

/** Remove objects from the array.
  * NOTE: this function does not deallocate memory.
  *
  * @param[in] arr array
  * @param[in] idx index
  * @param[in] cnt object count
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   arr is NULL
  * @retval M_ARRAY_E_BOUNDS the removal interval is out of bounds
  * @retval M_ARRAY_OK       success
**/
int
m_array_remove(m_array* arr, uint64_t idx, uint64_t cnt)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  if (arr->ar_ulen < idx + cnt)
    return M_ARRAY_E_BOUNDS;

  memmove(&arr->ar_data[idx         * arr->ar_obsz],
          &arr->ar_data[(idx + cnt) * arr->ar_obsz],
         (arr->ar_ulen - idx - cnt) * arr->ar_obsz);
  arr->ar_ulen -= cnt;

  return M_ARRAY_OK;
}

/** Remove elements from the end of the array.
  * NOTE: this function does not deallocate memory.
  *
  * @param[in] arr array
  * @param[in] cnt object count
  *
  * @return status code
  * @retval M_ARRAY_E_NULL   ar is NULL
  * @retval M_ARRAY_E_BOUNDS not enough objects to remove
  * @retval M_ARRAY_OK       success
**/
int
m_array_remove_last(m_array* arr, uint64_t cnt)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  if (arr->ar_ulen < cnt)
    return M_ARRAY_E_BOUNDS;

  arr->ar_ulen -= cnt;

  return M_ARRAY_OK;
}

/** Remove all objects from the array.
  * NOTE: this function does not deallocate memory.
  *
  * @param[in] arr array
  *
  * @return status code
  * @retval M_ARRAY_E_NULL arr is NULL
  * @retval M_ARRAY_OK     success
**/
int
m_array_remove_all(m_array* arr)
{
  if (arr == NULL)
    return M_ARRAY_E_NULL;

  arr->ar_ulen = 0;

  return M_ARRAY_OK;
}
