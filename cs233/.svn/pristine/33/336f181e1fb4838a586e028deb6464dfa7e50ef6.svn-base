# run with QtSpim -file main.s question_5.s

# 
# void selection_sort(char **array, int length) {
#     for (int i = 0; i < length; i++) {
#        int current_best = i;
# 
#        for (int j = i + 1; j < length; j++) {
#           if (strcmp(array[j], array[current_best]) < 0) {  // do not inline, call with "jal strcmp"
#              current_best = j;
#           }
#        }
# 
#        char *temp = array[i];
#        array[i] = array[current_best];
#        array[current_best] = temp;
#     }
# }
.globl selection_sort
selection_sort:
	#char ** array is in $a0
	#int length is in $a1
	li	$t0,	1		#int i = 0
	sub	$sp,	$sp,	12
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	sw	$a1,	8($sp)
loopf1:
	bge	$t0,	$a1,	endoff1	#i < length
	move	$t1,	$t0		#current_best = i
	add	$t2,	$t0,	1	#j = i + 1
loopf2:
	bge	$t2,	$a1,	endoff2	#j < length	
	mul	$t3,	$t2,	4	#j * 4
	add	$t4,	$a0,	$t3	#**array[j]
	lw	$t4,	0($t4)
	lw	$t4,	0($t4)		#array[j]
	mul	$t5,	$t1,	4	#current_best * 4
	add	$t6,	$a0,	$t5	#**array[current_best]
	lw	$t6,	0($t6)
	lw	$t6,	0($t6)		#array[current_best]
	move	$a0,	$t4
	move	$a1,	$t6
	jal	strcmp
	bge	$v0,	$0,	skipif1
	move 	$t1,	$v0
skipif1:
	#increment
	add	$t2,	$t2,	1
	lw	$a1,	8($sp)
	lw	$a0,	4($sp)	
	j	loopf2	
endoff2:
	mul	$t3,	$t0,	4
	add	$t7,	$a0,	$t3
	lw	$t7,	0($t7)		#array[i]
	move	$t9,	$t7		#char *temp = array[i]
	mul	$t3,	$t1,	4
	add	$t8,	$a0,	$t3
	lw	$t8,	0($t8)		#array[current_best]
	move	$t7,	$t8
	move	$t8,	$t9
	add	$t0,	$t0,	1
	j	loopf1
endoff1:
	sw	$ra,	0($sp)
	jr	$ra
	


