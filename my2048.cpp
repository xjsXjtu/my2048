#include <iostream>
#include <assert.h>
#include "conio.h"

#include "my2048.h"

int my2048::get_zero_num(int *m, int size)
{
    int zero_num = 0;
    for(int i=0; i<size; i++)
    {
        if(m[i]==0)
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
    int zero_num = get_zero_num(m_a, m_size * m_size);
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
void my2048::matrix_transpose(int *des, int *src, int dim)				// tranpose a square matrix
{
	assert(des != NULL && src != NULL);
	for(int x=0; x<dim; x++)
	{
		for(int y=0; y<dim; y++)
		{
			des[x * dim + y] = src[y * dim + x];
		}
	}
}

void my2048::matrix_horizontal_symmetry(int *des, int *src, int dim)	// horizontally symmetry a square matrix
{
	assert(des != NULL && src != NULL);
	for(int x=0; x<dim; x++)
	{
		for(int y=0; y<dim; y++)
		{
			des[x * dim + y] = src[x * dim + dim - 1 - y];
		}
	}
}

void my2048::re_organize(int *des, int *src, int dim,					// re organize m_a[...], so as to use accumulate_meta().
						 int action, bool direction)					// direction: true->transform from m_a to re_org; false->restore from re_org to m_a 
{
	assert(des != NULL && src != NULL);
	switch(action)
	{
	case m_action_left:
		memcpy(des, src, m_size * m_size * sizeof(int));
		break;
	case m_action_right:
		matrix_horizontal_symmetry(des, src, m_size);
		break;
	case m_action_up:
		matrix_transpose(des, src, m_size);
		break;
	case m_action_down:
		{
			int *tmp = (int*)malloc(dim * dim * sizeof(int));
			if(direction)
			{
				matrix_transpose(tmp, src, m_size);
				matrix_horizontal_symmetry(des, tmp, m_size);
			}
			else
			{
				matrix_horizontal_symmetry(tmp, src, m_size);
				matrix_transpose(des, tmp, m_size);
			}
			free(tmp);
		}
		break;
	default:
		break;
	}
}

bool my2048::remove_zeros_meta(int *meta)
{
	int zero_num = get_zero_num(meta, m_size);

	int x=0, x_right=0;
    for(int i=0; i<m_size - zero_num; i++)
    {
        while(meta[x_right] == 0)
            x_right++;
        meta[x] = meta[x_right];
        x++;
        x_right++;
    }
    for(int i=0; i<zero_num; i++)
	{
        meta[m_size - 1 - i] = 0;
	}        
    
	return x != x_right;
}

bool my2048::accumulate_meta(int *meta)						// accumulate one row/colum, accumulate towards meta[0]	
{
	bool b_changed = false;

	b_changed |= remove_zeros_meta(meta);
    for(int x=0; x<m_size-1; )
    {
        if(meta[x] > 0 && meta[x] == meta[x+1])
        {
            meta[x] = 2 * meta[x];
            meta[x+1] = 0;
            x += 2;
            b_changed = true;
        }
        else
        {
            x++;
        }
    }
    b_changed |= remove_zeros_meta(meta);
	return b_changed;
}

bool my2048::accumulate(int action)
{
    bool b_changed = false;
	int *re_org = (int*)malloc(m_size * m_size * sizeof(int));

	re_organize(re_org, m_a, m_size, action, true);
    for(int x = 0; x < m_size; x++)
    {
		int *meta = &(re_org[x * m_size]);
		b_changed |= accumulate_meta(meta);
	}
	re_organize(m_a, re_org, m_size, action, false);
	free(re_org);
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
    printf("a: left; d: right\n");
    printf("w: up  ; s: down\n");
    printf("p: quit\n\n");

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
        printf("Lose! Press p to try again.\n");
    }
}

void my2048::clear_screen()
{
    system("cls");
}

bool my2048::respond_one_action(int action)
{
    bool b_changed = false;
	b_changed = accumulate(action);
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
        if(ch == 'p')
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
        clear_screen();
        print();
    }
    return true;
}