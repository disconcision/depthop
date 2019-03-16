#include "write_file.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <iterator>

bool write_file(
        const std::string &filename,
        Image image)
{
    std::ofstream f;
    f.open(filename);
    if (!f) return false;

    if (image.num_channels == 1)
        f << "P2\n";
    else
        f << "P3\n";

    f << image.width << " " << image.height << std::endl;
    f << 255 << std::endl;
    std::copy(image.data.begin(), image.data.end(),
            std::ostream_iterator<int>(f, " "));
    f.close();
    return true;
}
