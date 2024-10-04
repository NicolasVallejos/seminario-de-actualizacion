import express from 'express';
import { createServer } from 'http';
import { WebSocketServer } from 'ws';

const app = express();
const server = createServer(app);
const wss = new WebSocketServer({ server });

// Servir archivos estáticos desde la carpeta 'public'
app.use(express.static('public'));

// Endpoint para obtener un mensaje de ejemplo
app.get('/public-key', (req, res) => {
    res.send('No encryption in use'); // Simplemente enviar un mensaje
});

// Manejar conexiones de clientes
wss.on('connection', (client) => {
    console.log('Client connected!');

    // Manejar mensajes recibidos
    client.on('message', (msg) => {
        try {
            console.log(`Message: ${msg}`);
            broadcast(msg); // Simplemente transmitir el mensaje
        } catch (error) {
            console.error(`Error processing message: ${error}`);
        }
    });

    // Manejar desconexión del cliente
    client.on('close', () => {
        console.log('Client disconnected');
    });

    // Manejar errores del cliente
    client.on('error', (error) => {
        console.error(`WebSocket error: ${error}`);
    });
});

// Función para transmitir mensajes a todos los clientes conectados
function broadcast(msg) {
    for (const client of wss.clients) {
        if (client.readyState === client.OPEN) {
            client.send(msg);
        }
    }
}

// Definir el puerto para el servidor
const PORT = process.argv[2] || 8080;

// Iniciar el servidor y manejar errores
server.listen(PORT, (err) => {
    if (err) {
        console.error(`Failed to start server: ${err.message}`);
        return;
    }
    console.log(`Server listening on port ${PORT}...`);
});
