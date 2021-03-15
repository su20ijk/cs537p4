/*
* Copyright Jianping Shen UW Madison CS537 2021 Spring
*/
#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[]){
  int sliceA = atoi(argv[1]);
  //int sleepA = atoi(argv[2]);
  int sliceB = atoi(argv[3]);
  //int sleepB = atoi(argv[4]);
  int sleepParent = atoi(argv[5]);
  int pidA, pidB;
  int compA = -1;
  int compB = -1;
  char *path = "./loop";
  char *argvA[3];
  char *argvB[3];
  argvA[0] = path;
  argvA[1] = argv[2];
  argvA[2] = 0;
  argvB[0] = path;
  argvB[1] = argv[4];
  argvB[2] = 0;
  struct pstat p;
  pidA = fork2(sliceA);
  if(pidA == 0){
    exec(path, argvA);
  } else {
    pidB = fork2(sliceB);
    if(pidB == 0){
      exec(path, argvB);
    } else {
      sleep(sleepParent);
      getpinfo(&p);
      wait();
      wait();
      for(int i = 0; i < 64; i++){
        if(p.pid[i] == pidA){
          compA = p.compticks[i];
          break;
        }
      }
      for(int i = 0; i < 64; i++){
        if(p.pid[i] == pidB){
          compB = p.compticks[i];
          break;
        }
      }
      printf(1, "%d %d\n", compA, compB);
      exit();
    }
    exit();
  }
  exit();
}