**PackageDownloader**

This is a rather simple C++ program. It was created to familiarize myself with the POCO C++ libraries.
 
The program uses Poco::Util::Application, Task objects and AbstractConfiguration (config()).

The actual use-case for this program seems rather thin. Suppose you have a large number of servers in your environment.
You need to deploy some software on multiple servers. However, due to security restrictions and firewalls, you do not have one single server where you can place this package on.
Rather, you have a bunch of servers (for example, YUM repo servers etc).
It is however difficult to predict which server will be reachable on a given client.

To complicate matters, HTTPS is preferred (for security reasons), and your machines may not have a HTTP client (again, for security reasons)

This program, as it is based on POCO libraries, should be highly portable and compile on most common unices, including HP-UX, Solaris and Tru64.
By using CMake as the build system, compiling the program should also work cross-platform.

**Compiler requirements**

The following things are required to compile the program:

- C++11 compliant compiler
- POCO libraries (preferably static)
- libSSL
- libcrypto
- pthreads

**Runtime requirements**

To limit the amount of runtime dependencies, compiling the POCO libraries statically should be preferred. 
The CMake configuration first searches for static (.a) libraries, before falling back to shared (.so) libraries.
