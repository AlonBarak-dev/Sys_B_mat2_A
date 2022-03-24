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
            int max_row;
        
        public:
            Page();
            std::string get_line( int line);
            std::string get_column( int column, int length, int start);
            int get_max_line();
            void set_line(int line, int column, std::string data);
            void set_column( int line, int column, int length, std::string data);
            void create_line(int line_num);

    };



    class Notebook
    {
        private:
            std::unordered_map< int, Page> pages;
            int number_of_pages;
        public:
            Notebook();
            void write( int page, int row, int column, ariel::Direction dircetion , std::string text);
            std::string read( int page, int row, int column, ariel::Direction dircetion , int length);
            void erase( int page, int row, int column, ariel::Direction dircetion , int length);
            void show( int page);
    };
}

#endif