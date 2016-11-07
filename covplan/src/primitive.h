#include <iostream>
#include <vector>
#include "basics.h"


using namespace std;


struct s1
{
  int velocity;
};

typedef struct s1 state;

class Primitive 
{
  private:
    state q_i;
    state q_f;
    position pos_f;
    string cost;
    pos_vec_t swath;    
    position pos_min;
    position pos_max;

  public:
    Primitive(state , state , position , string , pos_vec_t , position , position );
    state get_q_i();
    state get_q_f();
    position get_pos_f();
    string get_cost();
    pos_vec_t get_swath();
    position get_pos_min();
    position get_pos_max();
    ~Primitive();  
};

typedef std::vector<Primitive> prim_vec_t;
