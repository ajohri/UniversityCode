/*
 * CS 233 Fall 2016 Lab 7
 * clang++ lab7.cpp -o lab7
 */

#include <cassert>
#include <iostream>
#include <stdio.h>

// This is part 1.

// Checks if only one bit is set to 1 in the domain.
int
is_single_value_domain(int domain) {
    if (domain != 0 && (domain & (domain - 1)) == 0) {
        return 1;
    }
    return 0;
}

// Converts the highest bit in the domain
// to an integer corresponding to its position.
// Example: 0b1001 converts to 4.
int
convert_highest_bit_to_int(int domain) {
    int result = 0;
    for (; domain; domain >>= 1) {
        result++;
    }
    return result;
}

// This is part 2.

// Returns an integer as possible domain for a cage with "+" operator,
// target sum, number of cells, and the possible domain for cells.
int
get_domain_for_addition(int target, int num_cell, int domain) {
    int upper_bound = convert_highest_bit_to_int(domain);
    // For an integer i, i & -i keeps only the lowest 1 in the integer.
    int lower_bound = convert_highest_bit_to_int(domain & (-domain));
    int high_bits = target - (num_cell - 1) * lower_bound;
    if (high_bits < upper_bound) {
        domain = domain & ((1 << high_bits) - 1);
    }
    int low_bits = target - (num_cell - 1) * upper_bound;
    if (low_bits > 0) {
        domain = (domain >> (low_bits - 1)) << (low_bits - 1);
    }
    return domain;
}

// Returns an integer as possible domain for a cage with "-" operator,
// the domain of this cell, and the domain of the other cell in the cage.
int
get_domain_for_subtraction(int target, int domain, int other_domain) {
    int base_mask = 1 | (1 << (target * 2));
    int mask = 0;
    for (; other_domain; other_domain >>= 1) {
        if (other_domain & 1) {
            mask |= (base_mask >> target);
        }
        base_mask <<= 1;
    }
    return domain & mask;
}

// Unit tests.
// You can add more test cases here.
void
test_is_single_value_domain() {
    assert(is_single_value_domain(0x0) == 0);  // 0b0
    assert(is_single_value_domain(0x2) == 1);  // 0b10
    assert(is_single_value_domain(0x3) == 0);  // 0b11
    assert(is_single_value_domain(0x80) == 1); // 0b1000 0000

    printf("is_single_value_domain(0x0) is %d\n", is_single_value_domain(0x0));
    printf("is_single_value_domain(0x2) is %d\n", is_single_value_domain(0x2));
    printf("is_single_value_domain(0x3) is %d\n", is_single_value_domain(0x3));
    printf("is_single_value_domain(0x80) is %d\n",
           is_single_value_domain(0x80));
}

void
test_convert_highest_bit_to_int() {
    assert(convert_highest_bit_to_int(0x0) == 0);
    assert(convert_highest_bit_to_int(0x1) == 1);
    assert(convert_highest_bit_to_int(0x90) == 8);  // 0b1001 0000
    assert(convert_highest_bit_to_int(0x1ff) == 9); // 0b1 1111 1111

    printf("convert_highest_bit_to_int(0x0) is %d\n",
           convert_highest_bit_to_int(0x0));
    printf("convert_highest_bit_to_int(0x1) is %d\n",
           convert_highest_bit_to_int(0x1));
    printf("convert_highest_bit_to_int(0x90) is %d\n",
           convert_highest_bit_to_int(0x90));
    printf("convert_highest_bit_to_int(0x1ff) is %d\n",
           convert_highest_bit_to_int(0x1ff));
}

void
test_get_domain_for_addition() {
    assert(get_domain_for_addition(11, 3, 0x1ff) == 0x1ff); // 0b1 1111 1111
    assert(get_domain_for_addition(11, 3, 0x1fe) == 0x7e);  // 0b111 1110

    printf("get_domain_for_addition(11, 3, 0x1ff) is 0x%x\n",
           get_domain_for_addition(11, 3, 0x1ff));
    printf("get_domain_for_addition(11, 3, 0x1fe) is 0x%x\n",
           get_domain_for_addition(11, 3, 0x1fe));
}

void
test_get_domain_for_subtraction() {
    assert(get_domain_for_subtraction(8, 0x1ff, 0x1ff) ==
           0x101);                                            // 0b1 0000 0001
    assert(get_domain_for_subtraction(3, 0x49, 0x8) == 0x41); // 0b10 1001
    assert(get_domain_for_subtraction(3, 0x9, 0x8) == 0x1);   // 0b1

    printf("get_domain_for_subtraction(8, 0x1ff, 0x1ff) is 0x%x\n",
           get_domain_for_subtraction(8, 0x1ff, 0x1ff));
    printf("get_domain_for_subtraction(3, 0x49, 0x8) is 0x%x\n",
           get_domain_for_subtraction(3, 0x49, 0x8));
    printf("get_domain_for_subtraction(3, 0x9, 0x8) is 0x%x\n",
           get_domain_for_subtraction(3, 0x9, 0x8));
}

int
main() {
    test_is_single_value_domain();
    test_convert_highest_bit_to_int();
    test_get_domain_for_addition();
    test_get_domain_for_subtraction();
    return 0;
}
