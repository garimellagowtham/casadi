/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef STABILIZED_QP_HPP
#define STABILIZED_QP_HPP

#include "function.hpp"
#include "qp_solver.hpp"

//#include "../autogenerated.hpp"


/** \defgroup StabilizedQPSolver_doc

  Solves the following strictly convex problem:
  
  \verbatim
  min          1/2 x' H x + g' x 
   x
  
  subject to
              LBA <= A x <= UBA
              LBX <= x   <= UBX
              
      with :
        H sparse (n x n) positive definite
        g dense  (n x 1)
              
      n: number of decision variables (x)
      nc: number of constraints (A)
      
  \endverbatim
  
  If H is not positive-definite, the solver should throw an error.
  
*/
      
namespace casadi{
  
/// Input arguments of a QP problem [stabilizedQpIn]
enum StabilizedQPSolverInput{
  /// The square matrix H: sparse, (n x n). Only the lower triangular part is actually used. The matrix is assumed to be symmetrical. [h]
  STABILIZED_QP_SOLVER_H,
  /// The vector g: dense,  (n x 1) [g]
  STABILIZED_QP_SOLVER_G,
  /// The matrix A: sparse, (nc x n) - product with x must be dense. [a]
  STABILIZED_QP_SOLVER_A,
  /// dense, (nc x 1) [lba]
  STABILIZED_QP_SOLVER_LBA,
  /// dense, (nc x 1) [uba]
  STABILIZED_QP_SOLVER_UBA,
  /// dense, (n x 1) [lbx]
  STABILIZED_QP_SOLVER_LBX,
  /// dense, (n x 1) [ubx]
  STABILIZED_QP_SOLVER_UBX,
  /// dense, (n x 1) [x0]
  STABILIZED_QP_SOLVER_X0,
  /// dense [lam_x0]
  STABILIZED_QP_SOLVER_LAM_X0,
  /// dense (1 x 1) [muR]
  STABILIZED_QP_SOLVER_MUR,
  /// dense (nc x 1) [muE]
  STABILIZED_QP_SOLVER_MUE,
  /// dense (nc x 1) [mu]
  STABILIZED_QP_SOLVER_MU,
  STABILIZED_QP_SOLVER_NUM_IN};

// Forward declaration of internal class
class StabilizedQPSolverInternal;

/** \brief StabilizedQPSolver


@copydoc StabilizedQPSolver_doc

  \author Joel Andersson 
  \date 2010
*/
class CASADI_EXPORT StabilizedQPSolver : public Function{
  public:

  /// Default constructor
  StabilizedQPSolver();
  
  /// Access functions of the node
  StabilizedQPSolverInternal* operator->();
  const StabilizedQPSolverInternal* operator->() const;

  /// Check if the node is pointing to the right type of object
  virtual bool checkNode() const;
  
  /// Set options that make the QP solver more suitable for solving LPs
  void setLPOptions();
  
  /** Generate native code in the interfaced language for debugging */
  virtual void generateNativeCode(const std::string &filename) const;
};

} // namespace casadi

#endif // STABILIZED_QP_HPP

