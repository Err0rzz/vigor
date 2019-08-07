open Data_spec

let containers = ["dyn_map", Map ("ip_addr", "capacity", "");
                  "dyn_keys", Vector ("ip_addr", "capacity", "");
                  "dyn_heap", DChain "capacity";
                  "dyn_vals", Vector ("DynamicValue", "capacity", "dyn_val_condition");
                  "capacity", UInt32;
                  "dev_count", UInt32;
                  "flow_emap", EMap ("ip_addr", "dyn_map", "dyn_keys", "dyn_heap");
                 ]

let custom_includes = ["dynamic_value.h.gen.h";
                       "ip_addr.h.gen.h"]
