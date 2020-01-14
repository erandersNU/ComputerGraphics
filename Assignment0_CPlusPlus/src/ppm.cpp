#include "PPM.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>

static std::vector<char> file_to_vector(std::string file_name) {
    std::ifstream input(file_name);

    input.seekg(0, std::ios::end);
    size_t size = input.tellg();

    std::vector<char> ret(size, ' ');

    input.seekg(0);
    input.read(ret.data(), size);

    input.close();
    return ret;
}

static void clear_comments(std::vector<char>& buffer) {
    bool comment = false;
    buffer.erase(std::remove_if(buffer.begin(),
                                buffer.end(),
                                [&](char x){
                                    comment &= !(x == '\n');
                                    return comment |= (x == '#');
                                }),
                 buffer.end());
}

enum ParserState {
    VERSION,
    SIZE_1,
    SIZE_2,
    COLORS,
    PIXEL_R,
    PIXEL_G,
    PIXEL_B
};

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string file_name){
    auto buffer = file_to_vector(file_name);

    clear_comments(buffer);

    std::string word;
    word.reserve(8);

    ParserState state = VERSION;

    auto begin = buffer.begin();
    auto end   = buffer.end();

    while (begin != end) {
        /* Get the next word. */
        word.clear();
        for (; begin != end; ++begin) {
            if (!std::ispace(*begin)) break;
        }

        for (; begin != end; ++begin) {
            if (std::ispace(*begin)) break;
            word.push_back(*begin);
        }

        /* Parse it based on the current state */
        switch (ParserState) {
        case VERSION:
            if(!word.compare("P3")) {
                throw std::runtime_error("Invalid PPM file version");
            } else {
                state = SIZES;
            }
            break;
        case SIZES:
            if (
        }



    for (auto& x : buffe) {
        if (std::isspace(x)) continue;

        printf("%c", x);
    }
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string outputFileName){
    // TODO: Save a PPM image to disk
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken(){
    // TODO: Output a 'filtered' PPM image.
}

// Sets a pixel to a specific R,G,B value
void PPM::setPixel(int x, int y, int R, int G, int B){
    // TODO: Implement
}
