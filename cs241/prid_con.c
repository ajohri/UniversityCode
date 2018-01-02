#include <stdio.h>

#define MAX 256
int buffer[MAX];

int fill =0;
int use = 0;

sem_t	empty;			// seeing if we can add data
sem_t	full;			// seeing if we can get data
sem_t	mutex;			// Going to act as a mutex whenever we want to put or get.

void put(int val) 
{
	buffer[fill] = val;
	fill++;
}

int get(int val) 
{
	int tmp;

	tmp = buffer[val];
	use++;
	return tmp;
}

// Adding to the buffer
void *producer()
{
	int i;

	for(i=0; i< MAX; i++) {
		sem_wait(&empty);						// Decrements the value until it's zero after zero then it will unlock the thread
		sem_wait(&mutex);						// Same thing as a pthread_lock
		put(i);									// Critical Section
		sem_post(&mutex);						// Same thing as a pthread_unlock
		sem_post(&full);
	}
}

// Revoming from the buffer
void *consumer()
{
	int i,tmp;

	for(i=0;i<MAX;i++)	{
		sem_wait(&full);
		sem_wait(&mutex);						// Same thing as a pthread_lock
		tmp = get(i);							// Critical Section
		sem_post(&mutex);						// Same thing as a pthread_unlock
		sem_post(&empty);

		print("%d\n",tmp);
	}
}

main(int argc, char **argv)
{
	int	no_prod;
	int	no_cons;
	int	i,j;

	no_prod = atoi(*argv[1]);
	no_cons = atoi(*argv[2]);
	
	sem_init(&empty, 0 , MAX);					// MAX # of entries can go in the buffer
	
	sem_init(&full,0, 0);						// Condition for allowing the consumer thread
	
	sem_init(&mutex, 0, 1);						// Mutex to protect the array used for buffer

	for(i=0;i<no_prod;i++)
		pthread_create(&pid, NULL, producer, NULL);

	for(i=0;i<no_cons;i++)
		pthread_create(&pid, NULL, consumer, NULL);


	// Add code for thread join
}