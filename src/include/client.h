#ifndef CLIENT_H
#define CLIENT_H

// #pragma GCC optimize(3)

#include <iostream>
#include <utility>
#include <vector>
#include <queue>

extern int rows;         // The count of rows of the game map.
extern int columns;      // The count of columns of the game map.
extern int total_mines;  // The count of mines of the game map.

// You MUST NOT use any other external variables except for rows, columns and total_mines.

struct visit_info
{
  int row;
  int column;
  int unvisited;
  int marked_count;
};

struct op_compare
{
  bool operator() (visit_info & a, visit_info & b) {
    return 0.34*a.marked_count-a.unvisited < 0.34*b.marked_count-b.unvisited;
  }
};

struct operation
{
  int row;
  int column;
  int type;
};



//Global variables

std::vector <std::vector<int>> cli_game_map;
std::vector <operation> immediate;
int remaining_mines;


std::vector<std::vector<int>> copy (std::vector<std::vector<int>> &map) {
  std::vector<std::vector<int>> new_map(map.size(), std::vector<int>(map[0].size()));
  for (int r=0; r<map.size(); r++) {
    new_map[r] = map[r];
  }
  return new_map;
}

bool check(std::vector<std::vector<int>> &map, int r, int c);
bool check_need(int r, int c);

bool assume (std::vector<std::vector<int>> &map, int r, int c, int type, int rec) {
  if (rec == 0) return true;
  map[r][c] = type;
  if (r > 0 && c > 0) {
    if (cli_game_map[r-1][c-1] >= 0) {
      if (!check(map, r-1, c-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (r > 0) {
    if (cli_game_map[r-1][c] >= 0) {
      if (!check(map, r-1, c)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (r > 0 && c < columns-1) {
    if (cli_game_map[r-1][c+1] >= 0) {
      if (!check(map, r-1, c+1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (c > 0) {
    if (cli_game_map[r][c-1] >= 0) {
      if (!check(map, r, c-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (c < columns-1) {
    if (cli_game_map[r][c+1] >= 0) {
      if (!check(map, r, c+1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (r < rows-1 && c > 0) {
    if (cli_game_map[r+1][c-1] >= 0) {
      if (!check(map, r+1, c-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (r < rows-1) {
    if (cli_game_map[r+1][c] >= 0) {
      if (!check(map, r+1, c)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (r < rows-1 && c < columns-1) {
    if (cli_game_map[r+1][c+1] >= 0) {
      if (!check(map, r+1, c+1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }

  if (check_need(r-1, c-1)) {
    if (!assume(map, r-1, c-1, -3, rec-1)) {
      if (!assume(map, r-1, c-1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r-1, c)) {
    if (!assume(map, r-1, c, -3, rec-1)) {
      if (!assume(map, r-1, c, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r-1, c+1)) {
    if (!assume(map, r-1, c+1, -3, rec-1)) {
      if (!assume(map, r-1, c+1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r, c-1)) {
    if (!assume(map, r, c-1, -3, rec-1)) {
      if (!assume(map, r, c-1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r, c+1)) {
    if (!assume(map, r, c+1, -3, rec-1)) {
      if (!assume(map, r, c+1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r+1, c-1)) {
    if (!assume(map, r+1, c-1, -3, rec-1)) {
      if (!assume(map, r+1, c-1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r+1, c)) {
    if (!assume(map, r+1, c, -3, rec-1)) {
      if (!assume(map, r+1, c, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }
  if (check_need(r+1, c+1)) {
    if (!assume(map, r+1, c+1, -3, rec-1)) {
      if (!assume(map, r+1, c+1, -1, rec-1)) {
        map[r][c] = -4;
        return false;
      }
    }
  }

  map[r][c] = -4;
  return true;
}

bool check_need (int r, int c) {
  if (r < 0 || r >= rows || c < 0 || c >= columns) return false;
  int count = 0, marked_count = 0;
  if (r > 0 && c > 0) {
    if (cli_game_map[r-1][c-1] > 0) count++;
  }
  if (r > 0) {
    if (cli_game_map[r-1][c] > 0) count++;
  }
  if (r > 0 && c < columns-1) {
    if (cli_game_map[r-1][c+1] > 0) count++;
  }
  if (c > 0) {
    if (cli_game_map[r][c-1] > 0) count++;
  }
  if (c < columns-1) {
    if (cli_game_map[r][c+1] > 0) count++;
  }
  if (r < rows-1 && c > 0) {
    if (cli_game_map[r+1][c-1] > 0) count++;
  }
  if (r < rows-1) {
    if (cli_game_map[r+1][c] > 0) count++;
  }
  if (r < rows-1 && c < columns-1) {
    if (cli_game_map[r+1][c+1] > 0) count++;
  }
  if (count > 0) {
    return true;
  }
  return false;
}

bool check (std::vector<std::vector<int>> &map, int r, int c) {
  int count = 0, marked_count = 0;
  if (r > 0 && c > 0) {
    if (map[r-1][c-1] == -3) marked_count++;
    if (map[r-1][c-1] == -4) count++;
  }
  if (r > 0) {
    if (map[r-1][c] == -3) marked_count++;
    if (map[r-1][c] == -4) count++;
  }
  if (r > 0 && c < columns-1) {
    if (map[r-1][c+1] == -3) marked_count++;
    if (map[r-1][c+1] == -4) count++;
  }
  if (c > 0) {
    if (map[r][c-1] == -3) marked_count++;
    if (map[r][c-1] == -4) count++;
  }
  if (c < columns-1) {
    if (map[r][c+1] == -3) marked_count++;
    if (map[r][c+1] == -4) count++;
  }
  if (r < rows-1 && c > 0) {
    if (map[r+1][c-1] == -3) marked_count++;
    if (map[r+1][c-1] == -4) count++;
  }
  if (r < rows-1) {
    if (map[r+1][c] == -3) marked_count++;
    if (map[r+1][c] == -4) count++;
  }
  if (r < rows-1 && c < columns-1) {
    if (map[r+1][c+1] == -3) marked_count++;
    if (map[r+1][c+1] == -4) count++;
  }
  if (marked_count > cli_game_map[r][c]) return false;
  if (marked_count + count < cli_game_map[r][c]) return false;
  return true;
}

/**
 * @brief The definition of function Execute(int, int, bool)
 *
 * @details This function is designed to take a step when player the client's (or player's) role, and the implementation
 * of it has been finished by TA. (I hope my comments in code would be easy to understand T_T) If you do not understand
 * the contents, please ask TA for help immediately!!!
 *
 * @param r The row coordinate (0-based) of the block to be visited.
 * @param c The column coordinate (0-based) of the block to be visited.
 * @param type The type of operation to a certain block.
 * If type == 0, we'll execute VisitBlock(row, column).
 * If type == 1, we'll execute MarkMine(row, column).
 * If type == 2, we'll execute AutoExplore(row, column).
 * You should not call this function with other type values.
 */
void Execute(int r, int c, int type);

/**
 * @brief The definition of function InitGame()
 *
 * @details This function is designed to initialize the game. It should be called at the beginning of the game, which
 * will read the scale of the game map and the first step taken by the server (see README).
 */
void InitGame() {
  // TODO (student): Initialize all your global variables!


  // init global
  cli_game_map = std::vector<std::vector<int>>(rows, std::vector<int>(columns));
  immediate = std::vector <operation>();


  int first_row, first_column;
  std::cin >> first_row >> first_column;
  Execute(first_row, first_column, 0);
}

/**
 * @brief The definition of function ReadMap()
 *
 * @details This function is designed to read the game map from stdin when playing the client's (or player's) role.
 * Since the client (or player) can only get the limited information of the game map, so if there is a 3 * 3 map as
 * above and only the block (2, 0) has been visited, the stdin would be
 *     ???
 *     12?
 *     01?
 */
void ReadMap() {
  // TODO (student): Implement me!
  char b;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      std::cin >> b;
      if (b == '?') {
        cli_game_map[r][c] = -4;
      }
      else if (b == '@') {
        cli_game_map[r][c] = -3;
      }
      else {
        cli_game_map[r][c] = b - '0';
      }
    }
  }
}

/**
 * @brief The definition of function Decide()
 *
 * @details This function is designed to decide the next step when playing the client's (or player's) role. Open up your
 * mind and make your decision here!
 */
void Decide() {
  // TODO (student): Implement me!
  // while (true) {
  //   Execute(0, 0);
  //   记得Excute之后Return;
  // }
  std::priority_queue<visit_info, std::vector<visit_info>, op_compare> visit;

  if (immediate.size() > 0) {
    operation imme = immediate.back();
    immediate.pop_back();
    Execute(imme.row, imme.column, imme.type);
    return;
  }

  for (int r=0; r<rows; r++) {
    for (int c=0; c< columns; c++) {
      int count = 0, marked_count = 0;
      if (r > 0 && c > 0) {
        if (cli_game_map[r-1][c-1] == -3) marked_count++;
        if (cli_game_map[r-1][c-1] == -4) count++;
      }
      if (r > 0) {
        if (cli_game_map[r-1][c] == -3) marked_count++;
        if (cli_game_map[r-1][c] == -4) count++;
      }
      if (r > 0 && c < columns-1) {
        if (cli_game_map[r-1][c+1] == -3) marked_count++;
        if (cli_game_map[r-1][c+1] == -4) count++;
      }
      if (c > 0) {
        if (cli_game_map[r][c-1] == -3) marked_count++;
        if (cli_game_map[r][c-1] == -4) count++;
      }
      if (c < columns-1) {
        if (cli_game_map[r][c+1] == -3) marked_count++;
        if (cli_game_map[r][c+1] == -4) count++;
      }
      if (r < rows-1 && c > 0) {
        if (cli_game_map[r+1][c-1] == -3) marked_count++;
        if (cli_game_map[r+1][c-1] == -4) count++;
      }
      if (r < rows-1) {
        if (cli_game_map[r+1][c] == -3) marked_count++;
        if (cli_game_map[r+1][c] == -4) count++;
      }
      if (r < rows-1 && c < columns-1) {
        if (cli_game_map[r+1][c+1] == -3) marked_count++;
        if (cli_game_map[r+1][c+1] == -4) count++;
      }
      if (count>0 && count == cli_game_map[r][c] - marked_count) {
        if (r > 0 && c > 0) {
          if (cli_game_map[r-1][c-1] == -4) {
            immediate.push_back(operation{r-1, c-1, 1});
          }
        }
        if (r > 0) {
          if (cli_game_map[r-1][c] == -4) {
            immediate.push_back(operation{r-1, c, 1});
          }
        }
        if (r > 0 && c < columns-1) {
          if (cli_game_map[r-1][c+1] == -4) {
            immediate.push_back(operation{r-1, c+1, 1});
          }
        }
        if (c > 0) {
          if (cli_game_map[r][c-1] == -4) {
            immediate.push_back(operation{r, c-1, 1});
          }
        }
        if (c < columns-1) {
          if (cli_game_map[r][c+1] == -4) {
            immediate.push_back(operation{r, c+1, 1});
          }
        }
        if (r < rows-1 && c > 0) {
          if (cli_game_map[r+1][c-1] == -4) {
            immediate.push_back(operation{r+1, c-1, 1});
          }
        }
        if (r < rows-1) {
          if (cli_game_map[r+1][c] == -4) {
            immediate.push_back(operation{r+1, c, 1});
          }
        }
        if (r < rows-1 && c < columns-1) {
          if (cli_game_map[r+1][c+1] == -4) {
            immediate.push_back(operation{r+1, c+1, 1});
          }
        }
      }
      if (immediate.size() > 0) {
        operation imme = immediate.back();
        immediate.pop_back();
        Execute(imme.row, imme.column, imme.type);
        return;
      }
      if (marked_count==cli_game_map[r][c]&&count>0) {
        Execute(r, c, 2);
        return;
      }

      if (cli_game_map[r][c] == -4) {
        visit.push(visit_info({r, c, count, marked_count}));
      }
    }
  }
  int size = visit.size();
  visit_info root;
  for (int i=0; i<std::min(size, 4); i++) {
    root = visit.top();
    visit.pop();
    auto temp_map = copy(cli_game_map);
    if (!assume(temp_map, root.row, root.column, -3, 6)) {
      Execute(root.row, root.column, 0);
      return;
    }
    if (!assume(temp_map, root.row, root.column, -1, 6)) {
      Execute(root.row, root.column, -1);
      return;
    }
  }

  if (!visit.empty()) {
    root = visit.top();
    Execute(root.row, root.column, 0);
    return;
  }

  if (size > 0) {
    Execute(root.row, root.column, 0);
    return;
  }

  Execute(0, 0, 2);
  return;
}

#endif