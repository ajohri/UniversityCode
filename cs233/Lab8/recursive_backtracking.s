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
## int
## recursive_backtracking(Solution *solution, Puzzle *puzzle) {
##     if (is_complete(solution, puzzle)) {
##         return 1;
##     }
##     int position = get_unassigned_position(solution, puzzle);
##     for (int val = 1; val < puzzle->size + 1; val++) {
##         if (puzzle->grid[position].domain & (0x1 << (val - 1))) {

##						 solution->assignment[position] = val;
##             solution->size += 1;
##             // Applies inference to reduce space of possible assignment.
##             Puzzle puzzle_copy;
##             Cell grid_copy[81]; // 81 is the maximum size of the grid.
##             puzzle_copy.grid = grid_copy;
##             clone(puzzle, &puzzle_copy);
##             puzzle_copy.grid[position].domain = 0x1 << (val - 1);
##             if (forward_checking(position, &puzzle_copy)) {
##                 if (recursive_backtracking(solution, &puzzle_copy)) {
##                     return 1;
##                 }
##             }
##             solution->assignment[position] = 0;
##             solution->size -= 1;
##         }
##     }
##     return 0;
## }

.globl recursive_backtracking
recursive_backtracking:
	# Your code goes here :)
	jal is_complete													#is_complete(solution, puzzle)
	bne $v0,	0,	if_skip										#if(is_complete(solution, puzzle))
  li 	$v0,	1															#return 1 if it is equal otherwise move forware with the program
	jr	$ra																	#return

if_skip:
	jal get_unassigned_position							#get_unassigned_position(solution, puzzle)
	move $t0,	$v0														#position = get_unassigned_position(solution, puzzle)
	li 	$t1,	1															#val counter
	lw 	$t2,	0($a1)												#puzzle->size
	add $t2,	$t2,	1												#puzzle->size + 1
	mul $t4,	$t0,	8												#position * 8
	lw 	$t3,	4($a1)												#puzzle->grid
	add $t3,	$t3,	$t4											#puzzle->grid[position]
	lw 	$t3,	0($t3)												#puzzle->grid[position].domain
loop:
	bge $t1,	$t2,	end_of_for_loop					#for val < puzzle->size + 1
	sub $t5,	$t1,	1												#(val - 1)
	li 	$t6,	1															#temp variable for 1
	sll $t5,	$t6, 	$t5											#(0x1 << (val - 1))
	and $t7,	$t3,	$t5											#(puzzle->grid[position].domain & (0x1 << (val - 1)))
	bne $t7,	$t6,	if_skip2

if_skip2:
	add $t1,	$t1,	1												#val++
	j 	loop
end_of_for_loop:
	li 	$v0,	0
	jr  $ra
