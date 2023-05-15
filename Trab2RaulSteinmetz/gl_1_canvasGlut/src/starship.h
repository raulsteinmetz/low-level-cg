#ifndef STARSHIP_H
#define STARSHIP_H


#include <string>

class Starship {
private:
    // attributes
    double max_speed;
    double current_speed;
    int missile_delay;
    int bullet_delay;
    int hp;
    int bullet_power;
    int missile_power;
    int color_r;
    int color_g;
    int color_b;
    float polygon_x[3];
    float polygon_y[3];
    float angle;
    float radius;
    float gun_x;
    float gun_y;




public:
    // Constructor
    Starship(double max_speed, double current_speed, int missile_delay,
             int bullet_delay, int bullet_power, int missile_power, int hp,
             float px, float py, float radius);

    // Getter methods
    double getMaxSpeed();
    double getCurrentSpeed();
    int getMissileDelay();
    int getBulletDelay();
    int getHP();
    int getBulletPower();
    int getMissilePower();
    int getColor_r();
    int getColor_g();
    int getColor_b();

    float px;
    float py;



    // Setter methods
    void setMaxSpeed(double max_speed);
    void setCurrentSpeed(double current_speed);
    void setMissileDelay(int missile_delay);
    void setBulletDelay(int bullet_delay);
    void setHP(int hp);
    void setBulletPower(int bullet_power);
    void setMissilePower(int missile_power);
    void setColor_r(int color_r);
    void setColor_g(int color_g);
    void setColor_b(int color_b);



    void draw();
    void updatePos();
    void aim(float x, float y);

};

#endif // STARSHIP_H
