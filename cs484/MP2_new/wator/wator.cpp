/*
 * WaTor Simulation
 */

// #define ASCII_ART                //Whether to print ascii art of a part of the simulation

#include <algorithm>             //std::copy
#ifdef ASCII_ART
  #include <string>              //std::string, printf()
#else
  #include <stdio.h>             //printf()
#endif

const int  FISHTIME   = 2;       //Time for fish to reproduce
const int  SHARKTIME  = 2;       //Time for shark to reproduce
const int  EGAIN      = 2;       //Shark energy gain for eating fish

const int  WW         = 512;     //Width of world
const int  WH         = 512;     //Height of world
const int  FISHFRAC   = 30;      //Fraction of starting cells that are fish
const int  SHARKFRAC  = 100;     //Fraction of starting cells that are sharks
const int  CHRONONS   = 10000;   //Maximum number of chronons to iterate through

const bool DENSE      = true;    //Whether fish are densely seeded
const int  IPF        = 1;       //Iterations per draw cycle (if using ASCII art)

const int  SEED       = 1234567; //Random number seed

#define IS_FISH(x)  (x <  0)     //Check if a value is a fish
#define IS_SHARK(x) (x >  0)     //Check if a value is a shark
#define IS_WATER(x) (x == 0)     //Check if a value is water

//Pseudo-pseudo random number generator
static inline int fakerand(int i, int j, int t) {
  return t*i + t*j + t*i*j - t % (i+j+1);
}

static inline void init_arrays(int ***vals, int*** newvals) {
  //Allocate arrays for current / future grid values
  *vals    = (int **)malloc(WH*sizeof(int*));
  *newvals = (int **)malloc(WH*sizeof(int*));
  (*vals)[0]       = (int *)malloc(WW*WH*sizeof(int));
  (*newvals)[0]    = (int *)malloc(WW*WH*sizeof(int));
  for(int i = 0; i < WH; i++) {
    (*vals)[i]    = (*(*vals)    + WW * i);
    (*newvals)[i] = (*(*newvals) + WW * i);
  }

  //Initialize ecosystem
  srand(SEED);
  for(int i = 0; i < WH; ++i) {
    for(int j = 0; j < WW; ++j) {
      if ( (DENSE && (i < WH/2 || j < WW/2)) || ((not DENSE) && fakerand(i,j,SEED)%FISHFRAC == 0))
        (*vals)[i][j] = -1; // fish
      else if (fakerand(i,j,SEED)%SHARKFRAC == 0)
        (*vals)[i][j] = EGAIN; // shark
      else
        (*vals)[i][j] = 0;
      (*newvals)[i][j] = (*vals)[i][j];
    }
  }
}

static inline void free_arrays(int ***vals, int*** newvals) {
  free(*vals); free(*newvals);
}

static inline void print_status(int** vals, int frame) {
  int tsharks = 0, tfish = 0;
  #ifdef ASCII_ART
    std::string s;
    for (int i = 0; i < WH; ++i) {
      for (int j = 0; j < WW; ++j) {
        if(vals[i][j] > 0) {//sharks
          ++tsharks;
          if (i < 20 && j < 60)
            s.append("\033[1;31ms");
        }
        else if(vals[i][j] < 0) {//fish
          ++tfish;
          if (i < 20 && j < 60)
            s.append("\033[1;32mf");
        }
        else {
          if (i < 20 && j < 60) {
            s.append("\033[1;34mw");
          }
        }
        if (i < 20 && j == 59)
          s.append("\n\033[0m");
      }
    }
    s.append("\n");
    printf(s.c_str());
  #else
    for (int i = 0; i < WH; ++i) {
      for (int j = 0; j < WW; ++j) {
        if(vals[i][j] > 0)      ++tsharks;
        else if(vals[i][j] < 0) ++tfish;
      }
    }
  #endif
  printf("chronon %i: %i sharks, %i fish\n",frame*IPF,tsharks,tfish);
}

static inline void update_sharks(int** vals, int** newvals, int chronon) {
  //Calculate shark movements
  for (int i = 0; i < WH; ++i) {
    for (int j = 0; j < WW; ++j) {
      if (IS_SHARK(vals[i][j])) {
        int iminus = (i == 0)    ? WH - 1 : i-1;
        int iplus  = (i == WH-1) ? 0      : i+1;
        int jminus = (j == 0)    ? WW - 1 : j-1;
        int jplus  = (j == WW-1) ? 0      : j+1;

        //Count fish cells
        int nfish = 0;
        if (IS_FISH(vals[iminus][j])) ++nfish;
        if (IS_FISH(vals[iplus][j]))  ++nfish;
        if (IS_FISH(vals[i][jminus])) ++nfish;
        if (IS_FISH(vals[i][jplus]))  ++nfish;

        if (nfish > 0) {  //Nearby food
          int rn = fakerand(i,j,chronon)%nfish;
          if (vals[iminus][j] < 0 && (rn % (nfish--)==0))
            newvals[iminus][j] = vals[i][j]+EGAIN-1;
          else if (vals[iplus][j] < 0 && (rn % (nfish--)==0))
            newvals[iplus][j] = vals[i][j]+EGAIN-1;
          else if (vals[i][jminus] < 0 && (rn % (nfish--)==0))
            newvals[i][jminus] = vals[i][j]+EGAIN-1;
          else if (vals[i][jplus] < 0 && (rn % (nfish--)==0))
            newvals[i][jplus] = vals[i][j]+EGAIN-1;

        } else if (vals[i][j] == 1) { //Starving
          newvals[i][j] = 0;
          continue;
        } else { //Searching
          //Count empty cells
          int nempty=0;
          if (IS_WATER(vals[iminus][j])) ++nempty;
          if (IS_WATER(vals[iplus][j]))  ++nempty;
          if (IS_WATER(vals[i][jminus])) ++nempty;
          if (IS_WATER(vals[i][jplus]))  ++nempty;

          if (nempty == 0)
            continue;

          int rn = fakerand(i,j,chronon)%nempty;
          if (IS_WATER(vals[iminus][j]) && (rn%(nempty--)==0))
            newvals[iminus][j] = vals[i][j]-1;
          else if (IS_WATER(vals[iplus][j]) && (rn%(nempty--)==0))
            newvals[iplus][j] = vals[i][j]-1;
          else if (IS_WATER(vals[i][jminus]) && (rn%(nempty--)==0))
            newvals[i][jminus] = vals[i][j]-1;
          else if (IS_WATER(vals[i][jplus]) && (rn%(nempty--)==0))
            newvals[i][jplus] = vals[i][j]-1;
        }
        if ( chronon%SHARKTIME == 0 ) newvals[i][j] = EGAIN; // Shark reproduced
        else                          newvals[i][j] = 0;     // Shark moved away
      }
    }
  }
}

static inline void update_fish(int** vals, int** newvals, int chronon) {
  //Calculate fish movements
  for (int i = 0; i < WH; ++i) {
    for (int j = 0; j < WW; ++j) {
      if (IS_FISH(vals[i][j])) {
        int iminus = (i == 0)    ? WH - 1 : i-1;
        int iplus  = (i == WH-1) ? 0      : i+1;
        int jminus = (j == 0)    ? WW - 1 : j-1;
        int jplus  = (j == WW-1) ? 0      : j+1;

        //Count empty cells
        int nempty = 0;
        if (IS_WATER(vals[iminus][j])) ++nempty;
        if (IS_WATER(vals[iplus][j]))  ++nempty;
        if (IS_WATER(vals[i][jminus])) ++nempty;
        if (IS_WATER(vals[i][jplus]))  ++nempty;
        if (nempty == 0) continue;

        // Find somewhere to move
        int* newaddr = nullptr;
        int rn = fakerand(i,j,chronon)%nempty;
        if (IS_WATER(vals[iminus][j]) && (rn % (nempty--)==0))
          newaddr = &(newvals[iminus][j]);
        else if (IS_WATER(vals[iplus][j]) && (rn % (nempty--)==0))
          newaddr = &(newvals[iplus][j]);
        else if (IS_WATER(vals[i][jminus]) && (rn % (nempty--)==0))
          newaddr = &(newvals[i][jminus]);
        else if (IS_WATER(vals[i][jplus]) && (rn % (nempty--)==0))
          newaddr = &(newvals[i][jplus]);

        // Move
        *(newaddr) = vals[i][j];
        if ( chronon%FISHTIME == 0 ) {  //Fish can repopulate
          *(newaddr) = -1;
          newvals[i][j] = -1;
        } else {
          newvals[i][j] = 0; //Fish moved away
        }

      }
    }
  }
}

//UPDATE THIS METHOD
static inline void update_sharks_in_parallel(int** vals, int** newvals, int chronon) {
  /*
    Write function for updating sharks in parallel using MPI
  */
}

//UPDATE THIS METHOD
static inline void update_fish_in_parallel(int** vals, int** newvals, int chronon) {
  /*
    Write function for updating fish in parallel using MPI
  */
}

void wator() {
  //Initialize arrays for holding world status
  int **vals, **newvals; init_arrays(&vals,&newvals);

  //Simulate
  for (int frame = 0; frame < CHRONONS; ++frame) {
    for (int chronon = frame*IPF; chronon < (frame+1)*IPF; ++chronon) {
      //Update shark positions
      update_sharks(vals,newvals,chronon);
      std::copy(&newvals[0][0], &newvals[0][0]+WH*WW,&vals[0][0]);
      //Update fish positions
      update_fish(vals,newvals,chronon);
      std::copy(&newvals[0][0], &newvals[0][0]+WH*WW,&vals[0][0]);
    }
    print_status(vals,frame); //Draw and output to terminal
  }

  free_arrays(&vals,&newvals);
}

void wator_parallel() {
  //Initialize arrays for holding world status
  int **vals, **newvals; init_arrays(&vals,&newvals);

  //Simulate
  for (int frame = 0; frame < CHRONONS; ++frame) {
    for (int chronon = frame*IPF; chronon < (frame+1)*IPF; ++chronon) {
      //Update shark positions
      update_sharks_in_parallel(vals,newvals,chronon); //UPDATE THIS METHOD
      std::copy(&newvals[0][0], &newvals[0][0]+WH*WW,&vals[0][0]);
      //Update fish positions
      update_fish_in_parallel(vals,newvals,chronon); //UPDATE THIS METHOD
      std::copy(&newvals[0][0], &newvals[0][0]+WH*WW,&vals[0][0]);
    }
    print_status(vals,frame); //Draw and output to terminal
  }

  free_arrays(&vals,&newvals);
}

int main(int argc, char* argv[]) {
  wator();          //Sequential reference method
  // wator_parallel(); //Parallel method using MPI
}
