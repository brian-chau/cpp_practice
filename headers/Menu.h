#include <ncurses.h>

#include <string>
#include <vector>

class Menu {
   public:
    Menu(std::vector<std::string> choices);
    ~Menu();
    std::string HandleMenu();
    void PrintMenu();

   private:
    std::vector<std::string> m_Choices;
    unsigned int m_nChoices;
    WINDOW *m_MenuWin;
    unsigned int m_Highlight;
};