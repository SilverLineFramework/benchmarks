#pragma once

namespace llvm {

  class UnionFind {
    private:
      std::map<Value*, Value*> parent_map;

    public:
      void initialize (std::set<Value*> value_vec) {
        for (auto& val : value_vec) {
          parent_map[val] = val;
        }
      }

      // Return the parent value of Value* V
      Value* find (Value* V) {
        return parent_map[V];
      }

      bool isSynonymous (Value* V1, Value* V2) {
        return find(V1) == find(V2);
      }

      // Get all aliases of a value
      std::vector<Value*> getAliasSet (Value* V) {
        std::vector<Value*> aliases;
        for (auto& it : parent_map) {
          if (it.second == find(V)) {
            aliases.push_back(V);
          }
        }
        return aliases;
      }
      
      // Union of V1's set and V2's set: Add all elements in V2's set to V1
      void unionOperation (Value* V1, Value* V2) {
        Value* target_parent = parent_map[V1];
        Value* change_parent = parent_map[V2];

        for (auto& it : parent_map) {
          if (it.second == change_parent) {
            it.second = target_parent;
          }
        }
      }

  };
}
