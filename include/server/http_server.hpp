#pragma once

#include <csignal>
#include <memory>
#include <iostream>
#include <functional>
#include <cstring>

#include "asio.hpp"
#include "utils/utils.hpp"
#include "utils/basic_option.hpp"
#include "utils/logger.hpp"
#include "event/event.hpp"
#include "event/get_request_event.hpp"
#include "event/thread_pool.hpp"

_IMPLEMENT_SCOPE

class http_server
{
	std::unique_ptr<logging::logger> log;

private:
	asio::io_service io_service;
	asio::signal_set signal;
	asio::ip::tcp::socket listen_socket;
	asio::ip::tcp::acceptor acceptor;

	std::string root_path;
	int worker_number;
	int max_task;
	thread_pool<std::shared_ptr<event>> event_pool;

private:
	//accept connection and reday to communication
	void run();

	void on_accept(const asio::error_code error_code);
	void on_stop(const asio::error_code error_code);

public:
	//initialize server with default option
	http_server(int max_worker, int max_task);
	virtual ~http_server();

	//Not allow assign, copy, move
	http_server(const http_server& server) = delete;
	http_server(http_server&& server) = delete;
	http_server& operator=(const http_server& server) = delete;

	//server start end function
	//get all resource
	void start(std::string ip, std::string port, std::string root_path);
	//release all resource
	void stop();

	std::string get_root_path();
};

_IMPLEMENT_END
