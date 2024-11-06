# HTTP Web Server

This project is a simple HTTP web server application built with Winsock and C++ in Visual Studio. It is capable of handling multiple client connections, serving static HTML files, and responding to HTTP GET requests.

## Features

- **Multi-client Support**: Manages multiple client connections concurrently.
- **Static File Serving**: Serves HTML files located in the `wwwroot` directory based on client GET requests.
- **Basic Error Handling**: Responds with a 404 page if the requested file is not found.
- **Modular Structure**: Uses separate classes to handle core server functions.

## Project Structure

- **`main.cpp`**: Entry point that initializes and launches the `Server`.
- **`server.h` and `server.cpp`**: Defines the `Server` class, which handles client connections, disconnections, and processes HTTP requests.
- **`listener.h` and `listener.cpp`**: Core listener class that manages socket operations, including connection handling and message broadcasting.

## How It Works

1. **Initialization**: The server initializes Winsock, sets up a listening socket, binds to the specified IP and port, and listens for incoming client connections.
2. **Client Connections**: Upon client connection, a welcome message is sent, and the client is added to the master set.
3. **HTTP Request Handling**: The server parses HTTP GET requests from clients, retrieves the requested file from the `wwwroot` directory, and responds with the file's content. If the file is not found, a 404 page is returned.

### HTTP Request Parsing

The server processes basic GET requests and looks for HTML files in the `wwwroot` folder. If a client requests a file (e.g., `GET /index.html HTTP/1.1`), the server attempts to find and return it. If the file is unavailable, a simple 404 error message is sent instead.

## How to Run

1. **Build the Project**: Open the project in Visual Studio and build it.
2. **Run the Server**: Launch the application to start the server on `127.0.0.1:8080`.
3. **Access the Server**: Open a web browser and navigate to `http://localhost:8080/greet.html,`, `http://localhost:8080/index.html` and `http://localhost:8080/` to interact with the server. Make sure to place HTML files in the `wwwroot` directory for them to be accessible.

## Dependencies

- **Winsock**: Windows Sockets API for network programming.

## Notes

- The **wwwroot** directory should be located in the executable's directory and contain an `index.html` file for the default page.
- The server is a single-threaded application using `select()` for socket management.

## License

This project is open-source and available under the MIT License.
