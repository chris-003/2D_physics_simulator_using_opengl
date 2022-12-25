#pragma once
#include <boost/property_tree/ptree.hpp>

namespace SResourceData {
typedef boost::property_tree::basic_ptree<std::string,
                                          std::pair<const char *, int>>
                  resource_t;
extern resource_t resource_pt;

resource_t get_resource(const std::string &id);

std::pair<const char *, int> get(const resource_t  &resource,
                                 const std::string &path);

// std::pair<const char *, int>
// get(const boost::property_tree::basic_ptree<
//         std::string, std::pair<const char *, int>> &resource,
//     const boost::property_tree::path               &path);
} // namespace SResourceData