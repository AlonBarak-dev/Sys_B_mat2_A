#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>

using namespace std;
using namespace ariel;


namespace ariel{

    // Page::Page(){
    //     this->number_of_lines = 0;
    // }

    // string Page::get_line(int line){
    //     // return the line if exist
    //     if (this->lines.find(line) == this->lines.end())
    //     {
    //         return this->lines.at(line);
    //     }
    //     // return a line of 100 "_"
    //     else{
    //         string empty;
    //         for (int i = 0; i < 100; i++)
    //         {
    //             empty.append("_");
    //         }
    //         return empty;
    //     }
    // }

    // string Page::get_column(int column, int length, int start){

    //     string col_str;
    //     for (int i = start; i < length; i++)
    //     {
    //         if (this->lines.find(i) == this->lines.end())
    //         {
    //             col_str.push_back(this->lines.at(i).at(column));
    //         }
    //         else{
    //             col_str.push_back('_');
    //         }
    //     }
    //     return col_str;


    // }


    Notebook::Notebook(){
        this->number_of_pages = 0;
    }

    void Notebook::write(int page, int row, int column, ariel::Direction dircetion , string text){
        
    }
    string Notebook::read(int page, int row, int column, ariel::Direction dircetion , int length){
        return "";
    }
    void Notebook::erase(int page, int row, int column, ariel::Direction dircetion , int length){
        
    }
    void Notebook::show(int page){
        
    }

}
