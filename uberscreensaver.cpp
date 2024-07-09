#include <ScreenSaver.h>
#include <View.h>
#include <cmath>
#include <random>
#include <vector>

struct Square {
    float cx;
    float cy;
    float cxl2;
    float cyl2;
    float cxl3;
    float cyl3;
    float angle;
    float border;
};

class screensaver : public BScreenSaver {
    std::vector<Square> squares;
    std::vector<Square> squaresl2;
    std::vector<Square> squaresl3;
    int squareCount;
    int squareCountl2;
    int squareCountl3;

    public:
    screensaver(BMessage* archive, image_id id)
        : BScreenSaver(archive, id), squareCount(20) {
        startSquares();
    }

    void startSquares() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> disX(0, 2000);
        std::uniform_real_distribution<> disY(0, 1000);

        for (int i = 0; i < squareCount; ++i) {
            Square square;
            square.cx = disX(gen);
            square.cy = disY(gen);
            square.angle = 0;
            squares.push_back(square);

            Square squarel2;
            squarel2.cxl2 = disX(gen);
            squarel2.cyl2 = disY(gen);
            squarel2.angle = 0;
            squaresl2.push_back(square);

            Square squarel3;
            squarel3.cxl3 = disX(gen);
            squarel3.cyl3 = disY(gen);
            squarel3.angle = 0;
            squaresl3.push_back(square);
        }
    }

    void setSquareCount(int count) {
        squareCount = count;
        squares.clear();
        squaresl2.clear();
        squaresl3.clear();
        startSquares();
    }

    void Draw(BView* view, int32 frame) override {
        rgb_color pink = {255,204,221};
        view->SetHighColor(pink);
        view->FillRect(view->Bounds());

        BRect bounds = view->Bounds();
        float squareSize = bounds.Width() / 50;
        float squareSizel2 = bounds.Width() / 60;
        float squareSizel3 = bounds.Width() / 90;
        float borderSize = squareSize / 10;
        float borderSizel2 = squareSizel2 / 10;
        float borderSizel3 = squareSizel2 / 10;

        for (auto& square : squaresl3) {
            square.angle += 0.1;
            if (square.angle >= 2 * M_PI) {
                square.angle -= 2 * M_PI;
            }

            BPoint pointsl3[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                pointsl3[i].x = square.cxl3 + (squareSizel3 /2) * cos(cornerAngle);
                pointsl3[i].y = square.cyl3 + (squareSizel3 /2) * sin(cornerAngle);
            }

            BPoint bordersl3[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                bordersl3[i].x = square.cxl3 + ((squareSizel3/2) + borderSizel3) * cos(cornerAngle);
                bordersl3[i].y = square.cyl3 + ((squareSizel3/2) + borderSizel3) * sin(cornerAngle);
            }

            square.cyl3 += 5;
            if (square.cyl3 >= bounds.Height() + 200) {
                square.cyl3 = 2;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> disX(0, bounds.Width());
                std::uniform_real_distribution<> disY(-bounds.Height(), 0);
                square.cxl3 = disX(gen);
                square.cyl3 = disY(gen);
            }

            rgb_color darkpink = {255,102,179};
            rgb_color white = {255, 255, 255, 255};

            view->SetHighColor(darkpink);
            view->FillPolygon(bordersl3, 4);

            view->SetHighColor(white);
            view->FillPolygon(pointsl3, 4);

        }


        for (auto& square : squaresl2) {
            square.angle += 0.1;
            if (square.angle >= 2 * M_PI) {
                square.angle -= 2 * M_PI;
            }

            BPoint pointsl2[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                pointsl2[i].x = square.cxl2 + (squareSizel2 /2) * cos(cornerAngle);
                pointsl2[i].y = square.cyl2 + (squareSizel2 /2) * sin(cornerAngle);
            }

            BPoint bordersl2[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                bordersl2[i].x = square.cxl2 + ((squareSizel2/2) + borderSizel2) * cos(cornerAngle);
                bordersl2[i].y = square.cyl2 + ((squareSizel2/2) + borderSizel2) * sin(cornerAngle);
            }

            square.cyl2 += 5;
            if (square.cyl2 >= bounds.Height() + 200) {
                square.cyl2 = 2;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> disX(0, bounds.Width());
                std::uniform_real_distribution<> disY(-bounds.Height(), 0);
                square.cxl2 = disX(gen);
                square.cyl2 = disY(gen);
            }

            rgb_color darkpink = {255,102,179};
            rgb_color white = {255, 255, 255, 255};

            view->SetHighColor(darkpink);
            view->FillPolygon(bordersl2, 4);

            view->SetHighColor(white);
            view->FillPolygon(pointsl2, 4);

        }

        for (auto& square : squares) {
            square.angle += 0.1;
            if (square.angle >= 2 * M_PI) {
                square.angle -= 2 * M_PI;
            }

            BPoint points[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                points[i].x = square.cx + (squareSize /2) * cos(cornerAngle);
                points[i].y = square.cy + (squareSize /2) * sin(cornerAngle);
            }

            BPoint borders[4];
            for (int i = 0; i < 4; i++) {
                float cornerAngle = square.angle + i * M_PI_2;
                borders[i].x = square.cx + ((squareSize/2) + borderSize) * cos(cornerAngle);
                borders[i].y = square.cy + ((squareSize/2) + borderSize) * sin(cornerAngle);
            }

            square.cy += 5;
            if (square.cy >= bounds.Height() + 200) {
                square.cy = 2;
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<> disX(0, bounds.Width());
                std::uniform_real_distribution<> disY(-bounds.Height(), 0);
                square.cx = disX(gen);
                square.cy = disY(gen);
            }

            rgb_color darkpink = {255,102,179};
            rgb_color white = {255, 255, 255, 255};

            view->SetHighColor(darkpink);
            view->FillPolygon(borders, 4);

            view->SetHighColor(white);
            view->FillPolygon(points, 4);

        }


    }
};

extern "C" BScreenSaver* instantiate_screen_saver(BMessage* msg, image_id id) {
    return new screensaver(msg, id);
}
