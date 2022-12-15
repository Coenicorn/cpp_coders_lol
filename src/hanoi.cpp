#include <iostream>
#include <vector>

typedef std::vector<std::vector<int>> tower_t;

char pegNames[3] = {65, 66, 67};

void moveTower(tower_t &tower, int height, int source, int target, int helper)
{
    if (height == 0) return;

    // move height - 1 disks to helper
    moveTower(tower, height-1, source, helper, target);

    // move disk tower[height] to target
    int currentDisk = tower[source].back();
    tower[target].push_back(currentDisk);
    tower[source].pop_back();

    // log move
    std::cout << "Move disk " << currentDisk << " from " << pegNames[source] << " to " << pegNames[target] << ".\n";

    // move tower from helper to target
    moveTower(tower, height-1, helper, target, source);
}

int main(void)
{
    
    tower_t tower;
    int nDisks;

    // initial disk configuration
    std::cout << "How many disks should the tower consist of? ";
    std::cin >> nDisks;

    if (std::cin.fail() || nDisks < 1)
    {
        std::cout << "invalid input.\n";
        return 1;
    }

    // damn you and your grading program ;)
    std::cout << "\n";
    
    for (int i = 0; i < 3; i++)
    {
        std::vector<int> v;
        tower.push_back(v);
    }

        // fill tower with initial configuration of disks

    for (int i = nDisks; i > 0; i--)
    {
        tower[0].push_back(i);
    }


    moveTower(tower, nDisks, 0, 2, 1);

    return 0;
}