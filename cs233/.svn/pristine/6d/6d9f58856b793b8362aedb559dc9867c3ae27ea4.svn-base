.data

# Strings for printing purposes
get_domain_for_sub_8_1ff_1ff_str:
.asciiz "get_domain_for_subtraction(8, 0x1ff, 0x1ff) is "
get_domain_for_sub_3_49_8_str:
.asciiz "get_domain_for_subtraction(3, 0x49, 0x8) is "
get_domain_for_sub_3_9_8_str:
.asciiz "get_domain_for_subtraction(3, 0x9, 0x8) is "

.text
MAIN_STK_SPC = 4
main:
	sub	$sp, $sp, MAIN_STK_SPC
	sw	$ra, 0($sp)

	la	$a0, get_domain_for_sub_8_1ff_1ff_str
	jal	print_string
	li	$a0, 8
	li	$a1, 0x1ff
	li	$a2, 0x1ff
	jal	get_domain_for_subtraction
	move	$a0, $v0
    jal	print_int_hex_and_space
	jal	print_newline

	la	$a0, get_domain_for_sub_3_49_8_str
	jal	print_string
	li	$a0, 3
	li	$a1, 0x49
	li	$a2, 0x8
	jal	get_domain_for_subtraction
	move	$a0, $v0
    jal	print_int_hex_and_space
	jal	print_newline

	la	$a0, get_domain_for_sub_3_9_8_str
	jal	print_string
	li	$a0, 3
	li	$a1, 0x9
	li	$a2, 0x8
	jal	get_domain_for_subtraction
	move	$a0, $v0
    jal	print_int_hex_and_space
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, MAIN_STK_SPC
	jr	$ra
