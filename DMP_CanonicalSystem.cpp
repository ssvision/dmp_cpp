

#include<iostream>
#include<cmath>
#include<vector>


using namespace std;


class CanonicalSystem{

    public:

        double step_size;
        double alpha_s;
        double run_time;

        double system_state;

        int timesteps;

        CanonicalSystem(double step_size, double alpha_s, double run_time){

            this-> step_size = step_size;
            this-> run_time = run_time;
            this-> alpha_s = alpha_s;
            this-> timesteps = int(this->run_time/this->step_size) + 1;

        }

        void reset(){
            /*
            Reset the system state
            */
            this->system_state = 1.0;
        }

        std::vector<double> rollout(double tau=1.0){

            int timesteps = int(this->timesteps/tau);
            std::vector<double> system_track;
            reset();

            for (int i=0; i<timesteps; i++){

                system_track.push_back(this->system_state);
                step(tau);

            }

            return system_track;

        }

        double step(double tau=1.0, double error_coupling=1.0){

            double cnst =  -1.0 * ((this->alpha_s / tau) / error_coupling);
            this->system_state = this->system_state * exp(cnst*this->step_size);
            return this->system_state;




        }

};

int main(){

    //create a Canonical System Object
    CanonicalSystem my_cs(0.01, 4.0, 1.0);

    std::vector<double> traj;
    traj = my_cs.rollout(0.8);

    std::cout<<"  Size is : "<<traj.size()<<std::endl;
    //Print the Sequence
    for(int i=0; i<traj.size(); i++){
        cout<<traj[i]<<endl;
    }

    return 0;
}