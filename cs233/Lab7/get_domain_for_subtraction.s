.text

## int
## get_domain_for_subtraction(int target, int domain, int other_domain) {
##     int base_mask = 1 | (1 << (target * 2));
##     int mask = 0;
##     for (; other_domain; other_domain >>= 1) {
##         if (other_domain & 1) {
##             mask |= (base_mask >> target);
##         }
##         base_mask <<= 1;
##     }
##     return domain & mask;
## }

.globl get_domain_for_subtraction
get_domain_for_subtraction:
	#Your code goes here :)
	#target is $a0
	#domain is $a1
	#other_domain is $a2
	mul	$t0,	$a0,	2		#base_mask = target * 2
	li	$t1,	1
	sll	$t0,	$t1,	$t0		#base_mask = 1 << (target * 2)
	or 	$t0, 	$t1,	$t0		#base_mask = 1 | (1 << (target * 2))
	li 	$t2,	0				#mask = 0
floop:	
	beq $a2,	$0,		ret 	#other_domain != 0
	and $t3,	$a2,	$t1		#other_domain & 1
	bne	$t3,	$t1,	if_skip	#if(other_domain & 1 == 1)
	sll	$t4,	$t0,	$a0		#base_mask >> target
	or 	$t2,	$t2,	$t4		#mask |= (base_mask >> target)
	j 	if_skip
if_skip:
	sll	$t0,	$t0,	1		#base_mask <<= 1
	srl	$a2,	$a2,	1		#other_domain >>= 1 (for the for loop)
	j 	floop
ret:
	and	$v0,	$a1,	$t2		#return domain & mask
	jr	$ra
