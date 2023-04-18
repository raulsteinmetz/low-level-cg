#ifndef FIGURE_H
#define FIGURE_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define DRAW_FUNCTION_DELAY 500
// figures
#define CIRCLE 0
#define MAX_CIRCLES 100

class Figure {
   public:
      float colorR;
      float colorB;
      float colorG;
      Figure();
      Figure(float r, float g, float b);
      //virtual void draw() = 0;
};

// Circle class inherits from Figure
class Circle : public Figure {
   public:
      int cX;
      int cY;
      int sides;
      int radius;
      float angle;
      int filled;

      Circle();
      Circle(int cX, int cY, int sides, int radius, float r, float g, float b, float angle);

      void draw();
};




class FigureDrawer {
    public:
        float current_color_red;
        float current_color_green;
        float current_color_blue;
        float current_radius;
        float current_sides;
        float angle;
        int fill;
        Circle circles[MAX_CIRCLES];
        int n_circles;
        int draw_delay;
        FigureDrawer(float red, float green, float blue);
        void add_circle(int x, int y);

        void save_to_file(const std::string& file_name, const std::string& key) {
            std::ofstream file(file_name, std::ios::binary);
            if (file.is_open()) {
                // XOR encryption
                std::string data(reinterpret_cast<char*>(this), sizeof(FigureDrawer));
                for (size_t i = 0; i < data.length(); i++) {
                    data[i] ^= key[i % key.length()];
                }
                file << data;
                file.close();
            }
        }

        void load_from_file(const std::string& file_name, const std::string& key) {
            std::ifstream file(file_name, std::ios::binary);
            if (file.is_open()) {
                // Read the encrypted data into a string
                std::string encrypted_data;
                file.seekg(0, std::ios::end);
                encrypted_data.resize(file.tellg());
                file.seekg(0, std::ios::beg);
                file.read(&encrypted_data[0], encrypted_data.size());

                // Decrypt the data using the key
                std::string data;
                data.resize(encrypted_data.length());
                for (size_t i = 0; i < encrypted_data.length(); i++) {
                    data[i] = encrypted_data[i] ^ key[i % key.length()];
                }

                // Copy the decrypted data to this object
                memcpy(reinterpret_cast<char*>(this), data.c_str(), sizeof(FigureDrawer));
                file.close();
            }
        }
};

#endif // FIGURE_H
