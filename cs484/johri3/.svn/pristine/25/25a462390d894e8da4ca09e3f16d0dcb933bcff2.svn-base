#include <algorithm>
#include <cstring>
#include <iostream>
#include <cassert>
#include <chrono>
#include <random>
#include <climits>

typedef int key;

const key maxkey = INT_MAX; //+infinity, any key which is greater than all possible input keys


int bucket_margin = 5; //bucket_size = N/p(1 + margin%) in the scanning algorithm (findSplitters)


/*
 * @Inputs
 *
 *  histCounts: histogram counts obtained after reduction
 *  probes: probe keys for the histogram (assumed to be sorted), last probe should be maxkey
 *          Specifically, histCounts[i] should contain number of keys (across all processors) that lie in [probes[i-1], probes[i])         
 *          histCounts[0] = Number of keys < probes[0] 
 *  probeSize: number of probe keys. Size of both histCounts and probes is probeSize
 *  
 *  nBuckets: number of buckets. In the usual case, number of buckets = number of processors 
 *
 * @Output
 *
 *  Splitters:  Will store splitter keys. The size of the array should be nBuckets
 *              The last splitter will always be maxkey. 
 *  bucketCounts:  Will store bucket counts for each bucket. Size of bucketCounts should also be nBuckets
 *              It is assumed that memory has been allocated to splitters and bucketCounts
*/
void findSplitters(uint64_t *histCounts, key *probes, int probeSize,
               int nBuckets, 
               key *splitters, uint64_t *bucketCounts){

    //Total number of keys across all processors
    uint64_t nElements = 0;
    for(int i=0; i<probeSize; i++){
      nElements += histCounts[i];
    }

    //std::cout<<"Total Elements: "<<nElements<<std::endl;

    //Finalize last splitter
    splitters[nBuckets-1] = maxkey;

    uint64_t max_bucket_size = (nElements)/nBuckets;
    uint64_t margin = (nElements * bucket_margin)/(100 * nBuckets); //epsilon %
    max_bucket_size += margin;

    //std::cout<<"max_bucket_size: "<<max_bucket_size<<std::endl;
    
    //Scanning algorithm
    //Scan from left to right and assign buckets if bucket size doesn't exceed max_bucket_size
    uint64_t curr_bucket_size = 0;
    uint64_t cum_bucket_size = 0; //running cumulative bucket size
    int currprobe = 0;
    for(int i=0; i<nBuckets-1; i++){
        
        while(  currprobe < probeSize-1 && 
                (curr_bucket_size + histCounts[currprobe] < max_bucket_size)
             )  
        {       
                //std::cout<<curr_bucket_size<<" "<<histCounts[currprobe]<<std::endl;
                curr_bucket_size += histCounts[currprobe];
                currprobe++;
        }
        cum_bucket_size += curr_bucket_size;
        //Finalize ith splitter
        splitters[i] = probes[currprobe];
        bucketCounts[i] = curr_bucket_size;
        curr_bucket_size = 0;
    }

    //All that's left goes in the last bucket
    bucketCounts[nBuckets-1] = nElements - cum_bucket_size;
}







