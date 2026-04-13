#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>

std::vector<std::vector<int>> maze();
int main()
{
    std::vector<std::vector<int>> grid = maze();
    std::stack<std::pair<int, int>> s;
    std::pair<int, int> pos = {0, 1};
    int size = 31;
    int i = 1;
    s.push(pos);
    do
    {
        pos = s.top();
        grid.at(pos.first).at(pos.second) = i; // Mark as visited
        grid.at(pos.first).at(pos.second) = i++;
        if (pos.first > 0 && grid.at(pos.first - 1).at(pos.second) == 0)
            pos.first -= 1;
        else if (pos.first < size - 1 && grid.at(pos.first + 1).at(pos.second) == 0)
            pos.first += 1;
        else if (pos.second > 0 && grid.at(pos.first).at(pos.second - 1) == 0)
            pos.second -= 1;
        else if (pos.second < size - 1 && grid.at(pos.first).at(pos.second + 1) == 0)
            pos.second += 1;
        s.push(pos);
    }
    while (pos != std::make_pair(size - 1, size - 2));
    std::vector<std::pair<int, int>> neighbors;
    while (pos != std::make_pair(0, 1))
    {
        if (pos.first > 0 && grid.at(pos.first - 1).at(pos.second) > 0)
            neighbors.push_back({pos.first - 1, pos.second});
        if (pos.first < size - 1 && grid.at(pos.first + 1).at(pos.second) > 0)
            neighbors.push_back({pos.first + 1, pos.second});
        if (pos.second > 0 && grid.at(pos.first).at(pos.second) > 0)
            neighbors.push_back({pos.first, pos.second - 1});
        if (pos.second < size - 1 && grid.at(pos.first).at(pos.second + 1) > 0)
            neighbors.push_back({pos.first, pos.second + 1});
        grid.at(pos.first).at(pos.second) = -2;
        pos = std::max_element(neighbors.begin(), neighbors.end());
    }
    for (const auto &row : grid)
    {
        for (int cell : row)
        {
            std::cout << (cell == 1 ? "##" : (cell == 2 ? ".." : "  "));
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<int>> maze()
{
    const int size = 31; // Using an odd number helps with wall/path alignment
    std::vector<std::vector<int>> grid(size, std::vector<int>(size, 1));

    // Initialize everything as a wall (1)
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            grid.at(i).at(j) = 1;

    std::stack<std::pair<int, int>> s;

    // Start at a random odd coordinate
    int startX = 1, startY = 1;
    grid.at(startX).at(startY) = 0;
    s.push({startX, startY});
    std::random_device rd;
    std::mt19937 g(rd());

    while (!s.empty())
    {
        auto [x, y] = s.top();

        // Check all 4 neighbors at a distance of 2
        std::vector<int> dirs = {1, 2, 3, 4};
        std::shuffle(dirs.begin(), dirs.end(), g);

        bool moved = false;
        for (int dir : dirs)
        {
            int nx = x, ny = y;
            int wx = x, wy = y; // Wall between current and next

            if (dir == 1)
            {
                nx = x + 2;
                wx = x + 1;
            } // Down
            else if (dir == 2)
            {
                nx = x - 2;
                wx = x - 1;
            } // Up
            else if (dir == 3)
            {
                ny = y + 2;
                wy = y + 1;
            } // Right
            else if (dir == 4)
            {
                ny = y - 2;
                wy = y - 1;
            } // Left

            // Check boundaries and if the destination is still a wall
            if (nx > 0 && nx < size - 1 && ny > 0 && ny < size - 1 && grid.at(nx).at(ny) == 1)
            {
                grid.at(wx).at(wy) = 0; // Break wall
                grid.at(nx).at(ny) = 0; // Mark path
                s.push({nx, ny});
                moved = true;
                break; // Move to the new cell immediately
            }
        }

        if (!moved)
        {
            s.pop(); // Nowhere to go? Backtrack.
        }
    }
    grid.at(0).at(1) = 0;               // Entrance
    grid.at(size - 1).at(size - 2) = 0; // Exit

    return grid;
}