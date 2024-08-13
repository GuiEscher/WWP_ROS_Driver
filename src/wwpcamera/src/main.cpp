#include <ros/ros.h>
#include "backend.h"
#include <iostream>
#include <exception> // Necessário para usar exceções padrão

int main(int argc, char** argv) {
    ros::init(argc, argv, "image_manipulate");
    ros::NodeHandle nh;
    Backend backend;
    int choice;
    // a câmera começa desconectada para poder gravar e tirar fotos
    backend.barrarConexaoUsb();
    while (true) {
        std::cout << "\n\nEscolha uma das opções:\n";
        std::cout << "1: Ler imagens com a câmera\n";
        std::cout << "2: Manipular as imagens salvas com OpenCV\n"; 
        std::cout << "3: Conectar câmera para salvar imagens (* Voce nao podera tirar fotos)\n";
        std::cout << "4: finalizar conexão e salvamento de imagens\n";
        std::cout << "5: desligar\n";
        std::cin >> choice;

        switch (choice) {
            case 1:
                ROS_INFO("Lendo imagens já tiradas...");
                backend.loadImage();
                break;
            case 2:
                ROS_INFO("Manipulando imagens salvas com OpenCV...");
                try {
                    backend.manipulateImage();
                } catch (const std::exception& e) { // Captura exceções padrão
                    ROS_ERROR("Erro ao tentar manipular imagens: %s", e.what());
                } catch (...) { // Captura qualquer outra exceção
                    ROS_ERROR("Erro desconhecido ao tentar manipular imagens.");
                }
                break;
            case 3:
                 try {
                    backend.remontarConexaoUsb();
                } catch (const std::exception& e) { // Captura exceções padrão
                    ROS_ERROR("Erro ao tentar reconectar usb: %s", e.what());
                } catch (...) { // Captura qualquer outra exceção
                    ROS_ERROR("Erro desconhecido ao tentar conectar usb.");
                }      
                break;
            case 4:
                ROS_INFO("Desmontando porta USB...");
                try {
                    backend.barrarConexaoUsb();
                } catch (const std::exception& e) {
                    ROS_ERROR("Erro ao tentar desmontar a porta USB: %s", e.what());
                } catch (...) {
                    ROS_ERROR("Erro desconhecido ao tentar desmontar a porta USB.");
                }
                break;
            case 5:
                exit(1);
                break;
            default:
                ROS_ERROR("Escolha inválida!");
                break; // Continua o loop em vez de sair do programa
        }
    }

    ros::spin();
    return 0;
}
