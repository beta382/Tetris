/*
 * Logo.cpp
 *
 *  Created on: Apr 30, 2014
 *      Author: Austin
 */


#include "Logo.h"
Logo::Logo():
Shape()
{
    init();
}

Logo::Logo(int x, int y, int blockSize, int padding, unsigned int background):
Shape(x, y, blockSize, padding, background)
{
    init();
}

void Logo::init() {
    /*T*/addBlock<Block>(0, 3, Color::BROWN).addBlock<Block>(1, 0, Color::BLUE)
            .addBlock<Block>(1, 1, Color::BLUE).addBlock<Block>(1, 2, Color::BROWN)
            .addBlock<Block>(1, 3, Color::BROWN).addBlock<Block>(2, 3, Color::BROWN)
    /*E*/.addBlock<Block>(4, 1, Color::CYAN).addBlock<Block>(4, 2, Color::DARK_GREEN)
        .addBlock<Block>(5, 0, Color::CYAN).addBlock<Block>(5, 1, Color::CYAN)
        .addBlock<Block>(5, 2, Color::DARK_GREEN).addBlock<Block>(5, 3, Color::DARK_GREEN)
        .addBlock<Block>(6, 0, Color::CYAN).addBlock<Block>(6, 3, Color::DARK_GREEN)
    /*T*/.addBlock<Block>(8, 3, Color::BROWN).addBlock<Block>(9, 0, Color::BLUE)
        .addBlock<Block>(9, 1, Color::BLUE).addBlock<Block>(9, 2, Color::BROWN)
        .addBlock<Block>(9, 3, Color::BROWN).addBlock<Block>(10, 3, Color::BROWN)
    /*R*/.addBlock<Block>(12, 0, Color::CYAN).addBlock<Block>(12, 1, Color::CYAN)
            .addBlock<Block>(12, 2, Color::RED).addBlock<Block>(12, 3, Color::RED)
            .addBlock<Block>(13, 1, Color::CYAN).addBlock<Block>(13, 2, Color::CYAN)
            .addBlock<Block>(13, 3, Color::RED).addBlock<Block>(14, 0, Color::GREEN)
            .addBlock<Block>(14, 2, Color::GREEN).addBlock<Block>(14, 3, Color::RED)
    /*I*/.addBlock<Block>(16, 0, Color::BLUE).addBlock<Block>(16, 1, Color::BLUE)
            .addBlock<Block>(16, 2, Color::BLUE).addBlock<Block>(16, 3, Color::BLUE)
    /*S*/.addBlock<Block>(18, 0, Color::DARK_GREEN).addBlock<Block>(18, 2, Color::DARK_GREEN)
        .addBlock<Block>(19, 0, Color::DARK_GREEN).addBlock<Block>(19, 1, Color::DARK_GREEN)
        .addBlock<Block>(19, 2, Color::DARK_GREEN).addBlock<Block>(19, 3, Color::DARK_GREEN)
        .addBlock<Block>(20, 1, Color::DARK_GREEN).addBlock<Block>(20, 3, Color::DARK_GREEN);
}
