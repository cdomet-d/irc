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

More about the socket interfaces in the [sources](#sources).

## Sources

- [Sockets interface](https://www.ibm.com/docs/en/aix/7.2?topic=sockets-interface)
- [Epoll](https://www.sobyte.net/post/2022-04/epoll-efficiently)
- [Buffered I/O operations](https://fgiesen.wordpress.com/2015/10/25/reading-and-writing-are-less-symmetric-than-you-probably-think/)
- [How the Linux Syscalls works](https://www.youtube.com/watch?v=FkIWDAtVIUM) (video)
- [Context switching](https://www.youtube.com/watch?v=H4SDPLiUnv4&t=310s) (video)