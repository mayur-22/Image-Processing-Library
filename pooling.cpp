#include "pooling.h"

std::vector<float> max_pooling(Matrix &A, Matrix &B){
	int m = B.get_sizeofrow();
	int n = A.get_sizeofrow();
	std::vector<float> ans;		//column priority
	float max = 0.00;
	
	//assuming i,j will give element of ith row and jth column

	for(int y=0;y<n;y+=m){
		for(int x=0;x<n;x+=m){
			max = 0.00;
			for (int i = 0; i < m; ++i){
				for (int j = 0; j < m; ++j){
					if(max<A.get_Element(j+y,i+x))
						max = A.get_Element(j+y,i+x);
				}
			}
			ans.push_back(max);
		}
	}
	return ans;

}

std::vector<float> average_pooling(Matrix &A, Matrix &B){
	int m = B.get_sizeofrow();
	int n = A.get_sizeofrow();
	std::vector<float> ans;		//column priority
	float sum = 0.00;
	
	//assuming i,j will give element of ith row and jth column

	for(int y=0;y<n;y+=m){
		for(int x=0;x<n;x+=m){
			sum = 0.00;
			for (int i = 0; i < m; ++i){
				for (int j = 0; j < m; ++j){
					sum += A.get_Element(j+y,i+x);
				}
			}
			ans.push_back(sum/(m*m));
		}
	}
	return ans;

}
