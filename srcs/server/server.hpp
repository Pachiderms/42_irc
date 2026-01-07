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
class Client;

class Server
{
    private:
        int Port;
        int SerSocketFd;
        static bool Signal;
        std::vector<Client> clients;
        std::vector<struct pollfd> fds;
    public:
        Server(){SerSocketFd = -1;}

        void ServerInit();
        void SerSocket();
        void AcceptNewClient();
        void ReceiveNewData(int fd);

        static void SignalHandler(int signum);
    
        void CloseFds();
        void ClearClients(int fd);
};

#endif