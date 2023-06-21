#include<iostream>
#include<vector>
using namespace std;

struct node {
    uint8_t data[9][9];
    vector<node> childs;
};

void CreateBranch(uint8_t code, node& parent, uint8_t x, uint8_t y);
void FindLegalMoves(node& parent);

node Root;
uint8_t  CurrentMatrix[9][9]; //CurrentMatrix [x][y]


void Matrixcpy(uint8_t (&MatrixL)[9][9], uint8_t MatrixR[9][9]){
     for(uint8_t x=0; x<9; x++){
       for(uint8_t y=0; y<9; y++){
         MatrixL[x][y] = MatrixR[x][y];
       }     
    }
}

uint8_t CreateMatrix(){
    //İnitalize a proper Matrix 
    for(uint8_t x=0; x<9; x++){
       for(uint8_t y=0; y<9; y++){
         if((x < 3 || x >= 6) && (y < 3 || y >= 6)){
            CurrentMatrix[x][y] = 0;
         }else{
            CurrentMatrix[x][y] = 1;
         }
       }     
    }
    CurrentMatrix[4][4] = 2;
    return 0;
}

void  PrintMatrix(uint8_t MatrixToPrint[9][9]){
    for(uint8_t x=0; x<9; x++){
        printf("\n");
       for(uint8_t y=0; y<9; y++){
           if(MatrixToPrint[x][y] == 0){
             printf(" #");
           }else if(MatrixToPrint[x][y] == 1){
             printf(" w");
           }else{
             printf(" O");
           }
       } 
    }
}

void CreateBranch(uint8_t code, node& _Parent, uint8_t x, uint8_t y){
  CurrentMatrix[x][y] = 2;
  switch(code){
    case 0:
      CurrentMatrix[x+1][y] = 2;
      CurrentMatrix[x+2][y] = 1;
      break; 
    case 1:
      CurrentMatrix[x-1][y] = 2;
      CurrentMatrix[x-2][y] = 1;
      break; 
    case 2:
      CurrentMatrix[x][y+1] = 2;
      CurrentMatrix[x][y+2] = 1;
      break; 
    case 3:
      CurrentMatrix[x][y-1] = 2;
      CurrentMatrix[x][y-2] = 1;
      break; 

  }
  node Branch;
  Matrixcpy(Branch.data,CurrentMatrix);
  _Parent.childs.push_back(Branch);
  FindLegalMoves(Branch);
}

void FindLegalMoves(node& parent){
      uint8_t  Branch[9][9];
      Matrixcpy(Branch,parent.data);
      for(uint8_t x=0; x<9; x++){
       for(uint8_t y=0; y<9; y++){
          if(!(Branch[x][y] == 1)) break;
          if(Branch[x+1][y] == 1 && Branch[x+2][y] == 1 && Branch[x+3][y] == 1) {
            CreateBranch(0, parent,x,y);
          }
          if(Branch[x-1][y] == 1 && Branch[x-2][y] == 1 && Branch[x-3][y] == 1) {
            CreateBranch(1, parent,x,y);
          }

          if(Branch[x+1][y] == 1 && Branch[x+2][y] == 1 && Branch[x][y+3] == 2) {
            CreateBranch(2, parent,x,y);
          }
          if(Branch[x-1][y] == 1 && Branch[x-2][y] == 1 && Branch[x][y-3] == 2) {
            CreateBranch(3, parent,x,y);
          }
        }
      }
}

int main()
{
    CreateMatrix();
    Matrixcpy(Root.data, CurrentMatrix);
    FindLegalMoves(Root);

    
    return 0;
}

