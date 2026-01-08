/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:22:05 by tzizi            #+#    #+#             */
/*   Updated: 2026/01/07 15:22:05 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../irc.hpp"

class Client
{
    private:
        int fd;
        std::string IPadd;
        std::string nickname;
        std::string username;

        bool registered;
    public:
        Client(){};
        Client(std::string nickname, std::string username, int fd);
        int GetFd(){return fd;}

        void SetFd(int fd){fd = fd;}
        void setIpAdd(std::string ipadd){IPadd = ipadd;}
};

#endif