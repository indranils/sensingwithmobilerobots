#include <vector>

using namespace std;


struct s2
{
  int x;
  int y;
};

typedef struct s2 position;

typedef std::vector<position> pos_vec_t;

struct d
{
  unsigned int length_x;
  unsigned int length_y;
};

typedef struct d dimension_t;


struct c
{
  float max_cost;
  float min_cost;
  float min2_cost;
  float min_cost_diff;
  float min2_min_cost_diff;
};

typedef struct c prim_cost_t;


bool isObstacle (pos_vec_t , unsigned int , unsigned int );
