#pragma once

#include <asio.hpp>
#include <csignal>

#include <iostream>


#include "asio.hpp"

#include "utils/utils.hpp"
#include "utils/basic_option.hpp"
#include "event/event.hpp"
#include "event/get_request.event.hpp"
#include "event/thread_pool.hpp"

_IMPLEMENT_SCOPE

class server
{
	using server_option = option::basic_option<std::string, std::string>;

private:
	server_option option;

	asio::io_service io_service;
	asio::signal_set signal;
	asio::ip::tcp::socket listen_socket;
	asio::ip::tcp::acceptor acceptor;

	thread_pool<event*> event_pool;


private:
	//accept connection and reday to communication
	void run();

	void on_accept(const asio::error_code error_code);
	void on_stop(const asio::error_code error_code);

public:
	//initialize server with default option
	server();

	//Not allow assign, copy, move
	server(const server& server) = delete;
	server(server&& server) = delete;
	server& operator=(const server& server) = delete;

	//server start end function
	//get all resource
	void start(server_option option);
	//release all resource
	void exit();

};

_IMPLEMENT_END