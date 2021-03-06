/*
 * Copyright (c) 2018 S.D. Cherukuri (srikarad007@gmail.com)
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef DSS_ADCS_DYNAMICAL_SYSTEM_HPP
#define DSS_ADCS_DYNAMICAL_SYSTEM_HPP

#include <sml/sml.hpp>

#include <astro/astro.hpp>

#include "dss_adcs/typedefs.hpp"

namespace dss_adcs
{

//! Class containing parameters and models to describe the dynamical system.
/*!
 * This class contains parameters and models to describe the dynamical system that governs the
 * rotational motion of a spacecraft. The dynamical system is defined in terms of a set of 1st-order ODEs,
 * with the right-hand side including all the force models acting on the spacecraft. This
 * dynamical system is provided as input to a numerical integrator to compute the derivative of the
 * state vector.
 */
class DynamicalSystem
{
public:

    //! Construct dynamical system.
    /*!
     * Constructor for dynamical system, taking model parameters to define the dynamical
     * environment.
     *
     * @param[in] aGravitationalParameter   Gravitational parameter of the central body  [km^3 s^-2]
     * @param[in] aInertiaPrinciple         Princple axes of inertia's of the spacecraft [kg m^2]
     * @param[in] intial
     */
    DynamicalSystem( const Real aPrincipleInertia )
        : aPrincipleInertia( aPrincipleInertia )
    { }

    //! Overload ()-operator to compute state derivative using dynamical system.
    /*!
     * Overloads the ()-operator to compute the state derivative, given the current state and epoch,
     * based on the parameters and models used to construct the dynamical system.
     * This function fulfills the prototype for the numerical integrators in the Boost Odeint
     * library.
     *
     * @sa boost::odeint::integrator
     * @param[in]  state             Current state of the dynamical system (1-D vector)
     * @param[out] stateDerivative   Computed state derivative of the dynamical system (1-D vector)
     * @param[in]  time              Current simulation epoch
     */
    void operator( )( const Vector6& state,
                      Vector6& stateDerivative,
                      const double time )
    {
        const Position currentPosition = { { state[0], state[1], state[2] } };

        // Set the derivative fo the position elements to the current velocity elements.
        stateDerivative[ 0 ] = state[ 3 ];
        stateDerivative[ 1 ] = state[ 4 ];
        stateDerivative[ 2 ] = state[ 5 ];

        // Compute the total acceleration acting on the system as a sum of the forces.
        // Central body gravity is included by default.
        Vector3 acceleration
            = astro::computeRotationalBodyAcceleration( principleInertia, currentPosition );

        // // Add J2 acceleration if model is set to active.
        // if ( isJ2AccelerationModelActive )
        // {
        //     acceleration = sml::add( acceleration,
        //                              astro::computeJ2Acceleration( gravitationalParameter,
        //                                                            currentPosition,
        //                                                            equatorialRadius,
        //                                                            j2Coefficient ) );
        // }

        // // Add solar radiation pressure acceleration if model is set to active.
        // if ( isRadiationPressureAccelerationModelActive )
        // {
        // //     acceleration = sml::add( acceleration,
        // //                              astro::computeJ2Acceleration( gravitationalParameter,
        // //                                                            currentPosition,
        // //                                                            equatorialRadius,
        // //                                                            j2Coefficient ) );
        // }

        // Set the derivative of the velocity elements to the computed total acceleration.
        stateDerivative[ 3 ] = acceleration[ 0 ];
        stateDerivative[ 4 ] = acceleration[ 1 ];
        stateDerivative[ 5 ] = acceleration[ 2 ];
    }

protected:
private:

    //! Gravitational parameter of central body [km^3 s^-2].
    const Real principleInertia;

    // //! Boolean flag indicating if J2 acceleration model is active (true) or not (false).
    // const bool isJ2AccelerationModelActive;

    // //! J2-coefficient (unnormalized) of spherical harmonics expansion of gravity field [-].
    // const Real j2Coefficient;

    // //! Equatorial radius of central body corresponding with spherical harmonics gravity field [km].
    // const Real equatorialRadius;

    // //! Boolean flag indicating if radiation pressure acceleration model is active (true) or not
    // //! (false).
    // const bool isRadiationPressureAccelerationModelActive;

    // //! Radius of dust particle [micron].
    // const Real particleRadius;

    // //! Bulk density of dust particle [kg m^-3].
    // const Real particleBulkDensity;

    // //! Radiation pressure coefficient [-].
    // const Real radiationPressureCoefficient;
};

} // namespace dss_adcs

#endif // dss_adcs_DYNAMICAL_SYSTEM_HPP