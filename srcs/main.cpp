/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzizi <tzizi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 11:30:19 by tzizi            #+#    #+#             */
/*   Updated: 2026/01/06 11:30:19 by tzizi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#include "server/server.hpp"
#include "client/client.hpp"

int main()
{
	Server ser;
	std::cout << "---- SERVER ----" << std::endl;
	try{
		signal(SIGINT, Server::SignalHandler); //-> catch the signal (ctrl + c)
		signal(SIGQUIT, Server::SignalHandler); //-> catch the signal (ctrl + \)
		ser.ServerInit(); //-> initialize the server
	}
	catch(const std::exception& e){
		ser.CloseFds(); //-> close the file descriptors
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}
