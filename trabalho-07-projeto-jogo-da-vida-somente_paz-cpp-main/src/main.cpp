/**
 * @file life_game.cpp
 *
 * @description
 * This program simulates the Conway's Game of Life.
 * It reads a initial game configuration from a input file and
 * keeps updating it, if the user so whishes.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03, updated 2024-05-31
 *
 * @remark On 2015-09-19 changed the way stability is verified.
 * In the previous version we just looked back one configuration and compare it
 * with the current configuration.
 * Now, the stability may span more than one configuration. Because of that we
 * need to keep track of all configurations and check whether the current
 * configuration has already been generated.
 * If this is the case, the game has reached stability and must stop.
 */

#include <cstdlib>  // EXIT_SUCCESS
#include "life.h"


int main(int argc, char* argv[]) { 
   if (argc == 2) {
        if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help") {
            std::cout << "Change this configurations on ../config/glife.ini\n";
            std::cout << "Running options:\n";
            std::cout << "  --help              Print this help text.\n";
            std::cout << "  maxgen              Maximum number of generations to simulate. No default.\n";
            std::cout << "  fps                 # of generations presented p/ second. Default = 2 fps.\n";
            std::cout << "  generate_image      Determines if false, the image will not be generated; if true, it will be generated.\n";
            std::cout << "  blocksize           Pixel size of a square cell. Default = 5.\n";
            std::cout << "  bkg                 Color name for the background. Default = GREEN.\n";
            std::cout << "  alive               Color name for the alive cells. Default = RED.\n";
            std::cout << "  input_cfg           Path for the configuration archive.\n";
            std::cout << "\nAvailable colors are:\n";
            std::cout << "  BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE GREEN LIGHT_BLUE\n";
            std::cout << "  LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE WHITE YELLOW\n";
            return 0;
        }
        else {
           std::cout << "Invalid arguments. Use -h or --help for help.\n";
           return 0;
        }
    }

  
    life::LifeCfg a;
    a.parseini();
    a.parsecomand();
    
    

    
    while (not a.over()) {
    a.render();
    a.update();
  }

    std::cout << std::endl;
    return EXIT_SUCCESS; 
}
