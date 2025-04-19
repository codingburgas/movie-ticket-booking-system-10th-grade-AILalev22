#include "pch.h"
#include "menu.h"
#include "print.h"
#include "options.h"

namespace Menu
{
    enum
    {
        empty,
        LOG,
        SIGN,
    };
    Menu::Menu() {
        names = {};
        max_string_len = 32;
        colors = {};
        neutral = "\033[0m";
        waitForNextIteration = true;
        keybinds = "wsq";
        heading = "MENU";
        colors.first = "\033[0;31m";
        pos = names.begin();
        is_exit = 0;
    }

    Menu::Menu(int max_len, std::string header, std::string head_color, std::string body_color,
        char up_key, char down_key, char sel_key) {
        if (max_len <= 0) {
            std::cout << "Error: Max String Length is set to 0.";
            return;
        }

        max_string_len = max_len;

        if (head_color.size() != 2) {
            std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
            return;
        }

        if (body_color.size() != 2) {
            std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
            return;
        }

        colors.first = "\033[0;" + head_color + "m";
        colors.second = "\033[0;" + body_color + "m";
        neutral = "\033[0m";
        heading = header;
        keybinds[0] = up_key;
        keybinds[1] = down_key;
        keybinds[2] = sel_key;
        pos = names.begin();
    }

    Menu Menu::operator=(Menu m1) {
        this->max_string_len = m1.max_string_len;
        this->names = m1.names;
        this->colors = m1.colors;
        this->pos = m1.pos;
        this->keybinds = m1.keybinds;
        this->waitForNextIteration = m1.waitForNextIteration;

        return *this;
    }

    int Menu::get_max_len() {
        return max_string_len;
    }

    void Menu::set_max_len(int max_len) {
        if (max_len <= 0) {
            std::cout << "Error: Max String Length is set to 0.";
            return;
        }

        max_string_len = max_len;
    }

    std::string Menu::get_heading() {
        return heading;
    }

    void Menu::set_heading(std::string header) {
        heading = header;
    }

    std::pair<std::string, std::string> Menu::get_colors() {
        return colors;
    }

    void Menu::set_colors(color c_head, color c_body) {


        colors.first = "\033[0;" + std::to_string((int)c_head) + "m";
        colors.second = "\033[0;" + std::to_string((int)c_body) + "m";
    }

    std::string Menu::get_keybinds() {
        return keybinds;
    }

    void Menu::set_up_key(char key) {
        keybinds[0] = key;
    }

    void Menu::set_down_key(char key) {
        keybinds[1] = key;
    }

    void Menu::set_sel_key(char key) {
        keybinds[2] = key;
    }

    void Menu::add_field(std::string name) {
        names.push_back(name);
        pos = names.begin();
    }

    void Menu::remove_field(std::string name) {
        for (auto itr = names.begin(); itr != names.end(); itr++) {
            if (*itr == name) {
                names.erase(itr);
                pos = names.begin();
                return;
            }
        }

        std::cout << "Error: Entry doesn\'t exist in the first place.";
    }

    void Menu::edit_field(std::string old_name, std::string new_name) {
        for (int itr = 0; itr != (int)names.size(); itr++) {
            if (names[itr] == old_name) {
                names[itr] = { new_name };
                pos = names.begin();
                return;
            }
        }

        std::cout << "Error: Entry doesn\'t exist in the first place.";
    }

    bool Menu::has_field(std::string name) {
        for (auto itr = names.begin(); itr != names.end(); itr++) {
            if (*itr == name) return true;
        }

        return false;
    }

    void Menu::set_iteration_state(bool waitForNextIteration) {
        this->waitForNextIteration = waitForNextIteration;
    }

    bool Menu::get_iteration_state() {
        return this->waitForNextIteration;
    }

    void Menu::gen_element(std::string str, std::string color) {
        int space_size = (max_string_len - ((int)str.size())) / 2;

        for (int i = 1; i <= max_string_len; i++) {
            if (i <= space_size || i > space_size + (int)str.size()) std::cout << " ";
            else std::cout << color << str[i - space_size - 1] << neutral;
        }
    }

    void Menu::printMenu() {
        if (max_string_len <= 0) {
            std::cout << "Error: Invalid Max String Length provided.";
            return;
        }

        std::cout << std::string(max_string_len + 2, '=') << std::endl << "|";
        gen_element(heading, colors.first);
        std::cout << "|" << std::endl << std::string(max_string_len + 2, '=') << std::endl;

        for (auto itr = names.begin(); itr != names.end(); itr++) {
            std::cout << ((itr != pos) ? "|" : "<");
            gen_element(*itr, ((itr == pos) ? colors.first : colors.second));
            std::cout << ((itr != pos) ? "|" : ">") << std::endl;
        }

        std::cout << std::string(max_string_len + 2, '=') << std::endl;
    }

    std::string Menu::run_menu() {
        char choice;
        bool run = true;
        pos = names.begin();

        if (!is_exit)
        {
            add_field("Exit");
            is_exit = 1;
        }
        while (run) {

            Utils::Clear();
            std::cout << "Press " << keybinds[0] << " and " << keybinds[1] << " to move up and down the menu." << std::endl;
            std::cout << "Press " << keybinds[2] << " to select an item." << std::endl;
            printMenu();
            choice = tolower(getch());

            if (choice == tolower(keybinds[0])) {
                if (pos != names.begin()) pos--;
            }

            else if (choice == tolower(keybinds[1])) {
                if (pos != prev(names.end())) pos++;
            }


            else if (choice == tolower(keybinds[2])) {
                Utils::Clear();
                if (pos == prev(names.end())) {
                    run = false;
                }
                return *pos;
            }
        }

        names.pop_back();
    }

    Menu::~Menu() {
        names = {};
        max_string_len = 0;
        colors = {};
        neutral = "";
        keybinds = "";
        pos = names.end();
    }


    void AuthMenu()
    {
        Menu authMenu;
        authMenu.set_heading("MovieSystem");
        authMenu.add_field("LogIn");
        authMenu.add_field("SignUp");
        authMenu.set_colors(color::RED, color::CYAN);
        authMenu.set_sel_key('e');

        bool res_opt;
        menu:

        std::string choice = authMenu.run_menu();
        if (choice == "LogIn")
        {
            res_opt = Options::LogSign(LOG);
        }
        else if (choice == "SignUp")
        {
            res_opt = Options::LogSign(SIGN);
        }
        else if (choice == "Exit")
        {
            Utils::Exit();
        }
        if (!res_opt) goto menu;
    }
    void MainMenu()
    {
        std::cout << "Main menu";
    }
}