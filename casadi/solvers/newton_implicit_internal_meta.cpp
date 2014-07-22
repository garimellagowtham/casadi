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


      #include "newton_implicit_internal.hpp"
      #include <string>

      const std::string casadi::NewtonImplicitInternal::meta_doc=
      "\n"
"\n"
">List of available options\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"|       Id        |      Type       |     Default     |   Description   |\n"
"+=================+=================+=================+=================+\n"
"| abstol          | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion       |\n"
"|                 |                 |                 | tolerance on    |\n"
"|                 |                 |                 | max(|F|)        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| abstolStep      | OT_REAL         | 0.000           | Stopping        |\n"
"|                 |                 |                 | criterion       |\n"
"|                 |                 |                 | tolerance on    |\n"
"|                 |                 |                 | step size       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| ad_mode         | OT_STRING       | \"automatic\"     | How to          |\n"
"|                 |                 |                 | calculate the   |\n"
"|                 |                 |                 | Jacobians.      |\n"
"|                 |                 |                 | (forward: only  |\n"
"|                 |                 |                 | forward         |\n"
"|                 |                 |                 | mode|reverse:   |\n"
"|                 |                 |                 | only adjoint    |\n"
"|                 |                 |                 | mode|automatic: |\n"
"|                 |                 |                 | a heuristic     |\n"
"|                 |                 |                 | decides which   |\n"
"|                 |                 |                 | is more         |\n"
"|                 |                 |                 | appropriate)    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| constraints     | OT_INTEGERVECTO | GenericType()   | Constrain the   |\n"
"|                 | R               |                 | unknowns. 0     |\n"
"|                 |                 |                 | (default): no   |\n"
"|                 |                 |                 | constraint on   |\n"
"|                 |                 |                 | ui, 1: ui >=    |\n"
"|                 |                 |                 | 0.0, -1: ui <=  |\n"
"|                 |                 |                 | 0.0, 2: ui >    |\n"
"|                 |                 |                 | 0.0, -2: ui <   |\n"
"|                 |                 |                 | 0.0.            |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| derivative_gene | OT_DERIVATIVEGE | GenericType()   | Function that   |\n"
"| rator           | NERATOR         |                 | returns a       |\n"
"|                 |                 |                 | derivative      |\n"
"|                 |                 |                 | function given  |\n"
"|                 |                 |                 | a number of     |\n"
"|                 |                 |                 | forward and     |\n"
"|                 |                 |                 | reverse         |\n"
"|                 |                 |                 | directional     |\n"
"|                 |                 |                 | derivative,     |\n"
"|                 |                 |                 | overrides       |\n"
"|                 |                 |                 | internal        |\n"
"|                 |                 |                 | routines. Check |\n"
"|                 |                 |                 | documentation   |\n"
"|                 |                 |                 | of DerivativeGe |\n"
"|                 |                 |                 | nerator.        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| gather_stats    | OT_BOOLEAN      | false           | Flag to         |\n"
"|                 |                 |                 | indicate        |\n"
"|                 |                 |                 | whether         |\n"
"|                 |                 |                 | statistics must |\n"
"|                 |                 |                 | be gathered     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| implicit_input  | OT_INTEGER      | 0               | Index of the    |\n"
"|                 |                 |                 | input that      |\n"
"|                 |                 |                 | corresponds to  |\n"
"|                 |                 |                 | the actual      |\n"
"|                 |                 |                 | root-finding    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| implicit_output | OT_INTEGER      | 0               | Index of the    |\n"
"|                 |                 |                 | output that     |\n"
"|                 |                 |                 | corresponds to  |\n"
"|                 |                 |                 | the actual      |\n"
"|                 |                 |                 | root-finding    |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| inputs_check    | OT_BOOLEAN      | true            | Throw           |\n"
"|                 |                 |                 | exceptions when |\n"
"|                 |                 |                 | the numerical   |\n"
"|                 |                 |                 | values of the   |\n"
"|                 |                 |                 | inputs don't    |\n"
"|                 |                 |                 | make sense      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver   | OT_STRING       | GenericType()   | User-defined    |\n"
"|                 |                 |                 | linear solver   |\n"
"|                 |                 |                 | class. Needed   |\n"
"|                 |                 |                 | for             |\n"
"|                 |                 |                 | sensitivities.  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| linear_solver_o | OT_DICTIONARY   | GenericType()   | Options to be   |\n"
"| ptions          |                 |                 | passed to the   |\n"
"|                 |                 |                 | linear solver.  |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| max_iter        | OT_INTEGER      | 1000            | Maximum number  |\n"
"|                 |                 |                 | of Newton       |\n"
"|                 |                 |                 | iterations to   |\n"
"|                 |                 |                 | perform before  |\n"
"|                 |                 |                 | returning.      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| monitor         | OT_STRINGVECTOR | GenericType()   | Monitors to be  |\n"
"|                 |                 |                 | activated (inpu |\n"
"|                 |                 |                 | ts|outputs)  (s |\n"
"|                 |                 |                 | tep|stepsize|J| |\n"
"|                 |                 |                 | F|normF)        |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| name            | OT_STRING       | \"unnamed_shared | name of the     |\n"
"|                 |                 | _object\"        | object          |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| regularity_chec | OT_BOOLEAN      | true            | Throw           |\n"
"| k               |                 |                 | exceptions when |\n"
"|                 |                 |                 | NaN or Inf      |\n"
"|                 |                 |                 | appears during  |\n"
"|                 |                 |                 | evaluation      |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| user_data       | OT_VOIDPTR      | GenericType()   | A user-defined  |\n"
"|                 |                 |                 | field that can  |\n"
"|                 |                 |                 | be used to      |\n"
"|                 |                 |                 | identify the    |\n"
"|                 |                 |                 | function or     |\n"
"|                 |                 |                 | pass additional |\n"
"|                 |                 |                 | information     |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"| verbose         | OT_BOOLEAN      | false           | Verbose         |\n"
"|                 |                 |                 | evaluation  for |\n"
"|                 |                 |                 | debugging       |\n"
"+-----------------+-----------------+-----------------+-----------------+\n"
"\n"
"\n"
">List of available monitors\n"
"+----------+\n"
"|    Id    |\n"
"+==========+\n"
"| F        |\n"
"+----------+\n"
"| J        |\n"
"+----------+\n"
"| inputs   |\n"
"+----------+\n"
"| normF    |\n"
"+----------+\n"
"| outputs  |\n"
"+----------+\n"
"| step     |\n"
"+----------+\n"
"| stepsize |\n"
"+----------+\n"
"\n"
"\n"
">List of available stats\n"
"+---------------+\n"
"|      Id       |\n"
"+===============+\n"
"| iter          |\n"
"+---------------+\n"
"| return_status |\n"
"+---------------+\n"
"\n"
"\n"
"\n"
"\n"
;
