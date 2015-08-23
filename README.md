# m_array
General-purpose dynamic array implementation in the C89 language that runs on
all POSIX-compatible systems.

## Features
TODO

## Time and space complexity
All operations have `O(1)` space complexity.

| Operation               |  Time   |
|-------------------------|---------|
| `m_array_append`        | `O(r)` |
| `m_array_get`           | `O(1)` |
| `m_array_growth_factor` | `O(1)` |
| `m_array_init`          | `O(1)` |
| `m_array_length`        | `O(1)` |
| `m_array_map`           | `O(n)` |
| `m_array_resize`        | `O(r)` |
| `m_array_set`           | `O(1)` |
| `m_array_sort`          | `O(q)` |

where:
 * `n` denotes the length of the array.
 * `r` is the complexity of the systems `realloc` function
 * `q` is the complexity of the systems `qsort` function

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

