.data

# Strings for printing purposes
convert_highest_bit_to_int_0x0_str: .asciiz "convert_highest_bit_to_int(0x0) is "
convert_highest_bit_to_int_0x1_str: .asciiz "convert_highest_bit_to_int(0x1) is "
convert_highest_bit_to_int_0x90_str: .asciiz "convert_highest_bit_to_int(0x90) is "
convert_highest_bit_to_int_0x1ff_str: .asciiz "convert_highest_bit_to_int(0x1ff) is "

.text
MAIN_STK_SPC = 4
main:
	sub	$sp, $sp, MAIN_STK_SPC
	sw	$ra, 0($sp)

	la	$a0, convert_highest_bit_to_int_0x0_str
	jal	print_string
	li	$a0, 0x0
	jal	convert_highest_bit_to_int
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, convert_highest_bit_to_int_0x1_str
	jal	print_string
	li	$a0, 0x1
	jal	convert_highest_bit_to_int
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, convert_highest_bit_to_int_0x90_str
	jal	print_string
	li	$a0, 0x90
	jal	convert_highest_bit_to_int
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	la	$a0, convert_highest_bit_to_int_0x1ff_str
	jal	print_string
	li	$a0, 0x1ff
	jal	convert_highest_bit_to_int
	move	$a0, $v0
	jal	print_int_and_space
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, MAIN_STK_SPC
	jr	$ra
