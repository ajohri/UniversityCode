.data

# Strings for printing purposes
get_domain_for_add_11_3_1ff_str: .asciiz "get_domain_for_addition(11, 3, 0x1ff) is "
get_domain_for_add_11_3_1fe_str: .asciiz "get_domain_for_addition(11, 3, 0x1fe) is "

.text
MAIN_STK_SPC = 4
main:
	sub	$sp, $sp, MAIN_STK_SPC
	sw	$ra, 0($sp)

	la	$a0, get_domain_for_add_11_3_1ff_str
	jal	print_string
	li	$a0, 11
	li	$a1, 3
	li	$a2, 0x1ff
	jal	get_domain_for_addition
	move	$a0, $v0
    jal	print_int_hex_and_space
	jal	print_newline

	la	$a0, get_domain_for_add_11_3_1fe_str
	jal	print_string
	li	$a0, 11
	li	$a1, 3
	li	$a2, 0x1fe
	jal	get_domain_for_addition
	move	$a0, $v0
    jal	print_int_hex_and_space
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, MAIN_STK_SPC
	jr	$ra
