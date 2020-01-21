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
    PIXELS
};

// Constructor loads a filename with the .ppm extension
PPM::PPM(std::string file_name){
    auto buffer = file_to_vector(file_name);

    clear_comments(buffer);

    const char* error = nullptr;

    std::string word;
    word.reserve(8);

    ParserState state = VERSION;

    double color_depth;
    int color_max;
    size_t pixels = 0;
    int color;

    auto begin = buffer.begin();
    auto end   = buffer.end();

#define fail(MSG) error = MSG; goto out

    while (begin != end) {
        /* Get the next word. */
        word.clear();
        for (; begin != end; ++begin) {
            if (!std::isspace(*begin)) break;
        }

        for (; begin != end; ++begin) {
            if (std::isspace(*begin)) break;
            word.push_back(*begin);
        }

        if (begin == end && word.length() == 0) break;

        /* Parse it based on the current state */
        switch (state) {
        case VERSION:
            if(word.compare("P3")) {
                fail("Invalid PPM file version");
            }
            state = SIZE_1;
            break;
        case SIZE_1:
            // NOTE(Casey)
            // Since we are not keeping track of locations, there is no better
            // way to signal error ATM than simply fail with invalid_argument.
            if ((m_width = std::stoi(word)) <= 0) {
                fail("Invalid width for image");
            }
            state = SIZE_2;
            break;
        case SIZE_2:
            if ((m_height = std::stoi(word)) <= 0) {
                fail("Invalid height for image");
            }
            state = COLORS;
            break;
        case COLORS:
            if ((color_max = std::stoi(word)) <= 0) {
                fail("Invalid color range");
            }
            color_depth = 255.0 / static_cast<double>(color_max);
            pixels = 3 * (m_width * m_height);
            m_PixelData = new unsigned char[pixels];
            state = PIXELS;
            break;
        case PIXELS:
            if ((color = std::stoi(word)) < 0) {
                fail("Invalid color value");
            }
            if (color > color_max) {
                fail("Invalid color value");
            }
            if (pixels < 0) {
                fail("Too many pixel values");
            }

            m_PixelData[(3 * (m_width * m_height)) - pixels] =
                static_cast<unsigned char>(color_depth *
                                           static_cast<double>(color));
            pixels = (pixels > 0) ? pixels - 1 : pixels;
            break;
        }
    }
#undef fail

  out:
    if (error != nullptr) {
        throw std::invalid_argument(error);
    }
    if (pixels > 0) {
        throw std::invalid_argument("Not enough values supplied");
    }
}

// Destructor clears any memory that has been allocated
PPM::~PPM(){
    delete m_PixelData;
}

// Saves a PPM Image to a new file.
void PPM::savePPM(std::string output_file){
    std::ofstream output(output_file);

    output << "P3\n"
           << m_width << " " << m_height << "\n"
           << "255\n";

    size_t len = 3 * m_width * m_height;
    for (size_t i = 0; i < len; ++i) {
        output << static_cast<int>(m_PixelData[i]);
        if ((i + 1) % 3 == 0) {
            output << "\n";
        } else {
            output << " ";
        }
    }

    output.close();
}

// Darken subtracts 50 from each of the red, green
// and blue color components of all of the pixels
// in the PPM. Note that no values may be less than
// 0 in a ppm.
void PPM::darken() {
    for (size_t pos = 0; pos < (3 * m_width * m_height); ++pos) {
        m_PixelData[pos] = (m_PixelData[pos] <= 50) ? 0 : m_PixelData[pos] - 50;
    }
}

// Sets a pixel to a specific R,G,B value
void PPM::setPixel(int x, int y, int R, int G, int B){
    if (x >= m_width || y >= m_height) {
        throw std::invalid_argument("Height/Width too large");
    }
    size_t pos = 3 * ((y * m_width) + x);
    m_PixelData[pos]   = static_cast<unsigned char>(R);
    m_PixelData[pos+1] = static_cast<unsigned char>(G);
    m_PixelData[pos+2] = static_cast<unsigned char>(B);
}
