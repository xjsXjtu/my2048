#include <iostream>
#include "conio.h"

#include "my2048.h"

bool my2048::remove_zeros(int xy, int action)
{
    bool b_changed = false;
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

            b_changed = (x != x_down);
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

            b_changed = (x != x_up);
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
        
            b_changed = (y != y_right);
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

            b_changed = (y != y_left);
        }
        break;
    default:
        printf("error in my2048::remove_zeros(): %d is not an illegal action", action);
        exit(-1);
    }
    return b_changed;
}

int my2048::get_zero_num()
{
    int zero_num = 0;
    for(int i=0; i<m_size*m_size; i++)
    {
        if(m_a[i]==0)
        {
            zero_num++;
        }
    }
    return zero_num;
}

int my2048::get_max_val()
{
    int max = m_a[0];
    for(int i=1; i<m_size*m_size; i++)
    {
        max = max > m_a[i] ? max : m_a[i];
    }
    return max;
}

bool my2048::add_rand_val(void)
{
    int zero_num = get_zero_num();
    if(zero_num == 0)
        return false;

    int rand_index = rand() % zero_num;
    int rand_val = gen_a_rand_val();

    for(int i=0; i<m_size*m_size; i++)
    {
        if(m_a[i] == 0)
        {
            if(rand_index == 0)
            {
                m_a[i] = rand_val;
                break;
            }
            rand_index--;
        }
    }
    return true;
}

bool my2048::accumulate_up()
{
    bool b_changed = false;
    for(int y = 0; y < m_size; y++)
    {
        b_changed |= remove_zeros(y, m_action_up);
        for(int x=0; x<m_size-1; )
        {
            if(get_val(x, y) > 0 && get_val(x, y) == get_val(x+1, y))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x+1, y, 0);
                x += 2;
                b_changed = true;
            }
            else
            {
                x++;
            }
        }
        b_changed |= remove_zeros(y, m_action_up);
    }
    return b_changed;
}

bool my2048::accumulate_down()
{
    bool b_changed = false;
    for(int y = 0; y < m_size; y++)
    {
        b_changed |= remove_zeros(y, m_action_down);
        for(int x=m_size-1; x>0; )
        {
            if(get_val(x, y) > 0 && get_val(x, y) == get_val(x-1, y))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x-1, y, 0);
                x -= 2;
                b_changed = true;
            }
            else
            {
                x--;
            }
        }
        b_changed |= remove_zeros(y, m_action_down);
    }
    return b_changed;
}

bool my2048::accumulate_left()
{
    bool b_changed = false;
    for(int x = 0; x < m_size; x++)
    {
        b_changed |= remove_zeros(x, m_action_left);
        for(int y=0; y<m_size-1; )
        {
            if(get_val(x, y) > 0 && get_val(x, y) == get_val(x, y+1))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x, y+1, 0);
                y += 2;
                b_changed = true;
            }
            else
            {
                y++;
            }
        }
        b_changed |= remove_zeros(x, m_action_left);
    }
    return b_changed;
}

bool my2048::accumulate_right()
{
    bool b_changed = false;
    for(int x = 0; x < m_size; x++)
    {
        b_changed |= remove_zeros(x, m_action_right);
        for(int y=m_size-1; y>0; )
        {
            if(get_val(x, y) > 0 && get_val(x, y) == get_val(x, y-1))
            {
                set_val(x, y, 2 * get_val(x, y));
                set_val(x, y-1, 0);
                y -= 2;
                b_changed = true;
            }
            else
            {
                y--;
            }
        }
        b_changed |= remove_zeros(x, m_action_right);
    }
    return b_changed;
}

bool my2048::is_lost()
{
    int x=0, y=0;
    for(x=0; x<m_size; x++)
    {
        for(y=0; y<m_size-1; y++)
        {
            if(get_val(x, y) == 0 || get_val(x, y) == get_val(x, y+1))
                return false;
        }
        if(get_val(x, y) == 0)
            return false;
    }
    for(y=0; y<m_size; y++)
    {
        for(x=0; x<m_size-1; x++)
        {
            if(get_val(x, y) == 0 || get_val(x, y) == get_val(x+1, y))
                return false;
        }
        if(get_val(x, y) == 0)
            return false;
    }
    return true;
}
void my2048::print()
{
    // clear screen 
    clear_screen();
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

    if(is_lost())
    {
        printf("Lose! Press q to try again.\n");
    }
}

void my2048::clear_screen()
{
    system("cls");
}

bool my2048::respond_one_action(int action)
{
    bool b_changed = false;
    switch(action)
        {
        case m_action_up:
            b_changed = accumulate_up();
            break;
        case m_action_down:
            b_changed = accumulate_down();
            break;
        case m_action_left:
            b_changed = accumulate_left();
            break;
        case m_action_right:
            b_changed = accumulate_right();
            break;
        default:
            printf("[my2048] Error action.\n");
            exit(-1);
        }
        if(b_changed)
        {
            add_rand_val();
        }
        return b_changed;
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
        int action;
        switch(ch)
        {
        case 'w':
            action = m_action_up;
            break;
        case 's':
            action = m_action_down;
            break;
        case 'a':
            action = m_action_left;
            break;
        case 'd':
            action = m_action_right;
            break;
        default:
            continue;
        }
        respond_one_action(action);
        print();
    }
    return true;
}