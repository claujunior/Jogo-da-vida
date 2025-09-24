/**
 * LLSeq class implementation.
 *
 */

#include "life.h"
namespace life {
std::vector<std::vector<coord>> tablete;
int cont = 1;
int amem2 = 1;
/**
 * @brief Compara se um vetor de coordenadas está presente em uma tabela de vetores de coordenadas.
 *
 * Esta função percorre todos os vetores dentro da tabela (uma matriz de vetores) e verifica se o vetor `search`
 * é igual a algum dos vetores presentes na tabela. Se encontrar uma correspondência exata, retorna `true`; 
 * caso contrário, retorna `false`.
 *
 * @param search Vetor de coordenadas que será procurado na tabela.
 * @param tablete Tabela (matriz) de vetores de coordenadas onde o vetor `search` será procurado.
 * @return Retorna `true` se o vetor `search` for encontrado na tabela, caso contrário retorna `false`.
 *
 * @note A comparação entre os vetores é feita utilizando o operador `==` sobrecarregado para o tipo `coord`.
 */
bool compa(const std::vector<coord>& search, const std::vector<std::vector<coord>>& tablete) {
     amem2 = 1;
    for (const auto& v : tablete) {
        if (v == search) {
            return true;  
        }
        amem2++;
     }
    return false; 
}
/**
 * @brief Processa e lê os dados de configuração de um arquivo de entrada para inicializar a simulação do Jogo da Vida de Conway.
 *
 * Este método lê o arquivo de configuração especificado pela variável `input_cfg` e configura a grade do jogo, 
 * o caractere que representa uma célula viva e a estrutura inicial da matriz do jogo. Ele também exibe mensagens
 * de status durante o processo de leitura e configuração da simulação. Em seguida, as células vivas são armazenadas 
 * em uma lista de coordenadas e a simulação é preparada para ser executada.
 *
 * O arquivo de entrada deve conter as dimensões da grade (número de linhas e colunas), o caractere que representa
 * uma célula viva, e os valores de células vivas ou mortas (representadas por esse caractere ou um ponto) em cada posição.
 *
 * @note Este método também imprime mensagens informativas sobre o progresso da configuração da simulação.
 *
 * @throws  Caso o arquivo de entrada não seja aberto corretamente, o método termina o programa.
 */
void LifeCfg::parsecomand(){
    
    nlin = 0;
    ncol = 0;
    carac = {};
    matriz = {};
    std::cout << ">>> Trying to open input file " <<  input_cfg;
    std::ifstream endereco(input_cfg);
    if (!endereco.is_open()) {
        cerr << std::endl << "Erro ao abrir o arquivo de dados!" << std::endl;
        exit(0);
    }
    std::cout << "... done!" << std::endl;
    std::cout << ">>> Running simulation up " <<  max_gen << " generations, or until extinction/stability is reached, wichever comes first." << std::endl;
    std::cout << ">>> Processing data, please wait..." << std::endl;
    char a;
    endereco >> nlin >> ncol;
    endereco >> carac;
    std::cout << ">>> Grid size read from input file: " << nlin << " rows by " << ncol << " cols." << std::endl;
    std::cout << ">>> Character that represents a living cell read from input file: '" << carac << "'" << std::endl;
    
    matriz.resize(nlin*ncol);
    for(int i = 0; i < nlin*ncol; ++i) {
        matriz[i] = '.';
    }
    for(int i = 0; i < nlin*ncol; ++i) {
        endereco >> a;
        if(a==carac){
            matriz[i]=carac;
        }
    }
    std::cout << ">>> Finished read input data file."<< std::endl<< std::endl;
    size_t y = 0;
    size_t x = 0;

     endereco.close();
     anvas(ncol,nlin,block_size);
     for(int i = 0; i < nlin*ncol; ++i) {
          if(i%ncol==0 and i!=0){
               y++;
               x=0;
          }
          if(matriz[i][0]==carac){
               coord a;
               a.x=x;
               a.y=y;
               coordenadas.push_back(a);
          }
          x++;
    }
     for(size_t i = 0;i<coordenadas.size();i++){
          canvas.pixel(coordenadas[i].x,coordenadas[i].y,alive);
     }
     for(size_t j = 0;j<70;j++){
          std::cout << "*";
     }
     
     std::cout << std::endl;
     std::cout << "   Welcome to Conway's game of Life." <<std::endl;
     std::cout << "   Running a simulation on a grid of size " << nlin <<" by " << ncol << " in which"<<std::endl;
     std::cout << "   each cell can either be ocuppied by an orgasnim or not"<<std::endl;
     std::cout << "   The ocuppied cells change from generation to generation"<<std::endl;
     std::cout << "   according to the number of neighboring cells which are alive"<<std::endl;
     for(size_t j = 0;j<70;j++){
          std::cout << "*";
     }
     std::cout << std::endl;
    
     
}
/**
 * @brief Processa e lê o arquivo de configuração INI para inicializar os parâmetros da simulação.
 *
 * Este método lê um arquivo de configuração INI localizado em `../config/glife.ini` e extrai várias informações
 * necessárias para configurar a simulação do Jogo da Vida de Conway, como:
 * - O caminho do arquivo de entrada para a configuração da grade.
 * - O número máximo de gerações para a simulação.
 * - A opção para gerar imagens.
 * - As cores associadas às células vivas e ao fundo.
 * - O tamanho dos blocos de células na tela.
 * - O caminho para salvar as imagens geradas.
 * - O número de quadros por segundo (FPS) para a simulação.
 *
 * Durante o processo de leitura, o método ignora comentários (linhas iniciadas com `;`) e seções (delimitadas por `[]`).
 * Após extrair os parâmetros, o método os armazena nas variáveis internas correspondentes.
 *
 * @note Este método espera um arquivo de configuração no formato específico, onde cada parâmetro é apresentado
 *       como uma chave e um valor, sendo que os valores são extraídos entre aspas ou após o sinal de igual `=`.
 * 
 * @throws  Caso o arquivo de configuração não seja aberto corretamente, o método termina o programa.
 */
void LifeCfg::parseini(){
    std::ifstream endereco("../config/glife.ini");
    if (!endereco.is_open()) {
        cerr << "Erro ao abrir o arquivo .ini!" << std::endl;
        exit(0);
    }
    string a;
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::string poi;
    std::stringstream ss(a);
    std::getline(ss,poi,'"');
    std::getline(ss,poi,'"');
    input_cfg = poi;
   
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s1(a);
    std::getline(s1,poi,'=');
    std::getline(s1,poi,';');
    max_gen = stoi(poi);
    
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
     std::stringstream s2(a);
    std::getline(s2,poi,'=');
    std::getline(s2,poi,';');
    if(poi.find("true")!= std::string::npos)
    generate_image = true;
    if(poi.find("false")!= std::string::npos)
    generate_image = false;
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s3(a);
    std::getline(s3,poi,'=');
    std::getline(s3,poi,';');
    alive = stringToColor(poi);  
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s4(a);
    std::getline(s4,poi,'=');
    std::getline(s4,poi,';'); 
    bkg = stringToColor(poi);
    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s5(a);
    std::getline(s5,poi,'=');
    std::getline(s5,poi,';'); 
    block_size = stoi(poi);

    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s6(a);
    std::getline(s6,poi,'=');
    std::getline(s6,poi,';'); 
    path = poi;

    std::getline(endereco,a);
    while(a[0]==';' or a[0]=='[' or a.empty()){
         std::getline(endereco,a);
    }
    std::stringstream s7(a);
    std::getline(s7,poi,'=');
    std::getline(s7,poi,';'); 
    fps = stoi(poi);
    endereco.close();
}

/**
 * @brief Salva uma imagem no formato PPM (Portable Pixel Map) com a codificação de cores em formato "P3".
 *
 * Esta função recebe os dados de uma imagem em formato de pixels RGB, com as dimensões da imagem (largura, altura e profundidade),
 * e salva a imagem em um arquivo com o formato PPM. O arquivo é gerado utilizando a codificação "P3", que armazena as cores
 * como valores inteiros separados por espaços.
 *
 * A função também permite ajustar o tamanho do bloco (`block_size`) para aumentar a resolução da imagem gerada no arquivo PPM,
 * multiplicando a largura e altura por esse valor.
 *
 * @param data Um ponteiro para os dados de imagem, representando a cor de cada pixel como valores RGB consecutivos.
 * @param w Largura da imagem (em pixels).
 * @param h Altura da imagem (em pixels).
 * @param d Profundidade dos dados de cor (geralmente 3 para RGB).
 * @param file_name O nome do arquivo PPM a ser salvo.
 * @param block_size O fator de escala (tamanho do bloco) para aumentar a resolução da imagem no arquivo gerado.
 * 
 * @return Retorna `true` se a imagem foi salva com sucesso, caso contrário, retorna `false`.
 * 
 * @note A função atualmente escreve um arquivo PPM, mas o código de geração da imagem está incompleto (comentário `TODO`).
 *       O formato gerado é `P3`, que armazena as cores como valores inteiros.
 * 
 * @throws std::ofstream::failure Caso haja uma falha ao abrir ou gravar o arquivo de saída.
 */
bool save_ppm3(const unsigned char* data,
               size_t w,
               size_t h,
               size_t d,
               const std::string& file_name,short block_size) {
  std::ofstream ofs_file(file_name, std::ios::out);
  if (not ofs_file.is_open()) {
    return false;
  }
  ofs_file << "P3" << "\n";
  ofs_file << w*block_size << " " << h*block_size << "\n";
  ofs_file << "255" << "\n";
  size_t count = 0;
  size_t mis = 0;
  for(size_t i = 0;i<w*d*h*block_size*block_size;i++){
      if(mis==3){
        count = count + d - 3;
        mis=0;
      }
      else{
      ofs_file << (int)data[count] << " ";
      count++;
      mis++;
      }
    }
    ofs_file << "\n";
  

  // TODO: Complete a geração do arquivo PPM!!

  ofs_file.close();

  return true;  // stub
}
/**
 * @brief Renderiza a próxima geração do Jogo da Vida de Conway e salva o estado atual em um arquivo ou imprime no console.
 *
 * Este método executa a renderização da próxima geração do Jogo da Vida, verificando se a configuração atual
 * (as células vivas) já foi processada anteriormente. Se a configuração for estável (ou seja, não houve alteração),
 * a simulação é encerrada. Caso contrário, o estado atual da simulação é exibido.
 *
 * Se a opção de gerar imagens (`generate_image`) estiver desabilitada, o estado da grade é impresso no console,
 * mostrando a evolução da simulação com as células vivas representadas por um caractere específico (`carac`).
 * Caso contrário, a função gera uma imagem no formato PPM com a representação atual da simulação e a salva em um arquivo
 * no diretório especificado.
 *
 * @note O método utiliza o contador `cont` para registrar o número da geração atual e imprime ou salva a representação
 *       da grade a cada geração.
 * 
 * @throws std::ofstream::failure Se houver uma falha ao salvar o arquivo PPM.
 */
void LifeCfg::render(){
     if(generate_image==false){
          std::cout << "Generation " << cont << std::endl;
          cont++;
      for(int i = 0; i < nlin*ncol; ++i) {
          if(i%ncol==0)
        std::cout << std::endl << "[";
          if(matriz[i][0]=='.')
        std::cout << " ";
          if(matriz[i][0]==carac)
        std::cout << "•";
          if((i+1)%ncol==0)
          std::cout << "]";
      }
     std::cout << std::endl;
     std::cout << std::endl;
     }
     
     else{
          string a = "../saida/test";
          a += std::to_string(cont);
          a += ".ppm";
          save_ppm3(canva().pixels(), canva().width(), canva().height(), 4, a,canva().blocks());
          cont++;
     }
     if(!compa(coordenadas,tablete)){
     tablete.push_back(coordenadas);
     }
     else if(compa(coordenadas,tablete)){
          std::cout << ">>> The current configuration is now STABLE"<< std::endl;
          std::cout << "    The same configuration appeared before in generation "  << amem2 << std::endl << std::endl << "    Quiting simulation...";
          std::cout << std::endl << std::endl << ">>> Thank you for trying out the Life Game Simulation! See you next time."<< std::endl;
           exit(0);
     }
     coordenadas.clear();
}
/**
 * @brief Atualiza o estado da simulação, aplicando o próximo passo da evolução.
 *
 * Este método realiza uma atualização da simulação do Jogo da Vida de Conway. Ele aguarda o intervalo de tempo necessário
 * (controlado pela taxa de quadros por segundo `fps`), limpa o canvas para preparar a próxima geração e atualiza o estado
 * das células vivas no canvas.
 *
 * O método também chama a função `set_alive` para configurar as células vivas de acordo com a lógica da simulação,
 * e em seguida desenha as células vivas no canvas usando a função `canvas.pixel` para cada coordenada armazenada.
 *
 * @note O tempo de espera entre as atualizações é ajustado pela variável `fps`, que controla a taxa de quadros por segundo.
 *
 * @throws std::chrono::system_error Se houver um erro durante o uso de `std::this_thread::sleep_for`.
 */
void LifeCfg::update(){
     std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps));
     canvas.clear(bkg);
     set_alive();
      for(size_t i = 0;i<coordenadas.size();i++){
          canvas.pixel(coordenadas[i].x,coordenadas[i].y,alive);
     }
}
/**
 * @brief Atualiza a lista de coordenadas das células vivas a partir da matriz.
 *
 * Este método percorre a matriz que representa a grade do Jogo da Vida de Conway e identifica as células vivas,
 * representadas pelo caractere `carac`. Para cada célula viva encontrada, ele armazena suas coordenadas (x, y)
 * em um vetor de coordenadas, permitindo que o estado das células vivas seja utilizado posteriormente na simulação.
 *
 * O método também chama a função `funcjuda`, que provavelmente auxilia na configuração ou atualização de dados
 * necessários para determinar as células vivas.
 *
 * @note A função percorre toda a matriz linha por linha e, quando encontra uma célula viva, armazena suas
 *       coordenadas em `coordenadas`, que são usadas por outras funções para renderizar e atualizar o estado da simulação.
 */
void LifeCfg::set_alive(){
     funcjuda();
     size_t y = 0;
     size_t x = 0;
     for(int i = 0; i < nlin*ncol; ++i) {
          if(i%ncol==0 and i!=0){
               y++;
               x=0;
          }
          if(matriz[i][0]==carac){
               coord a;
               a.x=x;
               a.y=y;
               coordenadas.push_back(a);
          }
          x++;
    }
    
};
/**
 * @brief Atualiza a matriz de células vivas de acordo com as regras de vizinhança do Jogo da Vida de Conway.
 *
 * Este método percorre a matriz de células e aplica as regras do Jogo da Vida para determinar quais células
 * devem permanecer vivas ou morrer. Para cada célula viva, o número de vizinhos vivos é contado, e com base nesse número,
 * a célula pode ser mantida viva ou marcada para morte. Para as células mortas, o método verifica se elas têm exatamente
 * três vizinhos vivos e, nesse caso, elas se tornam vivas.
 *
 * As células que permanecem vivas ou que devem se tornar vivas são armazenadas em um vetor temporário, que é
 * utilizado para atualizar a matriz após o cálculo. Se o número de células vivas após o processamento for zero,
 * significa que a simulação entrou em extinção e o programa é encerrado.
 *
 * @note A função faz uso da função auxiliar `contarVizinhos` para calcular o número de vizinhos vivos de uma célula.
 *       Após calcular as novas células vivas, a matriz é atualizada, e as células que devem permanecer vivas
 *       são repostas com o caractere `carac`.
 *
 * @throws std::exit Se a simulação entrar em extinção (sem células vivas).
 */
void LifeCfg::funcjuda(){
     size_t y = 0;
     size_t x = 0;
     std::vector<coord> temp;
     for(size_t i = 0;i<ncol*nlin;i++){
           size_t count = 0;
           
          if(i%ncol==0 and i!=0){
               y++;
               x=0;
          }
          if(matriz[i][0]==carac){
               count = contarVizinhos(y,x);
               
               if(count>=4){
               
               }
               else if(count<=1){
               }   
               else{
                     coord a;
                    a.x = x;
                    a.y = y;
                    temp.push_back(a);
               }
          }
          else{
               count = contarVizinhos(y,x);
               
                if(count==3){
                    coord a;
                    a.x = x;
                    a.y = y;
                    temp.push_back(a);
               }
          }
          x++;
     }
     if(temp.size()==0){
          std::cout << "Entrou em extinção" << std::endl;
          exit(0);
     }
     y = 0;
     x = 0;
     for(size_t i = 0;i<ncol*nlin;i++){  
        matriz[i] = '.';
     }
     size_t j =0;
     for(size_t i = 0;i<ncol*nlin;i++){  
          if(i%ncol==0 and i!=0){
          y++;
          x=0;
          }
          if(temp[j].x==x and temp[j].y==y){
               matriz[i]=carac;
               j++;
          }
          x++;
     } 
}
/**
 * @brief Conta o número de vizinhos vivos de uma célula no Jogo da Vida de Conway.
 *
 * Este método calcula o número de células vizinhas vivas ao redor de uma célula específica em uma grade representada
 * por uma matriz. Ele percorre as 8 células vizinhas (ao redor da célula especificada pelas coordenadas `linha` e `coluna`)
 * e conta quantas dessas células estão vivas, ou seja, quantas contêm o caractere `carac`.
 * 
 * As células vizinhas são consideradas dentro dos limites da matriz, e se uma célula estiver fora desses limites, ela
 * não é contada.
 * 
 * @param linha A linha da célula para a qual os vizinhos serão contados.
 * @param coluna A coluna da célula para a qual os vizinhos serão contados.
 * 
 * @return Retorna o número de vizinhos vivos da célula especificada.
 * 
 * @note As células vizinhas são verificadas em todas as 8 direções ao redor da célula alvo (norte, sul, leste, oeste,
 *       e as diagonais).
 */
int LifeCfg::contarVizinhos(int linha, int coluna) {
    int linhas = nlin;   
    int colunas = ncol;  
    int contador = 0;

    
    int movimentos[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, 
        { 0, -1},          { 0, 1}, 
        { 1, -1}, { 1, 0}, { 1, 1}  
    };

    
    for (auto& movimento : movimentos) {
        int novaLinha = linha + movimento[0];
        int novaColuna = coluna + movimento[1];

       
        if (novaLinha >= 0 and novaLinha < linhas and 
            novaColuna >= 0 and novaColuna < colunas) {
            
            int indice = novaLinha * colunas + novaColuna;

            
            if (matriz[indice][0] == carac) {
                contador++;
            }
        }
    }
    return contador;
}
/**
 * @brief Verifica se a simulação deve ser encerrada com base no número máximo de gerações.
 *
 * Este método verifica se o número máximo de gerações (`max_gen`) foi atingido durante a simulação do Jogo da Vida
 * de Conway. Se o número de gerações ultrapassar o limite definido por `max_gen`, o método retorna `true`, indicando
 * que a simulação deve ser encerrada. Caso contrário, retorna `false`.
 *
 * Se a simulação atingir o número máximo de gerações, uma mensagem é impressa no console indicando que o limite foi
 * atingido.
 *
 * @return Retorna `true` se o número máximo de gerações foi atingido, ou `false` caso contrário.
 *
 * @note Se `max_gen` for zero, o método sempre retornará `false`, indicando que a simulação deve continuar indefinidamente.
 */
bool LifeCfg::over(){
     if(max_gen==0){
          return false;
     }
     else if(max_gen+1==cont)
     std::cout << "Hit the max generation" << std::endl << std::endl << ">>> Thank you for trying out the Life Game Simulation! See you next time."<< std::endl;
     return max_gen+1==cont;
}



}  // namespace life
