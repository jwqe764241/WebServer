#pragma once

#include <map>
#include <string>

#include "http/http.hpp"
#include "utils/utils.hpp"

_IMPLEMENT_SCOPE

namespace http
{

	using header = std::map<std::string, std::string>;

	//���� ��û ����
	//GET / favicon.ico HTTP / 1.1
	//Host: 127.0.0.1 : 5000
	//Connection : keep - alive
	//User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 64.0.3282.186 Safari / 537.36
	//Accept : image / webp, image / apng, image/*,*/*; q = 0.8
	//Referer: http://127.0.0.1:5000/
	//Accept - Encoding : gzip, deflate, br
	//Accept - Language : ko - KR, ko; q = 0.9, en - US; q = 0.8, en; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5
	//n; q = 0.7, zh - CN; q = 0.6, zh; q = 0.5

	struct request
	{
	private:
		method method;
		std::string abs_url;
		std::string url;
		std::string version;

		header header;
		std::string body;
			
	public:
		request();
		request(std::string http_request);

		std::string operator[](std::string key);
		void parse(std::string http_request);
		void add(std::string key, std::string value);

	};

}

_IMPLEMENT_END