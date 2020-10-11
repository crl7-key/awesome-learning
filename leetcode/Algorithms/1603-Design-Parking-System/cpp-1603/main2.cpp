#include <iostream>
#include <vector>

using namespace std;

class ParkingSystem {
public:
    ParkingSystem(int big, int medium, int small) {
        // 初始化
       cnt = {big,medium,small};
    }
    
    bool addCar(int carType) {
        return cnt[carType - 1]-- > 0;
    }
    
private:
    vector<int> cnt;
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

