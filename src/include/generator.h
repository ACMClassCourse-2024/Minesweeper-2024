/**
 * This header file is used to generate a map for a batch test. (The judger will use a similar one)
 * You don't need to modify this file, nor do you have to understand this file.
 * If you do want to understand how maps are generated, you can focus on the GenerateMap() function.
 * (But there are some special syntax and semantics that you haven't learnt)
 */
#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>

inline std::mt19937_64 gen;

/**
 * Select a random number between [min, max]. All numbers have the same possibility to be selected.
 */
inline int Random(int min, int max, std::mt19937_64 &gen) {
  std::uniform_int_distribution<> dist(min, max);
  return dist(gen);
}

/**
 * Calculate the Manhattan distance of two blocks.
 * When generating a map, blocks too close to the initial step MUST NOT be mines.
 */
inline int Dist(int r0, int c0, int r1, int c1) {
  return std::abs(r0 - r1) + std::abs(c0 - c1);
}

/**
 * Initialize the random seed of a random generator.
 */
inline void InitSeed(uint64_t random_seed) {
  gen.seed(random_seed);
}

/**
 * Generate a map.
 */
inline void GenerateMap(int rows, int columns, int mine_count, int min_dist) {
  std::vector<std::pair<int, int>> available_block;
  bool map[35][35];
  int row0 = Random(1, rows - 2, gen);
  int col0 = Random(1, columns - 2, gen);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      map[i][j] = false;
      if (Dist(row0, col0, i, j) <= min_dist) {
        continue;
      }
      available_block.emplace_back(i, j);
    }
  }
  for (int i = 0; i < mine_count; ++i) {
    auto cnt = available_block.size();
    auto mine_pos = Random(0, static_cast<int>(cnt) - 1, gen);
    auto &mine = available_block[mine_pos];
    map[mine.first][mine.second] = true;
    available_block.erase(available_block.begin() + mine_pos);
  }
  std::cout << rows << "  " << columns << std::endl;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      std::cout << (map[i][j] ? 'X' : '.');
    }
    std::cout << std::endl;
  }
  std::cout << row0 << " " << col0 << std::endl;
}

#endif