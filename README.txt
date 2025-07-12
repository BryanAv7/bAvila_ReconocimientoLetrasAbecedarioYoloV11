Proyecto YOLOv11 – Reconocimiento de Letras del Alfabeto
--------------------------------------------------------

Autor: Bryan Avila
Carrera: Computación
Materia: Visión por Computadora
Fecha: 2025-06-28

Descripción:
------------
Este proyecto contiene un modelo de detección de objetos YOLOv11 con un proceso de transfer learning para reconocer letras de un alfabeto extranjero(Alfabeto Griego).

El modelo fue entrenado externamente desde un cuaderno de Google Colab, convertido a formato ONNX, y se utiliza para reconocer las letras en tiempo real desde la cámara del computador. Se pueden realizar pruebas tanto en CPU como en GPU.

Estructura del proyecto:
------------------------
TrabajoU4PartA/
├── build/                         → Carpeta de compilación
├── models/
│   ├── best.onnx     → Modelo entrenado y convertirdo en formato ONNX
│   ├── best2_simplified.onnx     → Modelo optimizado en formato ONNX
│   └── classes.txt               → Lista de clases (24 letras)
├── imagen/
│   └── imagen1.jpg               → Imagen de testeo(comprobar si el modelo predice)
├── src/
│   └── principal.cpp             → Función principal
├── onnxruntime-linux-x64-gpu-1.22.0/
│                                 → Librería ONNX Runtime (GPU)
├── CMakeLists.txt

Pasos para compilar y ejecutar:
-------------------------------
1. Eliminar build anterior y crear uno nuevo:

   cd /home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA
   rm -rf build
   mkdir build
   cd build

2. Configurar el proyecto con CMake:

   cmake -DONNXRUNTIME_DIR=/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/onnxruntime-linux-x64-gpu-1.22.0 ..

3. Compilar con todos los núcleos:

   make -j$(nproc)

4. Ejecutar:

   ./principal

Funcionamiento:
---------------
- El programa detecta automáticamente si hay una GPU disponible.
- En caso de no disponer una GPU, editar el código:
  // const bool isGPU = false;  // ← Usar CPU
  const bool isGPU = cv::cuda::getCudaEnabledDeviceCount() > 0;  

- Se realiza la prueba tanto sobre una imagen individual(como testeo del modelo) como en tiempo real desde la cámara.

- En la consola se muestran los FPS alcanzados para evaluar el rendimiento.

Notas adicionales:
------------------
- Verifica que el modelo `.onnx` y las clases `.txt` existan en el path correcto.
- ONNX Runtime debe estar correctamente descargado e integrado con CMake.
- Asegúrate de tener OpenCV con soporte de CUDA, en caso que se use la GPU.

