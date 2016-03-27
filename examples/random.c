#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <m_array.h>

static void
print_fn(void* number, void* payload)
{
	(void)payload;
	printf("%u ", *(uint8_t*)number);
}

static int
cmp_fn(const void* a, const void* b)
{
	return (*(uint8_t*)a - *(uint8_t*)b);
}

int
main(void)
{
	m_array array;
	int devrandom;
	uint8_t* minp;
	uint8_t* maxp;
	uint8_t min;
	uint8_t max;
	uint8_t number;
	unsigned int i;

	devrandom = open("/dev/random", O_RDONLY);
	m_array_init(&array, 10, 1);

	for (i = 0; i < 10; i++) {
		read(devrandom, &number, 1);
		m_array_append(&array, 1, &number);
	}

	m_array_map(&array, print_fn, NULL);
	printf("\n");
	m_array_extremes(&array, 0, 9, cmp_fn, (void**)&minp, (void**)&maxp);
	min = *minp;
	max = *maxp;

	m_array_sort(&array, cmp_fn);
	m_array_map(&array, print_fn, NULL);
	printf("\n");

	printf("min = %u\nmax = %u\n", min, max);

	m_array_free(&array);
	close(devrandom);
}

