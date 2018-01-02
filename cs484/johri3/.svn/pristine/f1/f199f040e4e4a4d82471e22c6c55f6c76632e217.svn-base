#ifndef _PAPI_SUPPORT_H_
#define _PAPI_SUPPORT_H_

#ifndef NOPAPI
#include <papi.h>
#endif
#include "papi_helpers.h"

void papi_init();

void papi_hw_details();
void papi_prepare_ins_fop_counters();
void papi_prepare_l1_counters();
void papi_prepare_l2_counters();
void papi_prepare_l3_counters();

void papi_start();
void papi_stop_and_report(long long v[2]);

#endif

