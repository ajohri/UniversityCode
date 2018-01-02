.text

## struct Puzzle {
##     int size;
##     Cell *grid;
## };
##
## struct Solution {
##     int size;
##     int assignment[81];
## };
##
## // Checks if the solution is complete.
## int
## is_complete(const Solution *solution, const Puzzle *puzzle) {
##     return solution->size == puzzle->size * puzzle->size;
## }

.globl is_complete
is_complete:
	# Your code goes here :)
	#0($a0)
	#0($a1)
	#0($a0) == 0($a1) * 0($a1)
	lw	$t0,	0($a0)								#solution -> size

	lw	$t1,	0($a1)								#puzzle -> size

	mul	$t2,	$t1,	$t1							#puzzle->size * puzzle->size
	beq	$t0,	$t2,	true_state			#solution->size == puzzle->size * puzzle->size
	li 	$v0,	0											#this is the false state
	jr	$ra													#return from here
true_state:
	li	$v0,	1											#this is the true state
	jr  $ra													#returen from here
