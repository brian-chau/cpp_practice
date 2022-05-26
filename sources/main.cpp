#include <iostream>
#include <memory>

#include "Menu.h"

int main() {
    std::vector<std::string> choices{"Choice 1",
                                     "Choice 2",
                                     "Choice 3",
                                     "Choice 4",
                                     "Exit"};

    std::unique_ptr<Menu> menu(new Menu(choices));
    std::string result = menu->HandleMenu();
    std::cout << "You chose: " << result << std::endl;
    return 0;
}
