#include <iostream>
#include <vector>
#include <unordered_map>
#include "output_container.h"

using namespace std;

class ThroneInheritance {
public:
    ThroneInheritance(string kingName) {
        king = kingName;
    }
    
    void birth(string parentName, string childName) {
        family[parentName].push_back(childName);
    }
    
    void death(string name) {
        isDead[name] = true;
    }
    
    vector<string> getInheritanceOrder() {
        vector<string> res;
        helper(res,king);
        return res;
    }
    void helper(vector<string>& res,string king) {
        if (!isDead[king]) {     // 如果没有死亡,第一继承人还是king
            res.push_back(king);
        }
        for (string child: family[king]) {
            helper(res, child);
        }
    }
private:
    string king;
    unordered_map<string, bool> isDead; // 记录是否死亡
    unordered_map<string, vector<string>> family;
};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

int main(int argc, const char** argv)
{
    ThroneInheritance *obj = new ThroneInheritance("king"); // 继承顺序：king
    obj->birth("king", "andy"); // 继承顺序：king > andy
    obj->birth("king", "bob"); // 继承顺序：king > andy > bob
    obj->birth("king", "catherine"); // 继承顺序：king > andy > bob > catherine
    obj->birth("andy", "matthew"); // 继承顺序：king > andy > matthew > bob > catherine
    obj->birth("bob", "alex"); // 继承顺序：king > andy > matthew > bob > alex > catherine
    obj->birth("bob", "asha"); // 继承顺序：king > andy > matthew > bob > alex > asha > catherine
    cout << obj->getInheritanceOrder() << endl; // 返回 ["king", "andy", "matthew", "bob", "alex", "asha", "catherine"]
    obj->death("bob"); // 继承顺序：king > andy > matthew > bob（已经去世）> alex > asha > catherine
    cout << obj->getInheritanceOrder() << endl; // 返回 ["king", "andy", "matthew", "alex", "asha", "catherine"]
    return 0;
}