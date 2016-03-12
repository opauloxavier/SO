#include <stdio.h>
#include <stdlib.h>

class Matriz{
	public:
		int **matriz,n,m;
		Matriz(int m,int n);
		void multiplicaMatriz(Matriz *a);
		void preencheMatriz();

};


Matriz::Matriz(int m,int n){
	int **mat = new int*[m];
		for(int i = 0; i < m; ++i) {
   	 	mat[i] = new int[n];
		}

	matriz=mat;
	this->m=m;
	this->
	n=n;
	preencheMatriz();
}

void Matriz::multiplicaMatriz (Matriz *a){
	Matriz *matrizResultado=new Matriz(2,2);

	for(int i=0;i<m;i++){
		int k=0;
		int resultado=0;
		
		for(int j=0;j<n;j++){
			resultado=this->matriz[i][j]*a->matriz[i][j+k];

			printf("Multiplicando a%d,%d -> %d por b%d,%d -> %d deu -> %d\n",i,j,i,j+k,this->matriz[i][j],a->matriz[i][j+k],resultado);
			k++;
		}
	}

}

void Matriz::preencheMatriz(){
	int contador=1;

	for (int i=0;i<this->m;i++){
		for(int j=0;j<this->n;j++){
			this->matriz[i][j]=contador;
			contador++;
		}
	}
}

int main(){

	Matriz *a = new Matriz(2,2);
	Matriz *b = new Matriz(2,2);

	a->multiplicaMatriz(b);

	printf("%d",a->matriz[0][0]);

	return 0;
}