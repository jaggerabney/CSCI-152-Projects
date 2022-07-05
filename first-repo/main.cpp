#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <memory>
#include <string>

using namespace std;

struct Color {
    float red;
    float green;
    float blue;

    static Color random() {
        static mt19937 engine{ std::random_device{}() };
        static uniform_real_distribution<float> dist{ 0, 1 };

        return Color{ dist(engine), dist(engine), dist(engine) };
    }

    float rgbSum() {
        return red + green + blue;
    }
};

void colorSink(unique_ptr<Color> color) {
    // ... do nothing ... do not change the signature or implementation of this function
    cout << "Success!\n";
}

ostream& operator<<(ostream& out, const Color& color) {
    out << "COLOR(" << color.red << ", " << color.green << ", " << color.blue << ")";
    return out;
}

ostream& operator<<(ostream& out, const vector<Color>& colors) {
    out << "[";
    for (auto it = colors.begin(); it != colors.end(); it++) {
        out << "\n\t" << *it;
    }
    out << "\n]";
    return out;
}

bool operator<(const Color& color1, const Color& color2) {
    // i.e. is color1 darker than color2? 
    // (a color is darker than another color if the sum of its red/green/blue components is smaller than the other)
    return ((color1.red + color1.blue + color1.green) < (color2.red + color2.blue + color2.green));
}

bool sortColors(const Color& lhc, const Color& rhc) {
    return lhc < rhc;
}

bool sortByBlue(const Color& lhc, const Color& rhc) {
    return lhc.blue < rhc.blue;
}

Color findDarkestColorIn(vector<Color> colors) {
    // sorts colors from darkest to lightest, then returns the front (i.e. the darkest)
    // colors is passed by value so as to not overwrite it
    sort(colors.begin(), colors.end(), sortColors);
    return colors.front();
}

int main() {
    cout << "Hello, World\n";

    // 1. overload the output stream operator so that you can print this color directly to the output stream
    auto c = Color::random();
    cout << "First color is: " << c << "\n";

    // 2. here is a list of ten colors, print them out in order, and then in reverse order
    vector<Color> colors;
    for (int i = 0; i < 10; i++) {
        colors.push_back(Color::random());
    }

    cout << "Colors initial order: " << colors << "\n";

    reverse(colors.begin(), colors.end());
    cout << "Colors reverse order: " << colors << "\n";

    // 3. find the color in the list that is darkest and print it out
    // the darkest color is defined as the color where the sum of the red, green, and blue components is the smallest

    cout << "Darkest color: " << findDarkestColorIn(colors) << "\n";

    // 4. order the colors from smallest 'blue' value to largest 'blue' value and print them out

    sort(colors.begin(), colors.end(), sortByBlue);
    cout << "Colors sorted by blue value: " << colors << "\n";

    // 5. create a std::unique_ptr to a color on the free-store and call it 'colorPtr', pass this color to the
    // 'colorSink' function.
    // i.e. auto colorPtr = ...

    auto colorPtr = make_unique<Color>();
    colorSink(move(colorPtr));
}