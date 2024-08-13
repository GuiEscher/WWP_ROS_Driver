#include "backend.h"
#include </usr/include/opencv4/opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <libusb-1.0/libusb.h>
#include <yaml-cpp/yaml.h>
#include <filesystem>
#include <exception>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <optional>
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/parameters/sequencemetadata.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/sources/thermalimage.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/parameters/sourcemetadata.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/measurement/roi.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/measurement/alarm.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/parameters/thermalparameters.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/parameters/palette.h"
#include "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/include/wtlib/measurement/measurementcontext.h"

// Inicializações se necessárias do construtor
Backend::Backend() {
    std::cout << " *** inicialização do driver wwp ***" << std::endl;
}
void Backend::loadImage(){
    std::cout << "Criacao do objeto" << std::endl;
    const std::string resourcePath = "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/example/resources/10-46-09-315-radiometric.jpg";
    auto image = wtl::ThermalImage::load(resourcePath);

    if (!image)
    {
        std::cerr << "Failed to open image" << std::endl;
        return;
    }

    auto metadata = image->getMetadata();

    std::cout << "----- METADATA -----" << std::endl;
    std::cout << "Source name: " << metadata.getSourceName() << std::endl;
    std::cout << "Source path: " << metadata.getSourcePath() << std::endl;
    std::cout << "Capture time: " << metadata.getCaptureTimeExif() << std::endl;
    std::cout << "Serial number: " << metadata.getCameraSerialNumber() << std::endl;
    std::cout << "Manufacturer: " << metadata.getCameraManufacturer() << std::endl;
    std::cout << "Source name: " << metadata.getSourceName() << std::endl;
    std::cout << "Article number: " << metadata.getCameraArtn() << std::endl;
    std::cout << "FW version: " << metadata.getCameraFWVersion() << std::endl;
    std::cout << "Lens: " << metadata.getCameraLensModel() << std::endl;

    auto measurement = image->getMeasurement();

    std::cout << "----- MEASUREMENT -----" << std::endl;
    std::cout << "ROI:" << std::endl;
    for (const auto& roi : measurement.getRois())
    {
        std::cout << "  " << roi->getName() << "  ";
        switch (roi->getType())
        {
        case wtl::Roi::Type::POINT:
            std::cout << "Point";
            break;
        case wtl::Roi::Type::RECTANGLE:
            std::cout << "Rectangle";
            break;
        case wtl::Roi::Type::LINE:
            std::cout << "Line";
            break;
        case wtl::Roi::Type::POLYLINE:
            std::cout << "Polyline";
            break;
        case wtl::Roi::Type::POLYAREA:
            std::cout << "Polyarea";
            break;
        case wtl::Roi::Type::ELLIPSE:
            std::cout << "Ellipse";
            break;
        }
        std::cout << std::endl;
    }

    std::cout << "Alarm:" << std::endl;
    for (const auto& alarm : measurement.getAlarms())
    {
        std::cout << "  " << alarm->m_Name << "  ";
        switch (alarm->m_Type)
        {
        case wtl::Alarm::Type::BELLOW:
            std::cout << "Bellow";
            break;
        case wtl::Alarm::Type::ABOVE:
            std::cout << "Above";
            break;
        case wtl::Alarm::Type::INTERVAL:
            std::cout << "Interval";
            break;
        case wtl::Alarm::Type::INVERTED_INTERVAL:
            std::cout << "Inverted interval";
            break;
        }
        std::cout << std::endl;
    }

    auto thermalParameters = image->getThermalParameters();

    std::cout << "----- THERMAL PARAMETERS -----" << std::endl;
    std::cout << "Emissivity: " << thermalParameters.emissivity << std::endl;
    std::cout << "Reflected temperature: " << thermalParameters.reflectedTemperature << std::endl;
    std::cout << "Object distance: " << thermalParameters.objectDistance << std::endl;
    std::cout << "Atmospheric temperature: " << thermalParameters.atmosphericTemperature << std::endl;
    std::cout << "Relative humidity: " << thermalParameters.relativeHumidity << std::endl;
    std::cout << "Optics transmission: " << thermalParameters.opticsTransmission << std::endl;
    std::cout << "Optics temperature: " << thermalParameters.opticsTemperature << std::endl;

    auto palette = image->getPalette();

    std::cout << "----- PALETTE -----" << std::endl;
    std::cout << "Name: " << palette.getName() << std::endl;

    std::cout << "----- TEMPERATURES -----" << std::endl;
    std::cout << "MAX: " << image->getMaximumTemperature() << "  MIN: " << image->getMinimumTemperature() << std::endl;
    return;
}

void Backend::manipulateImage(){
    std::cout << "Entrando em manipulação de imagens" << std::endl;
    // Caminho para a imagem que você deseja manipular
    std::string imagePath = "/home/guilherme/wwpcamera/WWP_ROS_Driver/lib/WTLIB-0.3.3-Linux/example/resources/08-53-22-427-radiometric.jpg";

    // Carregar a imagem
    cv::Mat image = cv::imread(imagePath);

    // Verificar se a imagem foi carregada corretamente
    if (image.empty()) {
        std::cerr << "Erro ao carregar a imagem: " << imagePath << std::endl;
        return;
    }

    // Converter a imagem para escala de cinza
   cv::Mat grayImage;
   cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

    // Mostrar a imagem original e a imagem em escala de cinza
    cv::imshow("Imagem Original", image);
    
    cv::imshow("Imagem em Escala de Cinza", grayImage);

    // Espera por uma tecla para fechar as janelas
   cv::waitKey(0);

    // Salvar a imagem em escala de cinza
    std::string outputPath = "/caminho/para/salvar/imagem_cinza.jpg";
    cv::imwrite(outputPath, grayImage);

    //std::cout << "Imagem manipulada e salva em: " << outputPath << std::endl;
}
void Backend::barrarConexaoUsb() {
    libusb_device **devs;
    libusb_context *ctx = nullptr;
    int r;
    ssize_t cnt;

    // Inicializar libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        std::cerr << "Erro ao inicializar libusb" << std::endl;
        return;
    }

    // Obter a lista de dispositivos
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Erro ao obter a lista de dispositivos" << std::endl;
        libusb_exit(ctx);
        return;
    }

    // Iterar sobre a lista de dispositivos
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *device = devs[i];
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);

        std::cout << "Dispositivo: VID_" << std::hex << desc.idVendor << "&PID_" << desc.idProduct << std::endl;

        // Verificar se é o dispositivo que você deseja barrar
        if (desc.idVendor == 0x22b8 && desc.idProduct == 0x2e24) { // Substitua pelos VID e PID do seu celular
            std::cout << "Barrando o dispositivo USB..." << std::endl;

            libusb_device_handle *handle;
            r = libusb_open(device, &handle);
            if (r != 0) {
                std::cerr << "Erro ao abrir o dispositivo USB" << std::endl;
                continue;
            }

            // Tentar desconectar o kernel driver, se estiver conectado
            if (libusb_kernel_driver_active(handle, 0) == 1) {
                r = libusb_detach_kernel_driver(handle, 0);
                if (r < 0) {
                    std::cerr << "Erro ao desanexar o driver do kernel" << std::endl;
                    libusb_close(handle);
                    continue;
                }
            }

            // Resetar o dispositivo
            r = libusb_reset_device(handle);
            if (r < 0) {
                std::cerr << "Erro ao resetar o dispositivo" << std::endl;
            } else {
                std::cout << "Dispositivo USB barrado com sucesso." << std::endl;
            }

            libusb_close(handle);
            break; // Sair após barrar o dispositivo
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
}

void Backend::remontarConexaoUsb() {
    libusb_device **devs;
    libusb_context *ctx = nullptr;
    int r;
    ssize_t cnt;

    // Inicializar libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        std::cerr << "Erro ao inicializar libusb" << std::endl;
        return;
    }

    // Obter a lista de dispositivos
    cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "Erro ao obter a lista de dispositivos" << std::endl;
        libusb_exit(ctx);
        return;
    }

    // Iterar sobre a lista de dispositivos
    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device *device = devs[i];
        libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);

        std::cout << "Dispositivo: VID_" << std::hex << desc.idVendor << "&PID_" << desc.idProduct << std::endl;

        // Verificar se é o dispositivo que você deseja remontar
        if (desc.idVendor == 0x22b8 && desc.idProduct == 0x2e24) { // Substitua pelos VID e PID do seu celular
            std::cout << "Remontando o dispositivo USB..." << std::endl;

            libusb_device_handle *handle;
            r = libusb_open(device, &handle);
            if (r != 0) {
                std::cerr << "Erro ao abrir o dispositivo USB" << std::endl;
                continue;
            }

            // Reanexar o driver do kernel
            r = libusb_attach_kernel_driver(handle, 0);
            if (r < 0) {
                std::cerr << "Erro ao reanexar o driver do kernel: " << libusb_error_name(r) << std::endl;
            } else {
                std::cout << "Driver do kernel reanexado com sucesso." << std::endl;
            }

            libusb_close(handle);

            // Leitura do arquivo config.yaml para obter diretórios
            try {
                YAML::Node config = YAML::LoadFile("config.yaml");
                std::string sourceDir = config["source_directory"].as<std::string>();
                std::string destDir = config["destination_directory"].as<std::string>();

                // Copiar arquivos do diretório de origem para o de destino
                try {
                    for (const auto &entry : std::filesystem::directory_iterator(sourceDir)) {
                        std::filesystem::path destPath = destDir / entry.path().filename();
                        std::filesystem::copy_file(entry.path(), destPath, std::filesystem::copy_options::overwrite_existing);
                        std::cout << "Arquivo " << entry.path().filename() << " copiado para " << destPath << std::endl;
                    }
                } catch (const std::exception &e) {
                    std::cerr << "Erro ao copiar arquivos: " << e.what() << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Erro ao ler o arquivo config.yaml: " << e.what() << std::endl;
            }

            break; // Sair após remontar o dispositivo e copiar os arquivos
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(ctx);
}
