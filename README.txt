# Trabajo Unidad 4 – Parte A  
## Modelo YOLOv11 con Transfer Learning para el Reconocimiento de Letras del Alfabeto Griego


---

### 📌 Descripción  
Esta parte del trabajo se implementa un sistema de detección de objetos basado en **YOLOv11**, adaptado mediante **transfer learning** para reconocer las 24 letras del **alfabeto griego**. El modelo se entrenó en Google Colab, se exportó al formato **ONNX** y se integra en una aplicación C++ que permite inferencia en tiempo real desde la cámara del equipo. Soporta ejecución tanto en **CPU** como en **GPU (CUDA)**.

---

### 📁 Estructura del proyecto  

TrabajoU4PartA/
├── build/ → Carpeta de compilación
├── models/
│ ├── best.onnx → Modelo entrenado en formato ONNX
│ ├── best2_simplified.onnx → Versión optimizada del modelo
│ └── classes.txt → Lista de clases (24 letras del alfabeto griego)
├── imagen/
│ └── imagen1.jpg → Imagen de prueba (extra para probar el modelo al cargar una imagen)
├── src/
│ └── principal.cpp → Código fuente principal
├── onnxruntime-linux-x64-gpu-1.22.0/ → Librería ONNX Runtime para GPU
├── onnxruntime-linux-x64-1.19.2/ → Librería ONNX Runtime para CPU
├── CMakeLists.txt → Script de configuración de CMake
└── README.md → Este archivo

---

### 🧰  Compilación y ejecución

1. **Eliminar compilación anterior y crear carpeta `build/`:**  
   ```bash
   cd /home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA
   rm -rf build
   mkdir build
   cd build
``` 

2. **Configurar el proyecto con CMake (indicando las rutas de ONNX Runtime):**

```bash
cmake \
  -DONNXRUNTIME_DIR=/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/onnxruntime-linux-x64-gpu-1.22.0 \
  -DONNXRUNTIME_CPU_DIR=/home/bryan/Documentos/segundoInterciclo/TrabajoU4PartA/onnxruntime-linux-x64-1.19.2 \
  ..
```

2. Compilar utilizando todos los núcleos disponibles:

```bash
make -j$(nproc)
```

4. **Ejecutar la aplicación:**

```bash
./principal
```


### ⚙🎥 Resultados

**Video en tiempo real**  
   Al abrir la cámara, el usuario podrá mostrar figuras de letras del alfabeto griego en tiempo real y la aplicación las detectará automáticamente.  
   - Se abre la ventana **“Detección en Tiempo Real”** con el flujo de video y las detecciones superpuestas.  
   - En la esquina superior izquierda aparece el contador de **FPS** para ambos modos de ejecución:  
     - **CPU:** FPS promedio al procesar en la CPU.  
     - **GPU:** FPS promedio al procesar con aceleración CUDA en GPU, mostrando el **speedup** logrado.  
   - Para salir, el usuario presiona la tecla `q`. 

