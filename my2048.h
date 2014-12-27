#ifndef MY2048_H__
#define MY2048_H__

#include <iostream>
#include <ctime>

class my2048{
private:
    int m_size;
    int *m_a;

public:
    static const int m_action_up    = 0;
    static const int m_action_down  = 1;
    static const int m_action_left  = 2;
    static const int m_action_right = 3;

public:
    my2048()
    {
#ifdef DEBUG_2048
        printf("[my2048] I am conscructor #1 of class m2048. size = 4\n");
#endif
        m_a = NULL;
        init(4);
    }

    my2048(int size)
    {
#ifdef DEBUG_2048
        printf("[my2048] I am conscructor #2 of class m2048. size = $d\n", size);
#endif
        m_a = NULL;
        init(size);
    }

    void init(int size)
    {
        destroy();

        if(size <=1)
        {
            printf("[my2048] Not valid size.\n");
            return;
        }
        m_size = size;
#ifdef DEBUG_2048
        printf("[my2048] Allocating memory: %d Bytes\n", sizeof(int) * m_size * m_size);
#endif
        m_a = (int*)malloc(sizeof(int) * m_size * m_size);
        memset(&m_a[0], 0, sizeof(int) * m_size * m_size);
        rand_init();
        set_val(rand() % m_size, rand() % m_size, 2);  
    }
    
    ~my2048()
    {
#ifdef DEBUG_2048
        printf("[my2048] I am descructor of class m2048\n");
#endif
        destroy();
    }

    void destroy()
    {
        if(m_a)
        {
#ifdef DEBUG_2048
            printf("[my2048] Freeing memory.\n");
#endif
            free(m_a);
        }
    }

private:
    int get_val(int x, int y)				// left & top is (0, 0)
    {
        return m_a[x * m_size + y];
    }
    void set_val(int x, int y, int val)
    {
        m_a[x * m_size + y] = val;
    }

    void rand_init()						// init rand(), actually just set a seed.
    {
        srand((unsigned)clock());
    }

    int gen_a_rand_val()
    {
        return rand() % 3 < 2 ? 2 : 4;
    }

private:
	void matrix_transpose(int *des, int *src, int dim);					// tranpose a square matrix
	void matrix_horizontal_symmetry(int *des, int *src, int dim);		// horizontally symmetry a square matrix
	void re_organize(int *des, int *src, int dim, 
		int action, bool direction);									// re organize m_a[...], so as to use accumulate_meta().
	bool remove_zeros_meta(int *meta);									// remove zeros in meta[0,...,(m_size-1)], towards to meta[0]
    bool remove_zeros(int xy, int action);								// remove zeros in the x'th rows or y's colums
	bool accumulate_meta(int *meta);									// accumulate one row/colum, accumulate towards meta[0]	
    bool accumulate(int action);										// accumulate(), caculate any possible accumulations
																		// return val: True if any accumulation happen.
    bool add_rand_val(void);											// invoked after invoking accumulate_xxx()
    
public:
    int size() {return m_size;}
    int get_zero_num(int *m, int size);
    int get_max_val();
    bool is_lost();

    bool respond_one_action(int action); // invoking accumulate_xxx(), then invoking add-rand_val(). return val: True if anything changed
    bool play();                         // manually play

    void print();
    void clear_screen();
};

#endif