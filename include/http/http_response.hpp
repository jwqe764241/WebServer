#pragma once

#include <sstream>
#include <string>

#include "http/http.hpp"
#include "utils/utils.hpp"

#include "exceptions/parse_exception.hpp"

_IMPLEMENT_SCOPE

namespace http{

	struct response
	{
	public:
		//������
		std::string http_version;
		std::string response_code;
		std::string describe;

		//�ΰ� ��� ���� �߰�
		header header;
		std::string body;
	public:
		response();
		response(
			std::string http_version, 
			std::string response_code, 
			std::string describe);
		~response();

		//std::string ���ڿ��� ����
		std::string string();
		std::string operator[](const std::string key);
		//�ΰ� ��� ���� �߰�
		void add(const std::string key, const std::string value);
	};

}

_IMPLEMENT_END