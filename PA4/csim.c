#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "cachelab.h"

typedef int bool;
#define true 1
#define false 0

typedef struct
{
	int s;				  //set bitnum
	int E;				  //E lines per set
	int b;				  //data bitnum
	unsigned long long S; //2**s
	unsigned long long B; //2**b
	unsigned int hit;
	unsigned int miss;
	unsigned int evict;
} param;

typedef struct
{
	bool valid;
	unsigned int tag;
	unsigned long long data;
} line;

typedef struct
{
	line *lines;
} set;

typedef struct
{
	set *sets;
} cache;

cache newCache;
param meta;

void construct()
{
	int i;
	set newSet;

	newCache.sets = (set *)calloc(sizeof(set), meta.S);

	for (i = 0; i < meta.S; i++)
	{
		newSet.lines = (line *)calloc(sizeof(line), meta.E);
		newCache.sets[i] = newSet;
	}

	meta.hit = meta.miss = meta.evict = 0;

	return;
}

void destroy()
{
	int i;
	for (i = 0; i < meta.S; i++)
	{
		set delSet = newCache.sets[i];
		free(delSet.lines);
	}
	free(newCache.sets);
}

void run_c(unsigned long long addr){
	//	taglen = 64-par.s-par.b
	//	idxlen = par.s
	unsigned long long index = (addr<<(64-meta.s-meta.b))>>(64-meta.s);
	unsigned long long tag = addr>>(meta.s+meta.b);
	int empty_loc = -1;
	//find

	for(int i=0;i<meta.E;i++){
		if((!newCache.sets[index].lines[i].valid) && (empty_loc == -1)) empty_loc = i;
		if((newCache.sets[index].lines[i].tag == tag) && newCache.sets[index].lines[i].valid){
			line temp = newCache.sets[index].lines[i];
			int j;
			for(j=i;(j<meta.E-1) && (newCache.sets[index].lines[j+1].valid);j++){
				newCache.sets[index].lines[j] = newCache.sets[index].lines[j+1];
			}
			newCache.sets[index].lines[j] = temp;
			meta.hit++;
			return;
		}
	}
	
	//miss
	if(empty_loc != -1){
		newCache.sets[index].lines[empty_loc].tag = tag;
		newCache.sets[index].lines[empty_loc].valid = true;
		meta.miss++;
		return;
	}
	//evict
	else{
		int j;
		for(j=0;(j<meta.E-1);j++){
			newCache.sets[index].lines[j] = newCache.sets[index].lines[j+1];
		}
		newCache.sets[index].lines[j].tag = tag;
		newCache.sets[index].lines[j].valid = true;
		meta.miss++;
		meta.evict++;
		return;
	}
}


int main(int args, char **argv)
{

	meta.hit = meta.miss = meta.evict = 0;

	FILE *trace;
	int opt;
	
	while((opt = getopt(args, argv, "s:E:b:t:")) != -1){
		switch (opt) {
			case 's':
				meta.s = atoi(optarg);
				meta.S = 2<<meta.s;
				break;
			case 'E':
				meta.E = atoi(optarg);
				break;
			case 'b':
				meta.b = atoi(optarg);
				meta.B = 2<<meta.b;
				break;
			case 't': 
				trace = fopen(optarg, "r");
				break;
			default:
				break;
		}
	}
	
	construct();
	char op;
	unsigned long long addr;
	int size;

	while (fscanf(trace, " %c %llx,%d", &op, &addr, &size) != EOF) {
    	switch (op) {
			case 'I':
				break;
			case 'M':
				run_c(addr);
				run_c(addr);
				break;
			case 'L':
				run_c(addr);
				break;
			case 'S':
				run_c(addr);
				break;
		}
  	}

	destroy();
	fclose(trace);
	printSummary(meta.hit, meta.miss, meta.evict);
	return 0;
}