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

#ifndef KINSOL_INTERNAL_HPP
#define KINSOL_INTERNAL_HPP

#include "kinsol_solver.hpp"
#include "casadi/fx/implicit_function_internal.hpp"
#include <nvector/nvector_serial.h>   /* serial N_Vector types, fcts., and macros */
#include <sundials/sundials_dense.h>  /* definitions DlsMat DENSE_ELEM */
#include <sundials/sundials_types.h>  /* definition of type double */
#include <kinsol/kinsol.h>            /* prototypes for CVode fcts. and consts. */
#include <kinsol/kinsol_dense.h>
#include <kinsol/kinsol_band.h> 
#include <kinsol/kinsol_spgmr.h>
#include <kinsol/kinsol_spbcgs.h>
#include <kinsol/kinsol_sptfqmr.h>
#include <kinsol/kinsol_impl.h> /* Needed for the provided linear solver */
#include <ctime>

namespace CasADi{
namespace Sundials{
  
class KinsolInternal : public ImplicitFunctionInternal{
  friend class KinsolSolver;
public:
  /** \brief  Constructor */
  explicit KinsolInternal(const FX& f, int nrhs);

  /** \brief  Clone */
  virtual KinsolInternal* clone() const;

  /** \brief  Destructor */
  virtual ~KinsolInternal();

  /** \brief  Initialize stage */
  virtual void init();
  
  /** \brief  Evaluate */
  virtual void evaluate(int fsens_order, int asens_order);

  /** \brief Generate a linear solver for the sensitivity equations */
  KinsolSolver jac(int iind=0, int oind=0);

  /** \brief Generate a linear solver for the sensitivity equations */
  KinsolSolver jac(const std::vector<int> iind, int oind=0);

  /** \brief  Set Jacobian */
  virtual void setJacobian(const FX& jac);
  
  /** \brief  Get Jacobian */
  virtual FX getJacobian();
 
  /** \brief  Set linear solver */
  virtual void setLinearSolver(const LinearSolver& linsol);
  
  /** \brief  Get linear solver */
  virtual LinearSolver getLinearSolver();
  
  /** \brief Residual */
  void func(N_Vector u, N_Vector fval);
  void djac(int N, N_Vector u, N_Vector fu, DlsMat J, N_Vector tmp1, N_Vector tmp2);
  void bjac(int N, int mupper, int mlower, N_Vector u, N_Vector fu, DlsMat J, N_Vector tmp1, N_Vector tmp2);
  void jtimes(N_Vector v, N_Vector Jv, N_Vector u, int* new_u);
  void psetup(N_Vector u, N_Vector uscale, N_Vector fval, N_Vector fscale, N_Vector tmp1, N_Vector tmp2);
  void psolve(N_Vector u, N_Vector uscale, N_Vector fval, N_Vector fscale, N_Vector v, N_Vector tmp);
  void lsetup(KINMem kin_mem);
  void lsolve(KINMem kin_mem, N_Vector x, N_Vector b, double *res_norm);
  
  /** \brief Wrappers */
  static int func_wrapper(N_Vector u, N_Vector fval, void *user_data);
  static int djac_wrapper(int N, N_Vector u, N_Vector fu, DlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2);
  static int bjac_wrapper(int N, int mupper, int mlower, N_Vector u, N_Vector fu, DlsMat J, void *user_data, N_Vector tmp1, N_Vector tmp2);
  static int jtimes_wrapper(N_Vector v, N_Vector Jv, N_Vector u, int* new_u, void *user_data);
  static int psetup_wrapper(N_Vector u, N_Vector uscale, N_Vector fval, N_Vector fscale, void* user_data, N_Vector tmp1, N_Vector tmp2);
  static int psolve_wrapper(N_Vector u, N_Vector uscale, N_Vector fval, N_Vector fscale, N_Vector v, void* user_data, N_Vector tmp);
  static int lsetup_wrapper(KINMem kin_mem);
  static int lsolve_wrapper(KINMem kin_mem, N_Vector x, N_Vector b, double *res_norm);
  
  /// KINSOL memory block
  void* mem_;
  
  /// Jacobian
  FX J_;
  
  /// Variable
  N_Vector u_;
  
  // Scaling
  N_Vector u_scale_, f_scale_;
  
  /// For timings
  clock_t time1_, time2_;
  
  /// Accummulated time since last reset:
  double t_func_; // time spent in the residual function
  double t_jac_; // time spent in the jacobian function
  double t_lsolve_; // preconditioner/linear solver solve function
  double t_lsetup_jac_; // preconditioner/linear solver setup function, generate jacobian
  double t_lsetup_fac_; // preconditioner setup function, factorize jacobian

  /// Globalization strategy
  int strategy_;

  /// Nonlinear solver for the augmented system
  KinsolSolver aug_;
  
  // Linear solver
  LinearSolver linsol_;  

};


} // namespace Sundials
} // namespace CasADi

#endif //KINSOL_INTERNAL_HPP

