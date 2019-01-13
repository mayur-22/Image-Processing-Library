#include "convolution.h"

std::vector<float> conv_withoutpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+u,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				try{
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+u,true)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
				}
				catch(char *msg){}
			}
		}

	}
	return ans;
}

std::vector<float> conv_withpadding(Matrix &A, Matrix &B){
	std::vector<float> ans;
	int n = A.get_sizeofrow();
	int m = B.get_sizeofrow();
	
	if(m%2==0){			//if m is even
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -(m-1)/2; u <= m/2; ++u){
					for (int v = -(m-1)/2; v <= m/2; ++v){
						sum+=A.get_Element(x+u,v+u,false)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}
	}

	else{
		for (int x = 0; x < n; ++x){
			for (int y = 0; y < n; ++y){
				int sum = 0.00;
				for (int u = -m/2; u <= (m-1)/2; ++u){
					for (int v = -m/2; v <= (m-1)/2; ++v){
						sum+=A.get_Element(x+u,v+u,false)*B.get_Element(u+(m/2),v+(m/2));
					}
				}
				ans.push_back(sum);
			}
		}

	}
	return ans;
}