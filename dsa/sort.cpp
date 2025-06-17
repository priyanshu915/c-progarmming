#include <iostream>
#include <vector>

template <typename T> struct Sort {
private:
  std::vector<T> arr;
  bool ascending = true;

public:
  Sort() { std::cout << "Please give the array in constructor" << std::endl; }
  Sort(std::vector<T> &array) : arr(array) {};
  Sort(bool order) : ascending(order) {};
  Sort(std::vector<T> &array, bool order) : arr(array), ascending(order) {};
  Sort(bool order, std::vector<T> &array) : arr(array), ascending(order) {};

  void bubble_sort() {}

  void selection_sort() {}

  void insertion_sort() {}
};

int main() {
  std::vector<int> nums = {5, 4, 3, 2, 1};
  Sort<int> sort(nums, true);

  std::cout << "original array: ";
  for (int i = 0; i < nums.size(); i++) {
    std::cout << nums[i] << " ";
  }
  std::cout << std::endl;

  sort.bubble_sort();

  std::cout << "sorted array: ";
  for (int n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}