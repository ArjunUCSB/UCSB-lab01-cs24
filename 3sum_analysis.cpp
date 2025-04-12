#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;
using namespace std::chrono;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        vector<int> triplet = {nums[i], nums[j], nums[k]};
                        // Manual sorting
                        if (triplet[0] > triplet[1]) {
                            int temp = triplet[0];
                            triplet[0] = triplet[1];
                            triplet[1] = temp;
                        }
                        if (triplet[1] > triplet[2]) {
                            int temp = triplet[1];
                            triplet[1] = triplet[2];
                            triplet[2] = temp;
                        }
                        if (triplet[0] > triplet[1]) {
                            int temp = triplet[0];
                            triplet[0] = triplet[1];
                            triplet[1] = temp;
                        }
                        // Check duplicates
                        bool isDuplicate = false;
                        for (const auto& existing : result) {
                            if (existing[0] == triplet[0] && 
                                existing[1] == triplet[1] && 
                                existing[2] == triplet[2]) {
                                isDuplicate = true;
                                break;
                            }
                        }
                        if (!isDuplicate) {
                            result.push_back(triplet);
                        }
                    }
                }
            }
        }
        return result;
    }
};

vector<int> generate_test_case(int n) {
    vector<int> nums;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-1000, 1000);
    
    // Ensure at least one valid triplet
    nums.push_back(-500);
    nums.push_back(200);
    nums.push_back(300);
    
    // Fill the rest with random numbers
    for (int i = 3; i < n; ++i) {
        nums.push_back(dist(gen));
    }
    
    return nums;
}

void run_tests() {
    ofstream outfile("runtime_data.csv");
    outfile << "n,time_ms\n";
    
    vector<int> test_sizes = {100, 200, 400, 800, 1600, 3200, 6400};
    Solution sol;
    
    for (int n : test_sizes) {
        vector<int> nums = generate_test_case(n);
        
        auto start = high_resolution_clock::now();
        vector<vector<int>> result = sol.threeSum(nums);
        auto end = high_resolution_clock::now();
        
        double time_ms = duration_cast<microseconds>(end - start).count() / 1000.0;
        outfile << n << "," << time_ms << "\n";
        
        cout << "n = " << n << ", time = " << time_ms << " ms\n";
    }
    
    outfile.close();
}

int main() {
    run_tests();
    return 0;
}
