#ifndef BACKEND_H
#define BACKEND_H

#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <iomanip>
#include <list>

class Backend {


public:
    // Construtor
    Backend();
    // Image loading & setting palettes
    void loadImage();
    void manipulateImage();
    void barrarConexaoUsb();
    void remontarConexaoUsb();
private:

};

#endif // BACKEND_H
