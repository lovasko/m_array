# m_array
General-purpose dynamic array implementation in the C89 language that runs on
all POSIX-compatible systems.

## Introduction 
### Objects
The design of the `m_array` expects the content to be homogeneous objects of
arbitrary size - from one byte upwards. The size of the object in bytes is set
during the call to the initialisation function `m_array_init`. All consequent
function working with the array operate on objects (blocks of bytes) of such
size.

### Access
Functions `m_array_get` and `m_array_set` allow to access or modify arbitrary
element of the array. In the case of the `set` function, it is possible to
modify multiple consecutive elements in one call.

#### Bounds checking
Both `get` and `set` operations are protected with boundary checks with object
size granularity. Therefore, it is not possible to add new array elements with
the `set` call.

### Growth factor
By definition, the dynamic array expands to necessary size when new elements
are being appended. In order to minimise the number of calls to the potentially
time-expensive `realloc` function, `m_array` pre-allocates memory. By default,
it doubles the current memory size - `M_ARRAY_GROWTH_EXPONENTIAL`. This growth
strategy might not be optimal at times and therefore, a second strategy that
allocates only half of the current memory more - `M_ARRAY_GROWTH_CONSERVATIVE`.
Both of these constants have type `double`, with values `2.0` and `1.5`
respectively. It is possible to supply an entirely different growth factor
(strictly great than `1.0`). To set the growth factor at any time, use the
`m_array_growth_factor` function.

### Memory management
Even though `m_array` takes care of all things memory, its behaviour might not
be optimal in all scenarios. Therefore, it is possible to either grow or shrink
the underlying memory with the `m_array_resize` function.

### Finalisation
Adding elements to a `m_array` causes its internal memory buffers to grow. Once
finished with adding elements, it is possible that the `m_array` would still
hold unused internal memory due to the prefetch, expecting elements to be
added. In order to release this memory back to the system, use the
`m_array_trim` function.

### Algorithms
Even though the `m_array` supports random access to arbitrary elements with
bounds checking, it is possible to perform certain high-level operations on the
whole list.

#### Map
In order to apply a certain function to all objects stored in the `m_array`,
use the function `m_array_map`. Such function can be provided with an extra
argument, a `payload` that can be used to provide additional data.

#### Sort
By providing a comparison function `cmp_fn` to the `m_array_sort`, the function
is able to sort the elements. There is no option to choose the direction of the
sort (ascending vs descending), as this can be precisely controlled by the
inner workings of the comparator function.

#### Search
In order to search for an element, us the `m_array_search` function. By
providing the `key` and the comparator `cmp_fn`, the library is able to locate
such element. Depending on the value of the `is_sorted`, either the more
optimal binary search algorithm is performed - resulting in `O(logn)`
performance - or the linear walk from left to right through every element of
the array - resulting in `O(n)` performance.

## Time and space complexity
All operations have `O(1)` space complexity.

| Operation               | Time                 |
|-------------------------|----------------------|
| `m_array_append`        | `O(r)`               |
| `m_array_get`           | `O(1)`               |
| `m_array_growth_factor` | `O(1)`               |
| `m_array_init`          | `O(1)`               |
| `m_array_insert`        | `O(n)`               |
| `m_array_length`        | `O(1)`               |
| `m_array_map`           | `O(n)`               |
| `m_array_prepend`       | `O(n)`               |
| `m_array_remove_all`    | `O(n)`               |
| `m_array_remove`        | `O(n)`               |
| `m_array_resize`        | `O(r)`               |
| `m_array_search`        | `O(n)` or `O(log n)` |
| `m_array_set`           | `O(1)`               |
| `m_array_sort`          | `O(q)`               |
| `m_array_trim`          | `O(1)` or `O(n)`     |

where:
 * `n` denotes the length of the array.
 * `r` is the complexity of the systems `realloc` function, usually `O(n)`
 * `q` is the complexity of the systems `qsort` function, usually `O(nlogn)`

## Return codes 
### M_ARRAY_OK
The operation was successful.

### M_ARRAY_E_NULL
Either one or more of the arguments are `NULL`.

### M_ARRAY_E_OUT_OF_BOUNDS
The array subscription index is greater than the actual size of the array.

### M_ARRAY_E_GROWTH
Based on the growth factor and the current size of the array it is not possible
to grow enough so that the operation can proceed. In order to fix this, set the
growth factor to a greater number with the `m_array_growth_factor` function and
retry the operation.

### M_ARRAY_NOT_FOUND
The `m_array_search` function was not able to locate the specified element.

## Examples
 * [Median of open files count](examples/openfiles.md)

## Supported platforms
 * FreeBSD 10.0 with Clang 3.3
 * OS X 10.9 with Clang 3.5
 * Linux Gentoo 2.2 with Clang 3.6

If a platform does not appear to be in the previous list, it does not mean that
`m_array` will not work in such environment. It only means that nobody tested
it - you are encouraged to do so and report either success or failure.

## Build & install
```
$ ninja
$ sudo ./install.sh
```

## License
2-clause BSD license. For more information please consult the
[LICENSE](LICENSE.md) file. In the case that you need a different license, feel
free to contact me.

## Author
Daniel Lovasko (daniel.lovasko@gmail.com)

