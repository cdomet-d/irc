# IRC Server Client Acceptance Documentation  
**`Server::acceptClient()` Function Breakdown**  

This document explains the client connection handling mechanism, detailing how new connections are established, configured, and integrated into the server's tracking systems.

---

## Function Overview  
**Purpose**: Accepts new TCP connections, configures client sockets, and registers them with the server's event system.  
**Flow**:  
1. Create client object  
2. Accept network connection  
3. Configure client metadata  
4. Set up non-blocking I/O  
5. Register with epoll  
6. Add to tracking maps  

---

## Key Components  

### 1. **Client Object Creation**  
```
Client *newCli = new Client();
newCli->cliInfo.setRegistration(0);
```
**Purpose**: Initializes client state  
**Components**:  
- `Client()`: Constructor for client-specific data  
- `setRegistration(0)`: Marks client as unregistered (awaiting NICK/USER commands)  

---

### 2. **Connection Acceptance**  
```
newCli->setFd(accept(servFd_, (struct sockaddr *)&newCli->cliAddr_, &cliLen));
```
**Parameters**:  
| Parameter       | Description                          |  
|------------------|--------------------------------------|  
| `servFd_`        | Server's listening socket            |  
| `&newCli->cliAddr_` | Client address structure (output)   |  
| `&cliLen`        | Size of address structure (in/out)   |  

**Behavior**:  
- Blocks until new connection arrives (queued by `listen()`)  
- Populates `cliAddr_` with client's IP/port  
- Returns new file descriptor for client communication  

---

### 3. **Client Metadata Setup**  

#### **IP Address Resolution**  
```
inet_ntop(AF_INET, &newCli->cliAddr_.sin_addr, client_ip, INET_ADDRSTRLEN);
```
**Purpose**: Converts binary IP to human-readable string  
**Parameters**:  
- `AF_INET`: IPv4 address family  
- `sin_addr`: Binary IP from `accept()`  
- `INET_ADDRSTRLEN`: Buffer size for "xxx.xxx.xxx.xxx"  

#### **Hostname Resolution**  
```
getnameinfo((sockaddr*)&newCli->cliAddr_, cliLen, hostname, NI_MAXHOST, NULL, 0, 0);
```
**Purpose**: Attempts reverse DNS lookup  
**Fallback**: Uses IP address if resolution fails  

---

### 4. **Non-Blocking Configuration**  
```
fcntl(newCli->getFd(), F_SETFL, O_NONBLOCK);
```
**Purpose**: Enables asynchronous I/O  
**Critical For**:  
- Preventing server blockage during slow client operations  
- Compatibility with epoll's edge-triggered mode  

---

### 5. **Epoll Registration**  
```
epoll_ctl(epollFd_, EPOLL_CTL_ADD, newCli->getFd(), newCli->getCliEpoll());
```
**Parameters**:  
| Parameter       | Description                          |  
|------------------|--------------------------------------|  
| `epollFd_`       | Main epoll instance                  |  
| `EPOLL_CTL_ADD`  | Add operation                        |  
| `newCli->getFd()` | Client socket descriptor            |  
| `cliEpollTemp`   | Event struct (EPOLLIN | EPOLLOUT)    |  

**Event Types**:  
- `EPOLLIN`: Monitor incoming data  
- `EPOLLOUT`: Monitor write availability  

---

### 6. **Client Tracking**  
```
**Parameters**:  
| Parameter       | Description                          |  
|------------------|--------------------------------------|  
| `epollFd_`       | Main epoll instance                  |  
| `EPOLL_CTL_ADD`  | Add operation                        |  
| `newCli->getFd()` | Client socket descriptor            |  
| `cliEpollTemp`   | Event struct (EPOLLIN | EPOLLOUT)    |  

**Event Types**:  
- `EPOLLIN`: Monitor incoming data  
- `EPOLLOUT`: Monitor write availability  

---

### 6. **Client Tracking**  

clients_.insert(clientPair(newCli->getFd(), newCli));
usedNicks_.insert(nickPair(newCli->cliInfo.getNick(), newCli->getFd()));
```
**Data Structures**:  
1. `clients_` (Map):  
   - Key: File descriptor  
   - Value: Client object pointer  
2. `usedNicks_` (Map):  
   - Key: Nickname  
   - Value: File descriptor  

**Purpose**: Enables O(1) client lookups by FD or nickname  

---

## Error Handling Strategy  

### 1. **Exception Hierarchy**  
```
class InitFailed : public std::exception { ... };
```
**Triggers**:  
- Socket acceptance failure (`accept()`)  
- Non-blocking setup failure (`fcntl()`)  
- Epoll registration failure (`epoll_ctl()`)  

### 2. **Resource Cleanup**  
```
if (fcntl() == -1) {
close(newCli->getFd());
throw ...;
}
```
**Guarantees**: No file descriptor leaks during failures  

---

## Critical Design Rationale  

### 1. **Non-Blocking Requirement**  
- **Epoll Compatibility**: Essential for edge-triggered event handling  
- **Performance**: Prevents single client from blocking entire server  

### 2. **Metadata Collection**  
- **IP/Hostname**: Used for WHOIS, bans, and connection logging  
- **Registration Flag**: Enforces IRC protocol sequence (NICK/USER before commands)  

### 3. **Epoll Event Selection**  
- `EPOLLIN`: Detect incoming client commands  
- `EPOLLOUT`: Optimize write operations (avoid EAGAIN errors)  

### 4. **Scalability Considerations**  
- **O(1) Insertions**: Map-based tracking handles thousands of clients  
- **FD Limits**: Should use `setrlimit()` to increase max open files  

---

## Flow Summary  
1. **Create** new client object  
2. **Accept** TCP connection  
3. **Resolve** client network identifiers  
4. **Configure** non-blocking socket  
5. **Register** with epoll event system  
6. **Track** in client/nickname maps  
7. **Log** connection success  

This implementation ensures robust client handling while maintaining server stability through comprehensive error checking and resource management.  
