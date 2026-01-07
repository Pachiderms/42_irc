/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:30:39 by tzizi            #+#    #+#             */
/*   Updated: 2026/01/06 11:30:39 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sys/socket.h> //-> for socket()bind , accept etc...
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in and linked structs
#include <fcntl.h>
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll() and pollfd struct
#include <csignal>

#define RED "\e[1;31m"
#define BLUE "\e[0;34m"
#define WHITE "\e[0;37m"
#define GREEN "\e[1;32m"
#define YELLOW "\e[1;33m"
#define GREY "\e[38;5;249m"

// struct sockaddr_in {
//     sa_family_t     sin_family;
//     in_port_t       sin_port;
//     struct  in_addr sin_addr;
//     char            sin_zero[8];
// };

// struct in_addr {
//     in_addr_t s_addr;
// };

// struct pollfd {
//     int     fd;
//     short   events;//-> requested events
//     short   revents;//-> returned events
// };

#endif