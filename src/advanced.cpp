#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include "client.h"
#include "generator.h"
#include "server.h"

bool batch_mode = false;

/**
 * @brief The implementation of function Execute
 * @details Use it only when trying advanced task. Do NOT modify it before discussing with TA.
 */
void Execute(int row, int column, int type) {
  std::string str;
  if (type == 0) {
    VisitBlock(row, column);
  } else if (type == 1) {
    MarkMine(row, column);
  } else if (type == 2) {
    AutoExplore(row, column);
  } else {
    std::cerr << "Invalid type = " << type << std::endl;
    exit(-1);
  }
  if (game_state != 0) {
    // PrintMap(); // this line may help you debug
    ExitGame();
    if (batch_mode) {
      return;
    }
  }
  std::ostringstream oss;
  std::streambuf *old_output_buffer = std::cout.rdbuf();
  std::cout.rdbuf(oss.rdbuf());
  // Here, we redirect the output stream to the string stream.
  // By this way the output of PrintMap() would be stored in the string.
  // If you do not understand, you can try to compare it with freopen, which redirect the output stream to a file.
  PrintMap();
  std::cout.rdbuf(old_output_buffer);  // Restore the output buffer
  str = oss.str();                     // Read the output
  std::istringstream iss(str);         // Redirect the input to the string, which stores the output recently
  std::streambuf *old_input_buffer = std::cin.rdbuf();
  std::cin.rdbuf(iss.rdbuf());
  ReadMap();
  std::cin.rdbuf(old_input_buffer);
  // PrintMap(); // These two lines may help you debug
  // std::cout << std::endl;
}

/**
 * Running a single test.
 * You should manually input the data.
 */
void TestSingle() {
  InitMap();
  InitGame();
  while (true) {
    Decide(); // Exit() will be called in this function
    if (batch_mode && game_state != 0) {
      break;
    }
  }
}

/**
 * Running test many times (to simulate real tests).
 * You just need to input rows, columns, mine_count and random seed.
 *
 * @note If you want to use this function, you should modify the program a little bit:
 *   - Modify your server so that it supports dealing with multiple maps in a single run;
 *   - Remove the line "exit(0)" in function ExitGame(). (Or your program may exit immediately after running a single test).
 * The special judger on OJ will be a special version of server.h.
 * We'll do some optimizations to it so that it will be faster.
 */
void TestBatch() {
  batch_mode = true;
  int rows, columns, mine_count, min_dist;
  uint64_t seed;
  std::cin >> rows >> columns >> mine_count >> seed >> min_dist;
  InitSeed(seed);
  for (int i = 0; i < 50; ++i) {
    std::string str;
    std::ostringstream oss;
    std::streambuf *old_output_buffer = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    GenerateMap(rows, columns, mine_count, min_dist);
    std::cout.rdbuf(old_output_buffer);  // Restore the output buffer
    str = oss.str();                     // Read the output
    std::istringstream iss(str);         // Redirect the input to the string, which stores the output recently
    std::streambuf *old_input_buffer = std::cin.rdbuf();
    std::cin.rdbuf(iss.rdbuf());
    TestSingle();
    std::cin.rdbuf(old_input_buffer);
    game_state = 0;
  }
}

int main() {
  TestSingle();
  // TestBatch();
}
