/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:18:51 by tzizi            #+#    #+#             */
/*   Updated: 2026/01/07 15:18:51 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "../irc.hpp"
#include <sstream>

class Client;

class Server
{
    private:
        int port;
        int server_socket_fd;
        std::string pwd;
        static bool Signal;
        std::vector<Client> clients;
        std::vector<struct pollfd> fds;
    public:
        Server(){server_socket_fd = -1;}

        int GetPort(){return this->port;}
        void SetPort(int _port){this->port = _port;}
        int GetFd(){return this->server_socket_fd;}
        void SetFd(int fd){this->server_socket_fd = fd;}
        void SetPassword(std::string _pwd){this->pwd = _pwd;}
        std::string GetPassword(){return this->pwd;}

        void ServerInit(std::string port, std::string pwd);
        void SetServerSocket();
        void AcceptNewClient();
        void ReceiveNewData(int fd);

        static void SignalHandler(int signum);
    
        void CloseFds();
        void ClearClients(int fd);
};

class Request
{
    public:
        Request(){cmd_set = false;}
        
        std::string cmd;
        std::vector<std::string> args;
        std::vector<std::string> params;
        bool cmd_set;
};

#endif