/*
[转载]cpp简单实现一下RNN神经网络
https://blog.csdn.net/qq_40708167/article/details/113781324

结果是：输入前4个字母，可以输出后面那个。
*/

#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct Matrix
{
	int rows, colums;
	float **val;
	void init(int _rows, int _colums)
	{
		rows=_rows, colums=_colums;
		val=new float*[rows];
		for (int i=0; i < rows; i++)
		{
			val[i]=new float[colums];
			for (int j=0; j < colums; j++)
				val[i][j]=(rand() % 200 - 100) / 100.0;
		}
	}
};

float tanh_my(float x) {
	x=exp(x); x=x * x;
	return  (x - 1) / (x + 1);
}
struct NerualNetwork
{
	int layoutNum;
	float factor=0.02;
	Matrix *X, *U, *V, *H, *B;
	Matrix *D, *dU, *dV, *dB, *TU, *TV, *TB;
	Matrix Softmax;
	std::vector<int>layout;
	void addLayout(int number)
	{
		layout.push_back(number);
		layoutNum++;
	}
	void bulid() {
		X=new Matrix[layoutNum];
		H=new Matrix[layoutNum];
		D=new Matrix[layoutNum];


		U =new Matrix[layoutNum];
		dU=new Matrix[layoutNum];
		TU=new Matrix[layoutNum];
		V =new Matrix[layoutNum];
		dV=new Matrix[layoutNum];
		TV=new Matrix[layoutNum];
		B =new Matrix[layoutNum];
		dB=new Matrix[layoutNum];
		TB=new Matrix[layoutNum];

		srand(time(NULL));
		X[0].init(layout[0], 1);
		D[0].init(layout[0], 1);
		for (int i=1; i < layoutNum; i++) {
			X[i].init(layout[i], 1);
			H[i].init(layout[i], 1);
			D[i].init(layout[i], 1);

			U[i].init(layout[i], layout[i - 1]);
			dU[i].init(layout[i], layout[i - 1]);
			TU[i].init(layout[i], layout[i - 1]);
			V[i].init(layout[i], layout[i]);
			dV[i].init(layout[i], layout[i]);
			TV[i].init(layout[i], layout[i]);
			B[i].init(layout[i], 1);
			dB[i].init(layout[i], 1);
			TB[i].init(layout[i], 1);
		}
		Softmax.init(layout[layoutNum - 1], 1);
	}
	void clearMenory() {
		for (int k=1; k < layoutNum; k++)
			for (int i=0; i < H[k].rows; i++)
				X[k].val[i][0]=0;
	}
	void InitTrainMenory() {
		for (int k=1; k < layoutNum; k++) {
			for (int i=0; i < B[k].rows; i++)dB[k].val[i][0]=TB[k].val[i][0]=0;
			for (int i=0; i < U[k].rows; i++) {
				memset(dU[k].val[i], 0, dU[k].colums * 4);
				memset(TU[k].val[i], 0, TU[k].colums * 4);
			}
			for (int i=0; i < V[k].rows; i++) {
				memset(dV[k].val[i], 0, dV[k].colums * 4);
				memset(TV[k].val[i], 0, TV[k].colums * 4);
			}
		}
	}
	int updateSoftmax() {
		float sum=0;
		Matrix M=X[layoutNum - 1];
		for (int i=0; i < M.rows; i++) {
			Softmax.val[i][0]=exp(M.val[i][0]);
			sum+=Softmax.val[i][0];
		}
		int k=0;
		for (int i=0; i < M.rows; i++) {
			Softmax.val[i][0]/=sum;
			if (Softmax.val[i][0] > Softmax.val[k][0])k=i;
		}
		return k;
	}
	Matrix run(int input) {
		for (int i=0; i < X[0].rows; i++)X[0].val[i][0]=0;
		X[0].val[input][0]=1;
		for (int k=1; k < layoutNum; k++)
		{
			for (int i=0; i < H[k].rows; i++)H[k].val[i][0]=X[k].val[i][0];
			for (int i=0; i < X[k].rows; i++) {
				X[k].val[i][0]=B[k].val[i][0];
				for (int j=0; j < U[k].colums; j++)
					X[k].val[i][0]+=U[k].val[i][j] * X[k - 1].val[j][0];

				for (int j=0; j < X[k].rows; j++)
					X[k].val[i][0]+=V[k].val[i][j] * H[k].val[j][0];
				X[k].val[i][0]=tanh_my(X[k].val[i][0]);
			}
		}
		return X[layoutNum - 1];
	}
	void Partial(int label) {
		if (label == -1) {
			for (int i=0; i < D[layoutNum - 1].rows; i++)
				D[layoutNum - 1].val[i][0]=0;
		}
		else {
			updateSoftmax();
			for (int i=0; i < D[layoutNum - 1].rows; i++)
				D[layoutNum - 1].val[i][0]=Softmax.val[i][0];
			D[layoutNum - 1].val[label][0]-=1;
		}
		for (int k=layoutNum - 1; k > 0; k--) {

			for (int i=0; i < V[k].colums; i++) {
				float sum=0;
				for (int j=0; j < V[k].rows; j++)sum+=V[k].val[j][i];
				for (int j=0; j < TU[k].colums; j++)TU[k].val[i][j]*=sum;
				for (int j=0; j < TV[k].colums; j++)TV[k].val[i][j]*=sum;
				TB[k].val[i][0]*=sum;
			}
			for (int i=0; i < TU[k].rows; i++)
				for (int j=0; j < TU[k].colums; j++) {
					TU[k].val[i][j]=(TU[k].val[i][j] + X[k - 1].val[j][0])*(1 - X[k].val[i][0] * X[k].val[i][0]);
					dU[k].val[i][j]+=TU[k].val[i][j] * D[k].val[i][0];
				}

			for (int i=0; i < TV[k].rows; i++)
				for (int j=0; j < TV[k].colums; j++) {
					TV[k].val[i][j]=(TV[k].val[i][j] + H[k].val[j][0])*(1 - X[k].val[i][0] * X[k].val[i][0]);
					dV[k].val[i][j]+=TV[k].val[i][j] * D[k].val[i][0];
				}
			for (int i=0; i < TB[k].rows; i++) {
				TB[k].val[i][0]=(TB[k].val[i][0] + 1)*(1 - X[k].val[i][0] * X[k].val[i][0]);
				dB[k].val[i][0]+=TB[k].val[i][0] * D[k].val[i][0];
			}
			for (int i=0; i < U[k].colums; i++) {
				D[k - 1].val[i][0]=0;
				for (int j=0; j < U[k].rows; j++)
					D[k - 1].val[i][0]+=U[k].val[j][i] * (1 - X[k].val[j][0] * X[k].val[j][0])*D[k].val[j][0];
			}
		}
	}
	void UpdateTrain() {
		for (int k=1; k < layoutNum; k++) {
			for (int i=0; i < B[k].rows; i++)B[k].val[i][0]-=dB[k].val[i][0] * factor;
			for (int i=0; i < U[k].rows; i++)
				for (int j=0; j < U[k].colums; j++)
					U[k].val[i][j]-=dU[k].val[i][j] * factor;
			for (int i=0; i < V[k].rows; i++)
				for (int j=0; j < V[k].colums; j++) {
					V[k].val[i][j]-=dV[k].val[i][j] * factor;

				}
		}
	}
}RNN;
int main()
{
	RNN.addLayout(5);
	RNN.addLayout(5);
	RNN.addLayout(5);
	RNN.bulid();
	for (int i=0; i < 10000; i++) {
		for (int j=0; j < 5; j++)
		{
			RNN.InitTrainMenory();
			RNN.clearMenory();
			for (int k=0; k < 4; k++) {
				RNN.run((k + j) % 5);
				if (k == 3)RNN.Partial((4 + j) % 5);
				else RNN.Partial(-1);
			}
			RNN.UpdateTrain();
		}
	}
	for (int j=0; j < 5; j++)
	{
		RNN.clearMenory();
		for (int k=0; k < 4; k++)RNN.run((k + j) % 5), printf("%c ", 'a' + (k + j) % 5);
		int ans=RNN.updateSoftmax();
		printf(" -->%c\n", 'a' + (ans));
	}

	return 0;
}
