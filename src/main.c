#include "manager.h"

Manager manager;

int main() {
    Action action = GameMenu(&manager);
    if(action == Exit)
        return 0;
    else if(action == Play2v2) {
        manager.tank_count = 2;
        InitializeGame(&manager);
    } else if(action == Play3v3) {
        manager.tank_count = 3;
        InitializeGame(&manager);
    }
}
