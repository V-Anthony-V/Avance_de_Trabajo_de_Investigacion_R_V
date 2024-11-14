import cv2
import numpy as np

# Umbral de luz (ajustable)
umbral_luz = 120

# Iniciar la captura de video desde la cámara web
cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("No se puede acceder a la cámara.")
    exit()

while True:
    # Captura un frame de la cámara
    ret, frame = cap.read()

    if not ret:
        print("No se pudo capturar imagen.")
        break

    # Obtener las dimensiones del frame
    altura, ancho = frame.shape[:2]
    mitad_x, mitad_y = ancho // 2, altura // 2

    # Dividir el frame en cuatro cuadrantes
    cuadrante1 = frame[0:mitad_y, 0:mitad_x]        # Superior izquierdo
    cuadrante2 = frame[0:mitad_y, mitad_x:ancho]    # Superior derecho
    cuadrante3 = frame[mitad_y:altura, 0:mitad_x]   # Inferior izquierdo
    cuadrante4 = frame[mitad_y:altura, mitad_x:ancho] # Inferior derecho

    # Convertir cada cuadrante a escala de grises
    gris1 = cv2.cvtColor(cuadrante1, cv2.COLOR_BGR2GRAY)
    gris2 = cv2.cvtColor(cuadrante2, cv2.COLOR_BGR2GRAY)
    gris3 = cv2.cvtColor(cuadrante3, cv2.COLOR_BGR2GRAY)
    gris4 = cv2.cvtColor(cuadrante4, cv2.COLOR_BGR2GRAY)

    # Calcular el brillo promedio en cada cuadrante
    brillo1 = np.mean(gris1)
    brillo2 = np.mean(gris2)
    brillo3 = np.mean(gris3)
    brillo4 = np.mean(gris4)

    # Determinar el cuadrante con mayor luz
    brillos = [brillo1, brillo2, brillo3, brillo4]
    max_brillo = max(brillos)
    indice_max = brillos.index(max_brillo) + 1  # Cuadrantes numerados de 1 a 4

    # Imprimir el cuadrante con mayor luz
    print(f"Cuadrante {indice_max} tiene la mayor luz con un brillo promedio de {max_brillo:.2f}")

    # Dibujar el cuadrante de mayor luz en rojo
    if indice_max == 1:
        cv2.rectangle(frame, (0, 0), (mitad_x, mitad_y), (0, 0, 255), 2)  # Superior izquierdo
    elif indice_max == 2:
        cv2.rectangle(frame, (mitad_x, 0), (ancho, mitad_y), (0, 0, 255), 2)  # Superior derecho
    elif indice_max == 3:
        cv2.rectangle(frame, (0, mitad_y), (mitad_x, altura), (0, 0, 255), 2)  # Inferior izquierdo
    elif indice_max == 4:
        cv2.rectangle(frame, (mitad_x, mitad_y), (ancho, altura), (0, 0, 255), 2)  # Inferior derecho

    # Mostrar el frame con los cuadrantes
    cv2.imshow('Detección de Luz en Cuadrantes', frame)

    # Salir con la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar la cámara y cerrar las ventanas
cap.release()
cv2.destroyAllWindows()