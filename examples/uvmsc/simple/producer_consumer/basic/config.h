//----------------------------------------------------------------------
//   Copyright 2009 Cadence Design Systems, Inc.
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

#ifndef CONFIG_H_
#define CONFIG_H_

class do_config
{
 public:
  do_config()
  {
    uvm::uvm_config_db<int>::set(NULL, "topenv.p1","num_packets", 2);
    uvm::uvm_config_db<int>::set(NULL, "topenv.p2","num_packets", 4);
  }
};

#endif /* CONFIG_H_ */
