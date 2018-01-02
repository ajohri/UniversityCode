.data

# Strings for printing purposes
is_single_val_0x0_str: .asciiz "is_single_value_domain(0x0) is "
is_single_val_0x2_str: .asciiz "is_single_value_domain(0x2) is "
is_single_val_0x3_str: .asciiz "is_single_value_domain(0x3) is "
is_single_val_0x80_str: .asciiz "is_single_value_domain(0x80) is "

.text
MAIN_STK_SPC = 4
main:
	sub	$sp, $sp, MAIN_STK_SPC
	sw	$ra, 0($sp)

	la	$a0, is_single_val_0x0_str
	jal	print_string
	li	$a0, 0x0
	jal	is_single_value_domain
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, is_single_val_0x2_str
	jal	print_string
	li	$a0, 0x2
	jal	is_single_value_domain
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, is_single_val_0x3_str
	jal	print_string
	li	$a0, 0x3
	jal	is_single_value_domain
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, is_single_val_0x80_str
	jal	print_string
	li	$a0, 0x80
	jal	is_single_value_domain
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, MAIN_STK_SPC
	jr	$ra
