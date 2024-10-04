let username = '';

// Función para mostrar el chat
function showChat() {
    document.getElementById('usernameContainer').style.display = 'none';
    document.getElementById('chatContainer').style.display = 'block';
}

// Evento para manejar el formulario de username
const usernameForm = document.getElementById('usernameForm');
usernameForm.addEventListener('submit', (event) => {
    event.preventDefault();
    username = document.getElementById('usernameInput').value;
    if (username.trim()) {
        showChat();
    }
});

// Crear la conexión WebSocket
const ws = new WebSocket(`ws://${window.document.location.host}`);

// Eventos de WebSocket
ws.addEventListener("open", event => {
    console.log("WebSocket connection opened");
});

ws.addEventListener("close", event => {
    console.log("WebSocket connection closed");
});

ws.addEventListener("error", event => {
    console.error("WebSocket error observed:", event);
});

// Recepción de mensajes
ws.onmessage = function (event) {
    // Si el mensaje es un Blob, lo convertimos a texto
    if (event.data instanceof Blob) {
        const reader = new FileReader();
        reader.onload = function () {
            const msgDiv = document.createElement('div');
            msgDiv.classList.add('msgCtn');
            msgDiv.innerHTML = reader.result; // Convertir Blob a texto
            document.getElementById('messages').appendChild(msgDiv);
            document.getElementById('messages').scrollTop = document.getElementById('messages').scrollHeight;
        };
        reader.readAsText(event.data); // Leer el Blob como texto
    } else {
        const msgDiv = document.createElement('div');
        msgDiv.classList.add('msgCtn');
        msgDiv.innerHTML = event.data; // Si ya es texto, simplemente lo mostramos
        document.getElementById('messages').appendChild(msgDiv);
        document.getElementById('messages').scrollTop = document.getElementById('messages').scrollHeight;
    }
};

// Enviar mensajes en texto plano
const form = document.getElementById('msgForm');
form.addEventListener('submit', (event) => {
    event.preventDefault();
    const message = document.getElementById('inputBox').value;
    if (message.trim()) {
        const fullMessage = `${username}: ${message}`;
        ws.send(fullMessage); // Enviar el mensaje en texto plano
        document.getElementById('inputBox').value = '';
    }
});
