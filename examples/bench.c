#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <m_array.h>

static void
bubble_sort(m_array* array)
{
	size_t i;
	size_t length;
	uint64_t* a;
	uint64_t* b;
	int swap;

	m_array_length(array, &length);
	while (1) {
		swap = 0;
		for (i = 0; i < length-1; i++) {
			m_array_get(array, i, (void**)&a);
			m_array_get(array, i+1, (void**)&b);

			if (*a > *b) {
				m_array_swap(array, i, i+1, 1);
				swap = 1;
			}
		}

		if (swap == 0)
			break;
	}
}

static int
uint64_t_cmp(const void* a, const void* b)
{
	return (*(uint64_t*)a - *(uint64_t*)b);
}

static void
print_elapsed_time(char* name, struct timeval* start, struct timeval* end)
{
	printf("%s: %lldus\n", name,
	                       (end->tv_sec - start->tv_sec) * 1000000 + 
	                       (end->tv_usec - start->tv_usec));
}

int
main(int argc, char* argv[])
{
	int dev_random;
	int i;
	int n;
	uint64_t number;
	uint64_t key;
	m_array bubble;
	m_array native;
	m_array unsorted;
	size_t idx1;
	size_t idx2;
	struct timeval tv_start;
	struct timeval tv_end;

	if (argc != 2) {
		fprintf(stderr, "ERROR: expected one argument.\n");
		return EXIT_FAILURE;
	}

	n = atoi(argv[1]);
	dev_random = open("/dev/random", O_RDONLY);
	m_array_init(&bubble, (size_t)n, 8);
	m_array_init(&native, (size_t)n, 8);
	m_array_init(&unsorted, (size_t)n, 8);

	for (i = 0; i < n; i++) {
		read(dev_random, &number, 8);
		m_array_append(&bubble, 1, &number);
		m_array_append(&native, 1, &number);
		m_array_append(&unsorted, 1, &number);
	}
	close(dev_random);

	gettimeofday(&tv_start, NULL);
	bubble_sort(&bubble);
	gettimeofday(&tv_end, NULL);
	print_elapsed_time("bubble sort", &tv_start, &tv_end);

	gettimeofday(&tv_start, NULL);
	m_array_sort(&native, uint64_t_cmp);
	gettimeofday(&tv_end, NULL);
	print_elapsed_time("native m_array sort", &tv_start, &tv_end);

	key = 0x123;	

	gettimeofday(&tv_start, NULL);
	m_array_search(&bubble, &key, uint64_t_cmp, M_ARRAY_SORTED, &idx1);
	gettimeofday(&tv_end, NULL);
	print_elapsed_time("binary search", &tv_start, &tv_end);

	gettimeofday(&tv_start, NULL);
	m_array_search(&unsorted, &key, uint64_t_cmp, M_ARRAY_NOT_SORTED, &idx2);
	gettimeofday(&tv_end, NULL);
	print_elapsed_time("linear search", &tv_start, &tv_end);

	return EXIT_SUCCESS;
}

