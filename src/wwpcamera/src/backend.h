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

    // Auth
    // std::string getAuthMessage() const;
    // void setAuthMessage(const std::string& newValue);
    // void setAuthKey(const std::string& newKey);
    // bool authentification();
    // void messageChanged();
    // void activate();
    // void deactivate();
    // int getImageSize() const;
    // variaveis de paths de imagens
    
    // bool activateTrial(const std::string& code);

   


    // Image loading & setting palettes
    int loadImage();
//     void exportThermalImage(const std::string& path); // Save as radiometric
//     void exportBasicImage(const std::string& path); // Save as basic jpeg
//     void newPalette(const std::string& newPalette);

//     // Temperature scale
//     float getTemperature(int x, int y) const; // For radiometric
//     int getRawRadiometricValue(float x, float y) const; // For radiometric
//     std::list<std::string> getTemperatureScale() const;
//     void setManualRangeOn();
//     void setManualRangeOff();

//     // Setters for ranges
//     void setMinTemperature(float newVal);
//     void setMaxTemperature(float newVal);
private:

    // o tipo auto e determinado pelo inicializador da variavel
    //auto image;
//     std::string m_authKey;
//     std::string m_authMessage;
//     bool authOK;
//     bool m_SequenceLoaded = false;
//     std::list <std::string> m_urls;
//     //Current file pointer
//     int m_photoPointer = 0; //por -1 dps
//     wtl::AuthState m_state;
//     // Outros membros privados que podem ser necessários
};

#endif // BACKEND_H
