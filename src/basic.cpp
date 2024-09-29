#include <iostream>

#include "server.h"

/**
 * This is the main function of the game. You don't need to modify it.
 * Just finish server.h and run!
 */
int main() {
  InitMap();
  PrintMap();
  while (true) {
    int pos_x, pos_y, type;
    // Read the coordinate and operation type. 0 for VisitBlock(x, y), 1 for MarkMine(x, y) and 2 for AutoExplore(x, y)
    std::cin >> pos_x >> pos_y >> type;
    if (type == 0) {
      VisitBlock(pos_x, pos_y);
    } else if (type == 1) {
      MarkMine(pos_x, pos_y);
    } else if (type == 2) {
      AutoExplore(pos_x, pos_y);
    }
    PrintMap();
    if (game_state != 0) {
      ExitGame();
    }
  }
}
