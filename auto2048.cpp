
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
            game.clear_screen();
            game.print();
            Sleep(500);
        }
    }
    game.print();
    return game.get_max_val();
}

std::vector<int> auto2048::evaluate_one_method(PFUN pfun_autoplay)
{
    std::vector<int> ret;
    for(int i=0; i<100; i++)
    {
        Sleep(2); // to get different rand() seed.
        game.init(game.size());
        int max_val = (this->*pfun_autoplay)(false);
        ret.push_back(max_val);
    }
    return ret;
}

void auto2048::evaluate_all_methods()
{
    std::cout << "max score for simple method:" << std::endl;
    std::vector<int> max_vec = evaluate_one_method(&auto2048::autoplay_simple);
    for(int i=0; i<max_vec.size(); i++)
    {
        std::cout << max_vec[i] << std::endl;
    }
}
