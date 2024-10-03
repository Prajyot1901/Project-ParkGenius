// Project-ParkGenius.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include <iostream>
#include <fstream>
#include<winsock2.h>
#include<tchar.h>
#include<WS2tcpip.h>
#include<thread>
#include<sstream>
#include<Windows.h>

#pragma comment(lib,"ws2_32.lib")

using namespace std;
using namespace sf;

class vehicle {
public:
    float weight;
    float width;
    float length;
    float height;
    string ROV;       // reason of visit;
    int time;      // time they stay;
    string entry_time;
    string number_plate;
    RectangleShape car;
    int cost;
    vehicle(int p,string np = "", string ET="", String R = "", int t = 0, float w=0.0, vector<float> dim={},int c=0)
    {
        weight = w;
        number_plate = np;
        entry_time = ET;
        ROV = R;
        time = t;
        length = 0;
        width = 0;
        height = 0;
        cost = c;
        RectangleShape temp(Vector2f(35.f, 70.f));
        car = temp;
        if(p==0)
            car.setFillColor(Color(0, 18, 53));
        if(p==1)
            car.setFillColor(Color(101,110, 126));
        car.setPosition(Vector2f(155.f, 565.f));
    }
};

class _Stack 
{
public:                                                                                                                                                                                     
    float weight_capacity;
    int space_capacity;
    int current_space;
    bool working;
    vector<vehicle*> upper_stack;
    vector<vehicle*> lower_stack;
    int lower_cnt;
    _Stack(float w = 500.0,int s = 5,int cs=0,bool wor=true)
    {
        weight_capacity = w;
        space_capacity = s;
        current_space = cs;
        working = wor;
        lower_cnt = 0;
        for (int i = 0; i < 5; i++)
        {
            vehicle* tmp = new vehicle(0, "", "", "", 0, 0.0, {}, 2);
            vehicle* tomp = new vehicle(1, "", "", "", 0, 0.0, {}, 1);
            upper_stack.push_back(tmp);
            lower_stack.push_back(tomp);
        }
    }
};

class Block {
public:
    vector<_Stack*> vec;
    int n;
    Block(int m)
    {
        n = m;
        for (int i = 0; i < n; i++)
        {
            _Stack* temp = new _Stack(500.0,5,0,true);
            vec.push_back(temp);
        }
    }
};

class parking {
public:
    Block* A;
    Block* B;
    Block* C;
    Block* D;
    Block* E;
    Block* F;
    Block* G;
    Block* H;
    int total_cost;
    vector<Block*> bk;
    CircleShape Entry_indicator;
    CircleShape Exit_indicator;
    parking()
    {
        A = new Block(4);
        bk.push_back(A);
        B = new Block(4);
        bk.push_back(B);
        C = new Block(4);
        bk.push_back(C);
        D = new Block(4);
        bk.push_back(D);
        E = new Block(4);
        bk.push_back(E);
        F = new Block(3);
        bk.push_back(F);
        G = new Block(4);
        bk.push_back(G);
        H = new Block(3);
        bk.push_back(H);
        total_cost = 0;
        Entry_indicator.setRadius(10);
        Entry_indicator.setFillColor(Color::Green);
        Entry_indicator.setPosition(Vector2f(970.f,860.f));
        Exit_indicator.setRadius(10);
        Exit_indicator.setFillColor(Color::Yellow);
        Exit_indicator.setPosition(Vector2f(970.f,190.f));
    }
};

bool check(string s)
{
    if (s[0] > 'H' || s[0] < 'A')
    {
        cout << "Block is not Available";
        return false;
    }
    for (int i = 1; i <= 6; i = i + 2)
    {
        if (s[i] != '_')
        {
            cout << "Not correct format";
            return false;
        }
    }
    if (s[0] == 'F' || s[0] == 'H')
    {
        if (s[2] <= '0' || s[2] > '3')
        {
            cout << "Not correct stack";
            return false;
        }
    }
    else
    {
        if (s[2] <= '0' || s[2] > '4')
        {
            cout << "Not correct stack";
            return false;
        }
    }
    if (s[4] <= '0' || s[4] > '5')
    {
        cout << "Not correct number of vehicle";
        return false;
    }
    return true;
}

string add_vehicle(parking* cityCenter,string Number, int weight, int time, vector<int> dim, string entry, string s)
{
    if (weight < 2000)
    {
        _Stack* ans=NULL;
        string ret_string;
        vehicle* anv=NULL;
        int ani;
        string B = "A";
        for (auto it : cityCenter->bk)
        {
            string S = "1";
            for(auto its : it->vec)
            {
                string N = "1";
                if (its->working && its->current_space < its->space_capacity)
                {
                    int index = -1;
                    for (auto bt : its->upper_stack)
                    {
                        index++;

                        if (bt->cost==2)
                        {
                            its->lower_stack[index]->cost = 0;
                            its->current_space++;
                            bt->number_plate = Number;
                            bt->weight = weight;
                            bt->ROV = s;
                            bt->entry_time = entry;
                            bt->time = time;
                            bt->length = dim[0];
                            bt->width = dim[1];
                            bt->height = dim[2];
                            bt->cost = INT_MAX;
                            bt->car.setFillColor(Color(0, 36, 107));
                            return B + "_" + S + "_" + N + "_1";
                        }
                        else if(bt->cost == 3)
                        {
                            ret_string = B + "_" + S + "_" + N + "_1";
                            cout << ret_string << endl;
                            ans = its;
                            anv = bt;
                            ani = index;
                        }
                        N[0]++;
                    }
                }
                S[0]++;
            }
            B[0]++;
        }
        if (ans != NULL)
        {
            ans->current_space++;
            anv->number_plate = Number;
            anv->weight = weight;
            anv->ROV = s;
            anv->entry_time = entry;
            anv->time = time;
            anv->length = dim[0];
            anv->width = dim[1];
            anv->height = dim[2];
            anv->cost = INT_MAX;
            anv->car.setFillColor(Color(0, 36, 107));
            return ret_string;
        }
        else if (ans == NULL)
        {
            string B = "A";
            for (auto it : cityCenter->bk)
            {
                string S = "1";
                for (auto its : it->vec)
                {
                    string N = "1";
                    if (its->working && its->lower_cnt < its->space_capacity)
                    {
                        for (auto bt : its->lower_stack)
                        {
                            if (bt->cost == 0)
                            {
                                its->lower_cnt++;
                                bt->cost = INT_MAX;
                                bt->number_plate = Number;
                                bt->weight = weight;
                                bt->ROV = s;
                                bt->entry_time = entry;
                                bt->time = time;
                                bt->length = dim[0];
                                bt->width = dim[1];
                                bt->height = dim[2];
                                bt->car.setFillColor(Color(202, 220, 252));
                                return B + "_" + S + "_" + N + "_0";
                            }
                            N[0]++;
                        }
                    }
                    S[0]++;
                }
                B[0]++;
            }
            cout << "1 Parking is full" << endl;
            return "";
        }
       
    }
    else if (weight>2000)
    {
        _Stack* ans=NULL;
        string ret_string;
        vehicle* anv=NULL;
        int ani;
        string B = "A";
        for (auto it : cityCenter->bk)
        {
            string S = "1";
            for (auto its : it->vec)
            {
                string N = "1";
                if (its->working && its->lower_cnt < its->space_capacity)
                {
                    int index = -1;
                    for (auto bt : its->lower_stack)
                    {
                        index++;
                        if (bt->cost == 0)
                        {
                            its->lower_cnt++;
                            bt->cost = INT_MAX;
                            bt->number_plate = Number;
                            bt->weight = weight;
                            bt->ROV = s;
                            bt->entry_time = entry;
                            bt->time = time;
                            bt->length = dim[0];
                            bt->width = dim[1];
                            bt->height = dim[2];
                            bt->car.setFillColor(Color(202, 220, 252));
                            return B + "_" + S + "_" + N + "_0";
                        }
                        else if (bt->cost == 1)
                        {
                            ret_string = B + "_" + S + "_" + N + "_0";
                            ans = its;
                            anv = bt;
                            ani = index;
                        }
                        N[0]++;
                    }
                }
                S[0]++;
            }
            B[0]++;
        }
        if (ans != NULL)
        {
            ans->upper_stack[ani]->cost = 3;
            ans->lower_cnt++;
            anv->number_plate = Number;
            anv->weight = weight;
            anv->ROV = s;
            anv->entry_time = entry;
            anv->time = time;
            anv->length = dim[0];
            anv->width = dim[1];
            anv->height = dim[2];
            anv->cost = INT_MAX;
            anv->car.setFillColor(Color(202, 220, 252));
            return ret_string;
        }
        if (ans == NULL)
        {
            cout << "Parking is full" << endl;
            return "";
        }
    }
}

bool change_working(parking* cityCenter, string s)
{
    if (!check(s))
        return false;
    if(s[6]=='0')
    {
        cityCenter->bk[s[0] - 'A']->vec[s[2] - '1']->lower_stack[s[4] - '1']->cost = INT_MAX;
        cityCenter->bk[s[0] - 'A']->vec[s[2] - '1']->lower_stack[s[4] - '1']->car.setFillColor(Color::Red);
    }
    else
    {
        cityCenter->bk[s[0] - 'A']->vec[s[2] - '1']->upper_stack[s[4] - '1']->car.setFillColor(Color::Red);
        cityCenter->bk[s[0] - 'A']->vec[s[2] - '1']->upper_stack[s[4] - '1']->cost = INT_MAX;
    }
    return true;
}

void readInput(parking* cityCenter)
{
    ofstream f;
    f.open("exitfile.csv");
    if (!f.is_open())
    {
        cout << "Not opened exit file";
        return;
    }
    ifstream inputfile;
    inputfile.open("entries.csv");
    if (!inputfile.is_open())
    {
        cout << "Not opened input file";
        return;
    }
    string s, reg, reason, entrytime;
    int weight=2000, time=0;
    while (getline(inputfile, s))
    {
        stringstream ss(s);
        string cell;
        int cnt = 0;
        while (getline(ss, cell, ','))
        {
            cnt++;
            if (cnt == 1)
            {
                reg = cell;
            }
            if (cnt == 2)
            {
                time = stoi(cell);
            }
            if (cnt == 3)
            {
                weight = stoi(cell);
            }
            if (cnt == 4)
            {
                reason = cell;
            }
            if (cnt == 5)
            {
                entrytime = cell;
            }
        }
        cout << add_vehicle(cityCenter, reg, weight, time, { 0,0,0 }, entrytime, reason) << "\n";
        Sleep(1000);
    }
}

void remove(string r,parking* cityCenter)
{
    fstream exitfile;
    exitfile.open("Exit.csv",ios_base::app);
    string reg, etime;
    if (!check(r))
        return;
    int B_index = r[0] - 'A';
    int S_index = r[2] - '1';
    int V_index = r[4] - '1';
    if (r[6] == '0')
    {
        if (cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->cost == 3)
        {
            cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->cost = 2;
            cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost = 1;
        }
        else if (cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost == INT_MAX)
        {
            cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost = 0;
        }
        else
        {
            cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost = 1;
        }
        cityCenter->bk[B_index]->vec[S_index]->lower_cnt--;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->entry_time = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->length = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->height = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->width = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->weight = 0;
        reg = cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->number_plate;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->number_plate = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->ROV = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->time = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->car.setFillColor(Color(101, 110, 126));
    }
    else if (r[6] == '1')
    {
        if (cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost == 0)
        {
            cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->cost = 1;
            cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->cost = 2;
        }
        else {
            cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->cost = 3;
        }
        cityCenter->bk[B_index]->vec[S_index]->current_space--;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->entry_time = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->length = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->height = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->width = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->weight = 0;
        reg = cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->number_plate;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->number_plate = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->ROV = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->time = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->car.setFillColor(Color(0, 18, 56));

    }
    else
        return;

    time_t now  = time(nullptr);
    if (!reg.empty())
    {
        exitfile << reg << "," << now << "\n";
    }
}

int Initialize()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data);
}

void Entry(parking* cityCenter)
{
    while(1)
    {
        fstream entryfile;
        entryfile.open("records.csv", ios_base::app);
        if (!entryfile.is_open())
        {
            cout << "File failed to open";
            return;
        }


        RenderWindow window(VideoMode(1920, 1060), "ENTRY");
        window.setFramerateLimit(60);

        Font font;
        font.loadFromFile("InputFont2.ttf");

        Font Cursive;
        Cursive.loadFromFile("font1.ttf");

        Text heading;
        heading.setString("CityCenter");
        heading.setPosition(Vector2f(700.f, 20.f));
        heading.setFillColor(Color::Black);
        heading.setCharacterSize(200);
        heading.setFont(Cursive);

        Text desc;
        desc.setString("Enter Registration Number");
        desc.setPosition(Vector2f(750.f, 500.f));
        desc.setFillColor(Color::Black);
        desc.setCharacterSize(50);
        desc.setFont(font);

        RectangleShape in(Vector2f(350.f, 70.f));
        in.setPosition(Vector2f(750.f,600.f));
        in.setFillColor(Color::White);
        
        Text input;
        input.setFont(font);
        input.setPosition(750.f, 600.f);
        input.setFillColor(Color::Black);
        input.setCharacterSize(50);

        RectangleShape Button(Vector2f(140.f, 70.f));
        Button.setPosition(Vector2f(855.f, 700.f));
        Button.setFillColor(Color::Blue);

        RectangleShape Redbox(Vector2f(50.f, 50.f));
        Redbox.setPosition(Vector2f(1850.f, 20.f));
        Redbox.setFillColor(Color::Red);

        Text issue;
        issue.setFont(font);
        issue.setString("Issue?");
        issue.setPosition(Vector2f(1700.f, 15.f));
        issue.setFillColor(Color::Black);
        issue.setCharacterSize(50);

        Text submit;
        submit.setFont(font);
        submit.setString("NEXT");
        submit.setPosition(Vector2f(855, 700));
        submit.setFillColor(Color::White);
        submit.setCharacterSize(50);

        String inputstring;

        string s, Number, entry;
        int t, w;

        string m;
        int cnt = 0;
        int ind = 0;
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::TextEntered)
                {
                    inputstring += event.text.unicode;
                    input.setString(inputstring);
                }
                if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x<995 && Mouse::getPosition(window).y<770 && Mouse::getPosition(window).x > 885 && Mouse::getPosition(window).y > 700)
                {
                    if (ind == 1)
                    {
                        m = string(inputstring);
                        change_working(cityCenter, m);
                        window.close();
                    }
                    m = string(inputstring);
                    if (cnt == 0)
                    {
                        Number = m;
                        desc.setString("Enter Time");
                        cnt++;
                    }
                    else if (cnt == 1)
                    {
                        t = stoi(m);
                        desc.setString("Enter Weight");
                        cnt++;
                    }
                    else if (cnt == 2)
                    {
                        w = stoi(m);
                        desc.setString("Enter Reason of Visit");
                        cnt++;
                    }
                    else if (cnt == 3)
                    {
                        s = m;
                        desc.setString("Enter Time of Entry");
                        submit.setString("SUBMIT");
                        cnt++;
                    }
                    else if (cnt == 4)
                    {
                        entry = m;
                        entryfile << Number << "," << w << "," << t << "," << entry << "," << s << "\n";
                        cout << add_vehicle(cityCenter, Number, w, t, { 0,0,0 }, entry, s) << endl;
                        cnt = 0;
                        window.close();
                    }
                    inputstring.clear();
                    input.setString(inputstring);
                }
                if (event.type == Event::MouseButtonPressed && Mouse::getPosition(window).x < 1900 && Mouse::getPosition(window).y < 70 && Mouse::getPosition(window).x > 1850 && Mouse::getPosition(window).y > 20)
                {
                    ind = 1;
                    desc.setString("Enter Stack Number");
                }

            }
            window.clear(Color(106, 137, 167));
            window.draw(Redbox);
            window.draw(heading);
            window.draw(in);
            window.draw(input);
            window.draw(desc);
            window.draw(Button);
            window.draw(submit);
            window.draw(issue);
            window.display();
        }
        entryfile.close();
    }
}

void Interact(SOCKET C, parking* cityCenter,int &n)
{
    char buffer[4096];
    while (1)
    {
        int data_size = recv(C, buffer, sizeof(buffer), 0);
        if (data_size <= 0)
            break;
        string message(buffer, data_size);
        n = 1;
        cout << "Message from client: " << message << endl;
        remove(message, cityCenter);
    }
    cout << "Connection problem close and reconnect";
    closesocket(C);
}

void simulate(parking* cityCenter)
{
    //Listen to the client 


    if (Initialize() != 0)
    {
        cout << "startup failed" << endl;
        return ;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        cout << "failed to create socket" << endl;
        return ;
    }
    else
        cout << "created socket successfully" << endl;
    int port = 5000;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "Binding error" << endl;
        return ;
    }

    if (listen(serverSocket, 10) == SOCKET_ERROR)
    {
        cout << "Cannot listen" << endl;
        return ;
    }
    else
    {
        cout << "listening on port " << port << endl;
    }

    SOCKET clientsocket = accept(serverSocket, nullptr, nullptr);

    if (clientsocket == INVALID_SOCKET)
    {
        cout << "couldnt accept" << endl;
    }
    else
        cout << "accepted client" << endl;

    char buffer[4096];
    int indicator=0;
    thread t(Interact, clientsocket, cityCenter,ref(indicator));
    t.detach();
    //thread E(readInput, cityCenter);
    //E.detach();
    thread E(Entry, cityCenter);
    E.detach();



    RenderWindow window(VideoMode(1920, 1060), "City_Center");
    window.setFramerateLimit(60);

    Font font;
    font.loadFromFile("InputFont2.ttf");

    Font Cursive;
    Cursive.loadFromFile("font1.ttf");

    Text heading;
    heading.setString("CityCenter");
    heading.setPosition(Vector2f(850.f, 20.f));
    heading.setFillColor(Color::Black);
    heading.setCharacterSize(70);
    heading.setFont(Cursive);

    Text E_Point;
    E_Point.setFillColor(Color::White);
    E_Point.setString(" Entry ");
    E_Point.setCharacterSize(45);
    E_Point.setPosition(Vector2f(930.f, 805.f));
    E_Point.setFont(font);
    
    Text Exit_Point;
    Exit_Point.setFillColor(Color::White);
    Exit_Point.setString(" Exit ");
    Exit_Point.setCharacterSize(45);
    Exit_Point.setPosition(Vector2f(940.f, 210.f));
    Exit_Point.setFont(font);

    Text Block_Name_A;
    Block_Name_A.setFillColor(Color::White);
    Block_Name_A.setString(" A ");
    Block_Name_A.setCharacterSize(45);
    Block_Name_A.setPosition(Vector2f(90.f, 600.f));
    Block_Name_A.setFont(font);

    Text Block_Name_B;
    Block_Name_B.setFillColor(Color::White);
    Block_Name_B.setString(" D ");
    Block_Name_B.setCharacterSize(45);
    Block_Name_B.setPosition(Vector2f(90.f, 420.f));
    Block_Name_B.setFont(font);

    Text Block_Name_C;
    Block_Name_C.setFillColor(Color::White);
    Block_Name_C.setString(" C ");
    Block_Name_C.setCharacterSize(45);
    Block_Name_C.setPosition(Vector2f(1780.f, 420.f));
    Block_Name_C.setFont(font);

    Text Block_Name_D;
    Block_Name_D.setFillColor(Color::White);
    Block_Name_D.setString(" B ");
    Block_Name_D.setCharacterSize(45);
    Block_Name_D.setPosition(Vector2f(1780.f, 600.f));
    Block_Name_D.setFont(font);

    Text Block_Name_E;
    Block_Name_E.setFillColor(Color::White);
    Block_Name_E.setString(" E ");
    Block_Name_E.setCharacterSize(45);
    Block_Name_E.setPosition(Vector2f(825.f, 270.f));
    Block_Name_E.setFont(font);

    Text Block_Name_F;
    Block_Name_F.setFillColor(Color::White);
    Block_Name_F.setString(" F ");
    Block_Name_F.setCharacterSize(45);
    Block_Name_F.setPosition(Vector2f(1220.f, 270.f));
    Block_Name_F.setFont(font);

    Text Block_Name_G;
    Block_Name_G.setFillColor(Color::White);
    Block_Name_G.setString(" G ");
    Block_Name_G.setCharacterSize(45);
    Block_Name_G.setPosition(Vector2f(825.f, 740.f));
    Block_Name_G.setFont(font);

    Text Block_Name_H;
    Block_Name_H.setFillColor(Color::White);
    Block_Name_H.setString(" H ");
    Block_Name_H.setCharacterSize(45);
    Block_Name_H.setPosition(Vector2f(1220.f, 740.f));
    Block_Name_H.setFont(font);

    Text lift;
    lift.setFillColor(Color::White);
    lift.setString("Lift");
    lift.setCharacterSize(40);
    lift.setPosition(Vector2f(855.f,175.f));
    lift.setFont(font);

    RectangleShape W_lift1(Vector2f(80.f,80.f));
    W_lift1.setFillColor(Color(120,120,120));
    W_lift1.setPosition(Vector2f(840.f,195.f));

    RectangleShape W_lift2(Vector2f(80.f, 80.f));
    W_lift2.setFillColor(Color(120, 120, 120));
    W_lift2.setPosition(Vector2f(840.f, 800.f));

    RectangleShape V_lift1(Vector2f(220.f, 80.f));
    V_lift1.setFillColor(Color(120, 120, 120));
    V_lift1.setPosition(Vector2f(1030.f, 195.f));

    RectangleShape V_lift2(Vector2f(220.f, 80.f));
    V_lift2.setFillColor(Color(120, 120, 120));
    V_lift2.setPosition(Vector2f(1030.f, 800.f));

    RectangleShape lift1(Vector2f(50.f, 50.f));
    lift1.setFillColor(Color::Black);
    lift1.setPosition(Vector2f(855.f, 210.f));

    RectangleShape display(Vector2f(30.f, 30.f));
    display.setFillColor(Color(202, 220, 252));
    display.setPosition(Vector2f(20.f,20.f));

    Text dis;
    dis.setFillColor(Color::Black);
    dis.setString(" Upper Stack when Vehicle is not present ");
    dis.setCharacterSize(30);
    dis.setPosition(Vector2f(60.f, 30.f));
    dis.setFont(font);


    RectangleShape bck(Vector2f(1650.f, 300.f));
    bck.setFillColor(Color(102, 165, 173));
    bck.setOrigin(Vector2f(825.f, 150.f));
    bck.setPosition(Vector2f(960.f, 537.f));
    RectangleShape temp(Vector2f(35.f, 70.f));
    temp.setPosition(Vector2f(155.f, 565.f));
    for (auto it : cityCenter->A->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x,temp.getPosition().y+35));
            temp.move(Vector2f(39.f, 0.f));
            //it->lower_stack[i]->car.setFillColor(Color(202, 220, 252));
            //it->upper_stack[i]->car.setFillColor(Color(0, 36, 107));
        }
        temp.move(Vector2f(4.f, 0.f));
    }
    temp.move(Vector2f(20,0));
    for (auto it : cityCenter->B->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y + 35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(4.f, 0.f));
    }
    temp.setPosition(Vector2f(155.f, 445.f));
    for (auto it : cityCenter->D->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y-35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.move(Vector2f(20, 0));
    for (auto it : cityCenter->C->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y-35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.setPosition(Vector2f(30.f,200.f));
    for (auto it : cityCenter->E->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y+35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.setPosition(Vector2f(1270.f, 200.f));
    for (auto it : cityCenter->F->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y+35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.setPosition(Vector2f(30.f,800.f));
    for (auto it : cityCenter->G->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y - 35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.setPosition(Vector2f(1270.f, 800.f));
    for (auto it : cityCenter->H->vec)
    {
        for (int i = 0; i < 5; i++)
        {
            it->upper_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y));
            it->lower_stack[i]->car.setPosition(Vector2f(temp.getPosition().x, temp.getPosition().y - 35));
            temp.move(Vector2f(39.f, 0.f));
        }
        temp.move(Vector2f(5.f, 0.f));
    }
    temp.setSize(Vector2f(1870.f, 710.f));
    temp.setPosition(15.f, 180.f);
    temp.setFillColor(Color(102, 165, 173));
    RectangleShape A_Block(Vector2f(805.f, 120));
    A_Block.setFillColor(Color(249,97,103));
    A_Block.setPosition(Vector2f(145.f, 557.f));
    RectangleShape Road(Vector2f(1830.f, 430.f));
    Road.setFillColor(Color(20,20,20));
    Road.setOrigin(Vector2f(915.f, 215.f));
    Road.setPosition(Vector2f(950.f, 535.f));

    RectangleShape entry(Vector2f(90.f, 150));
    entry.setFillColor(Color(20, 20, 20));
    entry.setOrigin(45.f,0.f);
    entry.setPosition(Vector2f(980.f, 180.f));

    RectangleShape l(Vector2f(50.f, 4.f));
    l.setPosition(Vector2f(675.f, 720.f));
    l.setFillColor(Color::White);

    RectangleShape ar(Vector2f(12.f, 4.f));
    ar.setPosition(Vector2f(675.f, 720.f));
    ar.setFillColor(Color::White);
    ar.rotate(45);

    RectangleShape l1(Vector2f(50.f, 4.f));
    l1.setPosition(Vector2f(675.f, 360.f));
    l1.setFillColor(Color::White);

    RectangleShape ar1(Vector2f(12.f, 4.f));
    ar1.setOrigin(12, 0);
    ar1.setPosition(Vector2f(725.f, 360.f));
    ar1.setFillColor(Color::White);
    ar1.rotate(45);

    int cnt = 0;
    int ecnt = 0;
    int framecnt = 0;
    int pic_cnt = 0;
    string picname = "output";

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear(Color(106, 137, 167));
        window.draw(heading);
        window.draw(temp);
        window.draw(entry);
        entry.setPosition(Vector2f(980.f, 740.f));
        window.draw(entry);
        entry.setPosition(Vector2f(980.f, 180.f));
        window.draw(Road);
        window.draw(l);
        ar.setSize(Vector2f(12.f,4.f));
        ar.rotate(-90);
        window.draw(ar);
        ar.rotate(90);
        ar.setSize(Vector2f(14.f, 4.f));
        window.draw(ar);


        l.move(610, 0);
        window.draw(l);
        l.move(-610, 0);
        ar.setSize(Vector2f(12.f, 4.f));
        ar.rotate(-90);
        ar.move(610, 0);
        window.draw(ar);
        ar.move(-610, 0);
        ar.rotate(90);
        ar.setSize(Vector2f(14.f, 4.f));
        ar.move(610, 0);
        window.draw(ar);
        ar.move(-610, 0);

        window.draw(l1);
        window.draw(ar1);
        ar1.rotate(-90);
        ar1.setSize(Vector2f(14.f, 4.f));
        ar1.setOrigin(14, 0);
        window.draw(ar1);
        ar1.rotate(90);
        ar1.setSize(Vector2f(12.f, 4.f));

        l1.move(610, 0);
        ar1.move(610, 0);
        window.draw(l1);
        window.draw(ar1);
        ar1.rotate(-90);
        ar1.setSize(Vector2f(14.f, 4.f));
        ar1.setOrigin(14, 0);
        window.draw(ar1);
        ar1.rotate(90);
        ar1.setSize(Vector2f(12.f, 4.f));
        l1.move(-610, 0);
        ar1.move(-610, 0);



        window.draw(bck);
        A_Block.setFillColor(Color(235,125,36));
        A_Block.setPosition(Vector2f(145.f, 557.f));
        window.draw(A_Block);
        A_Block.move(820.f, 0.f);
        A_Block.setFillColor(Color(235, 125, 36));
        window.draw(A_Block);
        A_Block.move(0.f, -155.f);
        A_Block.setFillColor(Color(235, 125, 36));
        window.draw(A_Block);
        A_Block.move(-820.f, 0.f);
        A_Block.setFillColor(Color(235, 125, 36));
        window.draw(A_Block);
        A_Block.setPosition(Vector2f(25.f, 195.f));
        A_Block.setFillColor(Color(235, 125, 36));
        window.draw(A_Block);
        A_Block.setPosition(Vector2f(25.f, 757.f));
        A_Block.setFillColor(Color(235, 125, 36));
        window.draw(A_Block);
        RectangleShape G_Block(Vector2f(605.f, 120.f));
        G_Block.setPosition(Vector2f(1263.f, 757.f));
        G_Block.setFillColor(Color(235, 125, 36));
        window.draw(G_Block);
        G_Block.setPosition(Vector2f(1263.f, 195.f));
        G_Block.setFillColor(Color(235, 125, 36));
        window.draw(G_Block);

        window.draw(W_lift1);
        window.draw(W_lift2);
        window.draw(V_lift1);
        window.draw(V_lift2);
        lift1.setPosition(Vector2f(855.f, 210.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(855.f, 815.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1045.f, 210.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1115.f, 210.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1185.f, 210.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1045.f, 815.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1115.f, 815.f));
        window.draw(lift1);
        lift1.setPosition(Vector2f(1185.f, 815.f));
        window.draw(lift1);

        lift.setPosition(Vector2f(855.f, 175.f));
        window.draw(lift);
        lift.setPosition(Vector2f(1115.f, 175.f));
        window.draw(lift);
        lift.setPosition(Vector2f(855.f, 845.f));
        window.draw(lift);
        lift.setPosition(Vector2f(1115.f, 845.f));
        window.draw(lift);

        display.setFillColor(Color(0, 36, 107));
        display.setPosition(Vector2f(1600.f, 95.f));
        window.draw(display);
        display.setPosition(Vector2f(1600.f, 135.f));
        display.setFillColor(Color(0,18,53));
        window.draw(display);
        display.setPosition(Vector2f(20.f, 95.f));
        display.setFillColor(Color(101, 110, 126));
        window.draw(display);
        display.setFillColor(Color(202, 220, 252));
        display.setPosition(Vector2f(20.f, 135.f));
        window.draw(display);

        dis.setString(" Upper Stack Available ");
        dis.setCharacterSize(30);
        dis.setPosition(Vector2f(1640.f, 90.f));
        dis.setFont(font);
        window.draw(dis);
        dis.setString(" Upper Stack Occupied ");
        dis.setPosition(Vector2f(1640.f, 130.f));
        window.draw(dis);
        dis.setString(" Lower Stack Available ");
        dis.setPosition(Vector2f(60.f, 90.f));
        window.draw(dis);
        dis.setString(" Lower Stack Occupied ");
        dis.setPosition(Vector2f(60.f, 130.f));
        window.draw(dis);


        window.draw(E_Point);
        window.draw(Exit_Point);
        window.draw(Block_Name_A);
        window.draw(Block_Name_B);
        window.draw(Block_Name_C);
        window.draw(Block_Name_D);
        window.draw(Block_Name_E);
        window.draw(Block_Name_F);
        window.draw(Block_Name_G);
        window.draw(Block_Name_H);
        cnt++;
        ecnt++;
        /*if (cnt > 60)
        {
            window.draw(cityCenter->Entry_indicator);
            if (ecnt > 3600)
            {
                window.draw(cityCenter->Exit_indicator);
            }
        }
        if (cnt == 120)
        {
            cnt = 0;
        }
        */
        for (auto it : cityCenter->bk)
        {
            for (auto its : it->vec)
            {
                for (int i = 0; i < 5; i++)
                {
                    window.draw(its->lower_stack[i]->car);
                    window.draw(its->upper_stack[i]->car);
                }
            }
        }
        
        framecnt++;
        if (framecnt == 300)
        {
            framecnt = 0;
            pic_cnt++;
            Texture texture;
            texture.create(1920, 1060);
            texture.update(window);
            Image img = texture.copyToImage();
            img.saveToFile("output/CityCenter.png");
        }
        window.display();
    }
}

int main()
{
    parking* cityCenter = new parking();
    simulate(cityCenter);
}

