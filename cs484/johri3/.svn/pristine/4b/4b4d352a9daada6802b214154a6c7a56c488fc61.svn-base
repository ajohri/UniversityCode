#include "sort.h"
#include <algorithm>
#include <mpi.h>
#include <chrono>
#include <random>
#include <climits>
#include <cstdlib>
#include <time.h>

int local_checksum(int *data, int n){
	int keysum = 0;
	for(int i = 0; i < n; i++)
		keysum += (int)(data[i] % 1009);
	return keysum;
}

int fhi(int * data, int val, int start, int stop)		// A simple binary search to find the number of elements smaller that it
{
    if(start == stop){
        return start;
    }
    if(val > data[stop]){
        return stop+1;
    }

    int mid = (stop + start) / 2;
	if(data[mid+1] < val){
		return fhi(data, val, mid+1, stop);
	}
    else if(data[mid] >= val ){
		return fhi(data, val, start, mid);
	}
    else{
        return mid+1;
    }
}




int main(int argc, char **argv)
{

	int num_elements, num_local;
	int num_pes, current_rank;
	int oversampling_ratio = 20;
	int *my_data;

	num_elements = atoi(argv[1]);
	if(argc > 2)
		oversampling_ratio = atoi(argv[2]);

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_pes);
	MPI_Comm_rank(MPI_COMM_WORLD, &current_rank);

	num_local = num_elements/num_pes;
	int rem = num_elements%num_pes;
	if(current_rank < rem) num_local++;
	int root = 0;

	//Step 1: populate and sort my_data
	srand(time(NULL));
	for(int i = 0; i < num_local; i++){
		my_data[i] = rand() % 1000000;			// Populate the array with random numbers
	}
	std::sort(my_data, my_data + num_local);

	//This computing the intial sum
	int local_sum = local_checksum(my_data, num_local);
	int initial_checksum;
	MPI_Reduce(&local_sum, &initial_checksum, 1, MPI_INT,
               MPI_SUM, root, MPI_COMM_WORLD);



	//Step 2: collect samples from my_data
	int num_samples = oversampling_ratio; 												// constant for every processor
	int *samples = new int[num_samples];													// create an array to hold the values of the samples
	for(int i = 0; i < num_samples; i++){
		samples[i] = my_data[0 + i * num_local / num_samples];			// the samples are obtained uniformly in my case
	}

	//Step 3: gather samples at root into the current_probe array
	int *current_probe;																									//Array to hold proves
	int number_of_probes;
	number_of_probes = num_pes * num_samples;
	current_probe = new int[number_of_probes+1];																// Allocating space for the current_probe
	MPI_Gather(samples, num_samples, MPI_INT, current_probe, num_samples, MPI_INT, 0, MPI_COMM_WORLD);	// Gather all the samples into the root node


	//Step 4: sort current_probe at root and broadcast
	if(current_rank == root){
		std::sort(current_probe, current_probe + number_of_probes);
		current_probe[number_of_probes] = INT_MAX; //add maxkey at the end
	}
	number_of_probes++;



  //Step 5: broadcast current_probe to all processors
	MPI_Bcast(current_probe, number_of_probes, MPI_INT, 0, MPI_COMM_WORLD);		// Broadcast the sorted current_probe to all the processors

  //Step 6: Compute local histogram
	uint64_t *historgram_count = new uint64_t[number_of_probes];
	for(int i = 0; i < number_of_probes; i++){
		historgram_count[i] = fhi(my_data, current_probe[i], 0, num_local-1); // create the histogram in which each element states the amound ofvalues smaller that the probe value
	}


	//Step 7: Reduce historgram_count at the root
	uint64_t *reducedCounts; //should store the reduced counts
	MPI_Reduce(historgram_count, reducedCounts, number_of_probes, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD); 		//Sum all the histogram counts into to the


  //Step 8: Select splitters from reduced count at the root, use findSplitters function in utils.cpp
	int *splitters = new int[num_pes];
	uint64_t *bucketCounts = new uint64_t[num_pes];
	if(current_rank == 0){
		findSplitters(reducedCounts, current_probe, number_of_probes, num_pes, splitters, bucketCounts);			// Generate the splitter Nodes
	}

  //Step 9: Broadcast all splitters
	MPI_Bcast(splitters, num_pes, MPI_INT, root, MPI_COMM_WORLD);									//Broadcast the splitters to all the processors

	//Step 10: Figure out how many keys to send to each processor
    int *send_counts = new int[num_pes]; //send counts
    for(int i=0; i<num_pes; i++){
        int sep1 = (i>0? splitters[i-1] : INT_MIN);
        int sep2 = splitters[i];
        int ind1 = std::lower_bound(my_data,
                                my_data + num_local, sep1) - my_data;
        int ind2 = std::lower_bound(my_data,
                                my_data + num_local, sep2) - my_data;
      	send_counts[i] = ind2 - ind1;
    }
  int *local_index = new int[num_pes];	//  Local Index of Elements where the divisions occur
	local_index[0] = 0;						// First Local Index is always 0
	for(int i = 1; i < num_pes; i++){
		local_index[i] = local_index[i-1] + send_counts[i-];	// Computing the Local Index of Elements
	}

  //Step 11: Convey to each processor how much elements we're going to send to that processor.
	int * AIndexes = new int[num_pes * num_pes];
	int * ASendCounts = new int[num_pes * num_pes];
	MPI_Allgather(local_index, num_pes, MPI_INT, AIndexes, num_pes, MPI_INT, MPI_COMM_WORLD);	// Gather all the Indexs into an array and broadcast
	MPI_Allgather(send_counts, num_pes, MPI_INT, ASendCounts, num_pes, MPI_INT, MPI_COMM_WORLD); // Gather all the Sizes of elements to be sent into an array and broadcast


  //Step 12: Send all keys to the right processor
	int finalnum = 0;
	int *final_my_data;
	int * current_part_count = new int[num_pes];	// Array to hold the number of elements to be received by each processor which is used in MPI_Allgatherv
	int * current_index_count = new int[num_pes];	// Array to hold the index of elements in the final_my_data array which divides the data acording to the processors it received it from.
	for(int i = 0; i < num_pes; i++){
		finalnum += ASendCounts[current_rank + i * num_pes];	// Computes the total number of elements to be received
		current_part_count = ASendCounts[current_rank + i * num_pes];
	}
	current_index_count[0] = 0;										// The first value of the array that holds the indexes
	for(int i = 1; i < num_pes; i++){
		current_index_count[i] = current_index_count[i-1] + current_part_count[i-1];	// Compute the current_index_count array
	}
	final_my_data = new int[finalnum];	// Compute the space required for each final_my_data

	int ** send_buf = new int*[num_pes];		// A 2D array to hold all the elemts to be sent to all processors
	for(int i = 0; i < num_pes; i++){
		send_buf[i] = new int[send_counts[i]];	// Each row will hold the number of elemts corresponding to the number of elemts to be sent to the processor of that rank
		for(int j = 0; j < send_counts[i]; j++){
			send_buf[i][j] = my_data[local_index[i] + j];	// Populate Each row with the elements
		}
	}
	for(int i = 0; i < num_pes; i++){
		MPI_Gatherv(send_buf[i], send_counts[i], MPI_INT, final_my_data, current_part_count, current_index_count, MPI_INT, i, MPI_COMM_WORLD);	// Send the elemts to the corresponding processors
	}
	std::sort(final_my_data, final_my_data + finalnum);	//	Sort the elements

  int * final_Count = new int[num_pes];
	int * final_Index = new int[num_pes];
	MPI_Allgather(final_Count, 1, MPI_INT, finalnum, 1, MPI_INT, MPI_COMM_WORLD);	// All processors broadcast the number of elements it holds to all processors
	final_Index[0] = 0;
	for(int j = 1; j < num_pes; j++){
		final_Index[i] = final_Index[i-1] + final_Count[i-1];
	}
	int * The_Final_Array = new int[num_elements];				// Create the final array
	MPI_Gatherv[final_my_data, finalnum, MPI_INT, The_Final_Array, final_Count, final_Index, 0, MPI_COMM_WORLD);

	local_sum = local_checksum(final_my_data, finalnum);
	int final_checksum;
	MPI_Reduce(&local_sum, &final_checksum, 1, MPI_INT,
               MPI_SUM, root, MPI_COMM_WORLD);
	// Final printing
	if(current_rank == root){
		std::cout<<"Sorting Finished. Inital checksum: "<<initial_checksum<<", Final checksum: "<<final_checksum<<std::endl;
	}

	MPI_Finalize();
	return 0;
}
