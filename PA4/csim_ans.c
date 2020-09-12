#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <math.h>

#include "cachelab.h"

/* Always use a 64-bit variable to hold memory addresses*/
typedef unsigned long long int mem_addr_t;

/* a struct that groups cache parameters together */
typedef struct
{
	int s; /* 2**s cache sets */
	int b; /* cacheline block size 2**b bytes */
	int E; /* number of cachelines per set */
	int S; /* number of sets, derived from S = 2**s */
	int B; /* cacheline block size (bytes), derived from B = 2**b */

	int hits;
	int misses;
	int evicts;
} cache_param_t;

typedef struct
{
	int last_used;
	int valid;
	mem_addr_t tag;
	char *block;
} set_line;

typedef struct
{
	set_line *lines;
} cache_set;

typedef struct
{
	cache_set *sets;
} cache;

int verbosity;

long long bit_pow(int exp)
{
	long long result = 1;
	result = result << exp;
	return result;
}

cache build_cache(long long num_sets, int num_lines, long long block_size)
{

	cache newCache;
	cache_set set;
	set_line line;
	int setIndex;
	int lineIndex;

	newCache.sets = (cache_set *)malloc(sizeof(cache_set) * num_sets);

	for (setIndex = 0; setIndex < num_sets; setIndex++)
	{

		set.lines = (set_line *)malloc(sizeof(set_line) * num_lines);
		newCache.sets[setIndex] = set;

		for (lineIndex = 0; lineIndex < num_lines; lineIndex++)
		{

			line.last_used = 0;
			line.valid = 0;
			line.tag = 0;
			set.lines[lineIndex] = line;
		}
	}

	return newCache;
}

void clear_cache(cache sim_cache, long long num_sets, int num_lines, long long block_size)
{
	int setIndex;

	for (setIndex = 0; setIndex < num_sets; setIndex++)
	{
		cache_set set = sim_cache.sets[setIndex];

		if (set.lines != NULL)
		{
			free(set.lines);
		}
	}
	if (sim_cache.sets != NULL)
	{
		free(sim_cache.sets);
	}
}

int find_empty_line(cache_set query_set, cache_param_t par)
{
	int num_lines = par.E;
	int index;
	set_line line;

	for (index = 0; index < num_lines; index++)
	{
		line = query_set.lines[index];
		if (line.valid == 0)
		{
			return index;
		}
	}
	//Control flow should not fall here. Method is only called if cache_full flag is set to false.
	return -1;
}

int find_evict_line(cache_set query_set, cache_param_t par, int *used_lines)
{

	//Returns index of least recently used line.
	//used_lines[0] gives least recently used line, used_lines[1] gives current lru counter or most recently used line.
	int num_lines = par.E;
	int max_used = query_set.lines[0].last_used;
	int min_used = query_set.lines[0].last_used;
	int min_used_index = 0;

	set_line line;
	int lineIndex;

	for (lineIndex = 1; lineIndex < num_lines; lineIndex++)
	{
		line = query_set.lines[lineIndex];

		if (min_used > line.last_used)
		{
			min_used_index = lineIndex;
			min_used = line.last_used;
		}

		if (max_used < line.last_used)
		{
			max_used = line.last_used;
		}
	}

	used_lines[0] = min_used;
	used_lines[1] = max_used;
	return min_used_index;
}

cache_param_t run_sim(cache sim_cache, cache_param_t par, mem_addr_t address)
{

	int lineIndex;
	int cache_full = 1;

	int num_lines = par.E;
	int prev_hits = par.hits;

	int tag_size = (64 - (par.s + par.b));
	mem_addr_t input_tag = address >> (par.s + par.b);
	unsigned long long temp = address << (tag_size);
	unsigned long long setIndex = temp >> (tag_size + par.b);

	cache_set query_set = sim_cache.sets[setIndex];

	for (lineIndex = 0; lineIndex < num_lines; lineIndex++)
	{

		set_line line = query_set.lines[lineIndex];

		if (line.valid)
		{

			if (line.tag == input_tag)
			{

				line.last_used++;
				par.hits++;
				query_set.lines[lineIndex] = line;
			}
		}
		else if (!(line.valid) && (cache_full))
		{
			//We found an empty line
			cache_full = 0;
		}
	}

	if (prev_hits == par.hits)
	{
		//Miss in cache;
		par.misses++;
	}
	else
	{
		//Data is in cache
		return par;
	}

	//We missed, so evict if necessary and write data into cache.

	int *used_lines = (int *)malloc(sizeof(int) * 2);
	int min_used_index = find_evict_line(query_set, par, used_lines);

	if (cache_full)
	{
		par.evicts++;

		//Found least-recently-used line, overwrite it.
		query_set.lines[min_used_index].tag = input_tag;
		query_set.lines[min_used_index].last_used = used_lines[1] + 1;
	}

	else
	{
		int empty_index = find_empty_line(query_set, par);

		//Found first empty line, write to it.
		query_set.lines[empty_index].tag = input_tag;
		query_set.lines[empty_index].valid = 1;
		query_set.lines[empty_index].last_used = used_lines[1] + 1;
	}

	free(used_lines);
	return par;
}

int main(int argc, char **argv)
{

	cache sim_cache;
	cache_param_t par;
	bzero(&par, sizeof(par));

	long long num_sets;
	long long block_size;

	FILE *read_trace;
	char trace_cmd;
	mem_addr_t address;
	int size;

	char *trace_file;
	char c;
	while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
	{
		switch (c)
		{
		case 's':
			par.s = atoi(optarg);
			break;
		case 'E':
			par.E = atoi(optarg);
			break;
		case 'b':
			par.b = atoi(optarg);
			break;
		case 't':
			trace_file = optarg;
			break;
		case 'v':
			verbosity = 1;
			break;
		default:
			return 1;
		}
	}

	// you need to compute S and B yourself
	num_sets = pow(2.0, par.s);
	block_size = bit_pow(par.b);
	par.hits = 0;
	par.misses = 0;
	par.evicts = 0;

	sim_cache = build_cache(num_sets, par.E, block_size);

	// fill in rest of the simulator routine
	read_trace = fopen(trace_file, "r");

	if (read_trace != NULL)
	{
		while (fscanf(read_trace, " %c %llx,%d", &trace_cmd, &address, &size) == 3)
		{

			switch (trace_cmd)
			{
			case 'I':
				break;
			case 'L':
				par = run_sim(sim_cache, par, address);
				break;
			case 'S':
				par = run_sim(sim_cache, par, address);
				break;
			case 'M':
				par = run_sim(sim_cache, par, address);
				par = run_sim(sim_cache, par, address);
				break;
			default:
				break;
			}
		}
	}

	printSummary(par.hits, par.misses, par.evicts);
	clear_cache(sim_cache, num_sets, par.E, block_size);
	fclose(read_trace);

	return 0;
}
