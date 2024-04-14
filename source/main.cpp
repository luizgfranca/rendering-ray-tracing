#include <iostream>

void render_test_image(int width, int height) {
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for(int line = 0; line < height; line ++) {
        for(int column = 0; column < width; column ++) {
           auto red = double(line) / (width - 1);
           auto green = double(column) / (height - 1);
           auto blue = 1.0 - red - green;

           if(blue < 0) {
                blue = 0;
           }

           int px_red = int(255.999 * red);
           int px_green = int(255.999 * green);
           int px_blue = int(255.999 * blue);

           std::cout << px_red << " " << px_green << " " << px_blue << "\n";
        }
    }
}

int main() {
    render_test_image(800, 800);

    return 0;
}