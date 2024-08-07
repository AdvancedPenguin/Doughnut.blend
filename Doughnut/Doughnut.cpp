#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    float A = 0, B = 0;
    int width = 80, height = 22;
    int size = width * height;
    vector<int> z(size, 0);
    vector<char> b(size, ' ');

    const char* colors[] = {
        "\033[31;1m", // Red
        "\033[32;1m", // Green
        "\033[33;1m", // Yellow
        "\033[34;1m", // Blue
        "\033[35;1m", // Magenta
        "\033[36;1m", // Cyan
        "\033[37;1m"  // White
    };
    int colorIndex = 0;

    cout << "\x1b[2J";
    auto lastColorChange = chrono::steady_clock::now();

    while (true) {
        fill(b.begin(), b.end(), ' ');
        fill(z.begin(), z.end(), 0);

        for (float j = 0; j < 6.28; j += 0.07) {
            for (float i = 0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;

                int x = int(40 + 30 * D * (l * h * m - t * n));
                int y = int(12 + 15 * D * (l * h * n + t * m));
                int o = x + width * y;
                int N = int(8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n));

                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        cout << "\x1b[H";
        cout << colors[colorIndex];  // Set text to the current color
        for (int k = 0; k < size; k++) {
            putchar(k % width ? b[k] : 10);
        }
        cout << "\033[0m";  // Reset text attributes

        A += 0.04;
        B += 0.02;
        this_thread::sleep_for(chrono::milliseconds(30));

        auto now = chrono::steady_clock::now();
        if (chrono::duration_cast<chrono::seconds>(now - lastColorChange).count() >= 1) {
            colorIndex = (colorIndex + 1) % 7;  // Cycle through colors every second
            lastColorChange = now;
        }
    }

    return 0;
}