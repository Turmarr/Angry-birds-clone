#ifndef POINTS_CLASS
#define POINTS_CLASS

class Points {
    public:
        Points() : points_(0) { }

        void AddPoints(int points) {
            points_ += points;
        }

        int GetPoints() const {
            return points_;
        }

    private:
        int points_;
};

#endif