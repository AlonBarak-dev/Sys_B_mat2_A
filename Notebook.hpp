#ifndef NOTEBOOK_INCLUDED
#define NOTEBOOK_INCLUDED

#include "Direction.hpp"
#include <string>

namespace ariel
{
    class Notebook
    {
        public:
            void write(int page, int row, int column, ariel::Direction dircetion , string text);
            string read(int page, int row, int column, ariel::Direction dircetion , int length);
            void erase(int page, int row, int column, ariel::Direction dircetion , int length);
            void show(int page);
    };
}

#endif