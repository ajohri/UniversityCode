/*
 * CS 233 Fall 2016 Lab 8
 * KenKen Puzzle Solver
 *
 * clang++ -std=c++11 lab8.cpp -o lab8
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>

struct Cage {
    char operation;
    int target;
    int num_cell;
    int *positions;
};

struct Cell {
    int domain;
    Cage *cage;
};

struct Puzzle {
    int size;
    Cell *grid;
};

struct Solution {
    int size;
    int assignment[81];
};

// Functions from lab 7.
int is_single_value_domain(int domain);
int convert_highest_bit_to_int(int domain);
int get_domain_for_addition(int target, int num_cell, int domain);
int get_domain_for_subtraction(int target, int domain, int other_domain);
// More helper functions.
int get_domain_for_cell(int position, const Puzzle *puzzle);
void clone(const Puzzle *orig, Puzzle *clone);

// Functions for lab 8 part 1.

// Checks if the solution is complete.
int
is_complete(const Solution *solution, const Puzzle *puzzle) {
    return solution->size == puzzle->size * puzzle->size;
}

// Returns next position for assignment.
// You can assume there is an unassigned position in the puzzle.
int
get_unassigned_position(const Solution *solution, const Puzzle *puzzle) {
    int unassigned_pos = 0;
    for (; unassigned_pos < puzzle->size * puzzle->size; unassigned_pos++) {
        if (solution->assignment[unassigned_pos] == 0) {
            break;
        }
    }
    return unassigned_pos;
}

// This is part 2.

// Given the assignment at current position, removes all inconsistent values
// for cells in the same row, column, and cage.
int
forward_checking(int position, Puzzle *puzzle) {
    int size = puzzle->size;
    // Removes inconsistent values in the row.
    for (int col = 0; col < size; col++) {
        if (col != position % size) {
            int row_pos = position / size * size + col;
            puzzle->grid[row_pos].domain &= ~puzzle->grid[position].domain;
            if (!puzzle->grid[row_pos].domain) {
                return 0;
            }
        }
    }
    // Removes inconsistent values in the column.
    for (int row = 0; row < size; row++) {
        if (row != position / size) {
            int col_pos = row * size + position % size;
            puzzle->grid[col_pos].domain &= ~puzzle->grid[position].domain;
            if (!puzzle->grid[col_pos].domain) {
                return 0;
            }
        }
    }
    // Removes inconsistent values in the cage.
    for (int i = 0; i < puzzle->grid[position].cage->num_cell; i++) {
        int cage_pos = puzzle->grid[position].cage->positions[i];
        puzzle->grid[cage_pos].domain &= get_domain_for_cell(cage_pos, puzzle);
        if (!puzzle->grid[cage_pos].domain) {
            return 0;
        }
    }
    return 1;
}

int
recursive_backtracking(Solution *solution, Puzzle *puzzle) {
    if (is_complete(solution, puzzle)) {
        return 1;
    }
    int position = get_unassigned_position(solution, puzzle);
    for (int val = 1; val < puzzle->size + 1; val++) {
        if (puzzle->grid[position].domain & (0x1 << (val - 1))) {
            solution->assignment[position] = val;
            solution->size += 1;
            // Applies inference to reduce space of possible assignment.
            Puzzle puzzle_copy;
            Cell grid_copy[81]; // 81 is the maximum size of the grid.
            puzzle_copy.grid = grid_copy;
            clone(puzzle, &puzzle_copy);
            puzzle_copy.grid[position].domain = 0x1 << (val - 1);
            if (forward_checking(position, &puzzle_copy)) {
                if (recursive_backtracking(solution, &puzzle_copy)) {
                    return 1;
                }
            }
            solution->assignment[position] = 0;
            solution->size -= 1;
        }
    }
    return 0;
}

void
test_is_complete() {
    Cage cages[8] = {
        {'+', 10, 3, new int[3]{0, 1, 5}}, {'-', 1, 2, new int[2]{2, 3}},
        {'+', 7, 3, new int[3]{4, 8, 12}}, {'-', 1, 2, new int[2]{6, 10}},
        {0, 2, 1, new int[1]{7}},          {0, 1, 1, new int[1]{9}},
        {'-', 1, 2, new int[2]{11, 15}},   {'-', 1, 2, new int[2]{13, 14}}};

    Puzzle puzzle = {4, new Cell[81]};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].domain = 0x1ff;
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    Solution complete_solution = {
        16, {1, 4, 3, 2, 2, 1, 4, 3, 3, 2, 1, 4, 4, 3, 2, 1}};
    Solution incomplete_solution = {4, {1, 4, 3, 2}};

    assert(is_complete(&complete_solution, &puzzle) == 1);
    assert(is_complete(&incomplete_solution, &puzzle) == 0);
}

void
test_get_unassigned_position() {
    Cage cages[8] = {
        {'+', 10, 3, new int[3]{0, 1, 5}}, {'-', 1, 2, new int[2]{2, 3}},
        {'+', 7, 3, new int[3]{4, 8, 12}}, {'-', 1, 2, new int[2]{6, 10}},
        {0, 2, 1, new int[1]{7}},          {0, 1, 1, new int[1]{9}},
        {'-', 1, 2, new int[2]{11, 15}},   {'-', 1, 2, new int[2]{13, 14}}};

    Puzzle puzzle = {4, new Cell[81]};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].domain = 0x1ff;
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    Solution solution_all_empty = {0, {0}};
    Solution solution_4_empty = {5, {1, 4, 3, 2, 0, 1}};
    Solution solution_15_empty = {
        15, {1, 4, 3, 2, 2, 1, 4, 3, 3, 2, 1, 4, 4, 3, 2, 0}};

    assert(get_unassigned_position(&solution_all_empty, &puzzle) == 0);
    assert(get_unassigned_position(&solution_4_empty, &puzzle) == 4);
    assert(get_unassigned_position(&solution_15_empty, &puzzle) == 15);
}

void
test_forward_checking() {
    Cage cages[8] = {
        {'+', 10, 3, new int[3]{0, 1, 5}}, {'-', 1, 2, new int[2]{2, 3}},
        {'+', 7, 3, new int[3]{4, 8, 12}}, {'-', 1, 2, new int[2]{6, 10}},
        {0, 2, 1, new int[1]{7}},          {0, 1, 1, new int[1]{9}},
        {'-', 1, 2, new int[2]{11, 15}},   {'-', 1, 2, new int[2]{13, 14}}};

    Puzzle puzzle = {4, new Cell[81]};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    // Fails removing inconsistent values from row.
    int row_domain[16] = {1,  2,  4,  4,   // 0b0001, 0b0010, 0b0100, 0b0100
                          14, 13, 15, 11,  // 0b1110, 0b1101, 0b1111, 0b1011
                          14, 13, 15, 11,  // 0b1110, 0b1101, 0b1111, 0b1011
                          14, 13, 15, 11}; // 0b1110, 0b1101, 0b1111, 0b1011
    // Initializes domain for each cell.
    for (int i = 0; i < 16; i++) {
        puzzle.grid[i].domain = row_domain[i];
    }
    assert(forward_checking(2, &puzzle) == 0);
    assert(puzzle.grid[3].domain == 0);

    // Fails removing inconsistent values from column.
    int col_domain[16] = {1,  14, 14, 14,  // 0b0001, 0b1110, 0b1110, 0b1110
                          2,  15, 15, 15,  // 0b0010, 0b1111, 0b1111, 0b1111
                          2,  13, 13, 13,  // 0b0010, 0b1101, 0b1101, 0b1101
                          14, 15, 15, 15}; // 0b1110, 0b1111, 0b1111, 0b1111
    // Initializes domain for each cell.
    for (int i = 0; i < 16; i++) {
        puzzle.grid[i].domain = col_domain[i];
    }
    assert(forward_checking(4, &puzzle) == 0);
    assert(puzzle.grid[5].domain == 13);
    assert(puzzle.grid[6].domain == 13);
    assert(puzzle.grid[7].domain == 13);
    assert(puzzle.grid[8].domain == 0);

    // Fails removing inconsistent values from cage.
    int cage_domain[16] = {1,  2,  4,  8,  // 0b0001, 0b0010, 0b0100, 0b1000
                           2,  13, 11, 7,  // 0b0010, 0b1101, 0b1011, 0b0111
                           12, 13, 11, 7,  // 0b1110, 0b1101, 0b1011, 0b0111
                           12, 13, 11, 7}; // 0b1110, 0b1101, 0b1011, 0b0111
    // Initializes domain for each cell.
    for (int i = 0; i < 16; i++) {
        puzzle.grid[i].domain = cage_domain[i];
    }
    assert(forward_checking(4, &puzzle) == 0);
    assert(puzzle.grid[6].domain == 9);
    assert(puzzle.grid[7].domain == 5);
    assert(puzzle.grid[8].domain == 0);

    // Tests a successful forward checking.
    int valid_domain[16] = {4,  8, 2,  1,   // 0b0100, 0b1000, 0b0010, 0b0001
                            1,  7, 13, 14,  // 0b0001, 0b0111, 0b1101, 0b1110
                            11, 7, 13, 14,  // 0b1011, 0b0111, 0b1101, 0b1110
                            11, 7, 13, 14}; // 0b1011, 0b0111, 0b1101, 0b1110
    // Initializes domain for each cell.
    for (int i = 0; i < 16; i++) {
        puzzle.grid[i].domain = valid_domain[i];
    }
    assert(forward_checking(4, &puzzle) == 1);
    assert(puzzle.grid[5].domain == 6);
    assert(puzzle.grid[6].domain == 12);
    assert(puzzle.grid[8].domain == 10);
    assert(puzzle.grid[12].domain == 10);
}

void
test_four_by_four() {
    Cage cages[8] = {
        {'+', 10, 3, new int[3]{0, 1, 5}}, {'-', 1, 2, new int[2]{2, 3}},
        {'+', 7, 3, new int[3]{4, 8, 12}}, {'-', 1, 2, new int[2]{6, 10}},
        {0, 2, 1, new int[1]{7}},          {0, 1, 1, new int[1]{9}},
        {'-', 1, 2, new int[2]{11, 15}},   {'-', 1, 2, new int[2]{13, 14}}};

    Puzzle puzzle = {4, new Cell[81]};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].domain = 0x1ff;
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    Solution solution = {0, {0}};
    int is_solvable = recursive_backtracking(&solution, &puzzle);
    assert(is_solvable == 1);
    std::cout << "Solution:" << std::endl;
    // Prints out solution.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << solution.assignment[i * 4 + j] << " ";
        }
        std::cout << std::endl;
    }
}

void
test_six_by_six() {
    Cage cages[18] = {
        {'-', 5, 2, new int[2]{0, 6}},   {'-', 2, 2, new int[2]{1, 2}},
        {'+', 8, 2, new int[2]{3, 9}},   {'+', 7, 2, new int[2]{4, 10}},
        {'-', 1, 2, new int[2]{5, 11}},  {'-', 2, 2, new int[2]{7, 13}},
        {'-', 3, 2, new int[2]{8, 14}},  {'-', 2, 2, new int[2]{12, 18}},
        {'+', 7, 2, new int[2]{15, 21}}, {'+', 13, 3, new int[3]{16, 22, 28}},
        {0, 1, 1, new int[1]{17}},       {'+', 10, 2, new int[2]{19, 20}},
        {'+', 7, 2, new int[2]{23, 29}}, {'-', 2, 2, new int[2]{24, 30}},
        {'-', 1, 2, new int[2]{25, 31}}, {'-', 1, 2, new int[2]{26, 27}},
        {'+', 7, 2, new int[2]{32, 33}}, {'-', 1, 2, new int[2]{34, 35}}};

    Puzzle puzzle = {6, new Cell[81]};
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].domain = 0x1ff;
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    Solution solution = {0, {0}};
    int is_solvable = recursive_backtracking(&solution, &puzzle);
    assert(is_solvable == 1);
    std::cout << "Solution:" << std::endl;

    // Prints out solution.
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            std::cout << solution.assignment[i * 6 + j] << " ";
        }
        std::cout << std::endl;
    }
}

void
test_invalid_four_by_four() {
    Cage cages[8] = {
        {'+', 10, 3, new int[3]{0, 1, 5}}, {'-', 1, 2, new int[2]{2, 3}},
        {'+', 8, 3, new int[3]{4, 8, 12}}, {'-', 1, 2, new int[2]{6, 10}},
        {0, 2, 1, new int[1]{7}},          {0, 1, 1, new int[1]{9}},
        {'-', 1, 2, new int[2]{11, 15}},   {'-', 1, 2, new int[2]{13, 14}}};

    Puzzle puzzle = {4, new Cell[81]};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < cages[i].num_cell; j++) {
            puzzle.grid[cages[i].positions[j]].domain = 0x1ff;
            puzzle.grid[cages[i].positions[j]].cage = &(cages[i]);
        }
    }

    Solution solution = {0, {0}};
    int is_solvable = recursive_backtracking(&solution, &puzzle);
    assert(is_solvable == 0);
    std::cout << "The puzzle is not solvable." << std::endl;
}

int
main() {
    test_is_complete();
    test_get_unassigned_position();
    test_forward_checking();
    test_four_by_four();
    test_six_by_six();
    test_invalid_four_by_four();
    return 0;
}

/*
 * Functions from lab 7 and more helper functions.
 */

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
        domain = domain >> (low_bits - 1) << (low_bits - 1);
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

// Returns an integer as possible domain for the given position in cage.
// This domain is necessary but not sufficient given current constraints.
int
get_domain_for_cell(int position, const Puzzle *puzzle) {
    int valid_domain = 0x0;
    if (puzzle->grid[position].cage->operation == 0) {
        valid_domain = 0x1 << (puzzle->grid[position].cage->target - 1);
    } else if (puzzle->grid[position].cage->operation == '+') {
        int remain_target = puzzle->grid[position].cage->target;
        int remain_cell = puzzle->grid[position].cage->num_cell;
        int domain_union = puzzle->grid[position].domain;
        for (int i = 0; i < puzzle->grid[position].cage->num_cell; i++) {
            int pos = puzzle->grid[position].cage->positions[i];
            if (pos != position &&
                is_single_value_domain(puzzle->grid[pos].domain)) {
                remain_target -=
                    convert_highest_bit_to_int(puzzle->grid[pos].domain);
                remain_cell -= 1;
            } else {
                domain_union |= puzzle->grid[pos].domain;
            }
        }
        valid_domain =
            get_domain_for_addition(remain_target, remain_cell, domain_union);
    } else {
        int other_pos = puzzle->grid[position].cage->positions[0] ^
                        puzzle->grid[position].cage->positions[1] ^ position;
        valid_domain = get_domain_for_subtraction(
            puzzle->grid[position].cage->target, puzzle->grid[position].domain,
            puzzle->grid[other_pos].domain);
    }
    return valid_domain;
}

// Helper function that copies a Puzzle object (deep copy the domain).
void
clone(const Puzzle *orig, Puzzle *clone) {
    clone->size = orig->size;
    memcpy(clone->grid, orig->grid, orig->size * orig->size * sizeof(Cell));
}
