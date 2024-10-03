#include<iostream>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\System.hpp>
#include<WinSock2.h>
#include<ws2tcpip.h>
#include<fstream>

#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace sf;

bool Initialize()
{
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data);
}

int main()
{

	if (Initialize())
	{
		cout << "initialization failed";
		return 0;
	}
	else
		cout << "initialized successfully"<<endl;


	SOCKET clientSocket;

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "SOCKET is not created" << endl;
		return 0;
	}
	cout << "Created socket" << endl;

	string serveraddress = "10.150.55.86";
	int port = 5000;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_pton(AF_INET, serveraddress.c_str(), &serveraddr.sin_addr);
	while(1)
	{
		if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
		{
			cout << "Not connected" << endl;
			closesocket(clientSocket);
			WSACleanup();
		}
		else
		{
			cout << "Connected" << endl;
			break;
		}

	}

	/*fstream inputfile;
	inputfile.open("exitfile.csv");
	if (!inputfile.is_open())
	{
		cout << "can't open file";
		return 0;
	}
	Sleep(180000);
	string s;
	while (getline(inputfile, s))
	{
		if (send(clientSocket, s.c_str(), s.length(), 0) == SOCKET_ERROR)
		{
			cout << "Message not sent";
			closesocket(clientSocket);
			WSACleanup();
			return 0;
		}
		cout << "Message sent" << endl;
		Sleep(2000);
	}
	*/
	while (1)
	{
		string m;
		RenderWindow window(VideoMode(1920, 1060), "CityCenter");
		window.setFramerateLimit(60);
		RectangleShape in;
		in.setFillColor(Color::White);
		in.setSize(Vector2f(350.f, 70.f));
		in.setPosition(Vector2f(785.f, 505.f));
		Font font;
		font.loadFromFile("ConsolaMono-Bold.ttf");
		Text Inputtext;
		Inputtext.setFont(font);
		Inputtext.setCharacterSize(50.f);
		Inputtext.setPosition(Vector2f(785.f, 505.f));
		Inputtext.setFillColor(Color::Black);
		Text cityCenter;
		Text Exit;
		Exit.setFont(font);
		Exit.setCharacterSize(60.f);
		Exit.setPosition(Vector2f(700.f, 400.f));
		Exit.setString("Enter Token Number");
		Exit.setFillColor(Color::Black);

		Font bali;
		bali.loadFromFile("Baliana.ttf");
		cityCenter.setFont(bali);
		cityCenter.setString("CityCenter");
		cityCenter.setCharacterSize(200);
		cityCenter.setFillColor(Color(255, 215, 0));
		cityCenter.setPosition(Vector2f(630.f, 50.f));
		RectangleShape button(Vector2f(200.f, 70.f));
		button.setFillColor(Color::Blue);
		button.setPosition(Vector2f(840.f, 600.f));
		Text submit;
		submit.setString("Submit");
		submit.setFont(font);
		submit.setCharacterSize(50);
		submit.setPosition(Vector2f(855.f, 600.f));
		submit.setFillColor(Color::White);
		String inputstring;

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x<1045&& Mouse::getPosition(window).x>845 && Mouse::getPosition(window).y<670 && Mouse::getPosition(window).y>600)
				{
					m = string(inputstring);
					window.close();
					break;
				}
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						inputstring += event.text.unicode;
						Inputtext.setString(inputstring);
					}
				}
				window.draw(Inputtext);
			}
			window.clear(Color(106, 137, 167));
			window.draw(in);
			window.draw(cityCenter);
			window.draw(Inputtext);
			window.draw(button);
			window.draw(submit);
			window.draw(Exit);
			window.display();
		}



		if (m.size() <= 0)
			continue;
		if (send(clientSocket, m.c_str(), m.length(), 0) == SOCKET_ERROR)
		{
			cout << "Message not sent";
			closesocket(clientSocket);
			WSACleanup();
			return 0;
		}
		cout << "Message sent" << endl;
	}

	
	closesocket(clientSocket);
	WSACleanup();
	return 1;
}