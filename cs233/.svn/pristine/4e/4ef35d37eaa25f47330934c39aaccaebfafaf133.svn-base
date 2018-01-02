.text

## struct Puzzle {
##     int size;
##     Cell *grid;
## };
##
## // Given the assignment at current position, removes all inconsistent values
## // for cells in the same row, column, and cage.
## int
## forward_checking(int position, Puzzle *puzzle) {
##     int size = puzzle->size;
##     // Removes inconsistent values in the row.
##     for (int col = 0; col < size; col++) {
##         if (col != position % size) {
##             int row_pos = position / size * size + col;
##             puzzle->grid[row_pos].domain &= ~puzzle->grid[position].domain;
##             if (!puzzle->grid[row_pos].domain) {
##                 return 0;
##             }
##         }
##     }
##     // Removes inconsistent values in the column.
##     for (int row = 0; row < size; row++) {
##         if (row != position / size) {
##             int col_pos = row * size + position % size;
##             puzzle->grid[col_pos].domain &= ~puzzle->grid[position].domain;
##             if (!puzzle->grid[col_pos].domain) {
##                 return 0;
##             }
##         }
##     }
##     // Removes inconsistent values in the cage.
##     for (int i = 0; i < puzzle->grid[position].cage->num_cell; i++) {
##         int cage_pos = puzzle->grid[position].cage->positions[i];
##         puzzle->grid[cage_pos].domain &= get_domain_for_cell(cage_pos, puzzle);
##         if (!puzzle->grid[cage_pos].domain) {
##             return 0;
##         }
##     }
##     return 1;
## }

.globl forward_checking
forward_checking:
    # Your code goes here :)
    sub $sp,  $sp,  4
    sw  $ra,  0($sp)
    lw  $t0,  0($a1)                      #size = puzzle->size
    li  $t1,  0                           #col = 0
    div $a0,  $t0                         #postion % size
    mfhi $t2                              #this has the modulo value
    mflo $t3                              #this is the regular division
loop1:
    bge $t1,  $t0,  end_loop1             #col < size
    beq $t1,  $t2,  if_skip1              #col != position % size
    mul $t4,  $t3,  $t0                   #position / size * size
    add $t4,  $t4,  $t1                   #row_pos = position / size * size + col
    mul $t5,  $t4,  8                     #row_pos * 8
    lw  $t6,  4($a1)                      #puzzle->grid
    add $t6,  $t6,  $t5                   #puzzle->grid[row_pos]
    lw  $t6,  0($t6)                      #puzzle->grid[row_pos].domain
    mul $t7,  $a0,  8                     #position * 8
    lw  $t8,  4($a1)                      #puzzle->grid
    add $t8,  $t8,  $t7                   #puzzle->grid[position]
    lw  $t8,  0($t8)                      #puzzle->grid[position].domain
    not $t8,  $t8                         #~puzzle->grid[position].domain
    and $t6,  $t6,  $t8                   #puzzle->grid[row_pos].domain &= ~puzzle->grid[position].domain;
    bne $t6,  0,  if_skip2
    li  $v0,  0
    lw  $ra,  0($sp)
    add $sp,  $sp,  4
    jr  $ra
if_skip2:
    j if_skip1
if_skip1:
    add $t1,  $t1,  1                     #col++
    j   loop1                             #jump to forloop
end_loop1:
    li  $t1,  0                           #row = 0
loop2:
    bge $t1,  $t0,  end_loop2             #row < size
    beq $t1,  $t3,  if_skip3              #row != position / size
    mul $t4,  $t1,  $t0                   #row * size
    add $t4,  $t4,  $t2                   #col_pos = row * size + position % size
    mul $t5,  $t4,  8                     #col_pos * 8
    lw  $t6,  4($a1)                      #puzzle->grid
    add $t6,  $t6,  $t5                   #puzzle->grid[col_pos]
    lw  $t6,  0($t6)                      #puzzle->grid[col_pos].domain
    mul $t7,  $a0,  8                     #position * 8
    lw  $t8,  4($a1)                      #puzzle->grid
    add $t8,  $t8,  $t7                   #puzzle->grid[position]
    lw  $t8,  0($t8)                      #puzzle->grid[position].domain
    not $t8,  $t8                         #~puzzle->grid[position].domain
    and $t6,  $t6,  $t8                   #puzzle->grid[col_pos].domain &= ~puzzle->grid[position].domain;
    bne $t6,  0,  if_skip4
    li  $v0,  0
    lw  $ra,  0($sp)
    add $sp,  $sp,  4
    jr  $ra
if_skip4:
    j if_skip3
if_skip3:
    add $t1,  $t1,  1                     #col++
    j   loop2                             #jump to forloop
end_loop2:
    li  $t0,  0                           #i = 0
    lw  $t6,  0($a1)                      #puzzle->grid
    mul $t2,  $a0,  8                     #position * 8
    add $t6,  $t6,  $t2                   #puzzle->grid[position]
    lw  $t6,  4($t6)                      #puzzle->grid[position].cage
    lw  $t6,  5($t6)                      #puzzle->grid[position].cage->num_cell
final_loop:
    bge $t0,  $t6,  end_final_loop
    lw  $t1,  0($a1)                      #puzzle->grid
    mul $t2,  $a0,  8                     #position * 8
    add $t1,  $t1,  $t2                   #puzzle->grid[position]
    lw  $t1,  4($t1)                      #puzzle->grid[position].cage
    lw  $t1,  9($t1)                      #puzzle->grid[position].cage->positions
    mul $t3,  $t0,  13                    # i * 13
    add $t1,  $t1,  $t3                   #cage_pos = puzzle->grid[position].cage->positions[i]
    move $a0, $t1                         #setting up the arguments for the next function
    jal   get_domain_for_cell             #$v0 now has the value returned from get_domain_for_cell
    lw  $t4,  0($a1)                      #puzzle->grid
    mul $t5,  $t1,  13                    #cage_pos * 13
    add $t4,  $t4,  $t5                   #puzzle->grid[cage_pos]
    lw  $t4,  0($t4)                      #puzzle->grid[cage_pos].domain
    and $t4,  $t4,  $v0                   #puzzle->grid[cage_pos].domain &= get_domain_for_cell(cage_pos, puzzle)
    bne $t4,  $0,   last_if
    li  $v0,  0
    lw  $ra,  0($sp)
    add $sp,  $sp,  4
    jr  $ra
last_if:
    add $t0,  $t0,  1                     #i++
    j   final_loop
end_final_loop:
    li  $v0,  1                           #the final return 1
    lw  $ra,  0($sp)
    add $sp,  $sp,  4
    jr  $ra
