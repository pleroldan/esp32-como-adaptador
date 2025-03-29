#ifndef HTML_CONTENT_H
#define HTML_CONTENT_H

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP32 WiFi USB Adapter</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    :root {
      --primary-light: #a8e6cf;
      --primary: #7accc8;
      --primary-dark: #63b7b3;
      --secondary: #dcedc1;
      --accent: #ffd3b6;
      --text-dark: #2a363b;
      --text-light: #f9f9f9;
      --shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
    }
    
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      margin: 0;
      padding: 0;
      background-color: #f5fffa;
      color: var(--text-dark);
      line-height: 1.6;
    }
    
    .container {
      max-width: 800px;
      margin: 20px auto;
      padding: 30px;
      background: white;
      border-radius: 15px;
      box-shadow: var(--shadow);
      background: linear-gradient(135deg, #f8fffe 0%, #f0fff8 100%);
    }
    
    h1 {
      color: var(--primary-dark);
      text-align: center;
      margin-bottom: 30px;
      font-weight: 600;
      position: relative;
      padding-bottom: 15px;
    }
    
    h1::after {
      content: '';
      position: absolute;
      bottom: 0;
      left: 50%;
      transform: translateX(-50%);
      width: 80px;
      height: 3px;
      background: var(--accent);
      border-radius: 3px;
    }
    
    .btn {
      background-color: var(--primary);
      color: white;
      border: none;
      padding: 12px 25px;
      font-size: 16px;
      border-radius: 50px;
      cursor: pointer;
      transition: all 0.3s ease;
      box-shadow: var(--shadow);
      font-weight: 500;
      letter-spacing: 0.5px;
      display: inline-block;
      margin: 10px 0;
    }
    
    .btn:hover {
      background-color: var(--primary-dark);
      transform: translateY(-2px);
      box-shadow: 0 6px 12px rgba(0, 0, 0, 0.15);
    }
    
    .btn-scan {
      background-color: var(--primary-light);
      color: var(--text-dark);
    }
    
    .btn-scan:hover {
      background-color: var(--primary);
      color: white;
    }
    
    .network-list {
      margin: 30px 0;
      border-radius: 10px;
      overflow: hidden;
    }
    
    .network-item {
      padding: 15px 20px;
      background: white;
      border-bottom: 1px solid #e0f7fa;
      transition: all 0.2s ease;
      display: flex;
      justify-content: space-between;
      align-items: center;
    }
    
    .network-item:hover {
      background-color: var(--secondary);
      transform: scale(1.01);
    }
    
    .network-ssid {
      font-weight: 600;
      color: var(--primary-dark);
    }
    
    .network-rssi {
      color: var(--text-dark);
      font-size: 14px;
      display: flex;
      align-items: center;
    }
    
    .signal-icon {
      margin-right: 8px;
      color: var(--primary);
    }
    
    .password-input {
      margin: 25px 0;
      padding: 20px;
      background-color: rgba(168, 230, 207, 0.2);
      border-radius: 10px;
    }
    
    input[type="password"] {
      width: 100%;
      padding: 12px 15px;
      margin: 10px 0 20px;
      border: 2px solid var(--primary-light);
      border-radius: 50px;
      font-size: 16px;
      transition: all 0.3s;
      background-color: rgba(255, 255, 255, 0.8);
    }
    
    input[type="password"]:focus {
      outline: none;
      border-color: var(--primary);
      box-shadow: 0 0 0 3px rgba(122, 204, 200, 0.3);
    }
    
    .status {
      padding: 15px 20px;
      margin: 20px 0;
      border-radius: 10px;
      display: none;
      animation: fadeIn 0.5s ease;
    }
    
    @keyframes fadeIn {
      from { opacity: 0; transform: translateY(10px); }
      to { opacity: 1; transform: translateY(0); }
    }
    
    .connected {
      background-color: rgba(168, 230, 207, 0.3);
      color: #2a6b5e;
      border-left: 4px solid var(--primary-dark);
    }
    
    .error {
      background-color: rgba(255, 179, 186, 0.3);
      color: #b33a3a;
      border-left: 4px solid #ff8a98;
    }
    
    .wifi-icon {
      display: inline-block;
      width: 24px;
      height: 24px;
      margin-right: 10px;
      vertical-align: middle;
    }
    
    .header {
      display: flex;
      justify-content: space-between;
      align-items: center;
      margin-bottom: 20px;
    }
    
    .logo {
      font-weight: 700;
      color: var(--primary-dark);
      font-size: 20px;
    }
    
    .connection-status {
      padding: 5px 10px;
      border-radius: 20px;
      font-size: 14px;
      background-color: var(--secondary);
      color: var(--text-dark);
    }
    
    @media (max-width: 600px) {
      .container {
        padding: 20px;
        margin: 10px;
      }
      
      h1 {
        font-size: 24px;
      }
    }
  </style>
</head>
<body>
  <div class="container">
    <div class="header">
      <div class="logo">ESP32 WiFi Adapter</div>
      <div id="connectionStatus" class="connection-status">Desconectado</div>
    </div>
    
    <h1>
      <svg class="wifi-icon" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
        <path d="M5 12.55a11 11 0 0 1 14.08 0"></path>
        <path d="M1.42 9a16 16 0 0 1 21.16 0"></path>
        <path d="M8.53 16.11a6 6 0 0 1 6.95 0"></path>
        <line x1="12" y1="20" x2="12" y2="20"></line>
      </svg>
      Configuración WiFi
    </h1>
    
    <div id="status" class="status"></div>
    
    <button id="scanBtn" class="btn btn-scan">
      <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="vertical-align: middle; margin-right: 8px;">
        <circle cx="11" cy="11" r="8"></circle>
        <line x1="21" y1="21" x2="16.65" y2="16.65"></line>
      </svg>
      Escanear Redes
    </button>
    
    <div id="networkList" class="network-list"></div>
    
    <div id="passwordSection" style="display:none;">
      <div class="password-input">
        <label for="wifiPassword">Contraseña para <span id="selectedSSID" style="color: var(--primary-dark); font-weight: 600;"></span>:</label>
        <input type="password" id="wifiPassword" placeholder="(opcional para redes abiertas)">
      </div>
      <button id="connectBtn" class="btn">
        <svg xmlns="http://www.w3.org/2000/svg" width="18" height="18" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" style="vertical-align: middle; margin-right: 8px;">
          <path d="M22 11.08V12a10 10 0 1 1-5.93-9.14"></path>
          <polyline points="22 4 12 14.01 9 11.01"></polyline>
        </svg>
        Conectar
      </button>
    </div>
  </div>

  <script>
    document.getElementById('scanBtn').addEventListener('click', scanNetworks);
    document.getElementById('connectBtn').addEventListener('click', connectToNetwork);

    function scanNetworks() {
      const networkList = document.getElementById('networkList');
      networkList.innerHTML = '<p>Escaneando redes...</p>';
      
      fetch('/scan')
        .then(response => response.json())
        .then(networks => {
          if (networks.length === 0) {
            networkList.innerHTML = '<p>No se encontraron redes WiFi</p>';
            return;
          }
          
          networkList.innerHTML = '';
          networks.forEach(network => {
            const networkItem = document.createElement('div');
            networkItem.className = 'network-item';
            networkItem.innerHTML = `
              <span class="network-ssid">${network.ssid}</span>
              <span class="network-rssi">${network.rssi} dBm</span>
              <div style="clear:both;"></div>
            `;
            networkItem.addEventListener('click', () => selectNetwork(network.ssid));
            networkList.appendChild(networkItem);
          });
        });
    }

    function selectNetwork(ssid) {
      document.getElementById('selectedSSID').textContent = ssid;
      document.getElementById('passwordSection').style.display = 'block';
      window.scrollTo(0, document.body.scrollHeight);
    }

    function connectToNetwork() {
      const ssid = document.getElementById('selectedSSID').textContent;
      const password = document.getElementById('wifiPassword').value;
      const statusDiv = document.getElementById('status');
      
      statusDiv.style.display = 'block';
      statusDiv.className = 'status';
      statusDiv.textContent = 'Conectando...';
      
      fetch('/connect', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
        },
        body: `ssid=${encodeURIComponent(ssid)}&password=${encodeURIComponent(password)}`
      })
      .then(response => response.text())
      .then(result => {
        if (result.includes('success')) {
          statusDiv.className = 'status connected';
          statusDiv.innerHTML = `Conectado a <strong>${ssid}</strong>. IP: ${result.split('|')[1]}`;
        } else {
          statusDiv.className = 'status error';
          statusDiv.textContent = result;
        }
      })
      .catch(error => {
        statusDiv.className = 'status error';
        statusDiv.textContent = 'Error de conexión: ' + error;
      });
    }

    // Actualizar estado de conexión
    function updateConnectionStatus() {
      fetch('/status')
        .then(response => response.json())
        .then(data => {
          const statusElement = document.getElementById('connectionStatus');
          if (data.connected) {
            statusElement.textContent = `Conectado a ${data.ssid}`;
            statusElement.style.backgroundColor = '#a8e6cf';
          } else {
            statusElement.textContent = 'Desconectado';
            statusElement.style.backgroundColor = '#dcedc1';
          }
        });
    }
    
    // Actualizar cada 5 segundos
    setInterval(updateConnectionStatus, 5000);
    updateConnectionStatus();
  </script>
</body>
</html>
)rawliteral";

#endif