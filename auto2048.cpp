
#include <vector>
#include "windows.h"
#include "auto2048.h"

int auto2048::autoplay_simple(bool b_show)
{
    int action_direction[4] = {my2048::m_action_up, my2048::m_action_right, my2048::m_action_down, my2048::m_action_left};
    int action_index = 0;

    while(!game.is_lost())
    {
        bool b_changed = game.respond_one_action(action_direction[action_index]);
        if(!b_changed)
        {
            action_index = (action_index + 1) % 4;
        }

        if(b_show)
        {
            game.print();
            Sleep(500);
        }
    }
    return game.get_max_val();
}

std::vector<int> auto2048::evaluate(const autoplay_t t)
{
    std::vector<int> ret;
    for(int i=0; i<100; i++)
    {
        int max_val;
        switch(t)
        {
        case ap_simple:
            max_val = autoplay_simple(false);
            break;
        default:
            std::cout << "[auto2048] Unsupported autoplay type." << std::endl;
            break;
        }
        ret.push_back(max_val);
    }
    return ret;
}

