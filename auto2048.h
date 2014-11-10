#ifndef AUTO_PLAY_H__
#define AUTO_PLAY_H__

#include <vector>
#include "my2048.h"

class auto2048{
private:
    my2048 game;

public:
    auto2048()
    {
        game.init(4);
    }
    auto2048(int size)
    {
        game.init(size);
    }
    ~auto2048()
    {
#ifdef DEBUG_2048
        printf("[auto2048] This is destructor.\n");
#endif
        // game.destroy(); // not need here, my2048::~my048() will invoked automatically.
    }
    
public:
    // stratage: always move up, if not move right, if not move down, if not move left, if not move up ...
    // input val: 
    //      b_show: if true, print the cells and pause 0.5 sec after each action.
    // return val: 
    //      the max value of the cells when game over.
    int autoplay_simple(bool b_show);

public:
    typedef int (auto2048::*PFUN)(bool);
    std::vector<int> evaluate_one_method(PFUN pfun_autoplay);   // playing 100 times. return value: a 100-element vector containg max-value of each time.
    void evaluate_all_methods();                                // evualte all autoplay methods.

    // return val:
    //  val[0]: max
    //  val[1]: min
    //  val[2]: average
    //  val[3]: standard deviation
    std::vector<double> calculate_statics(std::vector<int> v);
};

#endif