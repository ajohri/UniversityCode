# run with QtSpim -file main.s question_4.s

# void array_swap(int *A, int a_length, int *B, int b_length) {
#     int length = a_length;
#     if (b_length < a_length) {
#         length = b_length;
#     }
# 
#     for (int i = 0; i < length; i++) {
#         int temp = A[i];
#         A[i] = B[i];
#         B[i] = temp;
#     }
# }
.globl array_swap
array_swap:
	move	$t0,	$a1		#int length = a_length
	bge	$a3,	$a1,	skip_if	#if(b_length < a_length)
	move	$t0,	$a3
skip_if:
	li	$t1,	0		#int i = 0
loop:
	bge	$t1,	$t0,	end_of_loop
	mul	$t2,	$t1,	4	#i * 4
	add	$a0,	$a0,	$t2	#*A[i]
	add	$a2,	$a2,	$t2	#*B[i]
	lw	$t3,	0($a0)		#A[i]
	lw	$t5,	0($a2)		#B[i]
	move	$t4,	$t3		#int temp = A[i]
	move	$t3,	$t5		#A[i] = B[i]
	move	$t5,	$t4		#B[i] = temp
	add	$t1,	$t1,	1	#i++
	j	loop
end_of_loop:
	jr 	$ra	
