#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <string>

#include "asio.hpp"
#include "http/http.hpp"
#include "http/http_request.hpp"
#include "http/http_response.hpp"
#include "event/event.hpp"
#include "file/content.hpp"
#include "exceptions/parse_exception.hpp"
#include "exceptions/file_not_found_exception.hpp"

class get_request_event : public event
{
private:
	asio::ip::tcp::socket socket;

public:
	get_request_event() = delete;

	get_request_event(asio::io_service& service, asio::ip::tcp::socket socket)
		: socket(std::move(socket))                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	{
	}

	~get_request_event()
	{
	}

	virtual void notify() override
	{
		server::http::request request;

		//parse request
		try
		{
			char buff[4096] = { 0 };
			socket.read_some(asio::buffer(buff));

			request.parse(buff); 
		}
		catch(const server::parse_exception& e)
		{
			std::string status_string = server::http::get_status_string(server::http::BAD_REQUEST);

			server::http::response response(
				"Unknown",
				std::to_string(server::http::BAD_REQUEST),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}

		//TODO: change
		if (request.method == "GET")
		{
			do_get(request);
		}
		else if (request.method == "POST")
		{
			do_post(request);
		}
		else
		{
			std::string status_string = server::http::get_status_string(server::http::METHOD_NOT_ALLOWED);

			server::http::response response(
				request.version,
				std::to_string(server::http::METHOD_NOT_ALLOWED),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
	}

	void do_get(server::http::request request)
	{
		do_post(request);
	}

	void do_post(server::http::request request)
	{
		//send response
		try
		{
			content content("C:\\a" + request.url);
			std::ifstream read_stream = content.get_stream();

			//if file doesn't exist
			if (!read_stream)
			{
				throw server::file_not_found_exception("File doesn't exist", request.url);
			}

			std::string status_string = server::http::get_status_string(server::http::OK);

			server::http::response response(
				request.version,
				std::to_string(server::http::OK),
				status_string);

			/*
				get file data here
			*/
			std::stringstream file_stream;
			file_stream << read_stream.rdbuf();
			response.body = file_stream.str();

			response.set_header("Content-Type", content.get_type());

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const server::file_not_found_exception& e)
		{
			std::string status_string = server::http::get_status_string(server::http::NOT_FOUND);

			server::http::response response(
				request.version,
				std::to_string(server::http::NOT_FOUND),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();
		}
		catch (const std::exception& e)
		{
			std::string status_string = server::http::get_status_string(server::http::INTERNAL_SERVER_ERROR);

			server::http::response response(
				request.version,
				std::to_string(server::http::INTERNAL_SERVER_ERROR),
				status_string);

			response.body = status_string;

			socket.write_some(asio::buffer(response.string()));
			socket.close();

			throw e;
		}
	}
};