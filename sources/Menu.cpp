#include "Menu.h"

#include <stdio.h>

#define WIDTH 30
#define HEIGHT 10
Menu::Menu(std::vector<std::string> choices)
    : m_Choices(choices), m_nChoices(choices.size()), m_MenuWin(NULL), m_Highlight(1) {
}

Menu::~Menu() {
}

std::string Menu::HandleMenu() {
    int choice(0);
    int c;

    initscr();
    clear();
    noecho();
    cbreak(); /* Line buffering disabled. pass on everything */
    unsigned int startx = (80 - WIDTH) / 2;
    unsigned int starty = (24 - HEIGHT) / 2;

    m_MenuWin = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(m_MenuWin, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    PrintMenu();
    while (1) {
        c = wgetch(m_MenuWin);
        switch (c) {
            case KEY_UP:
                if (m_Highlight == 1) {
                    m_Highlight = m_nChoices;
                } else {
                    --m_Highlight;
                }
                break;
            case KEY_DOWN:
                if (m_Highlight == m_nChoices) {
                    m_Highlight = 1;
                } else {
                    ++m_Highlight;
                }
                break;
            case 10:
                choice = m_Highlight;
                break;
            default:
                printf("\nCharacter pressed is = %3d Hopefully it can be printed as '%c'\n", c, c);
                refresh();
                break;
        }
        PrintMenu();
        if (choice != 0) { /* User did a choice come out of the infinite loop */
            break;
        }
    }
    clrtoeol();
    refresh();
    endwin();

    return m_Choices[choice - 1];
}

void Menu::PrintMenu() {
    box(m_MenuWin, 0, 0);
    for (unsigned int i = 0, x = 2, y = 2; i < m_nChoices; ++i) {
        if (m_Highlight == i + 1) { /* High light the present choice */
            wattron(m_MenuWin, A_REVERSE);
            mvwprintw(m_MenuWin, y, x, "%s", m_Choices[i].c_str());
            wattroff(m_MenuWin, A_REVERSE);
        } else {
            mvwprintw(m_MenuWin, y, x, "%s", m_Choices[i].c_str());
        }
        ++y;
    }
    wrefresh(m_MenuWin);
}