


# ESP32-S como Adaptador WiFi USB

## 🚀 ESP32-S WiFi USB Adapter

### 📝 Descripción
Firmware para ESP32-S que permite:
- Configuración WiFi via interfaz web
- Escaneo de redes disponibles
- Persistencia de credenciales
- Transmisión de conexión via USB

##   Diagrama de Componentes

flowchart TB  
  - subgraph ESP32-S     
    -  A[WebServer] --> B[WiFi Manager]  
    -   B --> C[EEPROM]  
      -    D[USB Serial] --> E[PC]  
 end


## 💻 Código Principal
```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>

// Configuración EEPROM
#define EEPROM_SIZE 512
#define SSID_ADDR 0
#define PASS_ADDR 32

WebServer server(80);

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  
  if(!autoConnect()) {
    startAPMode();
  }
}

void loop() {
  server.handleClient();
}
```

## 🌈 Interfaz Web - CSS Completo
```css
:root {
  --primary-light: #a8e6cf;
  --primary: #7accc8;
  --primary-dark: #63b7b3;
  --accent: #ffd3b6;
  --text-dark: #2a363b;
}

body {
  font-family: 'Segoe UI', sans-serif;
  background: #f5fffa;
}

.container {
  background: white;
  border-radius: 15px;
  box-shadow: 0 4px 6px rgba(0,0,0,0.1);
}

.btn {
  background: var(--primary);
  transition: all 0.3s ease;
}

.btn:hover {
  transform: translateY(-2px);
  box-shadow: 0 6px 12px rgba(0,0,0,0.15);
}
```

## 🔄 Flujo de Operación
```
sequenceDiagram
    participant U as Usuario
    participant E as ESP32
    participant W as WiFi
    
    U->>E: Accede a 192.168.4.1
    E->>W: Escanea redes
    W-->>E: Lista redes
    E-->>U: Muestra interfaz
    U->>E: Envía credenciales
    E->>W: Intenta conexión
    alt Conexión exitosa
        W-->>E: Confirma
        E-->>U: Muestra éxito
    else Error
        W-->>E: Rechaza
        E-->>U: Pide reintentar
    end
```

## 📊 Especificaciones Técnicas
| Parámetro       | Detalle                  |
|-----------------|--------------------------|
| **Hardware**    |                          |
| Placa           | ESP32-S                  |
| Memoria         | 4MB Flash, 320KB RAM     |
| **Redes**       |                          |
| Protocolos      | 802.11 b/g/n             |
| Seguridad       | WPA/WPA2                 |
| **Interfaz**    |                          |
| Puerto Web      | 80                       |
| Tiempo Escaneo  | 2-3 segundos             |

## 🛠 Guía de Instalación
1. **Programar el ESP32**:
   ```bash
   platformio run --target upload
   ```

2. **Primera configuración**:
   - Conectarse al AP "ESP32-WiFi-Adapter"
   - Abrir `http://192.168.4.1`
   - Introducir credenciales WiFi

3. **Uso normal**:
   - El ESP32 se conectará automáticamente
   - La conexión estará disponible via USB

## 📚 API Reference
### Endpoints
| Ruta        | Método | Descripción                 |
|-------------|--------|-----------------------------|
| `/`         | GET    | Interfaz web principal      |
| `/scan`     | GET    | Devuelve redes WiFi (JSON)  |
| `/connect`  | POST   | Establece conexión          |

### Ejemplo de respuesta
```json
{
  "ssid": "MiRed",
  "rssi": -65,
  "encryption": 3
}
```

## ⚠️ Solución de Problemas
| Error                  | Solución                      |
|------------------------|-------------------------------|
| No aparece AP          | Verificar carga de firmware   |
| Conexión fallida       | Revisar credenciales          |
| Interfaz no carga      | Reiniciar dispositivo         |

## 📜 Licencia

<p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><span property="dct:title">ESP32-S como Adaptador WiFi USB</span> by <span property="cc:attributionName">pleroldan</span> is licensed under <a href="https://creativecommons.org/licenses/by-sa/4.0/?ref=chooser-v1" target="_blank" rel="license noopener noreferrer" style="display:inline-block;">CC BY-SA 4.0<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1" alt=""><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/sa.svg?ref=chooser-v1" alt=""></a></p>


## 🔄 Historial de Versiones
| Versión | Cambios            |
|---------|--------------------|
| 1.0.0   | Versión inicial    |
| 1.1.0   | Mejoras de interfaz|
| 1.1.1   | Identificacion de issues|


## 🔄 Historial de isues encontradas

| Versión | Problema            |
|---------|--------------------|
| 1.1.1   | No identifica la web de forma automatica    |

## 📚 Recursos Adicionales
- [Documentación ESP32](https://docs.espressif.com/)
- [Librería WebServer](https://github.com/espressif/arduino-esp32)
- [Ejemplos WiFi](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples)


> ✨ **Documentación completa**  
> 📅 Última actualización: 02/Abr/2025 
> 🔗 **Repositorio**: [github.com/tuusuario/esp32-wifi-adapter](https://github.com/tuusuario/esp32-wifi-adapter)


