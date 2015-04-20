#include <vector>
#include <string>
#include <iostream>

bool TryKuhn(int vert, const std::vector< std::vector<int> >& adjList, std::vector<int>& mt,
             std::vector<int>& used, int& timer)
{
  if (used[vert] == timer)
    return false;
  used[vert] = timer;
  int size = adjList[vert].size();
  for (int it = 0; it < size; ++it)
  {
    int to = adjList[vert][it];
    if (mt[to] == -1 || TryKuhn(mt[to], adjList, mt, used, timer))
    {
      mt[to] = vert;
      return true;
    }
  }
  return false;
}

inline bool IsEmpty(int it, int jt, int rows, int cols, const std::vector<std::string>& board)
{
  return (0 <= it && it < rows && 0 <= jt && jt < cols && board[it][jt] == '*');
}

int main()
{
  int rows = 0;
  int cols = 0;
  int aPrice = 0;
  int bPrice = 0;
  std::cin >> rows >> cols >> aPrice >> bPrice;
  
  std::vector<std::string> board;
  board.resize(rows);
  getline(std::cin, board[0]);
  for (int i = 0; i < rows; ++i)
  {
    getline(std::cin, board[i]);
    board[i].resize(cols);
  }

    int iDelta[4] = { 1, -1, 0,  0 };
    int jDelta[4] = { 0,  0, 1, -1 };

  std::vector< std::vector<int> > adjList;
  adjList.resize(rows * cols);

  int empty = 0;
  for (int iCur = 0; iCur < rows; ++iCur)
  {
    for (int jCur = 0; jCur < cols; ++jCur)
    {
      if ((iCur + jCur) % 2 != 0 && board[iCur][jCur] == '*')
        for (int kt = 0; kt < 4; ++kt)
        {
          int iNeigh = iCur + iDelta[kt];
          int jNeigh = jCur + jDelta[kt];
          if (IsEmpty(iNeigh, jNeigh, rows, cols, board))
            adjList[iCur * cols +jCur].push_back(iNeigh * cols + jNeigh);
        }
      if (board[iCur][jCur] == '*')
        ++empty;
    }
  }

  std::vector<int> used;
  std::vector<int> mt;

  if (aPrice >= 2 * bPrice)
  {
    std::cout << bPrice * empty << std::endl;
  }
  else
  {
    mt.assign(rows * cols, -1);
    used.assign(rows * cols, -1);
  }

  int timer = 0;
  for (int vert = 0; vert < rows * cols; ++vert)
  {
    ++timer;
    TryKuhn(vert, adjList, mt, used, timer);
  }

  int tiles = 0;
  for (int to = 0; to < rows * cols; ++to)
  {
    if (mt[to] != -1)
      ++tiles;
  }

  std::cout << tiles * aPrice + (empty - 2 * tiles) * bPrice << std::endl;
}
