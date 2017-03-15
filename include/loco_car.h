/*
Basically just need to provide class with f(dynamics), l(cost), lf(final cost)
*/

#pragma once
#include "standardIncludes.h"
#include "iLQR2.h"

class LocoCar : public iLQR
{
  // Model parameters
  const double m;         // mass (kg)
  const double g ;
  const double L;        // wheelbase (m)
  const double b;      // CoG to rear axle
  const double a;          // CoG to front axle
  const double G_front;   // calculated load or specify front rear load directly
  const double G_rear;

  const double C_x;       // longitude stiffness
  const double C_alpha;   //laternal stiffness
  const double Iz;     // rotational inertia
  const double mu;      //5.2/G_rear
  const double mu_spin;  //4.3/G_rear

  Eigen::Vector2d tire_dyn(double Ux, double Ux_cmd, double mu, double mu_slide,
                    double Fz, double C_x, double C_alpha, double alpha);

public:
  LocoCar(): m(2.35), g(9.81), L(0.257), b(0.14328), C_x(50), C_alpha(45),
                  Iz(0.045), mu(0.75), mu_spin(0.2), a(0.11372),
                  G_front(12.852550506), G_rear(10.200949494) { std::cout << "constructed\n";}

  virtual Eigen::VectorXd dynamics(const Eigen::VectorXd &x, const Eigen::Vector2d  &u); //dynamics

  virtual double cost(const Eigen::VectorXd &x, const Eigen::Vector2d &u);

  virtual double final_cost(const Eigen::VectorXd &x);

};