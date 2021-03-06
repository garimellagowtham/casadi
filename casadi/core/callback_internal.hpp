/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
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

#ifndef CASADI_CALLBACK_INTERNAL_HPP
#define CASADI_CALLBACK_INTERNAL_HPP

#include "callback.hpp"
#include "function_internal.hpp"

namespace casadi {

  class CASADI_EXPORT CallbackInternal : public FunctionInternal {
    friend class CallbackFunction;
  public:

    /** \brief Constructor */
    explicit CallbackInternal(const std::string& name, Callback* self);

    /** \brief Destructor */
    ~CallbackInternal() override;

    /** \brief Get type name */
    std::string type_name() const override {return "callback";}

    ///@{
    /** \brief Number of function inputs and outputs */
    size_t get_n_in() override;
    size_t get_n_out() override;
    ///@}

    /// @{
    /** \brief Sparsities of function inputs and outputs */
    Sparsity get_sparsity_in(int i) override;
    Sparsity get_sparsity_out(int i) override;
    /// @}

    ///@{
    /** \brief Names of function input and outputs */
    std::string get_name_in(int i) override;
    std::string get_name_out(int i) override;
    /// @}

    /** \brief  Initialize */
    void init(const Dict& opts) override;

    /** \brief Finalize the object creation */
    void finalize(const Dict& opts) override;

    /** \brief  Evaluate numerically, work vectors given */
    void eval(void* mem, const double** arg, double** res, int* iw, double* w) const override;

    /** \brief  Evaluate symbolically, work vectors given */
    void eval_sx(const SXElem** arg, SXElem** res, int* iw, SXElem* w, int mem) const override;

    ///@{
    /** \brief Return Jacobian of all input elements with respect to all output elements */
    bool hasFullJacobian() const override;
    Function getFullJacobian(const std::string& name,
                                     const std::vector<std::string>& i_names,
                                     const std::vector<std::string>& o_names,
                                     const Dict& opts) override;
    ///@}

    ///@{
    /** \brief Return function that calculates forward derivatives */
    Function get_forward(const std::string& name, int nfwd,
                                 const std::vector<std::string>& i_names,
                                 const std::vector<std::string>& o_names,
                                 const Dict& opts) const override;
    int get_n_forward() const override;
    ///@}

    ///@{
    /** \brief Return function that calculates adjoint derivatives */
    Function get_reverse(const std::string& name, int nadj,
                                 const std::vector<std::string>& i_names,
                                 const std::vector<std::string>& o_names,
                                 const Dict& opts) const override;
    int get_n_reverse() const override;
    ///@}

    /** \brief Pointer to the public class */
    Callback* self_;

    /** \brief Is the public class owned by the internal class? */
    bool own_;
  };

} // namespace casadi

#endif // CASADI_CALLBACK_INTERNAL_HPP
