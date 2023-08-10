//
// Created by merom on 7/7/2023.
//
#include "Viewer.h"
#include "../Model/Model.h"

Viewer::Viewer():zoom{DEFAULT_ZOOM}, origin{START_COORDINATES, START_COORDINATES}, displaySize{DEFAULT_DISPLAY_SIZE}{}


int GetNumOfDigits(const int &x) {
    return (int) to_string(x).size();
}

void Viewer::setDefault()
{
    zoom = DEFAULT_ZOOM;
    displaySize = DEFAULT_DISPLAY_SIZE;
    origin.x = START_COORDINATES;
    origin.y = START_COORDINATES;
}

void Viewer::setSize(int newSize)
{
    displaySize = newSize;
}

void Viewer::setZoom(float newZoom)
{
    zoom = newZoom;
}

void Viewer::pan(float x, float y)
{
    origin.x = x;
    origin.y = y;
}

shared_ptr<SimObject> Viewer::getObjByPoint(const Point &pnt) {
    for(const auto & farm : Model::getInstance().getFarms())
        if(farm->getLocation() == pnt) return farm;

    for(const auto & castle : Model::getInstance().getCastles())
        if(castle->getLocation() == pnt) return castle;

    float epsilon = 0.5;

    for(const auto & knight : Model::getInstance().getKnights())
        if(std::abs(knight->getLocation().x-pnt.x) <= epsilon&&
           std::abs(knight->getLocation().y-pnt.y) <= epsilon)
            return knight;

    for(const auto & thug : Model::getInstance().getThugs())
        if(std::abs(thug->getLocation().x-pnt.x) <= epsilon&&
           std::abs(thug->getLocation().y-pnt.y) <= epsilon)
            return thug;

    for(const auto & peasant : Model::getInstance().getPeasants())
        if(std::abs(peasant->getLocation().x-pnt.x) <= epsilon&&
           std::abs(peasant->getLocation().y-pnt.y) <= epsilon)
            return peasant;

    return nullptr;
}

string genNumStr(std::size_t length,int number)
{
    string ret;
    for(int i=0;i<length;i++)
        ret+=" ";
    string num = to_string(number);
    auto it_ret = ret.rbegin();
    for(auto it = num.rbegin();it != num.rend();it++)
    {
        *it_ret=*it;
        it_ret++;
    }
    return ret+" ";
}

void PrintCxTimes(const char &c, const int &times) {
    for (int i = 0; i < times; ++i) {
        cout << c;
    }
}

void Viewer::show() {
    cout << "Display size: " << displaySize << ", scale: " <<zoom<< ", origin: " << origin << endl;
    vector<string> map(displaySize);
    int yScale = int(origin.y + float(displaySize) * zoom - zoom);
    for(int i=0;i<displaySize;i++)
    {
        string newRow;
        for(int j=0;j<displaySize;j++)
        {
            bool flag=false;
            for(int k=0;k<(int)zoom;k++)
            {
                for(int m=0;m<(int)zoom;m++)
                {
                    Point location(origin.x+float(float(j)*zoom+float(k) ),yScale-m);
                    shared_ptr<SimObject> obj = getObjByPoint(location);
                    if(obj != nullptr)
                    {
                        newRow+=obj->getName().substr(0, 2);
                        flag=true;
                        break;
                    }
                }


            }
            if(!flag)
                newRow+=". ";
        }
        map[i]=std::move(newRow);
        yScale-=(int)zoom;
    }

    yScale=int(origin.y + float(displaySize) * zoom - zoom);
    std::size_t max_length = 0;
    while(yScale >= int(origin.y))
    {
        string tmp = to_string(yScale);
        if(max_length < tmp.size()) max_length = tmp.size();
        yScale-=(int)zoom;
    }
    yScale=int(origin.y + float(displaySize) * zoom - zoom);
    int mod=0;
    for(auto & row : map)
    {
        if(mod%3==0)
        {
            row=genNumStr(max_length,yScale)+row;
            cout<<row<<endl;
        }
        else{
            std::size_t i=0;
            while(i<max_length) {
                cout<<" ";
                i++;
            }
            cout<<" "<<row<<endl;
        }
        mod++;
        yScale-=int(zoom);
    }
    int digits = max(GetNumOfDigits(yScale), (int) to_string((int) origin.y).size());;
    int x = (int) origin.x;
    const int space = 6;

    PrintCxTimes(' ', (digits + 2) - GetNumOfDigits(x));
    cout << x;
    for (int i = 1; i < displaySize; i += 3) {
        x += (int) zoom * 3;
        int len = GetNumOfDigits(x);
        PrintCxTimes(' ', space - len);
        cout << x;
    }
    cout << endl;
}