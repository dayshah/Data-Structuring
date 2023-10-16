
#include <iostream>
#include <map>


struct Person {
    std::string name;
    Person(const std::string& name, int age):
        name(name) 
    {}
};

int longestNonDecreasing(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int dp1 = 1;
    int dp1Future = 1;
    int dp2 = 1;
    int res = 1;
    for (int i = 1; i < nums1.size(); ++i) {
        dp1Future = std::max(
            nums1[i] >= nums1[i-1] ? dp1+1 : 1,
            nums1[i] >= nums2[i-1] ? dp2+1 : 1
        );
        dp2 = std::max(
            nums2[i] >= nums1[i-1] ? dp1+1 : 1,
            nums2[i] >= nums2[i-1] ? dp2+1 : 1
        );
        dp1 = dp1Future;
        res = std::max({res, dp1, dp2});
    }
    return res;
}

int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int twoGroup) {
    
}


int main() {
    
}
