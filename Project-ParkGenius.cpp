// Project-ParkGenius.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include <iostream>
#include <fstream>

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
    vehicle(int p,string np = "", string ET="", String R = "", int t = 0, float w=0.0, vector<float> dim={})
    {
        weight = w;
        number_plate = np;
        entry_time = ET;
        ROV = R;
        time = t;
        length = 0;
        width = 0;
        height = 0;
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
    float current_weight;
    int space_capacity;
    int current_space;
    bool working;
    vector<vehicle*> upper_stack;
    vector<vehicle*> lower_stack;
    int cost;  
    int lower_cnt;
    _Stack(float w = 500.0,float cw=0.0,int s = 5,int cs=0,bool wor=true)
    {
        weight_capacity = w;
        current_weight = cw;
        space_capacity = s;
        current_space = cs;
        working = wor;
        cost = 0;
        lower_cnt = 0;
        for (int i = 0; i < 5; i++)
        {
            vehicle* tmp = new vehicle(0, "", "", "", 0, 0.0, {});
            vehicle* tomp = new vehicle(1, "", "", "", 0, 0.0, {});
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
            _Stack* temp = new _Stack(500.0,0.0,5,0,true);
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
    Block* I;
    vector<Block*> bk;
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
        I = new Block(2);
        bk.push_back(I);
    }
};


string add_vehicle(parking* cityCenter,string Number, int weight, int time, vector<int> dim, string entry, string s)
{
    if (weight < 100)
    {
        string B = "A";
        for (auto it : cityCenter->bk)
        {
            string S = "1";
            for(auto its:it->vec)
            {
                string N = "1";

                if (its->working && its->current_space < its->space_capacity && (its->weight_capacity - its->current_weight) >= weight)
                {
                    for (auto bt : its->upper_stack)
                    {
                        if (bt->weight == 0)
                        {
                            its->current_space++;
                            its->current_weight = its->current_weight + weight;
                            bt->number_plate = Number;
                            bt->weight = weight;
                            bt->ROV = s;
                            bt->entry_time = entry;
                            bt->time = time;
                            bt->length = dim[0];
                            bt->width = dim[1];
                            bt->height = dim[2];
                            bt->car.setFillColor(Color(0, 36, 107));
                            return B + "_" + S + "_" + N + "_1";
                        }
                        N[0]++;
                    }
                }
                S[0]++;
            }
            B[0]++;
        }
        B = "A";
        for (auto it : cityCenter->bk)
        {
            string S = "1";
            for (auto its : it->vec)
            {
                string N = "1";
                if(its->working && its->lower_cnt < its->space_capacity)
                {
                    for (auto bt : its->lower_stack)
                    {
                        if (bt->weight == 0)
                        {
                            its->lower_cnt++;
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
    }



    else
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
                        if (bt->weight == 0)
                        {
                            its->lower_cnt++;
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
        B = "A";
        for (auto it : cityCenter->bk)
        {
            string S = "1";
            for (auto its : it->vec)
            {
                string N = "1";
                if (its->working && its->current_space < its->space_capacity && (its->weight_capacity - its->current_weight) >= weight)
                {
                    for (auto bt : its->upper_stack)
                    {
                        if (bt->weight == 0)
                        {
                            its->current_space++;
                            its->current_weight = its->current_weight + weight;
                            bt->number_plate = Number;
                            bt->weight = weight;
                            bt->ROV = s;
                            bt->entry_time = entry;
                            bt->time = time;
                            bt->length = dim[0];
                            bt->width = dim[1];
                            bt->height = dim[2];
                            bt->car.setFillColor(Color(0, 36, 107));
                            return B + "_" + S + "_" + N + "_1";
                        }
                        N[0]++;
                    }
                }
                S[0]++;
            }
            B[0]++;
        }
    }
}

void remove(string r,parking* cityCenter)
{
    int B_index = r[0] - 'A';
    int S_index = r[2] - '1';
    int V_index = r[4] - '1';
    if(r[6]=='0')
    {
        cityCenter->bk[B_index]->vec[S_index]->lower_cnt--;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->entry_time = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->length = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->height = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->width = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->weight = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->number_plate = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->ROV = "";
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->time = 0;
        cityCenter->bk[B_index]->vec[S_index]->lower_stack[V_index]->car.setFillColor(Color(101, 110, 126));
    }
    else
    {
        cityCenter->bk[B_index]->vec[S_index]->current_space--;
        cityCenter->bk[B_index]->vec[S_index]->current_weight = cityCenter->bk[B_index]->vec[S_index]->current_weight - cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->weight;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->entry_time = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->length = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->height = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->width = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->weight = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->number_plate = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->ROV = "";
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->time = 0;
        cityCenter->bk[B_index]->vec[S_index]->upper_stack[V_index]->car.setFillColor(Color(0, 18, 56));

    }
}

void simulate(parking* &cityCenter)
{
    RenderWindow window(VideoMode(1920, 1060), "City_Center");
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
    //A_Block.setFillColor(Color(249,97,103));
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
        window.clear(Color::White);
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
        A_Block.setFillColor(Color(249,97,103));
        A_Block.setPosition(Vector2f(145.f, 557.f));
        window.draw(A_Block);
        A_Block.move(820.f, 0.f);
        A_Block.setFillColor(Color(234,115,141));
        window.draw(A_Block);
        A_Block.move(0.f, -155.f);
        A_Block.setFillColor(Color(249,136,102));
        window.draw(A_Block);
        A_Block.move(-820.f, 0.f);
        A_Block.setFillColor(Color(88,24,69));
        window.draw(A_Block);
        A_Block.setPosition(Vector2f(25.f, 195.f));
        A_Block.setFillColor(Color::Yellow);
        window.draw(A_Block);
        A_Block.setPosition(Vector2f(25.f, 757.f));
        A_Block.setFillColor(Color::Yellow);
        window.draw(A_Block);
        RectangleShape G_Block(Vector2f(605.f, 120.f));
        G_Block.setPosition(Vector2f(1263.f, 757.f));
        G_Block.setFillColor(Color(184, 80, 66));
        window.draw(G_Block);
        G_Block.setPosition(Vector2f(1263.f, 195.f));
        G_Block.setFillColor(Color::Yellow);
        window.draw(G_Block);
        
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
        window.display();
        cout << "Add a Vehicle: Enter 0" << endl;
        cout << "Remove a Vehicle: Enter 2" << endl;
        int ind;
        cin >> ind;
        if (ind == 0)
        {
            cout << "Enter Registration Number: ";
            string Number;
            cin >> Number;
            cout << "Enter time: ";
            int t;
            cin >> t;
            cout << "Enter Weight: ";
            int w;
            cin >> w;
            cout << "Reason of Visit: ";
            string s;
            cin >> s;
            cout << "Entry time: ";
            string entry;
            cin >> entry;
            cout << "Enter Dimention: ";
            int l=0, b=0, h=0;
            cin >> l;
            cin >> b;
            cin >> h;
            cout << add_vehicle(cityCenter,Number, w,t, { l,b,h }, entry, s);
        }
        if (ind == 2)
        {
            string v;
            cin >> v;
            remove(v, cityCenter);
        }
    }
}

int main()
{
    parking* cityCenter = new parking();
    simulate(cityCenter);

}

