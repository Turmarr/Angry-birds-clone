#include <algorithm>
#include "Box2D/box2d/box2d.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <sstream>
#include "level.hpp"





Level::Level(std::string filename) {

    //init pointcounter
    points_ = new Points();
    draw_ = new Vect();
     

    //std::cout << "pig" << std::endl;
    b2Vec2 gravity (0.0f, 10.0f);
    //b2World *world(gravity);
    world_ = new b2World(gravity);

    collisions_ = new collision_listener();
    world_->SetContactListener(collisions_);

    //std::cout << "pig" << std::endl;

    Filereader info(filename);
    level_ = info.GetLevel();
    //std::cout << "file" << std::endl;

    ground_ = info.GetGround();
    CreateGround();

    auto temp_pigs = info.GetPigs();
    sort(temp_pigs.begin(), temp_pigs.end(), [](Pigc a, Pigc b) {return a.pos < b.pos;});
    for (auto i : info.GetPigs()) {
        pigs_.push_back(i);
    }

    //std::cout << "pig" << std::endl;
    
    for (auto i : info.GetBirds()) {
        Bird *bird = new Bird(i.x, i.y, *world_, SCALE_, bird_radius_, points_);
        birds_.push_back(bird);
    }

    //std::cout << birds_.size() << std::endl;
    
    for (auto i : info.GetObjects()) {
        if (i.type == "box") {
            Box *object = new Box(i.x, i.y, i.material, i.width, i.height, i.angle, *world_, SCALE_, points_);
            box_.push_back(object);
        }
        if (i.type == "ball") {
            Ball *object = new Ball(i.x, i.y, i.material, i.radius, *world_, SCALE_, points_);
            ball_.push_back(object);
        }
    }

    //std::cout << "object" << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << ball_.size() << std::endl;

    for (auto i : info.GetGround()) {
        ground_.push_back(i);
    }

    cannon_ = info.GetCannon();

    NextPig();

    view_.setCenter(sf::Vector2f(400.f,300.f));
    view_.setSize(sf::Vector2f(800.f, 600.f));
    //std::cout << "all" << std::endl;
    //std::cout << birds_.size() << std::endl;
    //std::cout << box_.size() << std::endl;
    //std::cout << world_->GetBodyCount() << std::endl;
    cannnon_hitbox_.setPosition(cannon_.x,cannon_.y);
    cannnon_hitbox_.setRadius(20);
    cannnon_hitbox_.setFillColor(sf::Color::Red);
    
    stars_ = info.GetStars();
    highscore_file_ = info.GetHighScoreFile();
    viewxpos_ = cannon_.x;
    custom_camera_ = false;
    moving_camera_ = false;
    camera_offset_ = 175;
    
}

void Level::LastLevelCleared() {
    int level = 0;
    std::ifstream ifs("../src/Levels/lastlevel.txt");
    if (ifs.rdstate() & (ifs.failbit | ifs.badbit)) { }
    else {
        ifs >> level;
        ifs.close();
        //std::cout << level << std::endl;
    }
    if (level > level_) {
        level_ = level;
    }
    std::ofstream ofs("../src/Levels/lastlevel.txt");
    //std::cout << level_ << std::endl;
    ofs << level_;
    ofs.close();
}

void Level::NextPig() {
    //std::cout << pigs_.size() << std::endl;
    viewxpos_ = cannon_.x;
    camera_offset_ = 175;
    pig_passed_viewxpos_ = false;
    pig_flying_ = false;
    pig_drawn_ = false;
    if (pigs_.size() != 0) {
        //std::cout << "adding" << std::endl;
        Pigc current = pigs_.back();
        pigs_.pop_back();
        if (current.type == "normal") {
            Normal *pig = new Normal(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else if (current.type == "bomb") {
            Bomb *pig = new Bomb(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else if (current.type == "speed") {
            Speed *pig = new Speed(cannon_.x / SCALE_, cannon_.y / SCALE_, world_);
            current_pig_ = pig;
        }
        else {
            current_pig_ = nullptr;
        }
    }
    else {
        current_pig_ = nullptr;
        //std::cout << "null" << std::endl;
    }
}

void Level::CreateGround() {
    for (auto i : ground_) {
        b2BodyDef groundBodyDef;
        groundBodyDef.type = b2_staticBody;
        groundBodyDef.position.Set(i.x/SCALE_, i.y/SCALE_);
        
        b2Body* body = world_->CreateBody(&groundBodyDef);
        
        b2PolygonShape groundBox;
        groundBox.SetAsBox((i.width/2) / SCALE_, (i.height/2) / SCALE_);

        body->CreateFixture(&groundBox, 0.0f);
    }
}

void Level::DrawGround(sf::RenderWindow& window) {
    for (auto i : ground_) {
        sf::RectangleShape ground { { i.width, i.height } };
        ground.setOrigin(i.width/2, i.height/2);
        ground.setPosition(i.x, i.y);
        //ground.setRotation(groundBody->GetAngle() * 180/b2_pi);
        ground.setFillColor(sf::Color(8, 130, 16));
        sf::RectangleShape line(sf::Vector2f(i.width, 2));
        line.setOrigin(i.width/2, i.height/2);
        line.setPosition(i.x, i.y );
        line.setFillColor(sf::Color::Black);
        window.draw(ground);
        window.draw(line);
    }
}

void Level::DrawScore(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../src/Fonts/arial.ttf")) {
        std::cout << "error getting font"<< std::endl;
    }
    sf::Text text;
    text.setFont(font);
    std::stringstream ss;
    ss << points_->GetPoints();
    text.setString(ss.str());
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(10.f,10.f));
    text.setPosition(worldPos.x, worldPos.y);
    window.draw(text);
}

void Level::DrawPigcount(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("../src/Fonts/arial.ttf")) {
        std::cout << "error getting font"<< std::endl;
    }
    sf::Text text;
    text.setFont(font);
    std::stringstream ss;
    ss << "Pigs left: " << pigs_.size() + 1 << " Next Pig: " << current_pig_->GetType();
    text.setString(ss.str());
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Red);
    sf::Vector2f worldPos = window.mapPixelToCoords(sf::Vector2i(10.f,40.f));
    text.setPosition(worldPos.x, worldPos.y);
    window.draw(text);
}

void Level::DrawCannon(sf::RenderWindow& window) {
    cannnon_hitbox_.setOrigin(cannnon_hitbox_.getLocalBounds().width/2, cannnon_hitbox_.getLocalBounds().height/2);
    
    sf::RectangleShape shape;
    shape.setPosition(cannon_.x, cannon_.y);
    shape.setSize(sf::Vector2f(90,60));
    shape.setOrigin(30,30);
    shape.rotate(angle_);
    shape.setFillColor(sf::Color::Black);
    

    sf::RectangleShape shape2;
    shape2.setSize(sf::Vector2f(30, ground_[0].y));
    shape2.setOrigin(15,0);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition(cannon_.x,cannon_.y);
    


    if (pig_drawn_) {
        Vect offset;
        offset.SetVec(draw_->x_,draw_->y_);
        offset.SetLen(70);
        sf::ConvexShape arrow;
        arrow.setPointCount(3);
        arrow.setPoint(0, sf::Vector2f(0,0));
        arrow.setPoint(1, sf::Vector2f(draw_->GetLength(),10));
        arrow.setPoint(2, sf::Vector2f(0,20));
        arrow.setOrigin(0,10);
        arrow.setFillColor(sf::Color::Red);
        arrow.rotate(angle_);
        arrow.setPosition(cannon_.x + offset.x_, cannon_.y + offset.y_);
        window.draw(arrow);
    }

    window.draw(shape);
    window.draw(shape2);
    window.draw(cannnon_hitbox_);
    
}

float Level::GetDistance(float x1, float y1, float x2, float y2) {
    float dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return dist;
}

void Level::ReadyCannon(float x, float y) {
    draw_->SetVec(cannon_.x - x, cannon_.y - y);
    if (draw_->GetLength() > max_draw_) {
        draw_->SetLen(max_draw_);
    }
    angle_ = draw_->GetAngle() * 180 / b2_pi;
    //add the rotating of the cannon and the possible arrow
}

void Level::FirePig() {
    current_pig_->SetDynamic();
    current_pig_->SetAngle(angle_ * b2_pi / 180);
    current_pig_->SetVelocity(b2Vec2(draw_->x_/cannon_power_, draw_->y_/cannon_power_));
    pig_flying_ = true;
    pig_drawn_ = false;
}

void Level::DeleteDestroyed() {
    std::vector<Bird*>::iterator it = birds_.begin();
    for (; it != birds_.end(); ) {
        //std::cout << "birdhp" << (*it)->GetHp() << std::endl;
        if ((*it)->GetHp() <= 0) {
            delete *it;
            it = birds_.erase(it);
        }
        else {it++;}
    }
    std::vector<Ball*>::iterator itb = ball_.begin();
    for (; itb != ball_.end(); ) {
        if ((*itb)->GetHp() <= 0) {
            delete *itb;
            itb = ball_.erase(itb);
        }
        else {itb++;}
    }
    std::vector<Box*>::iterator itx = box_.begin();
    for (; itx != box_.end(); ) {
        if ((*itx)->GetHp() <= 0) {
            delete *itx;
            itx = box_.erase(itx);
        }
        else {itx++;}
    }
}

void Level::DrawLevel(sf::RenderWindow& window) {
    window.setView(view_);
    window.clear(sf::Color::White);
    DrawCannon(window);
    DrawGround(window);
    
    if (current_pig_ != nullptr && pig_flying_) {
        current_pig_->Draw(window);
    }

    for (auto i : birds_) {
        i->Draw(window);
    }
    for (auto i : box_) {
        i->Draw(window);
    }
    for (auto i : ball_) {
        i->Draw(window);
    }

    DrawScore(window);
    //DrawPigcount(window);

    window.display();
}


//controls the camera, currently moving from destroyed pig
//back to cannon abrupt, mousescroll for zoom
void Level::ControlView() {
    view_.zoom(resize_);
    float vsx = view_.getSize().x;
    float vsy = view_.getSize().y;
    float fh = ground_[0].y + ground_[0].height/2;
    float vpy = fh - vsy/2;
    if (pig_flying_) {
        float vpx = current_pig_->GetPosition().x *SCALE_;
        if (vpx >= viewxpos_) {
            pig_passed_viewxpos_ = true;
        } 
        if (pig_passed_viewxpos_) {
            viewxpos_ = vpx;
        }
    }
    else {
        viewxpos_ = cannon_.x + 75 + camera_offset_;
    }
    
    if (move_to_right_) {
        camera_offset_ += 2;
    }
    if (move_to_left_) {
        camera_offset_ -= 2;
        
    }
    if (viewxpos_ <= cannon_.x) {
        viewxpos_ = cannon_.x;
    }
    if (viewxpos_ >= cannon_.x + 1500) {
        viewxpos_ = cannon_.x + 1500;
    }
    view_.setCenter(viewxpos_,vpy);
    resize_ = 1;
    //std::cout << vpx << " " << vpy << std::endl;
}

void Level::Simulate() {
    world_->Step(timeStep_, velocityIterations_, positionIterations_);

    if (current_pig_ != nullptr && pig_flying_) {
            if (current_pig_->GetSpeed() <= 0.1) {
                pig_time_ += 1;
                if (pig_time_ >= 60) {
                    delete current_pig_;
                    NextPig();
                }
            }
            else {
                pig_time_ = 0;
            }
        }
    //resize_ = 1;
    ControlView();
}

void Level::LevelStars() {
    std::map<int,int> star;
    std::ifstream is("../src/Levels/stars.txt");
    if (is.rdstate() & (is.failbit | is.badbit)) { }
    else {
        while(!is.eof()) {
            std::string line;
            std::getline(is, line);
            std::stringstream ss;
            ss << line;
            int starcount;
            int level;
            ss >> level >> starcount;
            
            star[level] = starcount;
        }
        is.close();
    }
    int current_stars;
    if (points_->GetPoints() >= stars_.third) {
        current_stars = 3;
    }
    else if (points_->GetPoints() >= stars_.second) {
        current_stars = 2;
    }
    else {
        current_stars = 1;
    }

    if (star[level_] < current_stars) {
        star[level_] = current_stars;
    }
    std::ofstream os("../src/Levels/stars.txt");
    for (int i = 1; i <= LEVELCOUNT_; i++) { //map.size() should work also
        os << i << " " << star[i] << "\n";
    }
    os.close();
    

}

state Level::Update(sf::RenderWindow& window, sf::Event& ev) {
    
    DeleteDestroyed();
    state state;
    
    //setup exiting the loop once the last pig dies

    resize_ = 1; //is needed so that the window stays the same size when not scrolling
    switch (ev.type)
    {
        case sf::Event::Closed:
            state.i = 3;
            return state;
        case sf::Event::MouseButtonPressed:
            if (pig_flying_) {
                current_pig_->Special();
            }
            else if (!pig_flying_ && current_pig_ != nullptr) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                float x = worldPos.x;
                float y = worldPos.y;
                if (cannnon_hitbox_.getGlobalBounds().contains(x,y)) {
                    pig_drawn_ = true;
                    custom_camera_ = false;
                }
                else {
                    custom_camera_ = true;
                    moving_camera_ = true;
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                    last_mouse_x_ = worldPos.x;
                }
            }
            break;
        case sf::Event::MouseMoved:
            if (pig_drawn_) {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                float x = worldPos.x;
                float y = worldPos.y;
                ReadyCannon(x,y);
            }
            if(moving_camera_){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                float x = worldPos.x;
                camera_offset_ += (last_mouse_x_ - x) / 20;
            }
            // This helps with level designing
            // Comment this out later
            if(custom_camera_){
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
                std::cout <<  worldPos.x <<"," << worldPos.y << std::endl;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (pig_drawn_) {
                FirePig();
            }
            if(moving_camera_){
                moving_camera_ = false;
            }
            break;
        case sf::Event::MouseWheelScrolled:
            if (ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                float ticks = ev.mouseWheelScroll.delta;
                resize_ = 1-ticks*0.01;
                //std::cout << resize_ << std::endl;
            }
            break;
        case sf::Event::Resized: {
            sf::FloatRect visibleArea(0.f, 0.f, ev.size.width, ev.size.height);
            view_.reset(visibleArea);
            break;
        }
        case sf::Event::KeyPressed:
            switch (ev.key.code) {
                case sf::Keyboard::Right:
                    move_to_right_ = true;
                    break;
                case sf::Keyboard::Left:
                    move_to_left_ = true;
                    break;
                case sf::Keyboard::Escape:
                    state.i = 5;
                    state.points = -1;
                    return state;
                default:
                    break;
                }
            break;
        case sf::Event::KeyReleased:
            switch (ev.key.code) {
                case sf::Keyboard::Right:
                    move_to_right_ = false;
                    break;
                case sf::Keyboard::Left:
                    move_to_left_ = false;
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
    }
    
    
    if ((current_pig_ != nullptr && birds_.size() != 0) || pig_flying_) {
        state.i = 4;
        return state;
    }
    else {
        state.i = 5;
        state.points = -1;
        if (birds_.size() == 0) {
            for (auto i : pigs_) {
                points_->AddPoints(1000);
            }
            if (current_pig_ != nullptr) {
                points_->AddPoints(1000);
            }
            state.points = points_->GetPoints();
            LevelStars();
            LastLevelCleared();
            std::stringstream ss;
            ss << highscore_file_;
            ss >> state.file;
        }
        return state;
    }
    
}
