#include <iostream>
//#include "/Users/paul/opt/miniconda3/pkgs/python-3.9.12-hdfd78df_0/include/python3.9/Python.h"
//#include <matplotlib-cpp-master/python.h>
#include <cmath>

//#include "/usr/local/Cellar/python@3.9/3.9.13_1/Frameworks/Python.framework/Versions/3.9/include/python3.9"

//#include "matplotlibcpp.h"

using namespace std;

class ferm{
    public:
    double xPos;//measured in angstrom
    double yPos;
    double zPos;

    double xMom;//measured in eV/c
    double yMom;
    double zMom;

    double theta;
    double phi;

    double mass;//measured in eV/c^2
    double charge;//measured in elementary charge
    double dipole;

    double xBT;
    double xBB;

    double yBT;
    double yBB;

    void print(){
        cout << this -> xPos <<endl;
        cout << this -> yPos <<endl;
    }
};



void iterate(ferm inFerm[],int n){
    double dist = 0;
    double dt = 10000;//a few femto seconds measured in angstrom/c
    double CL = 0;

    double xPosNew;
    double xMP = 0;
    double xCL = 0;
    double xBC = 0;
    double xFSum = 0;
    double xAbove = 0;
    double xBelow = 0;

    double yPosNew;
    double yMP = 0;
    double yCL = 0;
    double yBC = 0;//boundary condition for if I ever want to impliment soft edge boundaries
    double yFSum = 0;
    double yAbove = 0;
    double yBelow = 0;

    //double zPosNew;

    //double thetaNew;
    //double phiNew;

    for(int i = 0; i < n; i++) {
        for(int j=0; j < n; j++){
            if(i != j){
                dist = sqrt(pow(inFerm[i].xPos - inFerm[j].xPos,2) + pow(inFerm[i].yPos - inFerm[j].yPos,2));

                CL = - 14.3996 * inFerm[i].charge * inFerm[j].charge/ pow(dist,2);
                xCL = CL * (inFerm[i].xPos-inFerm[j].xPos) / dist;
                yCL = CL * (inFerm[i].yPos-inFerm[j].yPos) / dist;

                xFSum = xCL + xFSum;//add in extra forces to the force sum
                yFSum = yCL + yFSum;
            }
        }


        inFerm[i].xPos = (0.5 * xFSum * pow(dt,2) / inFerm[i].mass)  + (inFerm[i].xMom * dt/inFerm[i].mass) + inFerm[i].xPos;
        inFerm[i].yPos = (0.5 * yFSum * pow(dt,2) / inFerm[i].mass) + (inFerm[i].yMom * dt / inFerm[i].mass) + inFerm[i].yPos;
        //inFerm[i].zPos =
        
        inFerm[i].xMom = xFSum * dt + inFerm[i].xMom;
        inFerm[i].yMom = yFSum * dt + inFerm[i].yMom;

        while(inFerm[i].xPos > inFerm[i].xBT || inFerm[i].xPos < inFerm[i].xBB){
            inFerm[i].xMom = -inFerm[i].xMom;//using a good timescale should allow this to be an if statement
            xAbove = abs(inFerm[i].xPos - inFerm[i].xBT);
            xBelow = abs(inFerm[i].xPos - inFerm[i].xBB);

            if(xAbove < xBelow){
                inFerm[i].xPos = inFerm[i].xBT - xAbove;
            }
            else{
                inFerm[i].xPos = inFerm[i].xBB + xBelow;
            }
        }
        while(inFerm[i].yPos > inFerm[i].yBT || inFerm[i].yPos < inFerm[i].yBB){
            inFerm[i].yMom = -inFerm[i].yMom;
            yAbove = abs(inFerm[i].yPos - inFerm[i].yBT);
            yBelow = abs(inFerm[i].yPos - inFerm[i].yBB);

            if(yAbove < yBelow){
                inFerm[i].yPos = inFerm[i].yBT - yAbove;
            }
            else{
                inFerm[i].yPos = inFerm[i].yBB + yBelow;
            }
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
    mols1.xMom = 54000;//based on the velocity of rms velcity of argon at stp and mass of an argon atom
    mols1.yPos =  1;
    mols1.yMom = 1;
    mols1.mass = 937000000;//based on mass of an argon atom in eV/c^2
    mols1.charge = 1;
    mols1.xBB = 0;
    mols1.xBT = 125;//an arbitrary value based on the density of argon at stp
    mols1.yBB = 0;
    mols1.yBT = 125;

    mols[0] = mols1;
    mols[1] = mols1;
    mols[1].xPos = 70;
    mols[1].yPos = 40;
    mols[1].yMom = 54000;

    for(int i = 0; i<2000; i++){
        iterate(mols,2);

        cout << "momentum:" << mols[1].xMom << "," << mols[1].yMom << ";" << endl;
        cout << "momentum:" << mols[0].xMom << "," << mols[0].yMom << ";" << endl;

        cout << "position:" << mols[1].xPos << "," << mols[1].yPos << ";" << endl;
        cout << "position:" << mols[0].xPos << "," << mols[0].yPos << ";" << endl;

    }


    return 0;
}
