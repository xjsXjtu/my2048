
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
    std::cout << "[auto2048] max score for simple method:" << std::endl;
    std::vector<int>    max_vec = evaluate_one_method(&auto2048::autoplay_simple);
    std::vector<double> statics = calculate_statics(max_vec);
    for(int i=0; i<max_vec.size(); i++)
    {
        std::cout << max_vec[i] << std::endl;
    }
    std::cout << "Max: " << statics[0] << "\tMin: " << statics[1] << "\tAvg: " << statics[2] << "\tStandard Deviation: " << statics[3] << std::endl;
    

    std::cout << "max score for max_zeor_num method:" << std::endl;
}

std::vector<double> auto2048::calculate_statics(std::vector<int> v)
{
    std::vector<double> ret(4);

    if(v.size() == 0)
    {
        ret.clear();
        return ret;
    }

    double max_v, min_v, avg_v, sd_v;
    max_v = min_v = avg_v = v[0];
    sd_v = 0.0;

    for(int i=1; i<v.size(); i++)
    {
        max_v = max_v > v[i] ? max_v : v[i]; 
        min_v = min_v < v[i] ? min_v : v[i];
        avg_v += v[i];
    }
    avg_v /= v.size();

    sd_v = 0.0;
    for(int i=0; i<v.size(); i++)
    {
        sd_v += (v[i] - avg_v) * (v[i] - avg_v);
    }
    sd_v = sqrt(sd_v / v.size());

    ret[0] = max_v;
    ret[1] = min_v;
    ret[2] = avg_v;
    ret[3] = sd_v;
    return ret;
}
