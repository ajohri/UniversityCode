PRINT_STRING = 4
PRINT_CHAR   = 11
PRINT_INT    = 1

# debug constants
PRINT_INT_ADDR   = 0xffff0080
PRINT_FLOAT_ADDR = 0xffff0084
PRINT_HEX_ADDR   = 0xffff0088

# spimbot constants
VELOCITY       = 0xffff0010
ANGLE          = 0xffff0014
ANGLE_CONTROL  = 0xffff0018
BOT_X          = 0xffff0020
BOT_Y          = 0xffff0024
OTHER_BOT_X    = 0xffff00a0
OTHER_BOT_Y    = 0xffff00a4
TIMER          = 0xffff001c
SCORES_REQUEST = 0xffff1018

TILE_SCAN       = 0xffff0024
SEED_TILE       = 0xffff0054
WATER_TILE      = 0xffff002c
MAX_GROWTH_TILE = 0xffff0030
HARVEST_TILE    = 0xffff0020
BURN_TILE       = 0xffff0058
GET_FIRE_LOC    = 0xffff0028
PUT_OUT_FIRE    = 0xffff0040

GET_NUM_WATER_DROPS   = 0xffff0044
GET_NUM_SEEDS         = 0xffff0048
GET_NUM_FIRE_STARTERS = 0xffff004c
SET_RESOURCE_TYPE     = 0xffff00dc
REQUEST_PUZZLE        = 0xffff00d0
SUBMIT_SOLUTION       = 0xffff00d4

# interrupt constants
BONK_MASK               = 0x1000
BONK_ACK                = 0xffff0060
TIMER_MASK              = 0x8000
TIMER_ACK               = 0xffff006c
ON_FIRE_MASK            = 0x400
ON_FIRE_ACK             = 0xffff0050
MAX_GROWTH_ACK          = 0xffff005c
MAX_GROWTH_INT_MASK     = 0x2000
REQUEST_PUZZLE_ACK      = 0xffff00d8
REQUEST_PUZZLE_INT_MASK = 0x800

.data
capacity: .word 0
outer_capacity: .word 0


lol420xd: .word 0


tiles: .space 1600

puzzle: .space 4096

solution: .space 328

x: .word 0
y: .word 0


.text
main:
	la $t0, tiles
	sw $t0, TILE_SCAN
	# go wild
	# the world is your oyster :)
	li	$t4, 0x8000		# ENABLE INTERRUPTS
	or	$t4, $t4, 0x1000	# Bonk Interrupt Enable bit
	or	$t4, $t4, 1		# Global Interrupt Enable bit
	mtc0	$t4, $12		# Set interrupt mask

check:
	la $t0, tiles
	sw $t0, TILE_SCAN


seeding:
	lw		$t0, GET_NUM_SEEDS
	beq		$t0, 0, morepls	# if  ==  then

	la $t0, tiles
	sw $t0, TILE_SCAN

	li		$t1, 0	#  = 0


scan_seed:
	lw		$t2, 0($t0)		#
	beq		$t2, 0, seeds	# if $t2 == 0 then seeds



seed:
	li $t2, 10
	div $t1, $t2
	mfhi $t2
	li $t3, 30
	mult $t2, $t3
	mflo $t2
	add $t2, $t2, 15
	sw $t2, x

	li $2, 10
	div $t1, $t2
	mflo $t2
	li $t3, 30
	mult $t2, $t3
	mflo $t2
	add $t2, $t2, 15
	sw $t2, y

	#move to the proper location
	jal move_bot

	#Seed tile
	sw $0, SEED_TILE

	j seeding



morepls:
 	li		$t0, 1		# $t0 = 1
	sw		$t0, SET_RESOURCE_TYPE

	la		$t0, puzzle

	sw		$t0, REQUEST_PUZZLE

	li		$t0, 0


	# Start again.
	j	infinite

.kdata
chunkIH:	.space 8

main_block_str: .asciiz "We're currently in the main block\n"
non_intrpt_str: .asciiz "Non-interrupt exception\n"
unhandled_str:	.asciiz "Unhandled interrupt type\n"
fire_str:	.asciiz "Fire detected\n"
max_growth_str:	.asciiz "Max growth interrupt detected\n"
plant_str:	.asciiz "Seed planted\n"


.ktext 0x80000180
interrupt_handler:
.set noat
	move	$k1, $at

.set at
	la	$k0, chunkIH		# chunkIH is the data
		sw	$a0, 0($k0)		# store that shit
	sw	$a1, 4($k0)

	mfc0	$k0, $13
	srl	$a0, $k0, 2
	and	$a0, $a0, 0xf
	bne	$a0, 0, non_intrpt

# Handles all interrupt types & shit
interrupt_dispatch:

	mfc0	$k0, $13
	beq	$k0, $zero, done

	# Dispatch for Fires
	and	$a0, $k0, ON_FIRE_MASK
	bne	$a0, 0, fire_interrupt

	# Dispatch for Bonks
	and	$a0, $k0, BONK_MASK
	bne	$a0, 0, bonk_interrupt

	# Dispatch for Max Growth
	and	$a0, $k0, MAX_GROWTH_INT_MASK
	bne	$a0, 0, max_growth_interrupt

	# Add dispatch for other interrupt types here

	# Print that we found an unhandled interrupt
	la	$v0, PRINT_STR
	la	$a0, unhandled_str
	syscall
	j	done


harvest:
	lw	$t0, MAX_GROWTH_TILE

	and	$t1, $t0, 0xFFFF0000 # x-index
	srl	$t1, $t1, 16 # Right shift by 16
	mul	$t1, $t1, 30
	add	$t1, $t1, 15
	and	$t2, $t0, 0x0000FFFF # y-index
	mul	$t2, $t2, 30
	add	$t2, $t2, 15

	lw 	$t8,	BOT_X
	lw 	$t9,	BOT_Y

xcheck:
	bgt		$t8, $t3, back
	blt		$t8, $t3, forward
	sw		$0, VELOCITY		#

	j		  ycheck				# jump to ycheck


back:
	li		$t7, 180
	sw		$t7, ANGLE
	li		$t7, 1
	sw		$t7, ANGLE_CONTROL
	li		$t5, 10
	sw		$t5, VELOCITY
	lw		$t8, BOT_X
	j			xcheck

forward:
	li		$t7, 0
	sw		$t7, ANGLE
	li		$t7, 1
	sw		$t7, ANGLE_CONTROL
	li		$t5, 10
	sw		$t5, VELOCITY
	lw		$t8, BOT_X
	j			xcheck


ycheck:
	bgt		$t9, $t4, backy
	blt		$t9, $t4, forwardy
	sw		$0, VELOCITY		#
	sw 		$0,	HARVEST_TILE

backy:
	li		$t7, 270
	sw		$t7, ANGLE
	li		$t7, 1
	sw		$t7, ANGLE_CONTROL
	li		$t5, 10
	sw		$t5, VELOCITY
	lw		$t9, BOT_Y
	j			ycheck

forwardy:
	li		$t7, 90
	sw		$t7, ANGLE
	li		$t7, 1
	sw		$t7, ANGLE_CONTROL
	li		$t5, 10
	sw		$t5, VELOCITY
	lw		$t9, BOT_Y
	j			ycheck



########################
# Max growth interrupt #
########################
max_growth_interrupt:
	sw	$a1, MAX_GROWTH_ACK
	la	$v0, PRINT_STR
	la	$a0, max_growth_str
	syscall

	la 	$t0,	harvest
	jalr 	$t0

	# TODO: Move to plant and harvest the block

	j	done


##################
# Bonk Interrupt #
##################
bonk_interrupt:
	sw	$a1, BONK_ACK
	la	$v0, PRINT_STR
	la	$a0, fire_str
	syscall
	j	done


##################
# Fire interrupt #
##################
fire_interrupt:

	# Acknowledge the interrupt
	sw	$a1, ON_FIRE_ACK

	# Get fire loc
	lw	$t0, GET_FIRE_LOC

	and	$t1, $t0, 0xFFFF0000 # x-index
	srl	$t1, $t1, 16 # Right shift by 16
	mul	$t1, $t1, 30
	add	$t1, $t1, 15
	and	$t2, $t0, 0x0000FFFF # y-index
	mul	$t2, $t2, 30
	add	$t2, $t2, 15

	# Jump to the shit
	j	move_to_fire


move_to_fire:

	# bot-x  : $t3
	# fire-x : $t1

	# bot-y  : $t5
	# fire-y : $t2

	lw	$t3, BOT_X # get x
	lw	$t5, BOT_Y # get y


	bne	$t1, $t3, move_x_dispatch
	beq     $t1, $t3, kill_velocity_x

next:
	bne	$t2, $t5, move_y_dispatch
	beq     $t1, $t3, kill_velocity_y


move_x_dispatch:
	blt	$t3, $t1, move_right # If bot's x is less than fire's x, move right
	j	move_left # Else, move left!
	# Don't worry about edge case of equality because bne checks for that already before the dispatcher is called

move_y_dispatch:
	blt	$t5, $t2, move_down # If bot's y is less than fire's y, move down
	j	move_up # Else, move up!


move_left:
	li	$t8, 180
	sw	$t8, ANGLE
	li	$t7, 1
	sw	$t7, ANGLE_CONTROL
	j	set_velocity

move_right:
	li	$t8, 0
	sw	$t8, ANGLE
	li	$t7, 1
	sw	$t7, ANGLE_CONTROL
	j	set_velocity

move_up:
	li	$t8, 270
	sw	$t8, ANGLE
	li	$t7, 1
	sw	$t7, ANGLE_CONTROL
	j	set_velocity

move_down:
	li	$t8, 90
	sw	$t8, ANGLE
	li	$t7, 1
	sw	$t7, ANGLE_CONTROL
	j	set_velocity

set_velocity:
	li	$t7, 10
	sw	$t7, VELOCITY
	j	move_to_fire

kill_velocity_x:
	li	$t7, 0
	sw	$t7, VELOCITY
	j	next

kill_velocity_y:
	li	$t7, 0
	sw	$t7, VELOCITY
	j	extinguish_fire

extinguish_fire:
	# Extinguish the fire
	li	$t7, 2
	sw	$t7, PUT_OUT_FIRE
	j	interrupt_dispatch

non_intrpt:
	li	$v0, 4
	la	$a0, non_intrpt_str
	syscall
	j	done

done:
	la	$k0, chunkIH
	lw	$a0, 0($k0)
	lw	$a1, 4($k0)
	mfc0	$k0, $14






.set noat
	move	$at, $k1


#.set at
#	rfe
#	jr	$k0
#	nop


.set at
	eret

	# note that we infinite loop to avoid stopping the simulation early
	#j	main










	#j	main