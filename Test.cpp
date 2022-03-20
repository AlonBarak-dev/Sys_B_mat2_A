#include <doctest.h>
#include <Notebook.hpp>

using namespace std;

TEST_CASE("Good usage"){
    ariel::Notebook nootbook;

    /*
        HORIZONTAL 
    */

    // writing a sentence with 1 word in it
    nootbook.write(3,5,4,ariel::Direction::Horizontal, "hello");
    CHECK(nootbook.read(3,5,4,ariel::Direction::Horizontal, 5) == "hello");

    // writing a sentence with 2 word in it
    nootbook.write(2,5,4,ariel::Direction::Horizontal, "hello world");
    CHECK(nootbook.read(2,5,4,ariel::Direction::Horizontal, 11) == "hello world");

    // writing a sentence with 3 words in it
    nootbook.write(50, 10, 10, ariel::Direction::Horizontal, "hello world again");
    CHECK(nootbook.read(50,10,10,ariel::Direction::Horizontal, 16) == "hello world again");

    // writing an empty word
    nootbook.write(2,1,1,ariel::Direction::Horizontal, "");
    CHECK(nootbook.read(2,1,1,ariel::Direction::Horizontal,1) == " ");


    /*
        VERTICAL
    */

    // writing a sentence with 1 word in it
    nootbook.write(4,5,4,ariel::Direction::Vertical, "hello");
    CHECK(nootbook.read(4,5,4,ariel::Direction::Vertical, 5) == "hello");

    // writing a sentence with 2 word in it
    nootbook.write(1,5,4,ariel::Direction::Vertical, "hello world");
    CHECK(nootbook.read(1,5,4,ariel::Direction::Vertical, 11) == "hello world");

    // writing a sentence with 3 words in it
    nootbook.write(51, 10, 10, ariel::Direction::Vertical, "hello world again");
    CHECK(nootbook.read(51,10,10,ariel::Direction::Vertical, 16) == "hello world again");

    // writing an empty word
    nootbook.write(6,1,1,ariel::Direction::Vertical, "");
    CHECK(nootbook.read(6,1,1,ariel::Direction::Vertical,1) == " ");

    /*
        ERASE
    */

    // erasing a sentence
    nootbook.erase(51,10,10,ariel::Direction::Vertical, 16);
    CHECK(nootbook.read(51,10,10,ariel::Direction::Vertical, 16) == "~~~~~~~~~~~~~~~~");

    nootbook.erase(50,10,10,ariel::Direction::Horizontal, 16);
    CHECK(nootbook.read(50,10,10,ariel::Direction::Horizontal, 16) == "~~~~~~~~~~~~~~~~");

}

TEST_CASE("Bad usage"){

}