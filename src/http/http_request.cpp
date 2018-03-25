#include "http/http_request.hpp"

_IMPLEMENT_SCOPE

namespace http
{

	request::request()
	{
	}

	request::request(const string& http_request)
	try
	{
		parse(http_request);
	}
	catch(const parse_exception& e)
	{
		cout << "parse error : " << e.what() << endl;

		throw e;
	}

	string request::operator[](const string& key)
	{
		return header[key];
	}

	void request::parse(const string& http_request)
	{	
		if(http_request.empty())
		{
			throw parse_exception("HTTP request is empty. Check that request");
		}

		const int request_length = http_request.length();

		//ù°��
		const int start_offset = http_request.find(global::LINE_CHANGE, 0);
		if(start_offset != string::npos)
		{
			stringstream start_stream(http_request.substr(0, start_offset));

			start_stream >> method;
			start_stream >> url;
			start_stream >> version;
		}
		else
		{
			throw parse_exception("Can not resolve HTTP request, check that request");
		}

		//�ٵ� �Ľ�
		const int body_offset = http_request.find(global::DIVIDE_BODY, start_offset + 1);
		if(body_offset != string::npos)
		{
			body = http_request.substr(body_offset + 2, request_length);
		}
		
		//������ ���
		string data_string = http_request.substr(
			start_offset + 1,
			//������ ��� ���� = ��ü ���� - (��ü ���� - body ���� ��ġ - \n\n�� 2���̹Ƿ� -1) - ���� ��ġ
			request_length - (request_length - body_offset + 1) - start_offset
		);

		
		istringstream data_stream(data_string);
		for(string current_line; getline(data_stream, current_line);)
		{
			int token_offset = current_line.find(global::HEADER_TOKEN, 0);

			//add(
				//current_line.
			//)
		}




		//string temp_request(http_request);
		//std::replace(temp_request.begin(), temp_request.end(), global::LINE_CHANGE, global::WHITESPACE);



		//istringstream request_stream(temp_request);


		//while

	}

	void request::add(const string key, const string value)
	{
		header.insert(pair<string, string>(key, value));
	}

}

_IMPLEMENT_END