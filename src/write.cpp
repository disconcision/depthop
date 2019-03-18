#include "write.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <iterator>

bool write(
        const std::string &filename,
        Image &image)
{
    std::ofstream f;
    f.open(filename);
    if (!f) return false;

    std::string code;
    if (image.num_channels == 1)
      code = "P2\n";
    else
      code = "P3\n";

    f << code << "\n" << image.width << " "
      << image.height << "\n" << 255 << "\n";

    std::copy(image.data.begin(), image.data.end(),
            std::ostream_iterator<int>(f, " "));

    f.close();
    return true;
}
