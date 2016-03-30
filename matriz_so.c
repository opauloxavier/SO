#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

//parametros m, n, qt de processos

void printMatriz(int **matriz, int m, int n){
    int i, j;
    
    printf("\n");
    
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++)
            printf("%d\t", matriz[i][j]);
        
        printf("\n");
    }
}


int main(int argc, char **argv){

    int m = atoi(argv[1]), n = atoi(argv[2]), proc = atoi(argv[3]);

    int **A = NULL, **B = NULL;
    int i, j, k, l;    
    
    A = (int**) malloc(n * sizeof(int*));
    B = (int**) malloc(n * sizeof(int*));
    
    for (j = 0; j < n; j++){        
        A[j] = (int*) malloc(m * sizeof(int));
        B[j] = (int*) malloc(m * sizeof(int));
        
    }

    //preenche as matrizes
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){        
            k = j * m + i;

            A[i][j] = k + 1;
            if (i == j)
                B[i][j] = 1;
            else
                B[i][j] = 0;
            
        }
    }
    
  int id, aux, entrou = 0, cont;
  int segmento;

  //memória compartilhada
  segmento = shmget(IPC_PRIVATE, sizeof(int)*4, S_IRWXU);
  
  int **matrizSolucao = (int**)shmat(segmento, NULL, 0);
  
  for(aux = 1; aux <= proc; aux++){
      id = fork();

      //processo filho
      if (id == 0){  
        wait(id);
        int aux2 = 0;

        for(i = 0; i < m; i++){
          for (j = 0; j < n; j++)
              aux2 += A[aux][j] * B[j][i];        

          matrizSolucao[aux][i] = aux2; 
          
        }

        kill(id);

      }else//processo pai
        if(entrou == 0){
          entrou++;
          printMatriz(matrizSolucao, m, n);
        }
  }

  

  //libera a memória compartilhada do processo
  shmdt(matrizSolucao);
  
  //libera a memória compartilhada
  shmctl(segmento, IPC_RMID, 0);
 
  //libera memória das matrizes
  free (A);
  free (B);

  return EXIT_SUCCESS;
}
