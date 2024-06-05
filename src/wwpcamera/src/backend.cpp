#include "/home/guilherme/wwpcamera/src/wwpcamera/src/backend.h"
#include <iostream>
#include "lib/wwp-data-sdk-0.3.0-linux/wwp-data-sdk/headers/center.h"
#include <string>

// Inicializações se necessárias do construtor
Backend::Backend() {
    this->authOK = false;
    this->m_authKey = " ";
    // na inicialização - proposta: Criar uma func pra por aqui dps que verifica a auth ao inves de fazer esse if
    authentification();
}

// retorna mensagem de erro
std::string Backend::getAuthMessage() const { 
    return this->m_authMessage;
}

// seta uma mensagem de erro
void Backend::setAuthMessage(const std::string& message){
    this->m_authMessage = message;
}

// seta a key de auth
void Backend::setAuthKey(const std::string& newKey){
    this->m_authKey = newKey;
}

bool Backend::authentification(){
    std::cout<< "Autentificando" << std::endl;
    // verifica o estado de autenticação
    static wtl::AuthState m_state = wtl::Center::authentificate();
    if(m_state == wtl::AuthState::NotActivated){
        m_authMessage = "license not activated, enter serial number";
        // emitir sinal
        return false;
    }
    if(m_state == wtl::AuthState::FullActivated){
        m_authMessage = "license activated";
        // emitir sinal
        return true;
    }
    if(m_state == wtl::AuthState::TrialActivated){
        m_authMessage = "Trial license activated";
        // emitir sinal
        return true;
    }
    if(m_state == wtl::AuthState::TrialExpired){
        m_authMessage = "Trial license Expired";
        // emitir sinal
        return false;
    }
    if(m_state == wtl::AuthState::WrongSN){
        m_authMessage = "Invalid serial number";
        // emitir sinal
        return false;
    }
    if(m_state == wtl::AuthState::ComputerAlreadyUsed){
        m_authMessage = "this computer is already in use";
        // emitir sinal
        return false;
    }
    if(m_state == wtl::AuthState::AlreadyUsed){
        m_authMessage = "serial number already used";
        // emitir sinal
        return false;
    }
    m_authMessage = "An error ocurred!";
    return false;
}

// Método de ativação da chave
void Backend::activate(){
    std::cout << "Ativando a chave" << std::endl;
    wtl::Center::activate(m_authKey); //talvez necessario transformar em string
    this->authentification(); // chama para autenticar
}
//Método de desativação da chave
void Backend::deactivate(){
    std::cout << "Desativando a chave" << std::endl;
    if(!wtl::Center::deactivate())
        return;
    this->authentification();
    // emitir sinal
}

// void Backend::loadImage() {
//     // Implementação do carregamento de imagem
// }

// void Backend::exportThermalImage(const std::string& path) {
//     // Implementação da exportação de imagem termal
// }

// void Backend::exportBasicImage(const std::string& path) {
//     // Implementação da exportação de imagem básica
// }

// void Backend::newPalette(const std::string& newPalette) {
//     // Implementação da definição de nova paleta
// }

// float Backend::getTemperature(int x, int y) const {
//     // Implementação da obtenção de temperatura
//     return 0.0f;
// }

// int Backend::getRawRadiometricValue(float x, float y) const {
//     // Implementação da obtenção de valor radiométrico bruto
//     return 0;
// }

// std::list<std::string> Backend::getTemperatureScale() const {
//     // Implementação da obtenção da escala de temperatura
//     return {};
// }

// void Backend::setManualRangeOn() {
//     // Implementação da ativação do alcance manual
// }

// void Backend::setManualRangeOff() {
//     // Implementação da desativação do alcance manual
// }

// void Backend::setMinTemperature(float newVal) {
//     // Implementação da definição de temperatura mínima
// }

// void Backend::setMaxTemperature(float newVal) {
//     // Implementação da definição de temperatura máxima
// }
