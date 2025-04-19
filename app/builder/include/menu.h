#pragma once

/**
* Menu.h (Effortless console menu making software)
* Copyright (C) 2023 by LeeTuah (Discord: leetuah).
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// allow unsafe c-style functions
#pragma warning(disable : 4996)
# include <iostream>
# include <vector>
# include <functional>
# include <string>
# include <fstream>
# include <sstream>
# include <conio.h>
# include <utility>

namespace Menu
{
enum color;

class Menu {
    // Read thw following comments above the variables and functions
    // to get a brief idea of what they do
private:
    // this list stores the name of menu items, and the functions associated to them
    std::vector<std::string> names;
    // these are the pairs of colors (head color and body color) for colorizing the menu
    std::pair<std::string, std::string> colors;
    // neutral is const value with -> \033[0m to neutralize the effect of the head and body colors
    std::string neutral;
    // contains three keybinds as string format -> the up key, down key, and select key
    std::string keybinds;
    // stores the heading of the menu
    std::string heading;
    // it is the maximum characters count that the menu will extend upto. Default is 32.
    int max_string_len;
    // stores the position of the currently selected item in the menu
    std::vector<std::string>::iterator pos;
    // stores whether the program will wait after the function has completed running
    // for any random user input before next iteration of the menu
    bool waitForNextIteration;

    // prints the entirity of the menu in the terminal
    void printMenu();
    // helps to print the menu field in a centered manner
    void gen_element(std::string str, std::string color);
    // true if exit field has been added
    bool is_exit;
public:
    // default constructor for the class
    Menu();
    // constructor to initialize all non-constant values in the class
    Menu(
        int max_len, std::string header, std::string head_color, std::string body_color,
        char up_key, char down_key, char sel_key
    );
    // default destructor for the class
    ~Menu();

    // = operator for the class
    Menu operator=(Menu m1);

    // returns the max string length
    int get_max_len();
    // sets the max string length to a new value
    void set_max_len(int max_len);

    // returns the heading of the class
    std::string get_heading();
    // sets the new heading for the class
    void set_heading(std::string header);

    // returns the head and the body colors
    std::pair<std::string, std::string> get_colors();
    // sets the new head and body colors
    void set_colors(color c_head, color c_body);

    // returns all the keybinds
    std::string get_keybinds();
    // sets the up key
    void set_up_key(char key);
    // sets the down key
    void set_down_key(char key);
    // sets the select key
    void set_sel_key(char key);

    // adding a field to the map
    void add_field(std::string name);
    // removing a field from the map
    void remove_field(std::string name);
    // editing a currently existing field
    void edit_field(std::string old_name, std::string new_name);
    // if the map has a certain field
    bool has_field(std::string name);

    // sets whether the program will stop for a random user input after the 
    // given user function has completed running
    void set_iteration_state(bool waitForNextIteration);
    // returns the current iteration state
    bool get_iteration_state();

    // saves the current menu settings in a .txt file
    // void save(std::string fname = "menu-savefile");
    // loads menu settings from a .txt file
    // void load(std::string fname = "menu-savefile");

    // it is like the main method of the class, the event loop for the menu resides here
    std::string run_menu();
};


enum color
{
    DEFAULT = 0,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
    BRIGHT_RED = 91,
    BRIGHT_GREEN = 92,
    BRIGHT_BLUE = 94
};

// log and sign menu
void AuthMenu();
// main app menu
void MainMenu();
}