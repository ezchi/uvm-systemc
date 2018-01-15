//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

// TODO file used for MSVC. Find a way to pass version and revision info dynamically

#include "uvmsc/base/uvm_version.h"

namespace uvm {

const std::string uvm_nxp_copyright  = "(C) 2012-2015 NXP B.V.";
const std::string uvm_fhg_copyright  = "(C) 2012-2014 Fraunhofer IIS/EAS";
const std::string uvm_upmc_copyright = "(C) 2012-2014 University Pierre et Marie Curie";
const std::string uvm_mgc_copyright  = "(C) 2007-2013 Mentor Graphics Corporation";
const std::string uvm_cdn_copyright  = "(C) 2007-2013 Cadence Design Systems, Inc.";
const std::string uvm_snps_copyright = "(C) 2006-2013 Synopsys, Inc.";
const std::string uvm_cy_copyright   = "(C) 2011-2013 Cypress Semiconductor Corp.";
const std::string uvm_revision = UVM_VERSION_STRING;

std::string uvm_revision_string()
{
  return uvm_revision;
}

} // namespace uvm
