//2016024957
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include "cachelab.h"


//
// Virtual cache type structures
//
typedef struct {
  bool valid;
  int tag;
  int time; // check LRU
} line_t;

typedef struct {
  line_t *lines;
} set_t;

typedef struct {
  set_t *sets;
  size_t num_of_set;  
  size_t num_of_line; 
} cache_t;


cache_t cache = {};
void csim(int address);
int set_bits = 0,block_bits = 0; 
size_t hit = 0;
size_t miss = 0;
size_t eviction = 0;

int main(int argc, char *argv[]) {
 
  FILE *file = 0;
  for (int opt; (opt = getopt(argc, argv, "s:E:b:t:")) != -1;) {
    switch (opt) {
      case 's':
        set_bits = atoi(optarg); 
        cache.num_of_set= 2 << set_bits; //since its 2^bit
        break;
      case 'E':
        cache.num_of_line= atoi(optarg); 
        break;
      case 'b':
        block_bits = atoi(optarg); 
        break;
      case 't': 
        if (!(file = fopen(optarg, "r"))) { return 1; }
        break;
      default:
       printf("wrong input type\n");
        return 1;
    }
  }


  cache.sets = malloc(sizeof(set_t) * cache.num_of_set); //cache->set->line
  for (int i = 0; i < cache.num_of_set; ++i) {
    cache.sets[i].lines = calloc(sizeof(line_t), cache.num_of_line);
  }


  //
  // Parse trace input
  //
  char command;
  int address;
  // Parse only kind and access address, ignore access size,
  while (fscanf(file, " %c %x%*c%*d", &command, &address) != EOF) {
    // Ignore instruction load
    if (command == 'I')
    	continue;

    csim(address);
    
    if (command =='M') { csim(address); }
  }
  printSummary(hit, miss, eviction);


//malloc -> free
  fclose(file);
  for (size_t i = 0; i < cache.num_of_set; ++i) { free(cache.sets[i].lines); }
  free(cache.sets);
  return 0;
}


void update(set_t *set, size_t line_no);
void csim(int addr) {

  size_t set_index = (0x7fffffff >> (31 - set_bits)) & (addr >> block_bits);
  int tag = 0xffffffff & (addr >> (set_bits + block_bits));

  // Select a set
  set_t *set = &cache.sets[set_index];

  // Look up for cache hit
  for (size_t i = 0; i < cache.num_of_line; ++i) {
    line_t* line = &set->lines[i];


    if (!line->valid) { continue; }

    if (line->tag != tag) { continue; }

    // valid and tag == hit
    ++hit;
    update(set, i);
    return;
  }

  ++miss;

  for (size_t i = 0; i < cache.num_of_line; ++i) {
    line_t* line = &set->lines[i];

    if (line->valid)
    	continue; 

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }

  // all line full
  ++eviction;


  for (size_t i = 0; i < cache.num_of_line; ++i) {
    line_t* line = &set->lines[i];

    if (line->time) { continue; }

    line->valid = true;
    line->tag = tag;
    update(set, i);
    return;
  }
}


void update(set_t *set, size_t line_no) {
  line_t *line = &set->lines[line_no];

  for (size_t i = 0; i < cache.num_of_line; ++i) {
    line_t *now = &set->lines[i];
    if (!now->valid)
    	continue;
    if (now->time <= line->time)
    	continue;

    --now->time;
  }

  line->time = cache.num_of_line- 1;
}
