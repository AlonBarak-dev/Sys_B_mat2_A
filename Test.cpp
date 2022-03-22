#include "doctest.h"
#include "Notebook.hpp"

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
    CHECK(nootbook.read(50,10,10,ariel::Direction::Horizontal, 17) == "hello world again");

    // writing an empty word
    nootbook.write(2,1,1,ariel::Direction::Horizontal, "");
    CHECK(nootbook.read(2,1,1,ariel::Direction::Horizontal,1) == "_");


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
    CHECK(nootbook.read(51,10,10,ariel::Direction::Vertical, 17) == "hello world again");

    // writing an empty word
    nootbook.write(6,1,1,ariel::Direction::Vertical, "");
    CHECK(nootbook.read(6,1,1,ariel::Direction::Vertical,1) == "_");

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


    ariel::Notebook nootbook;

    // trying to write on used place in the nootbook
    nootbook.write(1,1,1, ariel::Direction::Horizontal, "hello");
    CHECK_THROWS(nootbook.write(1,1,3,ariel::Direction::Horizontal, "hello"));

    nootbook.write(50,20,4,ariel::Direction::Horizontal, "abcde hello");
    CHECK_THROWS(nootbook.write(50,20,9,ariel::Direction::Horizontal, "B"));


    nootbook.write(8,4,4,ariel::Direction::Vertical, "hello");
    CHECK_THROWS(nootbook.write(8,4,4,ariel::Direction::Vertical, "hi"));

    nootbook.write(10,10,10, ariel::Direction::Vertical, "hello world");
    CHECK_THROWS(nootbook.write(10,12,10, ariel::Direction::Vertical, "hi world, how are you?"));

    nootbook.write(0,0,0, ariel::Direction::Horizontal, "start");
    CHECK_THROWS(nootbook.write(0,0,2, ariel::Direction::Vertical, "not start"));

    nootbook.write(7,0,0, ariel::Direction::Horizontal, "testing");
    nootbook.write(7,1,0, ariel::Direction::Horizontal, "testing");
    CHECK_THROWS(nootbook.write(7,0,2, ariel::Direction::Vertical, "above"));

    CHECK_THROWS(nootbook.write(10,10,101,ariel::Direction::Horizontal, "end of page"));

    CHECK_THROWS(nootbook.write(20,10,95, ariel::Direction::Horizontal, "end of page"));

    CHECK_THROWS(nootbook.write(0,50,104, ariel::Direction::Vertical, "end of page"));

    /*
        WRITING AFTER ERASE
    */
    nootbook.erase(7,0,0,ariel::Direction::Horizontal, 7);
    CHECK_THROWS(nootbook.write(7,0,0,ariel::Direction::Horizontal, "trying to write on erased paper"));

}