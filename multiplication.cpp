#include "multiplication.h"

std::vector<float> to_toeplitz(Matrix &A, int m){
	std::vector<float> ans;
	int n = A.get_sizeofrow();

	for (int i = 0; i < n-m+1 ; ++i){
		for (int j = 0; j < n-m+1; ++j){
			for (int u = 0; u < m; ++u){
				for (int v = 0; v < m; ++v){
					ans.push_back(A.get_sizeofrow(i+u,j+v));
				}
			}
		}
	}

	return ans;

}
