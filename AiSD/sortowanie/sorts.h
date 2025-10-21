#ifndef SORTS_H
#define SORTS_H

template<typename Iterator>
Iterator find_min(Iterator start,Iterator stop){
	auto min = start;
	start++;
	while(start<stop){
		if(*(start)<*(min)){
			min = start;
		}
		start++;
	}
	return min;
}
template <typename Iterator>
void scal(Iterator start,Iterator srodek,Iterator stop){
	while((start<srodek)&&(srodek<stop)){
		if(*(srodek)<(*start)){
			for(int i=0;i<srodek-start;i++){
				std::swap(*(srodek-i),*(srodek-1-i));
			}
			srodek++;
		}
		start++;
	}
}
template <typename Iterator>
void select_sort(Iterator start,Iterator stop){
        auto min = start;
        while(start<stop-1){
                min = find_min(start,stop);
		if(min!=start){
			std::swap(*min,*start);
		}
		start++;
        }
}
template <typename Iterator>
void merge_sort(Iterator start,Iterator stop){
	if((stop-start)>1){
		auto srodek = start + (stop-start)/2;
		merge_sort(start,srodek);
		merge_sort(srodek,stop);
		scal(start,srodek,stop);
	}
}
#endif
