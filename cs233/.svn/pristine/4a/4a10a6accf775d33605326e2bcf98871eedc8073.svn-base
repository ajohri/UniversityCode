# syscall constants
PRINT_STRING	= 4
PRINT_CHAR	= 11
PRINT_INT	= 1

# memory-mapped I/O
VELOCITY	= 0xffff0010
ANGLE		= 0xffff0014
ANGLE_CONTROL	= 0xffff0018

BOT_X		= 0xffff0020
BOT_Y		= 0xffff0024

TIMER		= 0xffff001c

TILE_SCAN	= 0xffff0024
HARVEST_TILE	= 0xffff0020

GET_FIRE_LOC	= 0xffff0028
PUT_OUT_FIRE	= 0xffff0040

PRINT_INT_ADDR		= 0xffff0080
PRINT_FLOAT_ADDR	= 0xffff0084
PRINT_HEX_ADDR		= 0xffff0088

# interrupt constants
BONK_MASK	= 0x1000
BONK_ACK	= 0xffff0060

TIMER_MASK	= 0x8000
TIMER_ACK	= 0xffff006c

ON_FIRE_MASK	= 0x400
ON_FIRE_ACK	= 0xffff0050


.data
# put your data things here
TILE_SCAN = 0xffff0024

.align 2
tile_data: .space 1600


.text
main:
	# put your code here :)
	li 	$t5, 	0									#loading 0 into this temporary register
	sw 	$t5,	VELOCITY					#this will set our velocity to 0, This will change later on

	li 	$t1, 	3									#this is to make sure we harvested less than 3 fruits
	li 	$s1,	0									#our initial amount that we have harvested
	li 	$t5, 	0									
	sw 	$t5,	VELOCITY					#this will set our veloctiy to 0, will be modified later

	bge $s1,	$t1,	end					#if(harvest <= 3)
	li 	$t2,	0									#this will be our value on 0 that will be used to check for plant
	li 	$t3,	1									#counter will use this for the location that we are at in the plant array.
	li 	$t4,	1									#need a constant 1 value
	la 	$t0,	tile_data
	sw 	$t0,	TILE_SCAN

search:
	beq $t2,	$t4,	moveTile
	lw 	$t5,	0($t0)						#This will load the beginning of the array
	beq $t5,	$t4,	setTarget 	#Checking to see whether the tile we are at has a plant
	add $t0,	$t0,	16					#Incrementing by the size of our struct so that we can progress to the next tile
	add $t3,	$t3,	1						#counter++
	j 	search

setTarget:
	li 	$t2,	1									#The plan boolean will be set to true since we have found a plant
	j 	search

moveTile:
	li 	$t6, 	10
	div $t3,	$t6
	mfhi $t8 										#modulus will be the x position
	mflo $t9 										#division will be the y position

	beq $t8,	$0,		sameRow
	add $t9,	$t9,	1
	j 	newCoord

newCoord:
	li 	$t6,	30 								#This is for the 30 x 30
	sub $t8,	$t8,	1						# x position - 1
	sub $t9,	$t9,	1						# y position - 1
	mul $t8, 	$t8,	$t6					# (x position - 1) * 30
	mul $t9, 	$t9,	$t6					# (x position - 1) * 30
	add $t8,	$t8,	15					# We now need to get the center of the tile $t8 will now be the x coordinate
	add $t9,	$t9,	15					# We now need to get the center of the tile $t9 will now be the y coordinate

checkCoordinate:
	lw 	$t6,	BOT_X							#loading the x coordinate of the bot
	lw 	$t7,	BOT_Y							#loading the y coordinate of the bot
	beq $t8,	$t6, 	setting_X		#If the x coordinate of the bot is at the x coordinate then we need to move onto the y coordinate
	blt $t8,	$t6,	move_left		#if the x coordinate is less than the bot x coordinate then we need to move left otherwise we need to move right.
	#going right
	li 	$t5,	0									#setting the angle so that it goes right
	sw 	$t5,	ANGLE							#this will set the angle of the bot to 180
	li 	$t5,	1
	sw 	$t5,	ANGLE_CONTROL			#setting the absolute angle
	li 	$t5,	10
	sw 	$t5, 	VELOCITY					#setting the velocity to 10

	j 	checkCoordinate
move_left:
	li 	$t5,	180								#setting the angle so that it goes left
	sw 	$t5,	ANGLE							#this will set the angle of the bot to 0
	li 	$t5,	1
	sw 	$t5,	ANGLE_CONTROL			#setting the absolute angle
	li 	$t5,	10
	sw 	$t5, 	VELOCITY					#setting the velocity to 10

	j 	checkCoordinate

setting_X:
	li 	$t5,	0
	sw 	$t5,	VELOCITY
	beq $t9,	$t7,	collect_harvest	#Since the x coordinate will be taken care of here if the y coordinate is okay then we are at the plant that needs to be harvested
	bge $t9,	$t7,	go_down			#If our y coordinate of the bot is less than the y coordinate then we need to go down
	#going up
	li 	$t5, 	270
	sw 	$t5,	ANGLE 						#Setting the angle to 270 degree
	li 	$t5, 	1
	sw 	$t5,	ANGLE_CONTROL			#Setting the absolute angle control to 1
	li 	$t5,	10
	sw 	$t5, 	VELOCITY					#Setting the velocity to 10

	j 	checkCoordinate

go_down:
	li 	$t5,	90
	sw 	$t5,	ANGLE 						#Setting the angle to 90
	li 	$t5, 	1
	sw 	$t5,	ANGLE_CONTROL			#Setting the absolute angle to 1
	li 	$t5,	10
	sw 	$t5,	VELOCITY					#Setting the velocity to 10

	j 	checkCoordinate

collect_harvest:
	li 	$t5, 	0
	sw 	$t5,	VELOCITY
	li 	$t5, 	1
	sw 	$t5, 	HARVEST_TILE			#collecting the harvest
	add $s1,	$s1, 	1						#incrementing that we have collected the plant that we are at and we need to add 1 to our stack pointer

	# note that we infinite loop to avoid stopping the simulation early
end:
	j		main
