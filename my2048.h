#ifndef MY2048_H__
#define MY2048_H__

#include <iostream>
#include <ctime>

class my2048{
private:
    int m_size;
    int *m_a;

    static const int m_action_up    = 0;
    static const int m_action_down  = 1;
    static const int m_action_left  = 2;
    static const int m_action_right = 3;

public:
    my2048(int size)
    {   
        if(size <=1)
        {
            printf("Not valid size.\n");
            return;
        }
        m_size = size;
        m_a = (int*)malloc(sizeof(int) * m_size * m_size);
        memset(&m_a[0], 0, sizeof(int) * m_size * m_size);
        rand_init();
        set_val(rand() % m_size, rand() % m_size, 2);
    }
    
    ~my2048()
    {
        free(m_a);
    }

private:
    int get_val(int x, int y) // left & top is (0, 0)
    {
        return m_a[x * m_size + y];
    }
    void set_val(int x, int y, int val)
    {
        m_a[x * m_size + y] = val;
    }

    // init rand(), actually just set a seed.
    void rand_init()
    {
        srand((unsigned)time(0));
    }

    int gen_a_rand_val()
    {
        return rand() % 3 < 2 ? 2 : 4;
    }

    int get_zero_num();
    bool remove_zeros(int xy, int action);  // remove zeros in the x'th rows or y's colums 
    bool add_rand_val(void);                // invoked in the end of action_xxx()

    // action_xxx(): caculate any possible accumulations, and then invoke add_rand_val(xxx)
    bool action_up();
    bool action_down();
    bool action_left();
    bool action_right();

    bool is_lost();
    void print(bool b_going);

public:
    bool play();
};

#endif