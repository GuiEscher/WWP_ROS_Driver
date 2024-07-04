#include "backend.h"

#include <iostream>
#include <string>
#include <optional> // Adicionado
#include "/home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/include/wtlib/parameters/sequencemetadata.h"
#include "/home/guilherme/wwpcamera/lib/WTLIB-0.3.3-Linux/include/wtlib/sources/thermalimage.h"

// Inicializações se necessárias do construtor
Backend::Backend() {
    std::cout << "Criacao do objeto" << std::endl;
}

int Backend::loadImage() { // Tipo de retorno especificado
    // auto image = wtl::ThermalImage::load("/home/guilherme/wwpcamera/src/wwpcamera/src/lib/WTLIB-0.1-linux64/example/resources/wwe_image.jpg");
 
        std::cerr << "Failed to open image" << std::endl;
        return -1;


    return 0;
}





























// // retorna mensagem de erro
// std::string Backend::getAuthMessage() const { 
//     return this->m_authMessage;
// }

// // seta uma mensagem de erro
// void Backend::setAuthMessage(const std::string& message){
//     this->m_authMessage = message;
// }

// // seta a key de auth
// void Backend::setAuthKey(const std::string& newKey){
//     this->m_authKey = newKey;
// }

// bool Backend::authentification() {
//     std::cout << "Autentificando" << std::endl;
    
//     m_state = wtl::Center::authentificate();

//     // Printar o valor numérico de m_state
//     std::cout << "Estado de autenticação (valor numérico): " << static_cast<int>(m_state) << std::endl;

//     switch(m_state) {
//         case wtl::AuthState::NotActivated:
//             m_authMessage = "License not activated, enter serial number";
//             break;
//         case wtl::AuthState::FullActivated:
//             m_authMessage = "License activated";
//             break;
//         case wtl::AuthState::TrialActivated:
//             m_authMessage = "Trial license activated";
//             break;
//         case wtl::AuthState::TrialExpired:
//             m_authMessage = "Trial license expired";
//             break;
//         case wtl::AuthState::WrongSN:
//             m_authMessage = "Invalid serial number";
//             break;
//         case wtl::AuthState::ComputerAlreadyUsed:
//             m_authMessage = "This computer is already in use";
//             break;
//         case wtl::AuthState::AlreadyUsed:
//             m_authMessage = "Serial number already used";
//             break;
//         default:
//             m_authMessage = "An error occurred!";
//             break;
//     }

//     // Emitir sinal (se necessário)
//     return (m_state == wtl::AuthState::FullActivated || m_state == wtl::AuthState::TrialActivated);
// }


// bool Backend::activateTrial(const std::string& code) {
//     // Ativação do teste gratuito por 14 dias
//     bool activationResult = wtl::Center::requestTrial(code);
    
//     // Verifica se a ativação do teste foi bem-sucedida
//     if (activationResult) {
//         m_authMessage = "Trial ativado";
//         return true;
//     } else {
//         m_authMessage = "Trial não ativado";
//         return false;
//     }
// }



// // Método de ativação da chave
// // Método de ativação da chave
// void Backend::activate() {
//     std::cout << "Ativando a chave" << std::endl;
//     std::cout << "Serial number: " << m_authKey << " ------->" <<wtl::Center::activate(m_authKey) << std::endl;
//     static bool activationResult = wtl::Center::activate(m_authKey);
//     if (!activationResult) {
//         std::cout << "Falha na ativação" << std::endl;
//     }
//     this->authentification(); // Chama para autenticar
// }

// //Método de desativação da chave
// void Backend::deactivate(){
//     std::cout << "Desativando a chave" << std::endl;
//     if(!wtl::Center::deactivate())
//         return;
//     this->authentification();
//     // emitir sinal
// }

// //Image loading & setting plalettes
// void Backend::loadImage() {
//     // Garantir que, se uma sequência de imagens estiver 
//     // carregada, ela seja descarregada ao carregar uma nova imagem individual.
//     if(m_SequenceLoaded) {
//         m_SequenceLoaded = false;
//     }

//     // Verificar se m_photoPointer está dentro do intervalo da lista
//     if(m_photoPointer >= m_urls.size()) {
//         std::cout << "Index out of range" << std::endl;
//         return;
//     }

//     // Acessar o elemento da lista usando um iterador
//     auto it = m_urls.begin();
//     std::advance(it, m_photoPointer);
//     std::string url = *it;

//     if(wtl::Center::isRadiometricImage(url)) {
//         std::cout << "radiometric image" << std::endl;
//         image.reset();
//         image = wtl::Center::loadImageRadiometric(url);
//     }else {
//         std::cout << "erro em loadimage" << std::endl;
//         exit(1);
//     }
// }

// //Retorna dados da imagem;
// int Backend::getImageSize() const{
//     if(!image){
//         std::cout << "No image found" << std::endl;
//         return 0;
//     } else {
//         return image->getImageSize();
//     }
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
