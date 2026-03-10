#include <iostream>
#include <string>
using namespace std;

class carro
{
    private:
	int velocidade = 20;

	public:
    	void acelerar()
        {
            int a;
            cout << "A velocidade atual é:" << velocidade;
        	cout << "\n\nInforme quanto deseja acelerar:";
            cin >> a;
            a += velocidade;
            cout << "\nA nova velocidade é:" << a;
        }
};

int main()
{
	carro motor;
    
	motor.acelerar();
	return 0;
}