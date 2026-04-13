#include <iostream>
#include <vector>
#include <random>
#include <stack>
namespace island
{
    int count(std::vector<std::vector<int>> grid);
    void sink(std::vector<std::vector<int>> &g, int r, int c);
}

int main(int argc, char *argv[])
{
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";

    int size = 30;

    if (argc < 2)
    {
        std::cerr << "Error: Use ./main <number>" << std::endl;
        return 1;
    }
    try
    {
        size = std::stoi(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: needs to be a number." << std::endl;
        return 1;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    kt std::bernoulli_distribution d(5 / (float)10);
    std::vector<std::vector<int>> grid(size, std::vector<int>(size));
    
    int temp;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = d(gen) ? 1 : 0;
        }
    }
    std::cout << island::count(grid) << std::endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            temp = grid[i][j];
            std::cout << (temp ? RED : BLUE) << temp << " ";
            std::cout << RESET;
        }
        std::cout << std::endl;
    }
}

int island::count(std::vector<std::vector<int>> grid)
{
    int count = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid.size(); j++)
        {
            if (grid[i][j] == 1)
            {
                count++;
                sink(grid, i, j);
            }
        }
    }
    return count;
}
void island::sink(std::vector<std::vector<int>> &g, int r, int c)
{
    int size = g.size();
    std::stack<std::pair<int, int>> pixels;
    pixels.push({r, c});
    while (!pixels.empty())
    {
        std::pair<int, int> current = pixels.top();
        pixels.pop();

        int row = current.first;
        int col = current.second;

        if (row < 0 || row >= size || col < 0 || col >= size || g[row][col] == 0)
        {
            continue;
        }

        g[row][col] = 0;

        pixels.push({row + 1, col});
        pixels.push({row - 1, col});
        pixels.push({row, col + 1});
        pixels.push({row, col - 1});
    }
}
