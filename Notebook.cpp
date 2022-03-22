#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace ariel;


namespace ariel{

    Page::Page(){
        this->number_of_lines = 0;
    }

    string Page::get_line(int line){
        // return the line if exist
        if (this->lines.find(line) == this->lines.end())
        {
            return "";
        }
        // return a line of 100 "_"
        else{
            return this->lines.at(line);
        }
    }

    string Page::get_column(int column, int length, int start){

        string col_str;
        // loop over the rows and add the chars at row[column] if exist
        // and add "_" else.
        for (int i = start; i < start + length; i++)
        {
            if (this->lines.find(i) == this->lines.end())
            {
                col_str.push_back('_');
            }
            else{
                col_str.push_back(this->lines.at(i).at((unsigned int)column));
            }
        }
        return col_str;
    }

    void Page::set_line(int line,int column, string data){
        // replace the empty chars in line
        this->lines.at(line).replace((unsigned int)column, data.size(), data);
    }

    void Page::set_column(int line, int column, int length, string data){
        // replace the column-th index in each given row
        for(int i = line; i < line + length; i++){
            if(this->lines.find(i) == this->lines.end()){
                this->create_line(i);
            }
            this->lines.at(i).at((unsigned int)column) = data.at((unsigned int)(i - line));
        }

    }

    void Page::create_line(int line_num){
        string str;
        // create an empty line
        for (int i = 0; i < 100; i++)
        {
            str.push_back('_');
        }
        // insert the tuple {line number, empty string}
        this->lines.insert({line_num, str});
        this->number_of_lines++;
    }


    Notebook::Notebook(){
        this->number_of_pages = 0;
    }

    void Notebook::write(int page, int row, int column, ariel::Direction direction , string text){

        // throw error if the user trying to write at index 100 and above
        if (column > 99)
        {
            throw runtime_error("Can't write in index 100 and above");
        }
        if(((unsigned int)column + text.size() > 99) && (direction == ariel::Direction::Horizontal)){
            throw runtime_error("Can't write in index 100 and above");
        }
        
        // creates a new page if not exists
        if (this->pages.find(page) == this->pages.end())
        {
            Page new_page;
            this->pages.insert({page, new_page});
            this->number_of_pages++;
        }
        
        // creates the line if not exists 
        if(this->pages.at(page).get_line(row) == ""){
            this->pages.at(page).create_line(row);
        }
        
        // throw error if the user trying to write on used space in the page/line
        for (int i = column; i < ((unsigned int)column + text.size()); i++)
        {
            if (this->pages.at(page).get_line(row).at((unsigned int)i) != '_')
            {
                throw runtime_error("Can't write on unempty indexes!");
            }
        }
        if (direction == ariel::Direction::Vertical)
        {
            // throw error if the user trying to write on used apace in page/column
            string col_str = this->pages.at(page).get_column(column, text.size(), row);
            for (int i = 0; i < col_str.size(); i++)
            {
                if (col_str.at((unsigned int)i) != '_')
                {
                    throw runtime_error("Can't write on unempty indexes!");
                }   
            }
        }
        // do not change the page if the text is an empty text
        if (text.compare("") == 0)
        {
            return;
        }
        // write the text in Horizontal direction
        if (direction == ariel::Direction::Horizontal){
            this->pages.at(page).set_line(row, column, text);
        }

        // write the text in Vertical direction
        if(direction == ariel::Direction::Vertical){
            this->pages.at(page).set_column(row, column, text.size(), text);
        }
        
    }

    string Notebook::read(int page, int row, int column, ariel::Direction direction , int length){

        if (direction == ariel::Direction::Horizontal)
        {
            if ((this->pages.find(page) == this->pages.end()) || (this->pages.at(page).get_line(row) == ""))
            {
                // return an empty text since the line/page isn't exsits
                string str;
                for (int i = 0; i < length; i++)
                {
                    str.push_back('_');
                }
                return str;
            }
            else{
                // return line[column : column+length] 
                string str;
                string line;
                line = this->pages.at(page).get_line(row);
                for (int i = column; i < column + length; i++)
                {
                    str.push_back(line.at((unsigned int)i));
                }
                return str;
                
            }
        }
        else{

            if (this->pages.find(page) == this->pages.end())
            {
                // return an empty text since the page isn't exsits
                string str;
                for (int i = 0; i < length; i++)
                {
                    str.push_back('_');
                }
                return str;
            }
            // return the column using the get_column() method 
            return this->pages.at(page).get_column(column, length, row);
        }
        
        

        
    }
    void Notebook::erase(int page, int row, int column, ariel::Direction dircetion , int length){
        
    }
    void Notebook::show(int page){
        
    }

}
