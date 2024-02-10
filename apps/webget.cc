#include "../util/socket.hh"
// #include "socket.hh"

#include <cstdlib>
#include <iostream>
#include <span>
#include <string>

using namespace std;

void get_URL( const string& host, const string& path )
{
  // cerr << "Function called: get_URL(" << host << ", " << path << ")\n";
  // cerr << "Warning: get_URL() has not been implemented yet.\n";
  TCPSocket tcpSocket = TCPSocket();
  // string hostname = "8.8.8.8",servicename = path;
  Address tAddress = Address(host,"http");
  tcpSocket.connect(tAddress);
  // tcpSocket.write((string)"GET "+"http://"+host+path+" HTTP/1.1"+"\r\n");

  tcpSocket.write((string)"GET "+path+" HTTP/1.1"+"\r\n");
  tcpSocket.write("Host: "+host+"\r\n\r\n");
  tcpSocket.shutdown(SHUT_WR);
  // tcpSocket.write()
  while(!tcpSocket.eof())
  {
    std::string retStr;
    tcpSocket.read(retStr);
    cout<<retStr;
  }
  // cout<<retStr;
  tcpSocket.close();
}

int main( int argc, char* argv[] )
{
  try {
    if ( argc <= 0 ) {
      abort(); // For sticklers: don't try to access argv[0] if argc <= 0.
    }

    auto args = span( argv, argc );

    // The program takes two command-line arguments: the hostname and "path" part of the URL.
    // Print the usage message unless there are these two arguments (plus the program name
    // itself, so arg count = 3 in total).
    if ( argc != 3 ) {
      cerr << "Usage: " << args.front() << " HOST PATH\n";
      cerr << "\tExample: " << args.front() << " stanford.edu /class/cs144\n";
      return EXIT_FAILURE;
    }

    // Get the command-line arguments.
    const string host { args[1] };
    const string path { args[2] };

    // Call the student-written function.
    get_URL( host, path );
  } catch ( const exception& e ) {
    cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
