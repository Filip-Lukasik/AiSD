#include <cassert>
#include <vector>
#include <array>
#include <algorithm>
#include "sorts.h"

int main(){
	std::vector<int> v = {6,3,8,3,1,8,5,2,9,0,4};
	std::array<float,7> f = {3.43,7.34,1.11,8.45,2.77,9.56,6.35};
	merge_sort(f.begin(), f.end());
	select_sort(v.begin(),v.end());
	assert( std::is_sorted(v.begin(), v.end()) );
	assert( std::is_sorted(f.begin(), f.end()) );
	return 0;
}
