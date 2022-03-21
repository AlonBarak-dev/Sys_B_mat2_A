#ifndef NOTEBOOK_INCLUDED
#define NOTEBOOK_INCLUDED

#include "Direction.hpp"
#include <string>
#include <unordered_map>

namespace ariel
{
    class Page{

        private:
            std::unordered_map<int, std::string> lines;
            int number_of_lines;
        
        public:
            Page();
            std::string get_line(int line);
            std::string get_column(int column, int length, int start);
            void set_line(int line, std::string data);
    };



    class Notebook
    {
        private:
            std::unordered_map<int, Page> pages;
            int number_of_pages;
        public:
            Notebook();
            void write(int page, int row, int column, ariel::Direction dircetion , std::string text);
            std::string read(int page, int row, int column, ariel::Direction dircetion , int length);
            void erase(int page, int row, int column, ariel::Direction dircetion , int length);
            void show(int page);
    };
}

#endif