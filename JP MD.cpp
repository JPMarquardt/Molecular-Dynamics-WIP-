#include <iostream>
#include <cmath>
using namespace std;

class ferm{
    public:
    double xPos;
    double yPos;
    double zPos;

    double xMom;
    double yMom;
    double zMom;

    double theta;
    double phi;

    double mass;
    double charge;
    double dipole;

    double xBT;
    double xBB;

    double yBT;
    double yBB;

    void print(int i){
        cout << this -> xPos;
        cout << this -> yPos;
    }
    void print(){
        cout << this -> xPos <<endl;
    }
};



void iterate(ferm inFerm[],int n){
    double dist = 0;
    double dt = 0.1;
    double CL = 0;

    double xPosNew;
    double xMP = 0;
    double xCL = 0;
    double xBC = 0;
    double xFSum = 0;

    double yPosNew;
    double yMP = 0;
    double yCL = 0;
    double yBC = 0;//boundary condition for if I ever want to impliment soft edge boundaries
    double yFSum = 0;

    //double zPosNew;

    //double thetaNew;
    //double phiNew;

    for(int i = 0; i < n; i++) {
        for(int j=0; j < n; j++){
            if(i != j){
                dist = sqrt(pow(inFerm[i].xPos - inFerm[j].xPos,2) + pow(inFerm[i].yPos - inFerm[j].yPos,2));

                CL = -inFerm[i].charge * inFerm[j].charge/ pow(dist,2);
                xCL = CL * abs(inFerm[i].xPos-inFerm[j].xPos) / dist;
                yCL = CL * abs(inFerm[i].yPos-inFerm[j].yPos) / dist;
                //add extra forces?

                xFSum = xCL + xFSum;//add in extra forces to the force sum
                xFSum = xCL + xFSum;
            }
        }

        inFerm[i].xPos = (0.5 * xFSum * pow(dt,2) / inFerm[i].mass)  + (inFerm[i].xMom * dt/inFerm[i].mass) + inFerm[i].xPos;
        inFerm[i].yPos = (0.5 * yFSum * pow(dt,2) / inFerm[i].mass) + (inFerm[i].yMom * dt / inFerm[i].mass) + inFerm[i].yPos;
        //inFerm[i].zPos =
        
        inFerm[i].xMom = xFSum * dt + inFerm[i].xMom;
        inFerm[i].yMom = yFSum * dt + inFerm[i].yMom;

        if(inFerm[i].xPos > inFerm[i].xBT || inFerm[i].xPos < inFerm[i].xBB){
            inFerm[i].xMom = -inFerm[i].xMom;
        }
        if(inFerm[i].yPos > inFerm[i].yBT || inFerm[i].yPos < inFerm[i].yBB){
            inFerm[i].yMom = -inFerm[i].yMom;
        }
        //inFerm[i].zMom = zCL*dt + inFerm[i].zMom;

        //inFerm[i].theta = 
        //inFerm[i].phi =
    }
}

int main(){
    int n = 2;
    ferm mols1;
    ferm mols2;
    ferm mols[2];

    mols1.xPos =  1;
    mols1.xMom = 1;
    mols1.yPos =  1;
    mols1.yMom = 1;
    mols1.mass = 1;
    mols1.charge = 1;
    mols1.xBB = 0;
    mols1.xBT = 2;
    mols1.yBB = 0;
    mols1.yBT = 2;

    mols[0] = mols1;
    mols[1] = mols1;
    mols[1].xPos = 0.5;

    for(int i = 0; i<20; i++){
        iterate(mols,2);
        cout << mols[0].xPos <<endl;

    }


    return 0;
}
