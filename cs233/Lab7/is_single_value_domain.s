.text

## int
## is_single_value_domain(int domain) {
##     if (domain != 0 && (domain & (domain - 1)) == 0) {
##         return 1;
##     }
##     return 0;
## }

.globl is_single_value_domain
is_single_value_domain:
	#Your code goes here :)
	#domain = a0
		beq	$a0,	$0,		ret 	#domain != 0
		add	$t0,	$a0,	-1 		#domain - 1
		and	$t1,	$a0,	$t0		#domain & (domain - 1)
		bne	$t1,	$0,		ret 	#(domain & (domain - 1)) == 0
		li	$v0,	1				#return 1
		jr	$ra
	#v0 needs to have the value of 0
ret:	li	$v0,	0				#return 0
		jr	$ra
