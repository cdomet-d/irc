# EPOLL event monitoring

Epoll is an I/O event notification system. It allows I/O multiplexing within the Linux kernel.

Here's we're discussing *memory* I/O events, not external I/O events (such as the ones that allow one's keyboard to communicate with your computer).

## Definitions

- **I/O event or Input/Output event** is a read/write operation applied to an input/output object (files, pipes, sockets...). In Linux systems, those are `fds`.
- **I/O multiplexing** is the concurential monitoring of I/O sources, meaning that several sources are monitored at the same time, during the same operation. The monitor returns when one or more sources are available for operation, then perform said operations on them.
- **Events** can be of two kinds:
  - *readable event* means the [kernel read buffer](#kernel-buffer) associated with the fd is not empty and there is data to read.
  - *writable event* means the [kernel read buffer](#kernel-buffer) associated with the fd is not empty and there is space to write.

## Kernel buffer

When you make a system call (or syscall), you computer actually has to switch context between the space where your program operates - the *user space* - and the space where the kernel operates - the *kernel space*. These context switches are expensive, since they involve saving everything about the state of your applications (registers, stack pointers, etc...), but I/O operations are even more expensive.

The **kernel buffer** is a decicated memory space used to hold temporary information inbetween the *user space* and the *kernel space*. It's an intermediary between your hardware and the user-space operation space where your applications run. The OS uses it to store recently or frequently accessed information: you can think of it like a cache.

When using sockets, such as with `epoll()`, we are not interfacing with the hardware by default. This allows sockets to be more efficients than plain fds (even though, deep down, they are fds. [With a mustache and a sombrero](assets/socket.png), but fds nonetheless.)

Given the need to communicate easily between processes and across networks, the sockets were developped as a way to efficiently connect and communicate on a single, or across multiple machines. Sockets are a *software abstration* provided by an operating system; the underlying software then manages the *hardware operation* for the user.

By design, all operations on sockets are stored in the kernel buffer before being sent to or received from the hardware, which allows the frequency of hardware operations to be greatly reduced.

More about the socket interfaces with [the IBM documentation](https://www.ibm.com/docs/en/aix/7.2?topic=sockets-interface).

## The notification mechanism

In short, Epoll is a *notification mechanism* that monitors each socket associated kernel buffer, notifiying the kernel when the buffer is not empty (read) or when the buffer is full (write).

Epoll is an [indirection mechanism](#indirection) which allows the user to manipulate and monitor ressources without directly interfacing with raw fds. Instead, we interact with the Epoll API (ie: Application programming interface). 

### A word about epoll's structures

Epolls stores the ressources transmitted by the user within a [red black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree). That tree is stored in the kernel high-speed cache.

Each nodes contains the fd associated with the ressource, as well as a pointer to a file structure containing metadata regarding that fd (read/write offsets, permissions, reference count (ie: the number of processes that share the ressource)...)

That red-black tree is called the **interest list**. It is manipulated via `epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)`. More about this function [here](https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-epoll-ctl-control-interface-epoll-file-descriptor).

In addition to that, epoll also maintains a *linked list*, which holds a list of the fds that are already read


## Sources

- [Sockets interface](https://www.ibm.com/docs/en/aix/7.2?topic=sockets-interface)
- [Epoll](https://www.sobyte.net/post/2022-04/epoll-efficiently)
- [Buffered I/O operations](https://fgiesen.wordpress.com/2015/10/25/reading-and-writing-are-less-symmetric-than-you-probably-think/)
- [How the Linux Syscalls works](https://www.youtube.com/watch?v=FkIWDAtVIUM) (video)
- [Context switching](https://www.youtube.com/watch?v=H4SDPLiUnv4&t=310s) (video)
- [Async I/O](https://jvns.ca/blog/2017/06/03/async-io-on-linux--select--poll--and-epoll/)


The red-black tree allows O(log n) management of FDs, while the struct file reference enables direct access to the resource's state without traversing layers of indirection. => 

## Indirection

Indirection is a design patter that separate the desired outcome from the implementation details. More on this [here](https://stackoverflow.com/questions/18003544/what-does-level-of-indirection-mean-in-david-wheelers-aphorism).

> Relation to Abstraction

While often conflated, abstraction and indirection differ:

- Abstraction: Aggregates details into a simplified interface (e.g., a "file" concept).
- Indirection: Manages access through intermediaries (e.g., file descriptors pointing to struct file objects)

They frequently coexist: abstraction hides complexity, while indirection enables modularity.

David Wheeler’s aphorism — “All problems can be solved by another layer of indirection” — highlights its power, but RFC 1925 warns: “*It is always possible to add another level of indirection*” without solving the root issue/