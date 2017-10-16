#include "common.h"
#include "double_integrator.h"
#include "ilqr.h"

int main() {
  VectorXd goal(4);
  goal << 1.0, 1.0, 0.0, 0.0;
  DoubleIntegrator* simple_model = new DoubleIntegrator(goal);

  double dt = 0.05;
  iLQR ilqr_simple(simple_model, dt);

  VectorXd x0(4), xd(4);
  x0 << 0., 0., 0., 0.;

  int T = 99;
  VecOfVecXd u0;
  Vector2d u_init(0.1, 0.1);
  for (int i = 0; i < T; i++) u0.push_back(u_init);

  auto start = std::chrono::system_clock::now();

  ilqr_simple.generate_trajectory(x0, u0);

  auto now = std::chrono::system_clock::now();
  long int elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(now - start)
          .count();
  cout << "iLQR took: " << elapsed / 1000. << " seconds." << endl;

  return 0;
}
