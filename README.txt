# Trabajo Unidad 4 – Parte A  
## Modelo YOLOv11 con Transfer Learning para el Reconocimiento de Letras del Alfabeto Griego

---

## 📌 Descripción

En esta parte del trabajo se implementa un sistema de detección de objetos basado en **YOLOv11**, adaptado mediante **transfer learning** para reconocer las **24 letras del alfabeto griego**. El modelo fue entrenado en Google Colab, exportado al formato **ONNX**, y posteriormente integrado en una aplicación en **C++** que permite realizar inferencia en tiempo real desde la cámara del dispositivo.

La aplicación soporta ejecución tanto en **CPU** como en **GPU (CUDA)**, permitiendo comparar el desempeño entre ambos modos de procesamiento.

---

## 📁 Estructura del Proyecto

TrabajoU4PartA/
├── build/ → Carpeta donde se genera la compilación
├── models/
│ ├── best.onnx → Modelo entrenado en formato ONNX
│ ├── best2_simplified.onnx → Versión optimizada del modelo
│ └── classes.txt → Lista de clases (24 letras del alfabeto griego)
├── imagen/
│ └── imagen1.jpg → Imagen de prueba
├── src/
│ └── principal.cpp → Código fuente principal en C++
├── onnxruntime-linux-x64-gpu-1.22.0/ → Librería ONNX Runtime para GPU
├── onnxruntime-linux-x64-1.19.2/ → Librería ONNX Runtime para CPU
├── CMakeLists.txt → Script de configuración de CMake
└── README.md → Este archivo


---

## 🧰 Compilación y Ejecución

### 1. Limpiar carpeta de compilación previa y crear nueva:

```bash
cd /home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA
rm -rf build
mkdir build
cd build```

2. Configurar el proyecto con CMake:
⚠️ Reemplaza la ruta según la ubicación local de tu proyecto. 

```bash
cmake \
  -DONNXRUNTIME_DIR=/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/onnxruntime-linux-x64-gpu-1.22.0 \
  -DONNXRUNTIME_CPU_DIR=/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/onnxruntime-linux-x64-1.19.2 \
  ..
```

3. Compilar 

make

4. Ejecutar la aplicación:

```bash
./principal
```

---


⚙🎥 Resultados Esperados
Al ejecutar el programa, se abrirá la ventana “Detección en Tiempo Real” , mostrando el flujo de video desde la cámara del equipo y superponiendo cuadros delimitadores (bounding boxes ) sobre las letras detectadas.

Características:
- Detección automática de letras del alfabeto griego en tiempo real.
- Muestra de FPS promedio en pantalla:
Modo CPU
Modo GPU (CUDA)
- Presiona la tecla q para cerrar la ventana de video.

