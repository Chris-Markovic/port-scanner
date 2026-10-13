# Port Scanner

A simple **TCP port scanner written in C**. Give it an IPv4 address and a range of ports, and it tries to connect to each port and reports which ones are open, meaning a program on that machine is listening for connections.

I built it to learn how network connections work at a low level in C, using the standard POSIX socket API.

**Use responsibly:** only scan your own devices or networks you have permission to test. Scanning other people's systems without permission may be illegal.

## Features

- Scans any range of TCP ports on an IPv4 address
- Prints every open port it finds
- Uses only standard C and POSIX libraries, no external dependencies
- Clear usage message if arguments are missing

## How it works

A port is "open" if a program on the target machine accepts connections on it, for example a web server on port 80 or SSH on port 22. For each port in the range, the scanner:

1. Resolves the address and port with `getaddrinfo()`
2. Creates a TCP socket with `socket()`
3. Tries to connect with `connect()`
4. Reports the port as open if the connection succeeds, then closes the socket

This is called a **TCP connect scan**, the simplest and most common scanning technique.

## Requirements

- macOS or Linux (uses POSIX sockets, so it doesn't run natively on Windows; use WSL there)
- A C compiler such as `cc`, `gcc` or `clang`

## Installation

```bash
git clone https://github.com/Chris-Markovic/port-scanner.git
cd port-scanner
cc -Wall -o portscan port-scanner.c
```

## Usage

```bash
./portscan <IPv4 address> <first port> <last port>
```

**Example:** scan ports 1–1024 on your own computer:

```bash
./portscan 127.0.0.1 1 1024
```

**Example output:**

```
Port 22 is open.
Port 631 is open.
```

Only open ports are printed. If nothing is printed, no ports in that range are open.

## Limitations

- Ports are scanned one at a time, so large ranges can be slow, especially on remote hosts where a firewall silently drops connection attempts.
- IPv4 only.
- TCP only (no UDP scanning).

## Credits

Built with the help of the GeeksforGeeks tutorial [Creating a Port Scanner in C](https://www.geeksforgeeks.org/c/creating-a-portscanner-in-c/).
