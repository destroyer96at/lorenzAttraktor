#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#define NUMBER_OF_COMMANDS 2
using namespace std;
/*****************************************************************************/
class integrator{
    public:
        integrator(double , double);
        double GetOutput();
        void calc(void);
        void SetInput(double);
        ~integrator();
    private:
        double dt = 0;
        double value = 0;
        double in = 0;
};
/*****************************************************************************/
int main()
{
    int n = 10000;
    double a=10, b=28, c=8/3;
    double dx=0, dy=0, dz=0;
    double dt = 0.01;
    integrator X(1,dt),Y(1,dt),Z(1,dt);
    ofstream fileOut("output.txt",ofstream::out);
    FILE *plot = popen("gnuplot -persitent","w");
    char * commandsForGnuplot[] = {"set title \"Lorenz-Attraktor\"", "splot 'output.txt' u 1:2:3 with lines"};

    for (int i = 0; i < n; i++)
    {
        cout<<i*dt<<"\t"<<X.GetOutput()<<"\t"<<Y.GetOutput()<<"\t"<<Z.GetOutput()<<endl;
        fileOut/*<<i*dt*/<<"\t"<<X.GetOutput()<<"\t"<<Y.GetOutput()<<"\t"<<Z.GetOutput()<<endl;
        dx=a*(Y.GetOutput()-X.GetOutput());
        dy=X.GetOutput()*(b-Z.GetOutput())-Y.GetOutput();
        dz=X.GetOutput()*Y.GetOutput()-c*Z.GetOutput();
        X.SetInput(dx);
        Y.SetInput(dy);
        Z.SetInput(dz);
        X.calc();
        Y.calc();
        Z.calc();

    }
    for(int i = 0;i < NUMBER_OF_COMMANDS;i++)
    {
	fprintf(plot, "%s \n", commandsForGnuplot[i]);

    } 
    fileOut.close();
    return 0;
}
/*****************************************************************************/
integrator::integrator(double initialCondition,double timeStep)
{
    value = initialCondition;
    dt = timeStep;
}
/*****************************************************************************/
double integrator::GetOutput()
{
    return value;
}
/*****************************************************************************/
void integrator::calc()
{
    value += in * dt;
}
/*****************************************************************************/
void integrator::SetInput(double input)
{
    in = input;
}
/*****************************************************************************/
integrator::~integrator()
{


}
/*****************************************************************************/
