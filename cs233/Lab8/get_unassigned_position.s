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
## // Returns next position for assignment.
## int
## get_unassigned_position(const Solution *solution, const Puzzle *puzzle) {
##     int unassigned_pos = 0;
##     for (; unassigned_pos < puzzle->size * puzzle->size; unassigned_pos++) {
##         if (solution->assignment[unassigned_pos] == 0) {
##             break;
##         }
##     }
##     return unassigned_pos;
## }

.globl get_unassigned_position
get_unassigned_position:
	# Your code goes here :)
	li	$t0,	0							#unassigned_pos = 0
	lw	$t1,	0($a1)				#puzzle->size
	mul	$t2,	$t1,	$t1			#puzzle->size * puzzle->size
floop:
	bge	$t0,	$t2,	ret			#branches if unassigned_pos > puzzle->size * puzzle->size
	mul $t4,	$t0,	4				#for the offset
	add $t4,	$t4,	4
	add $t3,	$a0,	$t4			#&solution->assignment[unassigned_pos]
	lw 	$t3,  0($t3)				#solution->assignment[unassigned_pos]
	bne $t3,	0,		skip_if	#solution->assignent[unassigned_pos] == 0
	j		ret									#jump out of the loop or in other words jump to ret
skip_if:
	add $t0,	$t0,	1				#unassigned_pos++
	j 	floop

ret:
	move $v0,	$t0
	jr  $ra
