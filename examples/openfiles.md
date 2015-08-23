# openfiles

In this example we periodically check the number of open files on the 
system (by using the `kern.openfiles` sysctl) and compute an median of 
these values over a period of time. WARNING: this example works only on
FreeBSD.

```C
#include <sys/types.h>
#include <sys/sysctl.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <m_array.h>

static int
get_openfiles()
{
	int value;
	size_t size;

	size = sizeof(int);
	sysctlbyname("kern.openfiles", &value, &size, NULL, 0);
	return value;
}

static int
uint_cmp(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

static int
median(struct m_array* array)
{
	size_t length;
	int* m;

	m_array_sort(array, uint_cmp);
	m_array_length(array, &length);
	m_array_get(array, length/2, (void**)&m);

	return *m;
}

int
main(void)
{
	struct m_array array;
	int i;
	int openfiles;

	m_array_init(&array, sizeof(int));
	m_array_growth_factor(&array, M_ARRAY_GROWTH_CONSERVATIVE);

	for (i = 0; i < 40; i++) {
		openfiles = get_openfiles();
		m_array_append(&array, 1, &openfiles);
		sleep(5);
	}

	printf("%d\n", median(&array));
}
```

Compile & build
```
$ clang -o openfiles openfiles.c -lmarray
$ ./openfiles
203
```

