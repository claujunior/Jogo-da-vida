//! This class implements a life board in the Conway's Game of Life.
/*!
 * @file life.h
 *
 * @details Class Life, to simulate the Conway's Game of Life.
 *
 * @author	Selan R dos Santos, <selan.rds@gmail.com>
 * @date	2015, updated 2015-04-03
 * @update 2019, April 2nd.
 * @version     v1.1
 */

#ifndef _LIFE_H_
#define _LIFE_H_

#include <cassert>
#include <cstring>  // std::memcpy().
#include <iostream>
#include <set>
#include <sstream>  // std::ostringstream
#include <stdexcept>
#include <string>
#include <vector>
#include <cstddef>
#include <fstream>
#include <chrono>
#include <thread>
#include <functional> // Para std::hash
#include <set>     
#include <unordered_map>
using std::cerr;
using std::cout;
using std::endl;
using std::set;
using std::string;
using std::vector;

#include "canvas.hpp"

namespace life {
    /**
 * @brief Estrutura que representa as coordenadas (x, y) de uma célula no Jogo da Vida de Conway.
 *
 * A estrutura `coord` é usada para armazenar as coordenadas de uma célula dentro da grade do Jogo da Vida. Ela contém
 * dois membros, `x` e `y`, que representam as coordenadas horizontais e verticais, respectivamente. A estrutura também
 * sobrecarrega os operadores de comparação `==` e `!=` para facilitar a comparação de coordenadas.
 * 
 * - `x`: Representa a coordenada horizontal (coluna) de uma célula.
 * - `y`: Representa a coordenada vertical (linha) de uma célula.
 *
 * @note A sobrecarga dos operadores permite verificar facilmente se duas coordenadas são iguais ou diferentes.
 */
struct coord
{
    size_t x = 0;
    size_t y = 0;
      bool operator==(const coord& other) const {
        return x == other.x and y == other.y;
    }
    bool operator!=(const coord& other) const {
        return !(*this == other);
    }
};

/// A life configuration.
/**
 * @brief Classe que representa a configuração e lógica do Jogo da Vida de Conway.
 * 
 * A classe `LifeCfg` gerencia a lógica do Jogo da Vida de Conway, incluindo a leitura de arquivos de configuração, a
 * atualização das células na grade, a renderização do estado da simulação, e o controle da evolução das células ao
 * longo das gerações. A classe também interage com a classe `Canvas` para exibir a simulação visualmente e pode gerar
 * imagens em formato PPM.
 */

class LifeCfg {
    private:
        std::vector<coord> coordenadas;
        size_t nlin;
        size_t ncol;
        char carac;
        std::vector<string> matriz;
        Canvas canvas;
        string input_cfg;
        int max_gen;
        bool generate_image;
        Color alive;
        Color bkg;
        int block_size;
        string path;
        int fps; 
    public:
      void anvas(size_t ncol , size_t nlin,int bs) {
        canvas.seth(nlin);
        canvas.setblock(bs);
        canvas.setw(ncol);
        canvas.setpix(nlin,ncol,bs,bkg);
    };
    Canvas canva(){
        return canvas;
    }
    Color stringToColor(const std::string& colorName) {
    auto it = color_pallet.find(removeSpaces(colorName));
    if (it != color_pallet.end()) {
        return it->second; 
    } else {
        throw std::invalid_argument("Invalid color name: " + colorName);
    }
}   std::string removeSpaces(const std::string& input) {
    std::string result;
    for (char c : input) {
        if (c != ' ') { 
            result += c;
        }
    }
    return result;
}
        void parsecomand();
        void parseini();
        ~LifeCfg(){ /* empty */ };
        
    void set_alive();

    void update();
    void render();
    void funcjuda();
    int contarVizinhos(int linha, int coluna);
    bool over();
};

}  // namespace life

#endif
