#ifndef BACKEND_H
#define BACKEND_H

#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <iomanip>
//#include </home/guilherme/wwpcamera/src/wwpcamera/src/lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/center.h>

class Backend {
public:
    // Construtor
    Backend();

    // Auth
    std::string getAuthMessage() const;
    void setAuthMessage(const std::string& newValue);
    void setAuthKey(const std::string& newKey);
    bool authentification();
    void messageChanged();
    void activate();
    void deactivate();

//     // Image loading & setting palettes
//     void loadImage();
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
    std::string m_authKey;
    std::string m_authMessage;
    bool authOK;
//     // Outros membros privados que podem ser necessários
};

#endif // BACKEND_H
