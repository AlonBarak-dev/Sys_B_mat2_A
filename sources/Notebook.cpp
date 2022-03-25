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
        this->max_row = 0;
    }

    string Page::get_line(int line){
        // return the line if exist
        if (this->lines.find(line) == this->lines.end())
        {
            return "";
        }
        // return a line of 100 "_"    
        return this->lines.at(line);
        
    }

    string Page::get_column(int column, int length,int start){

        string col_str;
        // loop over the rows and add the chars at row[column] if exist
        // and add "_" else.
        for (int i = start; i < start + length; i++)
        {
            if (this->lines.find((unsigned long) i) == this->lines.end())
            {
                col_str.push_back('_');
            }
            else{
                col_str.push_back(this->lines.at((unsigned long)i).at(static_cast<unsigned long> (column)));
            }
        }
        return col_str;
    }

    void Page::set_line(int line, int column, string const & data){
        // replace the empty chars in line
        this->lines.at(line).replace(static_cast<unsigned long> (column), data.size(), data);
    }

    void Page::set_column(int line, int column, int length, string const & data){
        // replace the column-th index in each given row
        for(int i = line; i < line + int(length); i++){
            if(this->lines.find(i) == this->lines.end()){
                this->create_line(i);
            }
            this->lines.at(i).at(static_cast<unsigned long> (column)) = data.at((unsigned long) (i - line));
        }

    }

    int Page::get_max_line() const{
        return this->max_row;
    }

    void Page::create_line(int line_num){
        string str;
        int const rows = 100;
        // create an empty line
        for (int i = 0; i < rows; i++)
        {
            str.push_back('_');
        }
        // insert the tuple {line number, empty string}
        this->lines.insert({line_num, str});
        this->number_of_lines++;
        if (line_num > this->max_row)
        {
            this->max_row = line_num;
        }
        
    }


    Notebook::Notebook(){
        this->number_of_pages = 0;
    }

    void Notebook::write(int page, int row, int column, ariel::Direction direction , string const & text){

        if(page < 0 || row < 0 || column < 0){
            throw runtime_error("Negative Number");
        }

        // throw error if the user trying to write at index 100 and above
        int const col_max = 99;
        if (column > col_max)
        {
            throw runtime_error("Can't write in index 100 and above");
        }
        if((static_cast<unsigned long> (column) + text.size() > col_max) && (direction == ariel::Direction::Horizontal)){
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
        if(this->pages.at(page).get_line(row).empty()){
            this->pages.at(page).create_line(row);
        }
        
        // throw error if the user trying to write on used space in the page/line
        for (int i = column; i < column + int(text.size()); i++)
        {
            if (this->pages.at(page).get_line(row).at((unsigned long) i) != '_')
            {
                throw runtime_error("Can't write on unempty indexes!");
            }
        }
        if (direction == ariel::Direction::Vertical)
        {
            // throw error if the user trying to write on used apace in page/column
            string col_str = this->pages.at(page).get_column(column, text.size(), row);
            for (int i = 0; i < int(col_str.size()); i++)
            {
                if (col_str.at((unsigned long)i) != '_')
                {
                    throw runtime_error("Can't write on unempty indexes!");
                }   
            }
        }
        // do not change the page if the text is an empty text
        if (text.empty())
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

        if(page < 0 || row < 0 || column < 0){
            throw runtime_error("Negative Number");
        }
        int const col_max = 99;
        if (direction == ariel::Direction::Horizontal)
        {
            if(length > col_max){
                throw runtime_error("Can only read 100 chars");
            }
            if ((this->pages.find(page) == this->pages.end()) || (this->pages.at(page).get_line(row).empty()))
            {
                // return an empty text since the line/page isn't exsits
                string str;
                for (int i = 0; i < int(length); i++)
                {
                    str.push_back('_');
                }
                return str;
            }
            
            // return line[column : column+length] 
            string str;
            string line;
            line = this->pages.at(page).get_line(row);
            for (int i = column; i < column + int(length); i++)
            {
                str.push_back(line.at((unsigned long) i));
            }
            return str;
                
            
        }
        

        if (this->pages.find(page) == this->pages.end())
        {
            // return an empty text since the page isn't exsits
            string str;
            for (int i = 0; i < int(length); i++)
            {
                str.push_back('_');
            }
            return str;
        }
        // return the column using the get_column() method 
        return this->pages.at(page).get_column(column, length, row);
        
        
        

        
    }
    void Notebook::erase(int page, int row, int column, ariel::Direction direction , int length){

        if(page < 0 || row < 0 || column < 0){
            throw runtime_error("Negative Number");
        }
        int const col_max = 99;
        if (direction == ariel::Direction::Horizontal)
        {
            // HORIZONTAL

            if (length > col_max || length + column > col_max)
            {
                throw runtime_error("Can only erase 100 chars in a single line");
            }
            

            if (this->pages.find(page) == this->pages.end())
            {
                // create the page if not exist
                Page new_page;
                this->pages.insert({page,new_page});
            }
            if (this->pages.at(page).get_line(row).empty())
            {
                // create the line if not exist
                this->pages.at(page).create_line(row);
            }
            string del_line;
            for (int i = 0; i < int(length); i++)
            {
                del_line.push_back('~');
            }
            // delete the desired part of the line
            this->pages.at(page).set_line(row,column, del_line);
        }

        else{
            // VERTICAL

            string del_col;
            for (int i = row; i < row + int(length); i++)
            {
                if(this->pages.find(page) == this->pages.end()){
                    // create page if null
                    Page new_page;
                    this->pages.insert({page, new_page});
                }
                if (this->pages.at(page).get_line(row).empty())
                {
                    // create line if not exist
                    this->pages.at(page).create_line(row);
                }
                del_col.push_back('~');
            }
            // erase the desired column
            this->pages.at(page).set_column(row, column,length, del_col);
        }
        
    }
    void Notebook::show(int page){

        int page_counter = 0;
        string empty_str;
        int const rows_max = 100;
        for (int i = 0; i < rows_max; i++)
        {
            empty_str.push_back('_');
        }
        
        
        //print empty page if not exists
        if (this->pages.find(page) == this->pages.end()){
            for (int i = 0; i < rows_max; i++)
            {
                // print empty line in case not exist
                cout << page_counter << ". " << empty_str << endl;
                page_counter++;
            }
            return;
        }
        
        for(int i = 0; i <= this->pages.at(page).get_max_line(); i++){
            if (!this->pages.at(page).get_line(i).empty())
            {
                // if the line exits, print it.
                cout << page_counter << ". " << this->pages.at(page).get_line(i) << endl;
            }
            else{
                // print empty line in case not exist
                cout << page_counter << ". " << empty_str << endl;
            }
            page_counter++;
        }
    }

}
