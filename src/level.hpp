#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <list>
#include <algorithm>
#include <sstream>
#include <map>

#include "filereader.hpp"
#include "Bird.hpp"
#include "Box.hpp"
#include "Ball.hpp"
#include "Destructables.hpp"
#include "Pig.hpp"
#include "Normal.hpp"
#include "Bomb.hpp"
#include "Speed.hpp"
#include "Points.hpp"
#include "collision_listener.hpp"
#include "state.hpp"
#include "Speed.hpp"



#ifndef LEVEL_CLASS
#define LEVEL_CLASS



class Vect{
    public:
        Vect() {}

        void SetVec(float x, float y) {
            x_ = x;
            y_ = y;
        }

        float x_;
        float y_;

        float GetLength() const {
            return sqrt(pow(x_,2)+pow(y_,2));
        }

        void Multiply(float m) {
            x_ *= m;
            y_ *= m;
        }

        void Divide(float d) {
            x_ /= d;
            y_ /= d;
        }
                
        void UnaryVect() {
            float len = GetLength();
            Divide(len);
        }

        void SetLen(float len) {
            UnaryVect();
            Multiply(len);
        }

        float GetAngle() {
            float ang = atan2(y_,x_);
            return ang;
        }
};


class Level {
    public:
        //initialises the level and puts the first pig into the cannon
        Level(std::string filename);

        std::vector<Pigc> GetPigs() const {
            return pigs_;
        }

        state Update(sf::RenderWindow& window, sf::Event& ev);
        void Simulate();
        void DrawLevel(sf::RenderWindow& window);


        //deconstructs the level, is where the level end screen will be determined
        ~Level() {
            
            delete current_pig_;
            
            for (auto i : box_) {
                delete i;
            }
            for (auto i : ball_) {
                delete i;
            }
            for (auto i : birds_) {
                delete i;
            }
            //std::cout << points_->GetPoints() << std::endl;
            delete points_;
            
            delete draw_;
            delete collisions_;
            delete world_;
        }
        


    private:
        //functions
        void NextPig();
        void CreateGround();
        void DrawGround(sf::RenderWindow& target);
        void FirePig();
        void ReadyCannon(float x, float y);
        float GetDistance(float x1, float y1, float x2, float y2);
        void DrawCannon(sf::RenderWindow& window);
        void DrawScore(sf::RenderWindow& window);
        void DeleteDestroyed();
        
        void ControlView();
        void LastLevelCleared();
        void LevelStars();
        void DrawPigcount(sf::RenderWindow& window);
        

        //general variables
        const float SCALE_ = 30.f;
        b2World* world_;
        sf::View view_;
        const int LEVELCOUNT_ = 3; //map.size() should work also

        //constructor variables maybe added to stuff
        //float box_height;
        //float box_width_;
        //float box_angle_ = 0;
        float ball_radius_ = 30;
        float bird_radius_ = 30;


        //box2d variables
        float timeStep_ = 1.0f / 60.0f;
        int32 velocityIterations_ = 8;
        int32 positionIterations_ = 3;

        //update variables
        bool running_ = true;
        Points* points_;
        bool pig_flying_;
        bool pig_drawn_;
        Vect* draw_;
        float max_draw_ = 120; //how big the max draw can be
        float angle_ = 0;
        float pig_time_ = 0;
        sf::CircleShape cannnon_hitbox_;
        float resize_ = 1;
        float cannon_power_ = 8 ; //defines the max velocity of the pig smaller = bigger

        //camera control
        float viewxpos_;
        bool pig_passed_viewxpos_ = false;
        bool move_to_right_ = false;
        bool move_to_left_ = false;
        bool custom_camera_;
        bool moving_camera_;
        float camera_offset_;
        float last_mouse_x_;

        std::vector<Pigc> pigs_;
        Pig* current_pig_;
        std::vector<Pig*> old_pigs_;
        std::vector<Bird*> birds_;
        std::vector<Destructables*> objects_;
        std::vector<Box*> box_;
        std::vector<Ball*> ball_;
        std::vector<struct Groundc> ground_;
        struct Cannonc cannon_;
        collision_listener* collisions_;
        int level_;
        struct Stars stars_;
        std::string highscore_file_;
};

#endif
