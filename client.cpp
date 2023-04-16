#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

int main() {
      boost::asio::io_service io_service;
	//socket creation


      tcp::socket socket(io_service);
	//The tcp::socket class provides methods for establishing a connection to a remote host, 
	//sending and receiving data, and managing the socket's state. 
	//It is designed to be used in conjunction with other Boost.Asio classes and functions to create asynchronous network applications.
	
	//connection
      socket.connect( tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 	1234 ));
	
	// request/message from client
      const string msg = "Hello from Client!\n";

      boost::system::error_code error;
	//error_code is a class that represents an error code, typically used in conjunction with Boost.Asio 
	//and other Boost libraries to handle errors and exceptions that may occur during I/O operations.

      boost::asio::write( socket, boost::asio::buffer(msg), error );
	//boost::asio::write is a function in the Boost.Asio library that performs a synchronous write operation on a socket.
	
      if( !error ) {
         cout << "Client sent hello message!" << endl;
      }
      else {
         cout << "send failed: " << error.message() << endl;
      }
	
	// getting response from server
    	boost::asio::streambuf receive_buffer;
    	boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    	if( error && error != boost::asio::error::eof ) {
      	  cout << "receive failed: " << error.message() << endl;
    	}
    	else {
        const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
        cout << data << endl;
    	}
    	return 0;
}