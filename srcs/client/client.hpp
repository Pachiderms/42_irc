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
        int Fd;
        std::string IPadd;
        std::string nickname;
    public:
        Client(){};
        int GetFd(){return Fd;}

        void SetFd(int fd){Fd = fd;}
        void setIpAdd(std::string ipadd){IPadd = ipadd;}
};

#endif