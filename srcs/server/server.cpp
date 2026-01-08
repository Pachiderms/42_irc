/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:20:10 by tzizi            #+#    #+#             */
/*   Updated: 2026/01/07 15:20:10 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "../client/client.hpp"

bool Server::Signal = false;
void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::Signal = true; //-> set the static boolean to true to stop the server
}

void Server::CloseFds(){
	for(size_t i = 0; i < clients.size(); i++){
		std::cout << RED << "Client <" << clients[i].GetFd() << "> Disconnected" << WHITE << std::endl;
		close(clients[i].GetFd());
	}
	if (server_socket_fd != -1){
		std::cout << RED << "Server <" << server_socket_fd << "> Disconnected" << WHITE << std::endl;
		close(server_socket_fd);
	}
}

void Server::SetServerSocket()
{
	struct sockaddr_in add;
	struct pollfd newClient;
	add.sin_family = AF_INET; //-> set the address family to ipv4
	add.sin_port = htons(this->port); //-> convert the port to network byte order (big endian)
	add.sin_addr.s_addr = INADDR_ANY; //-> set the address to any local machine address

	server_socket_fd = socket(AF_INET, SOCK_STREAM, 0); //-> create the server socket
	if(server_socket_fd == -1) //-> check if the socket is created
		throw(std::runtime_error("failed to create socket"));

	int en = 1;
	if(setsockopt(server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1) //-> set the socket option (SO_REUSEADDR) to reuse the address
		throw(std::runtime_error("failed to set option (SO_REUSEADDR) on socket"));
	if (fcntl(server_socket_fd, F_SETFL, O_NONBLOCK) == -1) //-> le serveur passe en mode non blocquant -> les opérations bloquantes return sans attendre si rien a faire (read).
		throw(std::runtime_error("failed to set option (O_NONBLOCK) on socket"));
	if (bind(server_socket_fd, (struct sockaddr *)&add, sizeof(add)) == -1) //-> bind the socket to the address (le lier au port d'ecoute)
		throw(std::runtime_error("failed to bind socket"));
	if (listen(server_socket_fd, SOMAXCONN) == -1) //-> listen for incoming connections and making the socket a passive socket
		throw(std::runtime_error("listen() failed"));

	newClient.fd = server_socket_fd; //-> add the server socket to the pollfd
	newClient.events = POLLIN; //-> set the event to POLLIN for reading data
	newClient.revents = 0; //-> set the revents to 0
	fds.push_back(newClient); //-> add the server socket to the pollfd
}

void Server::ServerInit(std::string port, std::string pwd)
{
	std::istringstream(port) >> this->port;
	this->pwd = pwd;
	SetServerSocket(); //-> create the server socket

	std::cout << GREEN << "Server <" << server_socket_fd << "> Connected" << WHITE << std::endl;
	std::cout << "Waiting to accept a connection...\n";

	while (Server::Signal == false) //-> run the server until the signal is received
	{
		if((poll(&fds[0],fds.size(),-1) == -1) && Server::Signal == false) //-> wait for an event
			throw(std::runtime_error("poll() failed"));

		for (size_t i = 0; i < fds.size(); i++) //-> check all file descriptors
		{
			if (fds[i].revents & POLLIN)//-> check if there is data to read
			{
				if (fds[i].fd == server_socket_fd)
					AcceptNewClient(); //-> accept new client
				else
					ReceiveNewData(fds[i].fd); //-> receive new data from a registered client
			}
		}
	}
	CloseFds(); //-> close the file descriptors when the server stops
}

void Server::AcceptNewClient()
{
	Client client; //-> create a new client
	struct sockaddr_in cliadd;
	struct pollfd newClient;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(server_socket_fd, (sockaddr *)&(cliadd), &len); //-> accept the new client
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1) //-> set the socket option (O_NONBLOCK) for non-blocking socket
		{std::cout << "fcntl() failed" << std::endl; return;}

	newClient.fd = incofd; //-> add the client socket to the pollfd
	newClient.events = POLLIN; //-> set the event to POLLIN for reading data
	newClient.revents = 0; //-> set the revents to 0

	client.SetFd(incofd); //-> set the client file descriptor
	client.setIpAdd(inet_ntoa((cliadd.sin_addr))); //-> convert the ip address to string and set it
	clients.push_back(client); //-> add the client to the vector of clients
	fds.push_back(newClient); //-> add the client socket to the pollfd

	std::cout << GREEN << "Client <" << incofd << "> Connected" << WHITE << std::endl;
}

void Server::ReceiveNewData(int fd)
{
	char buff[1024]; //-> buffer for the received data
	memset(buff, 0, sizeof(buff)); //-> clear the buffer

	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1 , 0); //-> receive the data

	if(bytes <= 0){ //-> check if the client disconnected
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHITE << std::endl;
		ClearClients(fd); //-> clear the client
		close(fd); //-> close the client socket
	}

	else{ //-> print the received data
		buff[bytes] = '\0';
		std::cout << YELLOW << "Client <" << fd << "> Data: " << WHITE << buff;
		std::stringstream msgstream(buff);
		std::string token;
		Request  request;
		while (msgstream >> token){
			if (!request.cmd_set){
				request.cmd = token;
				request.cmd_set = true;
			}
			else if (std::string("+-").find(token[0], 0) != std::string::npos){
				request.args.push_back(token);
			}
			else{
				request.params.push_back(token);
			}
		}
		std::cout << "CMD: " << request.cmd << std::endl;
		std::cout << "args: ";
		for (size_t i = 0; i < request.args.size(); i++){std::cout << request.args[i] << std::endl;}
		std::cout << "params: ";
		for (size_t i = 0; i < request.params.size(); i++){std::cout << request.params[i] << std::endl;}
	}
}

void Server::ClearClients(int fd){
	for(size_t i = 0; i < fds.size(); i++){ //-> remove the client from the pollfd
		if (fds[i].fd == fd)
			{fds.erase(fds.begin() + i); break;}
	}
	for(size_t i = 0; i < clients.size(); i++){ //-> remove the client from the vector of clients
		if (clients[i].GetFd() == fd)
			{clients.erase(clients.begin() + i); break;}
	}

}
