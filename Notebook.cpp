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

    string Page::get_line(unsigned int line){
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

    string Page::get_column(unsigned int column, int length,unsigned int start){

        string col_str;
        // loop over the rows and add the chars at row[column] if exist
        // and add "_" else.
        for (unsigned int i = start; i < start + (unsigned int)length; i++)
        {
            if (this->lines.find(i) == this->lines.end())
            {
                col_str.push_back('_');
            }
            else{
                col_str.push_back(this->lines.at(i).at(column));
            }
        }
        return col_str;
    }

    void Page::set_line(unsigned int line, unsigned int column, string data){
        // replace the empty chars in line
        this->lines.at(line).replace(column, data.size(), data);
    }

    void Page::set_column(unsigned int line,unsigned int column, int length, string data){
        // replace the column-th index in each given row
        for(unsigned int i = line; i < line + (unsigned int)length; i++){
            if(this->lines.find(i) == this->lines.end()){
                this->create_line( i);
            }
            this->lines.at(i).at(column) = data.at((i - line));
        }

    }

    unsigned int Page::get_max_line(){
        return this->max_row;
    }

    void Page::create_line(unsigned int line_num){
        string str;
        // create an empty line
        for (unsigned int i = 0; i < 100; i++)
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

    void Notebook::write(unsigned int page,unsigned int row,unsigned int column, ariel::Direction direction , string text){

        // throw error if the user trying to write at index 100 and above
        if (column > 99)
        {
            throw runtime_error("Can't write in index 100 and above");
        }
        if((column + text.size() > 99) && (direction == ariel::Direction::Horizontal)){
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
        for (unsigned int i = column; i < (column + text.size()); i++)
        {
            if (this->pages.at(page).get_line(row).at(i) != '_')
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

    string Notebook::read(unsigned int page,unsigned int row,unsigned int column, ariel::Direction direction , int length){

        if (direction == ariel::Direction::Horizontal)
        {
            if(length > 99){
                throw runtime_error("Can only read 100 chars");
            }
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
                for (unsigned int i = column; i < column + (unsigned int)length; i++)
                {
                    str.push_back(line.at(i));
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
    void Notebook::erase(unsigned int page,unsigned int row,unsigned int column, ariel::Direction direction , int length){

        if (direction == ariel::Direction::Horizontal)
        {
            // HORIZONTAL

            if (length > 99)
            {
                throw runtime_error("Can only erase 100 chars in a single line");
            }
            

            if (this->pages.find(page) == this->pages.end())
            {
                // create the page if not exist
                Page new_page;
                this->pages.insert({page,new_page});
            }
            if (this->pages.at(page).get_line(row) == "")
            {
                // create the line if not exist
                this->pages.at(page).create_line(row);
            }
            string del_line;
            for (int i = 0; i < length; i++)
            {
                del_line.push_back('~');
            }
            // delete the desired part of the line
            this->pages.at(page).set_line(row,column, del_line);
        }

        else{
            // VERTICAL

            string del_col;
            for (unsigned int i = row; i < row + (unsigned int)length; i++)
            {
                if(this->pages.find(page) == this->pages.end()){
                    // create page if null
                    Page new_page;
                    this->pages.insert({page, new_page});
                }
                if (this->pages.at(page).get_line(row) == "")
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
    void Notebook::show(unsigned int page){

        int page_counter;
        page_counter = 0;
        string empty_str;

        for (int i = 0; i < 100; i++)
        {
            empty_str.push_back('_');
        }
        
        
        //print empty page if not exists
        if (this->pages.find(page) == this->pages.end()){
            for (int i = 0; i < 100; i++)
            {
                // print empty line in case not exist
                cout << page_counter << ". " << empty_str << endl;
                page_counter++;
            }
            return;
        }
        
        for(unsigned int i = 0; i <= this->pages.at(page).get_max_line(); i++){
            if (this->pages.at(page).get_line(i) != "")
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
