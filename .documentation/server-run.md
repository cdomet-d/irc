# IRC Server Event Loop Documentation  
**`Server::servRun()` Function Breakdown**  

This document explains the core event loop that drives the IRC server, detailing how it handles client connections and data exchanges using Linux's `epoll` system.

---

## Function Overview  
**Purpose**: Manages the server's main event loop using `epoll` for efficient I/O multiplexing.  
**Return**:  
- `true`: Normal shutdown (graceful exit)  
- `false`: Critical error during operation  

---

## Key Components  

### 1. **Initialization Output**  
```
                                std::cout << "Server listening on port " << port_
                                << " | IP address: " << inet_ntoa(servAddr_.sin_addr) << std::endl;
```
**Purpose**: Displays server's network configuration  
**Components**:  
- `port_`: Server's listening port (converted from host byte order)  
- `inet_ntoa()`: Converts binary IP (`servAddr_.sin_addr`) to human-readable string  

---

### 2. **Event Loop Structure**  
```
                                while (gSign == false) {
                                nbFds = epoll_wait(epollFd_, events_, MAX_EVENTS, -1);
                                // ... Event handling ...
}
```
**Purpose**: Continuous event monitoring until shutdown signal (`gSign`)  
**Flow Control**:  
- `gSign`: Global flag for graceful shutdown (e.g., SIGINT handler)  
- `-1` timeout: Blocks indefinitely until events occur  

---

### 3. **Epoll Event Harvesting**  
```
                                nbFds = epoll_wait(epollFd_, events_, MAX_EVENTS, -1);
```
**Purpose**: Retrieves active file descriptors with pending I/O  
**Parameters**:  
| Parameter    | Description                          |
|--------------|--------------------------------------|
| `epollFd_`   | Epoll instance created in `servInit` |
| `events_`    | Array to store triggered events      |
| `MAX_EVENTS` | Maximum events to process per cycle  |
| `-1`         | No timeout (wait indefinitely)       |  

**Returns**: Number of ready file descriptors (or `-1` on error)  

---

### 4. **Event Type Handling**  

#### **Case 1: New Client Connection**  
```
                                if (events_[i].data.fd == servFd_)
                                acceptClient();
```
**Trigger**: Activity on server socket (`servFd_`)  
**Behavior**:  
1. Accepts new TCP connection  
2. Creates `Client` object  
3. Registers client FD with epoll  
4. Adds to client tracking maps  

#### **Case 2: Client Data Exchange**  

```
                                else if (handleData(events_[i].data.fd) == false)
                                return (true);
```
**Trigger**: Activity on client socket  
**Process**:  
1. Reads incoming data using `recv()`  
2. Parses IRC commands  
3. Handles client disconnection (`bytes == 0`)  
4. Returns `false` on critical protocol errors  

---

## Critical Design Rationale  

### 1. **Epoll Efficiency**  
- **Scalability**: Handles 10,000+ connections efficiently vs. `select()`/`poll()`  
- **Edge Triggering**: Requires full read/write processing per event  
- **O(1) Complexity**: Constant-time event retrieval  

### 2. **Graceful Shutdown**  
- **Signal Handling**: External process sets `gSign` for clean exit  
- **Resource Cleanup**: Closes all client FDs and epoll instance  

### 3. **Event Prioritization**  
1. **New Connections**: Handled first to minimize connection latency  
2. **Client Data**: Processed in round-robin fashion to ensure fairness  

### 4. **Error Resilience**  
- **Epoll Errors**: Terminates on unexpected `epoll_wait` failures  
- **Client Errors**: Isolated per-client (doesn't crash server)  

---

## Flow Summary  
1. **Initialize** server state and display configuration  
2. **Enter loop**:  
   a. Wait for I/O events using `epoll_wait`  
   b. **New connection**: Call `acceptClient()`  
   c. **Existing client**: Process data via `handleData()`  
3. **Exit**:  
   - On shutdown signal (`gSign = true`)  
   - On critical epoll failure (`nbFds == -1`)  

---

## Key Functions & Parameters  

| **Component**       | **Purpose**                                  |
|----------------------|----------------------------------------------|
| `epoll_wait()`       | Retrieves I/O-ready file descriptors         |
| `acceptClient()`     | Handles new TCP connections                  |
| `handleData()`       | Processes client commands and disconnections |
| `events_[]`          | Stores active epoll events                   |
| `MAX_EVENTS`         | Limits events processed per iteration        |
| `gSign`              | Global shutdown flag                         |

This event loop implementation provides a robust foundation for handling concurrent client interactions while maintaining server stability and performance.  