#include <iostream>
#include <fstream>
#include <string>

#include <spawner.h>
#include "arguments.h"





int main(int argc, char *argv[]) {
    settings_parser_c parser;
    parser.parse(argc, argv);
    std::cout << parser.object.toStyledString();
    return 0;
    spawner_c spawner(argc, argv);

    spawner.init();
    spawner.run();
    
	return 0;
}
