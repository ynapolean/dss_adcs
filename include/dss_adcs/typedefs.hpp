/*
 * Copyright (c) 2017, K. Kumar, Delft University of Technology (me@kartikkumar.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef DSS_ADCS_TYPEDEFS_HPP
#define DSS_ADCS_TYPEDEFS_HPP

// #include <boost/array.hpp>
#include <Eigen/Dense>
#include <rapidjson/document.h>

namespace dss_adcs
{

//! Set type for integer numbers.
typedef int Int;

//! Set type for floating-point real numbers.
typedef double Real;

//! Set type for 3-dimensional vector.
typedef Eigen::Matrix< double, 3, 1 > Vector3;

//! Set type for 6-dimensional vector.
typedef Eigen::Matrix< double, 6, 1 > Vector6;

//! Set type for a 3 by 3 matrix.
// typedef boost::numeric::ublas::matrix Matrix33;
// typedef Real Matrix33[3][3];
typedef Eigen::Matrix< double, 3, 3 > Matrix33; 

//! Set type for position vector to 3D vector.
typedef Vector3 Position;

//! Set type for velocity vector to 3D vector.
typedef Vector3 Velocity;

//! Set type for state vector to 6D vector.
typedef Vector6 State;

//! Set type for ineratia vector to 3D vector. 
typedef Vector3 Inertia; 

//! JSON config iterator.
typedef rapidjson::Value::ConstMemberIterator ConfigIterator;

//! Define numerical integrators.
enum Integrator
{
  rk4,
  dopri5,
  rkf78,
  bs,
  testInt
};

} // namespace dss_adcs

#endif // DSS_ADCS_TYPEDEFS_HPP
