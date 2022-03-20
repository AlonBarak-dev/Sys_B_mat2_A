#include "Notebook.hpp"
#include "Direction.hpp"
#include <string>

using namespace std;


namespace ariel{

    class Notebook{



        public:
            void write(int page, int row, int column, ariel::Direction dircetion , string text){
                return;
            }
            string read(int page, int row, int column, ariel::Direction dircetion , int length){
                return "";
            }
            void erase(int page, int row, int column, ariel::Direction dircetion , int length){
                return;
            }
            void show(int page){
                return;
            }


    };

}