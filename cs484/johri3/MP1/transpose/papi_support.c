#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include "papi_support.h"

double start_time;

#if NOPAPI
void papi_init() { }
void papi_hw_details() {}
void papi_prepare_ins_fop_counters() { }
void papi_prepare_l1_counters() { }
void papi_prepare_l2_counters() { }
void papi_prepare_l3_counters() { }
#else

int eventset = PAPI_NULL;

int ins_counter_active = 0;


/* Initializes PAPI system. */
void papi_init()
{
  /* Init the PAPI library. */
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	if(retval != PAPI_VER_CURRENT)
    handle_error("PAPI library init error.", retval);

  /* Initialize the eventset. */
  check_error(PAPI_create_eventset(&eventset),
    "PAPI eventset initialization error");

  printf("Intializing PAPI.\n");
}

void papi_hw_details()
{

const PAPI_hw_info_t *hwinfo = NULL;
hwinfo = PAPI_get_hardware_info();
 
printf("ncpus = %d, nnodes = %d, total cpus = %d\n",hwinfo->ncpu,hwinfo->nnodes,hwinfo->totalcpus); 

printf("L1 details : size = %d\n",(hwinfo->mem_hierarchy).level[0].cache[0].size);

printf("L2 details : levels = %d, size = %d, line_size = %d, num_lines = %d, associativity = %d\n",(hwinfo->mem_hierarchy).levels,(hwinfo->mem_hierarchy).level[1].cache[0].size, (hwinfo->mem_hierarchy).level[1].cache[0].line_size, (hwinfo->mem_hierarchy).level[1].cache[0].num_lines,(hwinfo->mem_hierarchy).level[1].cache[0].associativity);

printf("L3 details : size = %d\n",(hwinfo->mem_hierarchy).level[2].cache[0].size);


}

/* Following are functions to initialize the various counters. */

void papi_prepare_ins_fop_counters()
{
  // So we know what to print.
  ins_counter_active = 1;

  int event_codes[] = {PAPI_TOT_INS, PAPI_FP_OPS};
  check_error(PAPI_add_events(eventset, event_codes, 2),
      "PAPI add total instructions and fops events error");

  printf("Prepared instruction and fops counters.\n");
}

void papi_prepare_l1_counters()
{
  int event_codes[] = {PAPI_L1_DCM, PAPI_LST_INS};

  check_error(PAPI_add_events(eventset, event_codes, 2),
      "PAPI add L1 events error.");

  printf("Prepared L1 counters.\n");
}

void papi_prepare_l2_counters()
{
  int event_codes[] = {PAPI_L2_DCM, PAPI_L2_DCA};
  check_error(PAPI_add_events(eventset, event_codes, 2),
      "PAPI add L2 events error.");

  printf("Prepared L2 counters.\n");
}

#endif

/* Starts the counters. */
void papi_start()
{

#ifndef NOPAPI
  printf("Starting PAPI counters.\n");

  check_error(PAPI_start(eventset),
      "PAPI start counters error.");
#endif
}

/* Stops the counters and prints the results. */
void papi_stop_and_report(long long values[2])
{
  /* Will hold counter values. */

  /* Place counter values into the above values arrays. */
  check_error(PAPI_stop(eventset, values),
      "PAPI stop counters error.\n");
  /* Print stats. */

  /* Reset the counters. */
  printf("Resetting PAPI.\n");
  check_error(PAPI_reset(eventset),
      "Resetting counters failed.");
}

