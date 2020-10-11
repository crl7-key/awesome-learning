#include <iostream>

using namespace std;

class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        // 初始化
        this->m_big = big;
        this->m_medium = medium;
        this->m_small = small;
    }
    // 检查是否有想要进入停车场的汽车的carType停车位
    bool addCar(int carType) {
        if (carType == 1 && m_big > 0) {
            m_big--;
            return true;
        }
        else if (carType == 2 && m_medium > 0) {
            m_medium --;
            return true;
        }
        else if (carType == 3 && m_small > 0) {
            m_small --;
            return true;
        }
        else 
            return false;
        
    }
    
private:
    int m_big;
    int m_medium;
    int m_small;
};

/**
 * Your ParkingSystem object will be instantiated and called as such:
 * ParkingSystem* obj = new ParkingSystem(big, medium, small);
 * bool param_1 = obj->addCar(carType);
 */

int main(int argc, char const *argv[])
{
    ParkingSystem *parkingSystem = new ParkingSystem(1, 1, 0);

    cout << parkingSystem->addCar(1) << endl;

    cout << parkingSystem->addCar(2) << endl;

    cout << parkingSystem->addCar(3) << endl;

    cout << parkingSystem->addCar(1) << endl;
    return 0;
}

