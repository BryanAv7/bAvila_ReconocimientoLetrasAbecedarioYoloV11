// ----------------------------------------------------------------------------------------------------------

// Parte 1A: Modelo Yolov11 con un proceso de transfer learning para reconocer las letras del abecedario.
// Nombre: Bryan Avila
// Carrera: Computación
// Materia: Visión por Computadora
// Fecha: 2025-06-28

// ----------------------------------------------------------------------------------------------------------

// Librerías por utilizar
#include <iostream>      
#include <vector>        
#include <thread>        
#include <atomic>        
#include <chrono>        
#include <sstream>       
#include <opencv2/highgui/highgui.hpp>    
#include <opencv2/imgcodecs.hpp>          
#include <opencv2/imgproc/imgproc.hpp>    
#include <opencv2/videoio/videoio.hpp>    
#include "YOLO11.hpp"                    

// Espacio de nombres de OpenCV
using namespace cv; 

// Función principal
int main()
{
    // Verifica si se esta utilizando la GPU 
    const bool isGPU = false; // Para usar CPU, descomentar esta línea y comentar la siguiente línea
    //const bool isGPU = cv::cuda::getCudaEnabledDeviceCount() > 0; 

    std::cout << "Inferencia usando: " << (isGPU ? "GPU" : "CPU") << std::endl;

    // Rutas de los archivos necesarios para el modelo
    const std::string labelsPath = "/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/models/classes2.txt"; // Nombres de clases (Etiquetas)
    const std::string modelPath = "/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/models/best4_simplified.onnx"; // Modelo ONNX (Previamente entrenado/optimizado)
    const std::string imagePath = "/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/imagen/imagen2.jpeg"; // Imagen a analizar

    // Crear instancia del detector YOLO con el modelo y las clases cargadas
    YOLO11Detector detector(modelPath, labelsPath, isGPU);

    // ------------------- DETECCIÓN SOBRE IMAGEN(Extra) ---------------------

    // Cargar imagen desde disco
    cv::Mat image = cv::imread(imagePath);
    if (image.empty())
    {
        std::cerr << "Error: No se pudo cargar la imagen.\n";
    }
    else
    {
        // Aplicar detección sobre la imagen cargada
        std::vector<Detection> results = detector.detect(image);

        // Dibujar las cajas delimitadoras sobre la imagen
        detector.drawBoundingBoxMask(image, results);

        // Mostrar imagen en ventana 
        cv::imshow("Resultado en Imagen", image);
    }

    // ------------------- DETECCIÓN EN VIDEO (CÁMARA EN TIEMPO REAL/Principal) ---------------------
    // Abrir la cámara 
    cv::VideoCapture cap(0, cv::CAP_V4L2);
    if (!cap.isOpened())
    {
        std::cerr << "Error: No se pudo abrir la cámara.\n";
        return -1;
    }

    // Configurar propiedades de la cámara
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);    
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);   
    cap.set(cv::CAP_PROP_FPS, 30);             

    // Variables para cálculo de FPS en tiempo real
    double freq = cv::getTickFrequency();      
    int count = 0;
    double startTick = cv::getTickCount();     
    double smoothedFPS = 0;                    

    cv::Mat frame;
    while (true)
    {
        // Capturar frame desde la cámara
        cap >> frame;
        if (frame.empty()) break;

        // Detectar objetos en el frame actual
        auto detections = detector.detect(frame);

        // Dibujar las detecciones sobre el frame
        detector.drawBoundingBoxMask(frame, detections);

        // Cálculo de FPS cada segundo
        count++;
        double endTick = cv::getTickCount();
        double elapsed = (endTick - startTick) / freq;
        if (elapsed >= 1.0)
        {
            double fps = count / elapsed;
            smoothedFPS = 0.9 * smoothedFPS + 0.1 * fps;  
            std::cout << "FPS: " << smoothedFPS << std::endl;
            startTick = endTick;
            count = 0;
        }

        // Mostrar los FPS sobre la imagen
        std::ostringstream oss;
        oss << "FPS: " << static_cast<int>(smoothedFPS);
        cv::putText(frame, oss.str(), cv::Point(10, 30),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

        // Mostrar frame en ventana
        cv::imshow("Detección en Tiempo Real", frame);

        // Salir 
        char key = (char)cv::waitKey(1);
        if (key == 'q') break;
    }

    // Liberar cámara y cerrar todas las ventanas
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
