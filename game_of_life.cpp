#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

int row = 40;
int column = 100;
#define refresh_rate 100 //time in milliseconds after which next generation is produced

std::vector<std::vector<int>> slate(row, std::vector<int>(column, 0));
/* The slate initially has all values zero.
 * But otherwise, the following values correspond to the foolowing statess:
 * 1 : Live cell.
 * 2 : Cell is dead. But it was previously inhabitated.
 * 3 : Cell has not yet been inhabitated.
 */

void init_slate();
void display_slate();
void next_gen();
bool validateArgs(int argc, char **argv);
void init_slate_from_file(char *path);

int main(int argc, char **argv)
{
    if (argc > 1 && validateArgs(argc, argv))
    {
        init_slate_from_file(argv[1]);
    }
    else
    {
        init_slate();
    }
    display_slate();
    int generation = 1;
    std::cout << "Generation: " << generation << std::endl;
    clock_t start = clock();
    while (true)
    {
        if ((clock() - start) / CLOCKS_PER_SEC > refresh_rate / 1000)
        {
            ++generation;
            start = clock();
            system("clear");
            next_gen();
            display_slate();
            std::cout << "Generation: " << generation << std::endl;
        }
    }
    return 0;
}

void init_slate()
{
    srand(time(NULL));
    slate.resize(row);
    for (int i = 0; i < row; i++)
    {
        slate[i].resize(column);
        for (int j = 0; j < column; j++)
            if (rand() % 2)
                slate[i][j] = 1; // Live state
            else
                slate[i][j] = 3; // Inhabitated state
    }
}

void display_slate()
{
    for (int i = 0; i < column + 2; i++)
        std::cout << "-";
    std::cout << std::endl;
    for (int i = 0; i < row; i++)
    {
        std::cout << '|';
        for (int j = 0; j < column; j++)
        {
            if (slate[i][j] == 1)
                std::cout << "*";
            else if (slate[i][j] == 2)
                std::cout << ".";
            else if (slate[i][j] == 3)
                std::cout << " ";
        }
        std::cout << "|" << std::endl;
    }
    for (int i = 0; i < column + 2; i++)
        std::cout << "-";
    std::cout << std::endl;
}

void next_gen()
{
    std::vector<std::vector<int>> val_neighbour(row, std::vector<int>(column, 0));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            int neighbours = 0,
                left = (j - 1 + column) % column,
                right = (j + 1 + column) % column,
                top = (i - 1 + row) % row,
                bottom = (i + 1 + row) % row;
            if (slate[top][left] == 1)
                ++neighbours;
            if (slate[top][j] == 1)
                ++neighbours;
            if (slate[top][right] == 1)
                ++neighbours;
            if (slate[i][left] == 1)
                ++neighbours;
            if (slate[i][right] == 1)
                ++neighbours;
            if (slate[bottom][left] == 1)
                ++neighbours;
            if (slate[bottom][j] == 1)
                ++neighbours;
            if (slate[bottom][right] == 1)
                ++neighbours;
            val_neighbour[i][j] = neighbours;
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {

            if (val_neighbour[i][j] > 3 && slate[i][j] == 1) // rule 1
                slate[i][j] = 2;
            if (val_neighbour[i][j] < 2 && slate[i][j] == 1) // rule 2
                slate[i][j] = 2;
            if ((val_neighbour[i][j] == 2 || val_neighbour[i][j] == 3) && slate[i][j] == 1) // rule 3
                slate[i][j] = 1;
            if (val_neighbour[i][j] == 3 && (slate[i][j] == 2 || slate[i][j] == 3)) // rule 4
                slate[i][j] = 1;
        }
    }
}

bool validateArgs(int argc, char **argv)
{
    if (argc > 2)
    {
        return false;
    }
    std::ifstream file(argv[1]);
    if (!file)
    {
        return false;
    }
    return true;
}

void init_slate_from_file(char *path)
{
    std::ifstream file(path);
    std::string line;
    std::vector<std::string> vec_lines;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vec_lines.push_back(line);
        }
        file.close();
    }

    int min_str_size = INT8_MAX;
    for (auto str : vec_lines)
    {
        if (min_str_size > str.size())
        {
            min_str_size = str.size();
        }
    }

    row = vec_lines.size();
    column = min_str_size;
    slate.resize(row);
    for (int i = 0; i < row; ++i)
    {
        slate[i].resize(column);
        for (int j = 0; j < column; ++j)
        {
            if (vec_lines[i][j] == '1')
            {
                slate[i][j] = 1;
            }
            else if (vec_lines[i][j] == '2')
            {
                slate[i][j] = 2;
            }
            else
            {
                slate[i][j] = 3;
            }
        }
    }
}