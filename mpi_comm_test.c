#include <stdio.h>
#include <mpi.h>

int main(){
    MPI_INIT(NULL, NULL);

    MPI_FINALIZE();
}