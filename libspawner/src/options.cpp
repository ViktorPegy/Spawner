#include "options.h"

void options_class::add_argument(std::string argument)
{
    arguments.push_back(argument);
}

std::string options_class::get_arguments()
{
    if (arguments.size() == 0)
        return "";
    std::string result = arguments.front();
    std::list<std::string>::iterator it = arguments.begin();
    while (++it != arguments.end())
        result += " " + *it;
    return result;
}