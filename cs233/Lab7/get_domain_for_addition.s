.text

## int
## get_domain_for_addition(int target, int num_cell, int domain) {
##     int upper_bound = convert_highest_bit_to_int(domain);
##     // For an integer i, i & -i keeps only the lowest 1 in the integer.
##     int lower_bound = convert_highest_bit_to_int(domain & (-domain)); // done
##     int high_bits = target - (num_cell - 1) * lower_bound; // done
##     if (high_bits < upper_bound) { // done
##         domain = domain & ((1 << high_bits) - 1); //done
##     } // done
##     int low_bits = target - (num_cell - 1) * upper_bound;
##     if (low_bits > 0) {
##         domain = (domain >> (low_bits - 1)) << (low_bits - 1);
##     }
##     return domain;
## }

.globl get_domain_for_addition
get_domain_for_addition:
	#Your code goes here :)
	#target = a0
	#num_cell = a1
	#domain = a2
	sub		$sp,	$sp,	16
	sw 		$ra,	0($sp)
	sw 		$a0,	4($sp)
	sw 		$a1,	8($sp)
	sw 		$a2,	12($sp)
	mul		$t0,	$a2,	2			#multiply by 2
	sub		$t1,	$a2,	$t0			#-domain
	and		$t2,	$a2,	$t1			#domain & (-domain)
	move	$a0,	$t2
	jal 	convert_highest_bit_to_int	#convert_highest_bit_to_int(domain & (-domain))
	#v0 at this point is basically lower_bound
	move	$t3,	$v0					#this moves lower_bound into a temp register so that we can store the final return later
										#lower_bound = convert_highest_bit_to_int(domain & (-domain))
	lw 		$a0,	4($sp)
	jal 	convert_highest_bit_to_int
	move 	$t0, 	$v0					#uppder_bound = convert_highest_bit_to_int(domain)
	sub		$a1,	$a1,	1 			#num_cell - 1
	mul 	$t4,	$a1,	$t3 		#(num_cell - 1) * lower_bound
	lw 		$a0,	4($sp)
	sub		$t5,	$a0,	$t4			#high_bits = target - (num_cell - 1) * lower_bound
	bgt 	$t5,	$t0,	skip_if		
	li 		$t6,	1
	sll		$t7,	$t6,	$t5			#1<< high_bits
	sub		$t7, 	$t7,	1 			#(1<< high_bits) - 1
	and		$a2,	$a2,	$t7			# domain = domain & ((1 << high_bits) - 1)
	j 		skip_if
skip_if:
	mul 	$t4,	$a1,	$t0 		#(num_cell - 1) * upper_bound 	
	sub		$t5,	$a0,	$t4			#low_bits = target - (num_cell - 1) * upper_bound
	blt 	$t5,	$0, 	ret
	sub 	$t5,	$t5,	1 			#(low_bits - 1)
	srl		$a2,	$a2,	$t5			#(domain >> (low_bits - 1))
	sll		$a2,	$a2,	$t5			#((domain >> low_bits - 1)) << (low_bits - 1)
	j 		ret
ret:
	move 	$v0,	$a2
	lw 	$ra,	0($sp)
	add $sp,	$sp,	16
	jr	$ra
