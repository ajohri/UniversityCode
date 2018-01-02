.text

## int
## convert_highest_bit_to_int(int domain) {
##     int result = 0;
##     for (; domain; domain >>= 1) {
##         result++;
##     }
##     return result;
## }

.globl convert_highest_bit_to_int
convert_highest_bit_to_int:
	#Your code goes here :)
	#domain = a0
			li	$v0,	0				#result = 0 it is in the v0 register because it needs to be returned anyways
	loop:	beq	$a0,	$0,		ret 	#domain != 0
			add	$v0, 	$v0, 	1		#result++
			srl	$a0,	$a0,	1		#domain >>= 1
			j 	loop					#looping it back around
	ret:	jr	$ra						#returing what is inside the return registers
