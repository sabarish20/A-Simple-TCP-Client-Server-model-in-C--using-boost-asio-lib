#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

string read_(tcp::socket &socket){
	boost::asio::streambuf buf; 
	//boost::asio::streambuf is a class provided by the Boost.Asio library in C++. 
	//It represents a stream buffer, which is an object used to read or write data to a stream.
     	//In the context of network programming, a stream buffer is often used to read data from or write data to a socket. 
     	//The boost::asio::streambuf class provides methods to read data from the buffer, write data to the buffer, and manipulate the buffer's internal 	
	//pointers to move data around. 
        
	boost::asio::read_until(socket , buf , "\n"); 
	//boost::asio::read_until provides a convenient and efficient way to read data from a stream 
	//until a specific delimiter is encountered, which is a common operation in network programming.
	
     string data = boost::asio::buffer_cast <const char*>(buf.data());
	//boost::asio::buffer_cast<const char*> is a function provided by the Boost.Asio library in C++. 
	//It is used to convert a buffer object to a const char* pointer.
      
	return data;

}

void send_(tcp::socket & socket, const string& message) {
       const string msg = message + "\n";
       boost::asio::write( socket, boost::asio::buffer(message) );
}

int main(){
	boost::asio::io_service service;
	//boost::asio::io_service is a C++ class that manages a queue of asynchronous operations, 
	//such as reading or writing data to a socket or waiting for a timer to expire.
	//It schedules these operations for execution on one or more threads and 
	//provides methods for starting, stopping, and restarting the message queue.

	//listen for new connection
	
	tcp::acceptor acceptor_(service , tcp::endpoint(tcp::v4() , 1234));
	//Used to listen for connection requested by the client.
	//tcp::v4() is Ip V4 address and port 1234

	//socket creation 
	
	tcp::socket socket_(service);
	//tcp::socket is a C++ class provided by the Boost.Asio library that represents a TCP socket object.
	
	//waiting for connection

	acceptor_.accept(socket_);

	//read operation
	
	string message = read_(socket_);
	cout << message << endl;

	//write operation
	send_(socket_ , "Hello From Server!");
	cout << "Servent sent Hello Message to Client!" << endl;
	
	return 0;
}

