/**
 * @file
 * Contains the implementation of the countOnes function.
 */

unsigned countOnes(unsigned input) {
	// TODO: write your code here
	int odd32 = input & 0x55555555;
	int even32 = input & 0xAAAAAAAA;
	
	input = odd32 + (even32 >> 1);

	int odd16 = input & 0x33333333;
	int even16 = input & 0xCCCCCCCC;
	
	input = odd16 + (even16 >> 2);

	int odd8 = input & 0x0F0F0F0F;
	int even8 = input & 0xF0F0F0F0;
	
	input = odd8 + (even8 >> 4);
	
	int odd4 = input & 0x00FF00FF;
	int even4 = input & 0xFF00FF00;
	
	input = odd4 + (even4 >> 8);

	int odd = input & 0x0000FFFF;
	int even = input & 0xFFFF0000;
	
	input = odd + (even >>16);
	

	return input;
}
