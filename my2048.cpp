#include <iostream>
#include "conio.h"

#include "my2048.h"

void my2048::remove_zeros(int xy, int action)
{
    // caculate zeros number
    int zero_num = 0;
    switch(action)
    {
    case m_action_up: case m_action_down:
        {
            for(int x=0; x<m_size; x++)
            {
                if(get_val(x, xy) == 0)
                {
                    zero_num++;
                }
            }
        }
        break;
    case m_action_left: case m_action_right:
        {
            for(int y=0; y<m_size; y++)
            {
                if(get_val(xy, y) == 0)
                {
                    zero_num++;
                }
            }
        }
        break;
    default:
        printf("error in my2048::remove_zeros(): %d is not an illegal action", action);
        exit(-1);
    }

    // remove zeros
    switch(action){
    case m_action_up:
        {
            int x=0, x_down=0;
            for(int i=0; i<m_size - zero_num; i++)
            {
                while(get_val(x_down, xy)==0)
                    x_down++;
                set_val(x, xy, get_val(x_down, xy));
                x++;
                x_down++;
            }
            for(int i=0; i<zero_num; i++)
                set_val(m_size - 1 - i, xy, 0);
        }
        break;
    case m_action_down:
        {
            int x=m_size-1, x_up=m_size-1;
            for(int i=0; i<m_size - zero_num; i++)
            {
                while(get_val(x_up, xy)==0)
                    x_up--;
                set_val(x, xy, get_val(x_up, xy));
                x--;
                x_up--;
            }
            for(int i=0; i<zero_num; i++)
                set_val(i, xy, 0);
        }
        break;
    case m_action_left:
        {
            int y=0, y_right=0;
            for(int i=0; i<m_size - zero_num; i++)
            {
                while(get_val(xy, y_right)==0)
                    y_right++;
                set_val(xy, y, get_val(xy, y_right));
                y++;
                y_right++;
            }
            for(int i=0; i<zero_num; i++)
                set_val(xy, m_size - 1 - i, 0);
        }
        break;
    case m_action_right:
        {
            int y=m_size-1, y_left=m_size-1;
            for(int i=0; i<m_size - zero_num; i++)
            {
                while(get_val(xy, y_left)==0)
                    y_left--;
                set_val(xy, y, get_val(xy, y_left));
                y--;
                y_left--;
            }
            for(int i=0; i<zero_num; i++)
                set_val(xy, i, 0);
        }
        break;
    default:
        printf("error in my2048::remove_zeros(): %d is not an illegal action", action);
        exit(-1);
    }

}

bool my2048::add_rand_val(int action)
{
    switch(action)
    {
        case m_action_up:
            {
                int base_index = 3 * m_size;
                if(m_a[base_index] && m_a[base_index + 1] && m_a[base_index + 2] && m_a[base_index + 3])
                {
                    // already full in the bottom line
                    return false;
                }

                // fill a rand value(2 or 4) in a random blank cell 
                int rand_index = rand() % m_size + base_index;
                while(m_a[rand_index])
                {
                    rand_index = rand() % m_size + base_index;
                }
                m_a[rand_index] = gen_a_rand_val();
            }
            break;

        case m_action_down:
            {
                int base_index = 0 * m_size;
                if(m_a[base_index] && m_a[base_index + 1] && m_a[base_index + 2] && m_a[base_index + 3])
                {
                    // already full in the top line
                    return false;
                }

                // fill a rand value(2 or 4) in a random blank cell 
                int rand_index = rand() % m_size + base_index;
                while(m_a[rand_index])
                {
                    rand_index = rand() % m_size + base_index;
                }
                m_a[rand_index] = gen_a_rand_val();
            }
            break;

        case m_action_left:
            {
            int base_index = m_size - 1;
            if(m_a[base_index] && m_a[base_index + 1 * m_size] && m_a[base_index + 2 * m_size] && m_a[base_index + 3 * m_size])
            {
                // already full in the right line
                return false;
            }

            // fill a rand value(2 or 4) in a random blank cell 
            int rand_index = base_index + (rand() % m_size) * m_size;
            while(m_a[rand_index])
            {
                rand_index = base_index + (rand() % m_size) * m_size;
            }
            m_a[rand_index] = gen_a_rand_val();
            }
            break;

        case m_action_right:
            {
                int base_index = 0;
                if(m_a[base_index] && m_a[base_index + 1 * m_size] && m_a[base_index + 2 * m_size] && m_a[base_index + 3 * m_size])
                {
                    // already full in the left line
                    return false;
                }

                // fill a rand value(2 or 4) in a random blank cell 
                int rand_index = base_index + (rand() % m_size) * m_size;
                while(m_a[rand_index])
                {
                    rand_index = base_index + (rand() % m_size) * m_size;
                }
                m_a[rand_index] = gen_a_rand_val();
            }
            break;

        default:
            printf("error action!!");
            exit(-1);
    }
}

bool my2048::action_up()
{
    for(int y = 0; y < m_size; y++)
    {
        remove_zeros(y, m_action_up);
        for(int x=0; x<m_size-1; )
        {
            if(get_val(x, y) == get_val(x+1, y))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x+1, y, 0);
                x += 2;
            }
            else
            {
                x++;
            }
        }
        remove_zeros(y, m_action_up);
    }
    // add new rand val
    return add_rand_val(m_action_up);
}

bool my2048::action_down()
{
    for(int y = 0; y < m_size; y++)
    {
        remove_zeros(y, m_action_down);
        for(int x=m_size-1; x>0; )
        {
            if(get_val(x, y) == get_val(x-1, y))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x-1, y, 0);
                x -= 2;
            }
            else
            {
                x--;
            }
        }
        remove_zeros(y, m_action_down);
    }

    return add_rand_val(m_action_down);
}

bool my2048::action_left()
{
    for(int x = 0; x < m_size; x++)
    {
        remove_zeros(x, m_action_left);
        for(int y=0; y<m_size-1; )
        {
            if(get_val(x, y) == get_val(x, y+1))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x, y+1, 0);
                y += 2;
            }
            else
            {
                y++;
            }
        }
        remove_zeros(x, m_action_left);
    }
    return add_rand_val(m_action_left);
}

bool my2048::action_right()
{
    for(int x = 0; x < m_size; x++)
    {
        remove_zeros(x, m_action_right);
        for(int y=m_size-1; y>0; )
        {
            if(get_val(x, y) == get_val(x, y-1))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x, y-1, 0);
                y -= 2;
            }
            else
            {
                y--;
            }
        }
        remove_zeros(x, m_action_right);
    }

    return add_rand_val(m_action_right);
}

void my2048::print()
{
    // clear screen 
    system("cls");
    printf("a: left; d: right\n");
    printf("w: up  ; s: down\n");
    printf("q: quit\n\n");

    // print m_a[x,y]
    for(int x=0; x<m_size; x++)
    {
        for(int i=0; i<m_size; i++)
        {
            printf("--------");
        }
        printf("-\n");
            
        for(int y=0; y<m_size; y++)
        {
            int val = get_val(x, y);
            if(val)
            {
                printf("|%4d\t", val);
            }
            else
            {
                printf("|\t");
            }
        }
        printf("|\n");
    }

    for(int i=0; i<m_size; i++)
    {
        printf("--------");
    }
    printf("-\n");
}

bool my2048::play()
{
    print();
    while(1)
    {
        // quit
        char ch = getch();
        if(ch == 'q')
            break;

        switch(ch)
        {
        case 'w':
            action_up();
            break;
        case 's':
            action_down();
            break;
        case 'a':
            action_left();
            break;
        case 'd':
            action_right();
            break;
        }
        print();
    }
    return true;
}