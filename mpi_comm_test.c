#include <stdio.h>
// ignore error here
#include <mpi.h>

int main(){
    int numtask, rank, dest, source, rc, count, tag = 1;
    char inmsg, outmsg = 'x';
    MPI_Status stat;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numtask);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0){
        dest = 1;
        source = 1;
        outmsg = 'a';
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stat);
    } else if (rank == 1){
        dest = 0;
        source = 0;
        outmsg = 'b';
        MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, &stat);
        MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    }
    MPI_Get_count(&stat, MPI_CHAR, &count);
    if (rank == 0 || rank == 1){
        printf("Task %d: Received %d char(s) from task %d with tag %d \nThe char was: %c \n",
            rank, count, stat.MPI_SOURCE, stat.MPI_TAG, inmsg);
    }


    MPI_Finalize();
}